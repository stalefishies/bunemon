#include "memory.hpp"
#include <tlhelp32.h>

#include "items.hpp"
#include "rando.hpp"

static HANDLE process;
static char *bytes_offset;
static char *words_offset;
static char *flags_offset;
static char *xyzrs_offset;

void scanFree(void) {
    if (process && process != INVALID_HANDLE_VALUE) { CloseHandle(process); }
    bytes_offset = words_offset = flags_offset = xyzrs_offset = NULL;
}

bool scanInit(void) {
    scanFree();

    HWND hwnd = FindWindowW(L"La-Mulana", NULL);
    if (!hwnd) { return false; }

    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid == 0) { return false; }

    HANDLE snapshot = CreateToolhelp32Snapshot(
        TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (!snapshot || snapshot == INVALID_HANDLE_VALUE) { return false; }

    char *base_offset = NULL;
    MODULEENTRY32 module_entry;
    module_entry.dwSize = sizeof(module_entry);
    if (Module32First(snapshot, &module_entry)) {
        do {
            if (wcscmp(module_entry.szModule, L"lamulana.exe")) {
                base_offset = (char *)module_entry.modBaseAddr;
                break;
            }
        } while (Module32Next(snapshot, &module_entry));
    }
    CloseHandle(snapshot);
    if (!base_offset) { return false; }

    process = OpenProcess(PROCESS_VM_READ, FALSE, pid);
    if (!process || process == INVALID_HANDLE_VALUE) { return false; }

    BOOL success     = true;
    SIZE_T read_size = 0;
    uint32_t offset  = 0;

    success = ReadProcessMemory(process, base_offset + 0x2E1820,
        &offset, sizeof offset, &read_size);
    if (!success || read_size != sizeof offset || !offset) {
        scanFree();
        return false;
    }

    // TODO: different offsets for different exe versions
    bytes_offset = base_offset + 0x2E1E48;
    words_offset = (char *)(uintptr_t)offset;
    flags_offset = base_offset + 0x2E1B90;
    xyzrs_offset = base_offset + 0x9C0EA0;

    return true;
}

bool scan(LMMemory *memory) {
    memory->prev_x      = memory->x;
    memory->prev_y      = memory->y;
    memory->prev_zone   = memory->zone;
    memory->prev_room   = memory->room;
    memory->prev_screen = memory->screen;
    memory->valid       = true;

    if (!memory || !process || !bytes_offset || !words_offset
        || !flags_offset || !xyzrs_offset)
    { return false; }

    bool success = true;
    SIZE_T read_size = 0;

    if (success) {
        success = ReadProcessMemory(process, bytes_offset,
            memory->bytes, LM_MEMORY_SIZE_BYTES, &read_size);
        if (read_size != LM_MEMORY_SIZE_BYTES) { success = false; }
    }

    if (success) {
        success = ReadProcessMemory(process, words_offset,
            memory->words, LM_MEMORY_SIZE_WORDS, &read_size);
        if (read_size != LM_MEMORY_SIZE_WORDS) { success = false; }
    }

    if (success) {
        success = ReadProcessMemory(process, flags_offset,
            memory->flags, LM_MEMORY_SIZE_FLAGS, &read_size);
        if (read_size != LM_MEMORY_SIZE_FLAGS) { success = false; }
    }

    if (success) {
        success = ReadProcessMemory(process, xyzrs_offset,
            memory->xyzrs, LM_MEMORY_SIZE_XYZRS, &read_size);
        if (read_size != LM_MEMORY_SIZE_XYZRS) { success = false; }
    }

    if (success) { return true; }

    scanFree();
    std::memset(memory, 0x00, sizeof *memory);
    memory->zone = 0xFF;
    return false;
}

DWORD WINAPI scanThread(void *) {
    HANDLE heap = GetProcessHeap();
    LMMemory *memory = (LMMemory *)HeapAlloc(heap,
        HEAP_ZERO_MEMORY, sizeof *memory);
    memory->zone = 0xFF;

    enum { SLEEP_MS = 200 };
    for (;; Sleep(SLEEP_MS)) {
        if (!process) { scanInit(); }
        scan(memory);

        updateItems(memory);
        updateRando(memory);
    }
}
