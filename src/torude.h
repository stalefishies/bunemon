/* TORUDE.H
 *
 * Single-header library for scanning the memory of the La-Mulana process
 *
 * To use this library, in exactly one translation unit, write
 *      #define TORUDE_IMPLEMENTATION
 * before #include-ing this header to generate the definitions. All other
 * translation units should only #include this header.
 *
 * For documentation on the words and bytes fields, see:
 *  https://github.com/worsety/LiveSplit.LaMulanaRemake/blob/master/ConsoleEye/names.xml
 *
 * Example usage:
 *  LMProcess *process = lmOpen();
 *  assert(process && "Could not open La-Mulana process");
 *
 *  LMMemory *memory = malloc(sizeof *memory);
 *  assert(memory && "Could not allocate La-Mulana memory");
 *  
 *  while (lmRead(process, memory)) {
 *      char coords[4] = "???";
 *      lmPrintCoords(memory, coords);
 *
 *      printf("Current location: %23s %.3s   (%5.1f, %5.1f)\n",
 *          lm_zone_name[memory->zone], coords, memory->x, memory->y);
 *      
 *      Sleep(1000);
 *  }
 *
 *  lmClose(process);
 *  free(memory);
 */

#ifndef TORUDE_HGUARD
#define TORUDE_HGUARD

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

// Constants
enum {
    LM_ZONE_COUNT = 26,
    LM_ROOM_COUNT = 23,

    LM_MEMORY_SIZE_BYTES = 4096,
    LM_MEMORY_SIZE_WORDS = 512,
    LM_MEMORY_SIZE_FLAGS = 20,
    LM_MEMORY_SIZE_XYZRS = 184,

    LM_MEMORY_SIZE = LM_MEMORY_SIZE_BYTES + LM_MEMORY_SIZE_WORDS
        + LM_MEMORY_SIZE_FLAGS + LM_MEMORY_SIZE_XYZRS

    //LM_MEMORY_SIZE   = 5856,
    //LM_MEMORY_SIZE_1 = 5672,
    //LM_MEMORY_SIZE_2 = 184,
};

// Struct to store scan of process memory
typedef struct LMMemory {
    uint8_t  bytes[LM_MEMORY_SIZE_BYTES];
    uint16_t words[LM_MEMORY_SIZE_WORDS / 2];
    uint8_t  flags[LM_MEMORY_SIZE_FLAGS];
    uint8_t  xyzrs[LM_MEMORY_SIZE_XYZRS];

    //union {
    //    struct {
    //        float    x;
    //        uint8_t _unused_3[26];
    //        uint8_t  room;
    //        uint8_t  screen;
    //        uint8_t _unused_4[38];
    //        uint8_t  zone;
    //        uint8_t _unused_5[109];
    //        float    y;
    //    };
    //};
} LMMemory;

typedef struct LMData {
    uint8_t whip;               // 1: normal, 2: chain, 3: flail
    uint8_t knife;
    uint8_t key_sword;          // 1: normal, 2: activated
    uint8_t axe;
    uint8_t katana;

    uint8_t shuriken;
    uint8_t rolling_shuriken;
    uint8_t earth_spears;
    uint8_t flares;
    uint8_t bombs;
    uint8_t chakram;
    uint8_t caltrops;
    uint8_t gun;
    uint8_t shield;             // 1: buckler, 2: fake, 3: silver, 4: angel

    uint8_t hand_scanner;
    uint8_t djed_pillar;
    uint8_t mini_doll;
    uint8_t magatama_jewel;
    uint8_t cog_of_the_soul;
    uint8_t lamp_of_time;       // 1: unlit, 2: lit
    uint8_t pochette_key;
    uint8_t dragon_bone;
    uint8_t crystal_skull;
    uint8_t vessel;             // 1: empty, 2: yellow, 3: green, 4: red
    uint8_t pepper;
    uint8_t woman_statue;       // 1: woman, 2: maternity
    uint8_t key_of_eternity;
    uint8_t serpent_staff;
    uint8_t talisman;
    uint8_t diary;
    uint8_t mulana_talisman;

    uint8_t msx_2;
    uint8_t waterproof_case;
    uint8_t heatproof_case;
    uint8_t shell_horn;
    uint8_t glove;
    uint8_t holy_grail;         // 1: normal, 2: golden, 3: broken
    uint8_t isis_pendant;
    uint8_t crucifix;
    uint8_t helmet;
    uint8_t grapple_claw;
    uint8_t bronze_mirror;
    uint8_t eye_of_truth;
    uint8_t ring;
    uint8_t scalesphere;
    uint8_t gauntlet;
    uint8_t treasures;
    uint8_t anchor;
    uint8_t plane_model;
    uint8_t ocarina;
    uint8_t feather;
    uint8_t book_of_the_dead;
    uint8_t fairy_clothes;
    uint8_t scriptures;
    uint8_t hermes_boots;
    uint8_t fruit_of_eden;
    uint8_t twin_statue;
    uint8_t bracelet;
    uint8_t perfume;
    uint8_t spaulder;
    uint8_t dimensional_key;
    uint8_t ice_cape;

    uint8_t origin_seal;
    uint8_t birth_seal;
    uint8_t life_seal;
    uint8_t death_seal;

    uint8_t reader;
    uint8_t xmailer;
    uint8_t yagomap;
    uint8_t yagostr;
    uint8_t bunemon;
    uint8_t bunplus;
    uint8_t torude;
    uint8_t guild;
    uint8_t mantra;
    uint8_t emusic;
    uint8_t beolamu;
    uint8_t deathv;
    uint8_t randc;
    uint8_t capstar;
    uint8_t move;
    uint8_t mekuri;
    uint8_t bounce;
    uint8_t miracle;
    uint8_t mirai;
    uint8_t lamulana;

    uint8_t secret_of_life;
    uint8_t bathing_suit;
    uint8_t hard_mode;

    uint8_t coins;
    uint8_t weights;
    uint8_t dialogue_score;

    union {
        struct {
            uint8_t shuriken;
            uint8_t rolling_shuriken;
            uint8_t earth_spears;
            uint8_t flares;
            uint8_t bombs;
            uint8_t chakram;
            uint8_t caltrops;
            uint8_t bullets;
            uint8_t clips;
            uint8_t ankh_jewels;
        };
        uint8_t array[10];
    } ammo;

    union {
        struct {
            uint8_t gate_of_guidance;
            uint8_t mausoleum_of_the_giants;
            uint8_t temple_of_the_sun;
            uint8_t spring_in_the_sky;
            uint8_t inferno_cavern;
            uint8_t chamber_of_extinction;
            uint8_t twin_labyrinths_front;
            uint8_t endless_corridor;
            uint8_t shrine_of_the_mother_front;
            uint8_t gate_of_illusion;
            uint8_t graveyard_of_the_giants;
            uint8_t temple_of_moonlight;
            uint8_t tower_of_the_goddess;
            uint8_t tower_of_ruin;
            uint8_t chamber_of_birth;
            uint8_t twin_labyrinths_back;
            uint8_t dimensional_corridor;
            uint8_t shrine_of_the_mother_back;
            uint8_t total;
        };
        uint8_t array[19];
    } grails;

    union {
        struct {
            uint8_t surface;
            uint8_t gate_of_guidance;
            uint8_t mausoleum_of_the_giants;
            uint8_t temple_of_the_sun;
            uint8_t spring_in_the_sky;
            uint8_t inferno_cavern;
            uint8_t chamber_of_extinction;
            uint8_t twin_labyrinths;
            uint8_t endless_corridor;
            uint8_t gate_of_illusion;
            uint8_t graveyard_of_the_giants;
            uint8_t temple_of_moonlight;
            uint8_t tower_of_the_goddess;
            uint8_t tower_of_ruin;
            uint8_t chamber_of_birth;
            uint8_t dimensional_corridor;
            uint8_t shrine_of_the_mother;
            uint8_t total;
        };
        uint8_t array[18];
    } maps;

    union {
        struct {
            uint8_t surface;
            uint8_t gate_of_guidance;
            uint8_t mausoleum_of_the_giants;
            uint8_t temple_of_the_sun;
            uint8_t spring_in_the_sky;
            uint8_t chamber_of_extinction;
            uint8_t twin_labyrinths;
            uint8_t tower_of_ruin;
            uint8_t dimensional_corridor;
            uint8_t shrine_of_the_mother;
            uint8_t total;
        };
        uint8_t array[11];
    } orbs;

    union {
        struct {
            uint8_t gate_of_guidance;
            uint8_t mausoleum_of_the_giants;
            uint8_t temple_of_the_sun;
            uint8_t spring_in_the_sky;
            uint8_t twin_labyrinths;
            uint8_t tower_of_ruin;
            uint8_t chamber_of_birth;
            uint8_t dimensional_corridor;
            uint8_t total;
        };
        uint8_t array[9];
    } ankh_jewels;

    // 1: ankh will appear, 2: ankh appeared, 3: defeated
    union {
        struct {
            uint8_t amphisbaena;
            uint8_t sakit;
            uint8_t ellmac;
            uint8_t bahamut;
            uint8_t viy;
            uint8_t palenque;
            uint8_t baphomet;
            uint8_t tiamat;
            uint8_t mother;
            uint8_t total;
        };
        uint8_t array[10];
    } guardians;

    // 1: will appear, 2: tablet appeared, 3: learned, 4: recited
    union {
        struct {
            uint8_t amphisbaena;
            uint8_t sakit;
            uint8_t ellmac;
            uint8_t bahamut;
            uint8_t viy;
            uint8_t palenque;
            uint8_t baphomet;
            uint8_t tiamat;
        };
        uint8_t array[8];
    } mantras;

    float x;
    float y;
    uint8_t zone;
    uint8_t room;
    uint8_t screen;
} LMData;

// Used to do the memory scan itself
typedef struct LMProcess LMProcess;
LMProcess *lmOpen();
bool lmScan (LMProcess *process, LMMemory *memory);
void lmParse(LMMemory  *memory,  LMData *data);
bool lmRead (LMProcess *process, LMData *data);
bool lmClose(LMProcess *process);

// Name, name length, width, and height of each field
extern const char   *lm_zone_name  [LM_ZONE_COUNT];
extern const uint8_t lm_zone_len   [LM_ZONE_COUNT];
extern const uint8_t lm_zone_width [LM_ZONE_COUNT];
extern const uint8_t lm_zone_height[LM_ZONE_COUNT];

// Get current screen coordinates (e.g. 'B4') as integers
//  X: 0 -> A, 1 -> B, etc.
//  Y: 0 -> 1, 1 -> 2, etc.
//  for both, -1 indicates an error (e.g. you're at the main menu)
void lmRoomCoords(const LMData *data, int *x, int *y);
int lmRoomCoordX(const LMData *data);
int lmRoomCoordY(const LMData *data);

// Used for locating each room in the field
// Exceptions to array:
//  zone  6   room 5   screen 1  =>  map x is 8 (I)
//  zone  8   room 5   screen 2  =>  map x is 0 (A)
//  zone  8   room 5   screen 3  =>  map x is 1 (B)
//  zone  9   room 9   screen 1  =>  map x is 0 (A)
//  zone 18   room 9   screen 1  =>  map x is 0 (A)
typedef union LMRoomPosition {
    struct { uint8_t x, y, w, h; };
    uint32_t exists;
} LMRoomPosition;
extern const LMRoomPosition lm_room_position[LM_ZONE_COUNT][LM_ROOM_COUNT];

#ifdef __cplusplus
}
#endif

#endif /* TORUDE_HGUARD */


#ifdef  TORUDE_IMPLEMENTATION
#ifndef TORUDE_IMPLEMENTED
#define TORUDE_IMPLEMENTED

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <tlhelp32.h>
#pragma comment(lib, "user32")

#ifdef __cplusplus
extern "C" {
#endif

struct LMProcess {
    HANDLE handle;
    void *bytes_ptr;
    void *words_ptr;
    void *flags_ptr;
    void *xyzrs_ptr;
};

LMProcess *lmOpen() {
    HANDLE        heap = GetProcessHeap();
    DWORD   process_id = 0;
    char         *base = NULL;
    HANDLE      handle = NULL;
    HANDLE    snapshot = NULL;
    LMProcess *process = NULL;

    HWND window = FindWindowW(L"La-Mulana", NULL);
    if (!window) { goto error; }

    GetWindowThreadProcessId(window, &process_id);
    if (process_id == 0) { goto error; }

    handle = OpenProcess(PROCESS_VM_READ, FALSE, process_id);
    if (!handle) { goto error; }

    snapshot = CreateToolhelp32Snapshot(
        TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_id);
    if (snapshot == INVALID_HANDLE_VALUE) { goto error; }

    MODULEENTRY32 module_entry;
    module_entry.dwSize = sizeof(module_entry);

    if (Module32First(snapshot, &module_entry)) {
        do {
            if (wcscmp(module_entry.szModule, L"lamulana.exe")) {
                base = (char *)module_entry.modBaseAddr;
                break;
            }
        } while (Module32Next(snapshot, &module_entry));
    }
    if (!base) { goto error; }

    process = (LMProcess *)HeapAlloc(heap, 0, sizeof *process);
    if (!process) { goto error; }

    // TODO: different offsets for different exe versions
    process->handle    = handle;
    process->bytes_ptr = base + 0x2E1E48;
    process->words_ptr = NULL;
    process->flags_ptr = base + 0x2E1B90;
    process->xyzrs_ptr = base + 0x9C0EA0;

    {
        BOOL success       = true;
        SIZE_T read_size   = 0;
        uint32_t words_ptr = 0;

        success = ReadProcessMemory(process->handle, base + 0x2E1820,
            &words_ptr, sizeof words_ptr, &read_size);

        if (success && read_size == sizeof words_ptr && words_ptr) {
            process->words_ptr = (void *)(uintptr_t)words_ptr;
        }
    }

    if (!process->words_ptr) { goto error; }
    return process;

error:
    if (handle && handle != INVALID_HANDLE_VALUE)
        { CloseHandle(handle); }

    if (snapshot && snapshot != INVALID_HANDLE_VALUE)
        { CloseHandle(snapshot); }

    if (process) { HeapFree(heap, 0, process); }

    return NULL;
}

bool lmClose(LMProcess *process) {
    HANDLE heap = GetProcessHeap();
    return (bool)HeapFree(heap, 0, process);
}

bool lmRead(LMProcess *process, LMData *data) {
    HANDLE heap = GetProcessHeap();
    LMMemory *memory = (LMMemory *)HeapAlloc(heap,
        HEAP_ZERO_MEMORY, sizeof *memory);
    if (!memory) { return false; }

    bool success = lmScan(process, memory);
    if (success) { lmParse(memory, data); }

    HeapFree(heap, 0, memory);
    return success;
}

bool lmScan(LMProcess *process, LMMemory *memory) {
    if (!process || !memory) { return false; }

    BOOL success = true;
    SIZE_T read_size = 0;

    success = ReadProcessMemory(process->handle, process->bytes_ptr,
        memory->bytes, LM_MEMORY_SIZE_BYTES, &read_size);
    if (!success || read_size != LM_MEMORY_SIZE_BYTES) { return false; }

    success = ReadProcessMemory(process->handle, process->words_ptr,
        memory->words, LM_MEMORY_SIZE_WORDS, &read_size);
    if (!success || read_size != LM_MEMORY_SIZE_WORDS) { return false; }

    success = ReadProcessMemory(process->handle, process->flags_ptr,
        memory->flags, LM_MEMORY_SIZE_FLAGS, &read_size);
    if (!success || read_size != LM_MEMORY_SIZE_FLAGS) { return false; }

    success = ReadProcessMemory(process->handle, process->xyzrs_ptr,
        memory->xyzrs, LM_MEMORY_SIZE_XYZRS, &read_size);
    if (!success || read_size != LM_MEMORY_SIZE_XYZRS) { return false; }

    return true;
}

void lmParse(LMMemory *memory, LMData *data) {
    memset(data, 0, sizeof *data);

#define SET_ITEM(name, byte, word) \
    (data->name = (memory->bytes[byte] == 2) || (!!memory->words[word]))

    if (memory->bytes[0x07E] == 2 || memory->words[0x02]) {
        data->whip = 3;
    } else if (memory->bytes[0x07D] == 2 || memory->words[0x01]) {
        data->whip = 2;
    } else if (memory->words[0x00] != 0xFFFF && memory->xyzrs[70] != 0xFF) {
        data->whip = 1;
    }
    SET_ITEM(knife,            0x07F, 0x03);
    if (memory->words[0x07]) {
        data->key_sword = 2;
    } else if (memory->bytes[0x080] == 2 || memory->words[0x04]) {
        data->key_sword = 1;
    }
    SET_ITEM(axe,              0x081, 0x05);
    SET_ITEM(katana,           0x082, 0x06);
    SET_ITEM(shuriken,         0x083, 0x08);
    SET_ITEM(rolling_shuriken, 0x084, 0x09);
    SET_ITEM(earth_spears,     0x085, 0x0A);
    SET_ITEM(flares,           0x086, 0x0B);
    SET_ITEM(bombs,            0x087, 0x0C);
    SET_ITEM(chakram,          0x088, 0x0D);
    SET_ITEM(caltrops,         0x089, 0x0E);
    SET_ITEM(gun,              0x08A, 0x0F);
    if (memory->bytes[0x08D] == 2 || memory->words[0x12]) {
        data->shield = 4;
    } else if (memory->bytes[0x08C] == 2 || memory->words[0x11]) {
        data->shield = 3;
    } else if (memory->words[0x4B]) {
        data->shield = 2;
    } else if (memory->words[0x10]) {
        data->shield = 1;
    }
    SET_ITEM(hand_scanner,     0x096, 0x14);
    SET_ITEM(djed_pillar,      0x097, 0x15);
    SET_ITEM(mini_doll,        0x098, 0x16);
    SET_ITEM(magatama_jewel,   0x099, 0x17);
    SET_ITEM(cog_of_the_soul,  0x09A, 0x18);
    if (memory->words[0x19]) {
        data->lamp_of_time = 2;
    } else if (memory->bytes[0x09B] == 2 || memory->words[0x50]) {
        data->lamp_of_time = 1;
    }
    SET_ITEM(pochette_key,     0x09C, 0x1A);
    SET_ITEM(dragon_bone,      0x09D, 0x1B);
    SET_ITEM(crystal_skull,    0x09E, 0x1C);
    SET_ITEM(vessel,           0x09F, 0x1D);
    SET_ITEM(pepper,           0x0A0, 0x1E);
    if (memory->bytes[0x10B] == 2 || memory->words[0x51]) {
        data->woman_statue = 2;
    } else if (memory->bytes[0x0A1] == 2 || memory->words[0x1F]) {
        data->woman_statue = 1;
    }
    SET_ITEM(key_of_eternity,  0x0A2, 0x20);
    SET_ITEM(serpent_staff,    0x0A3, 0x21);
    SET_ITEM(talisman,         0x0A4, 0x22);
    SET_ITEM(diary,            0x104, 0x48);
    SET_ITEM(mulana_talisman,  0x105, 0x49);
    data->msx_2            = !!memory->words[0x4C];
    SET_ITEM(waterproof_case,  0x0A5, 0x24);
    SET_ITEM(heatproof_case,   0x0A6, 0x25);
    SET_ITEM(shell_horn,       0x0A7, 0x26);
    SET_ITEM(glove,            0x0A8, 0x27);
    if (memory->words[0x52]) {
        data->holy_grail = 3;
    } else if (memory->words[0x53]) {
        data->holy_grail = 2;
    } else if (memory->bytes[0x089] == 2 || memory->words[0x28]) {
        data->holy_grail = 1;
    }
    SET_ITEM(isis_pendant,     0x0AA, 0x29);
    SET_ITEM(crucifix,         0x0AB, 0x2A);
    SET_ITEM(helmet,           0x0AC, 0x2B);
    SET_ITEM(grapple_claw,     0x0AD, 0x2C);
    SET_ITEM(bronze_mirror,    0x0AE, 0x2D);
    SET_ITEM(eye_of_truth,     0x0AF, 0x2E);
    SET_ITEM(ring,             0x0B0, 0x2F);
    SET_ITEM(scalesphere,      0x0B1, 0x30);
    SET_ITEM(gauntlet,         0x0B2, 0x31);
    SET_ITEM(treasures,        0x103, 0x47);
    SET_ITEM(anchor,           0x0B3, 0x32);
    SET_ITEM(plane_model,      0x0B4, 0x33);
    SET_ITEM(ocarina,          0x0B5, 0x34);
    SET_ITEM(feather,          0x0B6, 0x35);
    SET_ITEM(book_of_the_dead, 0x0B7, 0x36);
    SET_ITEM(fairy_clothes,    0x0B8, 0x37);
    SET_ITEM(scriptures,       0x0B9, 0x38);
    SET_ITEM(hermes_boots,     0x0BA, 0x39);
    SET_ITEM(fruit_of_eden,    0x0BB, 0x3A);
    SET_ITEM(twin_statue,      0x0BC, 0x3B);
    SET_ITEM(bracelet,         0x0BD, 0x3C);
    SET_ITEM(perfume,          0x0BE, 0x3D);
    SET_ITEM(spaulder,         0x0BF, 0x3E);
    SET_ITEM(dimensional_key,  0x0C0, 0x3F);
    SET_ITEM(ice_cape,         0x0C1, 0x40);
    SET_ITEM(origin_seal,      0x0C2, 0x41);
    SET_ITEM(birth_seal,       0x0C3, 0x42);
    SET_ITEM(life_seal,        0x0C4, 0x43);
    SET_ITEM(death_seal,       0x0C5, 0x44);
    SET_ITEM(reader,           0x0E2, 0x55);
    SET_ITEM(xmailer,          0x0E3, 0x56);
    SET_ITEM(yagomap,          0x0E4, 0x57);
    SET_ITEM(yagostr,          0x0E5, 0x58);
    SET_ITEM(bunemon,          0x0E6, 0x59);
    SET_ITEM(bunplus,          0x0E7, 0x5A);
    SET_ITEM(torude,           0x0E8, 0x5B);
    SET_ITEM(guild,            0x0E9, 0x5C);
    SET_ITEM(mantra,           0x0EA, 0x5D);
    SET_ITEM(emusic,           0x0EB, 0x5E);
    SET_ITEM(beolamu,          0x0EC, 0x5F);
    SET_ITEM(deathv,           0x0ED, 0x60);
    SET_ITEM(randc,            0x0EE, 0x61);
    SET_ITEM(capstar,          0x0EF, 0x62);
    SET_ITEM(move,             0x0F0, 0x63);
    SET_ITEM(mekuri,           0x0F1, 0x64);
    SET_ITEM(bounce,           0x0F2, 0x65);
    SET_ITEM(miracle,          0x0F3, 0x66);
    SET_ITEM(mirai,            0x0F4, 0x67);
    SET_ITEM(lamulana,         0x0F5, 0x68);
    SET_ITEM(secret_of_life,   0x0C6, 0x54);
    SET_ITEM(bathing_suit,     0x106, 0x4A);
    data->hard_mode        = memory->bytes[0x16A];

    data->coins            = memory->words[0x6A];
    data->weights          = memory->words[0x69];
    data->dialogue_score   = memory->bytes[0x7B];

    data->ammo.shuriken         = memory->words[0x6B];  
    data->ammo.rolling_shuriken = memory->words[0x6C];
    data->ammo.earth_spears     = memory->words[0x6D];      
    data->ammo.flares           = memory->words[0x6E];
    data->ammo.bombs            = memory->words[0x6F];
    data->ammo.chakram          = memory->words[0x70]; 
    data->ammo.caltrops         = memory->words[0x71];  
    data->ammo.bullets          = memory->words[0x74]; 
    data->ammo.clips            = memory->words[0x72];
    data->ammo.ankh_jewels      = memory->words[0x13];

    for (int i = 0x8E; i <= 0x95; ++i) { data->ankh_jewels.total += (memory->bytes[i] > 1); }
    data->ankh_jewels.gate_of_guidance        = memory->bytes[0x08E] > 1;
    data->ankh_jewels.mausoleum_of_the_giants = memory->bytes[0x08F] > 1;
    data->ankh_jewels.temple_of_the_sun       = memory->bytes[0x090] > 1;
    data->ankh_jewels.spring_in_the_sky       = memory->bytes[0x091] > 1;
    data->ankh_jewels.tower_of_ruin           = memory->bytes[0x092] > 1;
    data->ankh_jewels.chamber_of_birth        = memory->bytes[0x093] > 1;
    data->ankh_jewels.twin_labyrinths         = memory->bytes[0x094] > 1;
    data->ankh_jewels.dimensional_corridor    = memory->bytes[0x095] > 1;

    for (int i = 0x64; i <= 0x75; ++i) {
        if (i == 0x6C) { continue; }
        data->grails.total += !!memory->bytes[i];
    }
    data->grails.gate_of_guidance           = memory->bytes[0x064];
    data->grails.mausoleum_of_the_giants    = memory->bytes[0x065];
    data->grails.temple_of_the_sun          = memory->bytes[0x066];
    data->grails.spring_in_the_sky          = memory->bytes[0x067];
    data->grails.inferno_cavern             = memory->bytes[0x068];
    data->grails.chamber_of_extinction      = memory->bytes[0x069];
    data->grails.twin_labyrinths_front      = memory->bytes[0x06A];
    data->grails.endless_corridor           = memory->bytes[0x06B];
    data->grails.shrine_of_the_mother_front = memory->bytes[0x06C];
    data->grails.gate_of_illusion           = memory->bytes[0x06D];
    data->grails.graveyard_of_the_giants    = memory->bytes[0x06E];
    data->grails.temple_of_moonlight        = memory->bytes[0x06F];
    data->grails.tower_of_the_goddess       = memory->bytes[0x070];
    data->grails.tower_of_ruin              = memory->bytes[0x071];
    data->grails.chamber_of_birth           = memory->bytes[0x072];
    data->grails.twin_labyrinths_back       = memory->bytes[0x073];
    data->grails.dimensional_corridor       = memory->bytes[0x074];
    data->grails.shrine_of_the_mother_back  = memory->bytes[0x075];

    data->maps.total                   = memory->words[0x46];
    data->maps.surface                 = memory->bytes[0x0D1];
    data->maps.gate_of_guidance        = memory->bytes[0x0D2];
    data->maps.mausoleum_of_the_giants = memory->bytes[0x0D3];
    data->maps.temple_of_the_sun       = memory->bytes[0x0D4];
    data->maps.spring_in_the_sky       = memory->bytes[0x0D5];
    data->maps.inferno_cavern          = memory->bytes[0x0D6];
    data->maps.chamber_of_extinction   = memory->bytes[0x0D7];
    data->maps.twin_labyrinths         = memory->bytes[0x0D8];
    data->maps.endless_corridor        = memory->bytes[0x0D9];
    data->maps.gate_of_illusion        = memory->bytes[0x0DB];
    data->maps.graveyard_of_the_giants = memory->bytes[0x0DC];
    data->maps.temple_of_moonlight     = memory->bytes[0x0DD];
    data->maps.tower_of_the_goddess    = memory->bytes[0x0DE];
    data->maps.tower_of_ruin           = memory->bytes[0x0DF];
    data->maps.chamber_of_birth        = memory->bytes[0x0E0];
    data->maps.dimensional_corridor    = memory->bytes[0x0E1];
    data->maps.shrine_of_the_mother    = memory->bytes[0x0DA];

    data->orbs.total                   = memory->bytes[0x354];
    data->orbs.gate_of_guidance        = memory->bytes[0x355];//0x0C7];
    data->orbs.surface                 = memory->bytes[0x356];//0x0C8];
    data->orbs.mausoleum_of_the_giants = memory->bytes[0x357];//0x0C9];
    data->orbs.temple_of_the_sun       = memory->bytes[0x358];//0x0CA];
    data->orbs.spring_in_the_sky       = memory->bytes[0x359];//0x0CB];
    data->orbs.chamber_of_extinction   = memory->bytes[0x35A];//0x0CC];
    data->orbs.twin_labyrinths         = memory->bytes[0x35B];//0x0CD];
    data->orbs.shrine_of_the_mother    = memory->bytes[0x35C];//0x0CE];
    data->orbs.tower_of_ruin           = memory->bytes[0x35D];//0x0CF];
    data->orbs.dimensional_corridor    = memory->bytes[0x35E];//0x0D0];

    if (memory->bytes[0x0F6]) {
        data->guardians.amphisbaena = memory->bytes[0x0F6] + 1;
    } else if (memory->bytes[0x133] >= 5) {
        data->guardians.amphisbaena = 1;
    }

    if (memory->bytes[0x0F7]) {
        data->guardians.sakit = memory->bytes[0x0F7] + 1;
    } else if (memory->bytes[0x164] >= 1) {
        data->guardians.sakit = 2;
    }

    if (memory->bytes[0x0F8]) {
        data->guardians.ellmac = memory->bytes[0x0F8] + 1;
    } else if (memory->bytes[0x178] >= 5) {
        data->guardians.ellmac = 1;
    }

    if (memory->bytes[0x0F9]) {
        data->guardians.bahamut = memory->bytes[0x0F9] + 1;
    } else if (memory->bytes[0x19F] >= 1) {
        data->guardians.bahamut = 1;
    }

    if (memory->bytes[0x0FA]) {
        data->guardians.viy = memory->bytes[0x0FA] + 1;
    } else if (memory->bytes[0x1B4] >= 4) {
        data->guardians.viy = 1;
    }

    if (memory->bytes[0x0FB]) {
        data->guardians.palenque = memory->bytes[0x0FB] + 1;
    } else if (memory->bytes[0x1C3] >= 3) {
        data->guardians.palenque = 1;
    }

    if (memory->bytes[0x0FC]) {
        data->guardians.baphomet = memory->bytes[0x0FC] + 1;
    } else if (memory->bytes[0x1E0] >= 2) {
        data->guardians.baphomet = 1;
    }

    if (memory->bytes[0x0FD]) {
        data->guardians.tiamat = memory->bytes[0x0FD] + 1;
    } else if (memory->bytes[0x2EC] >= 11) {
        data->guardians.tiamat = 1;
    }

    if (memory->bytes[0x0FE]) {
        data->guardians.mother = memory->bytes[0x0FE] + 1;
    } else if (memory->bytes[0x2E0] >= 2) {
        data->guardians.mother = 1;
    }

    data->guardians.total = memory->bytes[0x102];

    data->mantras.amphisbaena = memory->bytes[0x124];
    data->mantras.sakit       = memory->bytes[0x125];
    data->mantras.ellmac      = memory->bytes[0x126];
    data->mantras.bahamut     = memory->bytes[0x127];
    data->mantras.viy         = memory->bytes[0x128];
    data->mantras.palenque    = memory->bytes[0x129];
    data->mantras.baphomet    = memory->bytes[0x12A];
    data->mantras.tiamat      = memory->bytes[0x12B];

    data->x      = ((float *)memory->xyzrs)[0];
    data->y      = ((float *)memory->xyzrs)[45];
    data->room   = memory->xyzrs[30];
    data->screen = memory->xyzrs[31];
    data->zone   = memory->xyzrs[70];
}

void lmRoomCoords(const LMData *data, int *x, int *y) {
    if (!x || !y) { return; }
    *x = *y = -1;

    if (!data) { return; }
    uint8_t zone   = data->zone;
    uint8_t room   = data->room;
    uint8_t screen = data->screen;

    LMRoomPosition room_pos = {0};
    if (zone < LM_ZONE_COUNT && room < LM_ROOM_COUNT) {
        room_pos = lm_room_position[zone][room];
    }

    if (room_pos.exists) {
        if (x) {
            if (zone == 6 && room == 5 && screen == 1) {
                *x = 8;
            } else if (zone == 8 && room == 5 && screen == 2) {
                *x = 0;
            } else if (zone == 8 && room == 5 && screen == 3) {
                *x = 1;
            } else if ((zone == 9 || zone == 18) && room == 9 && screen == 1) {
                *x = 0;
            } else {
                *x = room_pos.x + screen % room_pos.w;
            }
        }

        if (y) {
            *y = room_pos.y + screen / room_pos.w;
        }
    }
};

int lmRoomX(const LMData *data) {
    int x = -1;
    lmRoomCoords(data, &x, NULL);
    return x;
}

int lmRoomY(const LMData *data) {
    int y = -1;
    lmRoomCoords(data, NULL, &y);
    return y;
}


/*********
 * DATA
 */

const char *lm_zone_name[LM_ZONE_COUNT] = {
    /*  0 */ "Gate of Guidance",
    /*  1 */ "Surface",
    /*  2 */ "Mausoleum of the Giants",
    /*  3 */ "Temple of the Sun",
    /*  4 */ "Spring in the Sky",
    /*  5 */ "Inferno Cavern",
    /*  6 */ "Chamber of Extinction",
    /*  7 */ "Twin Labyrinths",
    /*  8 */ "Endless Corridor",
    /*  9 */ "Shrine of the Mother",
    /* 10 */ "Gate of Illusion",
    /* 11 */ "Graveyard of the Giants",
    /* 12 */ "Temple of Moonlight",
    /* 13 */ "Tower of the Goddess",
    /* 14 */ "Tower of Ruin",
    /* 15 */ "Chamber of Birth",
    /* 16 */ "Chamber of Birth",
    /* 17 */ "Dimensional Corridor",
    /* 18 */ "Shrine of the Mother",
    /* 19 */ "Gate of Time",
    /* 20 */ "Gate of Time",
    /* 21 */ "Gate of Time",
    /* 22 */ "Surface",
    /* 23 */ "Hell Temple",
    /* 24 */ "Hell Temple",
    /* 25 */ "Burning Cavern"
};

const uint8_t lm_zone_len[LM_ZONE_COUNT] = {
    /*        0   1   2   3   4   5   6   7   8   9 */
    /* 00 */ 16,  7, 23, 17, 17, 14, 21, 15, 16, 20,
    /* 10 */ 16, 23, 19, 20, 13, 16, 16, 20, 20, 12,
    /* 20 */ 12, 12,  7, 11, 11, 14
};

const uint8_t lm_zone_width[LM_ZONE_COUNT] = {
    /*        0   1   2   3   4   5   6   7   8   9 */
    /* 00 */  7, 12,  8,  7,  5,  7,  9, 10,  5,  6,
    /* 10 */  7,  7,  6,  5,  7,  9,  9,  4,  6,  7,
    /* 20 */  7,  7, 12,  5,  5,  1
};

const uint8_t lm_zone_height[LM_ZONE_COUNT] = {
    /*        0   1   2   3   4   5   6   7   8   9 */
    /* 00 */  6,  5,  6,  6, 10,  6,  5,  5,  5,  6,
    /* 10 */  6,  6,  6,  9,  6,  6,  6,  7,  6, 11,
    /* 20 */ 11, 11,  5, 11, 11, 20
};

const LMRoomPosition lm_room_position[LM_ZONE_COUNT][LM_ROOM_COUNT] = {
    {   /*  0 Gate of Guidance */
        /*  0 */ { 2, 0, 2, 1 },
        /*  1 */ { 3, 1, 2, 1 },
        /*  2 */ { 5, 1, 2, 1 },
        /*  3 */ { 2, 2, 2, 1 },
        /*  4 */ { 1, 2, 1, 3 },
        /*  5 */ { 0, 2, 1, 1 },
        /*  6 */ { 2, 3, 2, 1 },
        /*  7 */ { 2, 4, 2, 1 },
        /*  8 */ { 4, 3, 1, 2 },
        /*  9 */ { 0, 5, 2, 1 },
    },

    {   /*  1 Surface */
        /*  0 */ {  0, 2, 3, 1 },
        /*  1 */ {  3, 2, 1, 2 },
        /*  2 */ {  5, 3, 2, 1 },
        /*  3 */ {  7, 3, 1, 1 },
        /*  4 */ {  8, 0, 1, 3 },
        /*  5 */ {  9, 0, 1, 3 },
        /*  6 */ { 10, 0, 2, 1 },
        /*  7 */ { 10, 1, 2, 1 },
        /*  8 */ { 10, 2, 2, 1 },
        /*  9 */ {  4, 2, 1, 2 },
        /* 10 */ {  6, 1, 2, 2 },
        /* 11 */ {  7, 4, 2, 1 },
    },

    {   /*  2 Mausoleum of the Giants */
        /*  0 */ { 1, 0, 2, 1 },
        /*  1 */ { 1, 1, 2, 1 },
        /*  2 */ { 3, 1, 1, 2 },
        /*  3 */ { 0, 1, 1, 1 },
        /*  4 */ { 3, 2, 1, 1 },
        /*  5 */ { 4, 2, 1, 3 },
        /*  6 */ { 6, 2, 2, 1 },
        /*  7 */ { 6, 3, 3, 1 },
        /*  8 */ { 1, 4, 3, 1 },
        /*  9 */ { 4, 5, 1, 1 },
    },

    {   /*  3 Temple of the Sun */
        /*  0 */ { 1, 0, 2, 1 },
        /*  1 */ { 1, 1, 3, 1 },
        /*  2 */ { 0, 0, 1, 2 },
        /*  3 */ { 2, 2, 1, 1 },
        /*  4 */ { 3, 2, 3, 2 },
        /*  5 */ { 6, 3, 1, 1 },
        /*  6 */ { 3, 4, 2, 1 },
        /*  7 */ { 1, 4, 2, 1 },
        /*  8 */ { 3, 5, 1, 1 },
    },

    {   /*  4 Spring in the Sky */
        /*  0 */ { 0, 3, 1, 3 },
        /*  1 */ { 1, 5, 1, 1 },
        /*  2 */ { 2, 4, 1, 2 },
        /*  3 */ { 3, 0, 1, 5 },
        /*  4 */ { 2, 1, 1, 1 },
        /*  5 */ { 4, 1, 1, 2 },
        /*  6 */ { 1, 6, 1, 2 },
        /*  7 */ { 2, 7, 1, 2 },
        /*  8 */ { 1, 8, 1, 2 },
    },

    {   /*  5 Inferno Cavern */
        /*  0 */ { 5, 1, 2, 1 },
        /*  1 */ { 4, 0, 1, 2 },
        /*  2 */ { 3, 1, 1, 3 },
        /*  3 */ { 0, 2, 3, 1 },
        /*  4 */ { 2, 3, 1, 1 },
        /*  5 */ { 4, 3, 1, 2 },
        /*  6 */ { 5, 3, 1, 1 },
        /*  7 */ { 5, 4, 2, 1 },
        /*  8 */ { 3, 4, 1, 2 },
        /*  9 */ { 1, 0, 2, 1 },
    },

    {   /*  6 Chamber of Extinction */
        /*  0 */ { 2, 0, 2, 1 },
        /*  1 */ { 4, 0, 2, 1 },
        /*  2 */ { 0, 1, 2, 1 },
        /*  3 */ { 1, 2, 2, 1 },
        /*  4 */ { 2, 3, 1, 1 },
        /*  5 */ { 4, 3, 1, 2 },
        /*  6 */ { 5, 3, 1, 2 },
        /*  7 */ { 6, 4, 2, 1 },
        /*  8 */ { 6, 1, 2, 1 },
        /*  9 */ { 7, 2, 2, 1 },
    },

    {   /*  7 Twin Labyrinths */
        /*  0 */ { 3, 0, 2, 1 },
        /*  1 */ { 1, 0, 2, 1 },
        /*  2 */ { 1, 1, 3, 1 },
        /*  3 */ { 0, 1, 1, 3 },
        /*  4 */ { 2, 2, 2, 1 },
        /*  5 */ { 1, 2, 1, 2 },
        /*  6 */ { 2, 3, 2, 1 },
        /*  7 */ { 1, 4, 2, 1 },
        /*  8 */ { 3, 4, 2, 1 },
        /*  9 */ { 5, 0, 2, 1 },
        /* 10 */ { 7, 0, 2, 1 },
        /* 11 */ { 6, 1, 3, 1 },
        /* 12 */ { 9, 1, 1, 3 },
        /* 13 */ { 6, 2, 2, 1 },
        /* 14 */ { 6, 3, 2, 1 },
        /* 15 */ { 5, 5, 3, 1 },
        /* 16 */ { 8, 2, 1, 3 },
    },

    {   /*  8 Endless Corridor */
        /*  0 */ { 2, 0, 2, 1 },
        /*  1 */ { 0, 0, 2, 1 },
        /*  2 */ { 1, 1, 4, 1 },
        /*  3 */ { 0, 2, 4, 1 },
        /*  4 */ { 1, 3, 4, 1 },
        /*  5 */ { 2, 4, 4, 1 },
    },

    {   /*  9 Shrine of the Mother */
        /*  0 */ { 2, 0, 2, 1 },
        /*  1 */ { 1, 1, 2, 1 },
        /*  2 */ { 3, 1, 2, 1 },
        /*  3 */ { 2, 2, 2, 1 },
        /*  4 */ { 1, 3, 2, 1 },
        /*  5 */ { 3, 3, 2, 1 },
        /*  6 */ { 1, 4, 1, 2 },
        /*  7 */ { 2, 4, 2, 1 },
        /*  8 */ { 4, 4, 1, 2 },
        /*  9 */ { 5, 2, 2, 1 },
    },

    {   /* 10 Gate of Illusion */
        /*  0 */ { 3, 0, 2, 1 },
        /*  1 */ { 4, 1, 2, 1 },
        /*  2 */ { 3, 1, 1, 3 },
        /*  3 */ { 2, 1, 1, 1 },
        /*  4 */ { 2, 2, 1, 2 },
        /*  5 */ { 0, 2, 2, 1 },
        /*  6 */ { 0, 3, 1, 1 },
        /*  7 */ { 2, 4, 3, 1 },
        /*  8 */ { 5, 3, 1, 2 },
        /*  9 */ { 5, 5, 2, 1 },
    },

    {   /* 11 Graveyard of the Giants */
        /*  0 */ { 0, 0, 3, 1 },
        /*  1 */ { 0, 1, 2, 1 },
        /*  2 */ { 2, 1, 2, 1 },
        /*  3 */ { 2, 2, 1, 1 },
        /*  4 */ { 3, 2, 1, 4 },
        /*  5 */ { 1, 4, 2, 1 },
        /*  6 */ { 4, 2, 1, 1 },
        /*  7 */ { 4, 3, 1, 2 },
        /*  8 */ { 5, 2, 1, 1 },
        /*  9 */ { 5, 3, 2, 1 },
    },

    {   /* 12 Temple of Moonlight */
        /*  0 */ { 0, 0, 1, 2 },
        /*  1 */ { 1, 0, 1, 2 },
        /*  2 */ { 2, 1, 2, 1 },
        /*  3 */ { 1, 2, 1, 1 },
        /*  4 */ { 2, 2, 1, 4 },
        /*  5 */ { 3, 2, 1, 2 },
        /*  6 */ { 4, 2, 1, 2 },
        /*  7 */ { 5, 3, 1, 1 },
        /*  8 */ { 1, 4, 1, 1 },
        /*  9 */ { 3, 4, 2, 1 },
        /* 10 */ { 3, 5, 1, 1 },
    },

    {   /* 13 Tower of the Goddess */
        /*  0 */ { 1, 7, 1, 2 },
        /*  1 */ { 2, 6, 1, 2 },
        /*  2 */ { 1, 4, 1, 3 },
        /*  3 */ { 0, 3, 1, 2 },
        /*  4 */ { 0, 1, 1, 2 },
        /*  5 */ { 2, 3, 1, 2 },
        /*  6 */ { 3, 1, 1, 4 },
        /*  7 */ { 2, 0, 3, 1 },
        /*  8 */ { 1, 5, 1, 1 },
    },

    {   /* 14 Tower of Ruin */
        /*  0 */ { 4, 4, 3, 1 },
        /*  1 */ { 4, 3, 2, 1 },
        /*  2 */ { 3, 4, 1, 2 },
        /*  3 */ { 2, 3, 2, 1 },
        /*  4 */ { 2, 2, 2, 1 },
        /*  5 */ { 0, 2, 2, 1 },
        /*  6 */ { 3, 1, 2, 1 },
        /*  7 */ { 5, 1, 2, 1 },
        /*  8 */ { 4, 0, 3, 1 },
    },

    {   /* 15 Chamber of Birth (Top) */
        /*  0 */ { 3, 0, 1, 2 },
        /*  1 */ { 4, 1, 2, 1 },
        /*  2 */ { 6, 1, 1, 2 },
        /*  3 */ { 7, 2, 1, 2 },
        /*  4 */ { 8, 3, 1, 1 },
    },

    {   /* 16 Chamber of Birth (Bottom) */
        /*  0 */ { 0, 2, 2, 1 },
        /*  1 */ { 1, 3, 2, 1 },
        /*  2 */ { 2, 4, 2, 1 },
        /*  3 */ { 4, 4, 2, 1 },
        /*  4 */ { 4, 5, 3, 1 },
    },

    {   /* 17 Dimensional Corridor */
        /*  0 */ { 1, 5, 1, 2 },
        /*  1 */ { 0, 5, 1, 2 },
        /*  2 */ { 0, 4, 2, 1 },
        /*  3 */ { 3, 4, 1, 1 },
        /*  4 */ { 3, 5, 1, 2 },
        /*  5 */ { 2, 3, 1, 2 },
        /*  6 */ { 3, 3, 1, 1 },
        /*  7 */ { 0, 3, 2, 1 },
        /*  8 */ { 0, 2, 2, 1 },
        /*  9 */ { 2, 2, 2, 1 },
        /* 10 */ { 2, 0, 1, 2 },
    },

    {   /* 18 Shrine of the Mother */
        /*  0 */ { 2, 0, 2, 1 },
        /*  1 */ { 1, 1, 2, 1 },
        /*  2 */ { 3, 1, 2, 1 },
        /*  3 */ { 2, 2, 2, 1 },
        /*  4 */ { 1, 3, 2, 1 },
        /*  5 */ { 3, 3, 2, 1 },
        /*  6 */ { 1, 4, 1, 2 },
        /*  7 */ { 2, 4, 2, 1 },
        /*  8 */ { 4, 4, 1, 2 },
        /*  9 */ { 5, 2, 2, 1 },
    },

    {   /* 19 Gate of Time (MotG) */
        /*  0 */ { 3, 9, 1, 2 },
        /*  1 */ { 4, 9, 3, 1 },
        /*  2 */ { 2, 8, 2, 1 },
        /*  3 */ { 2, 6, 1, 2 },
        /*  4 */ { 0, 6, 2, 1 },
    },

    {   /* 20 Gate of Time (GG) */
        /*  0 */ { 0, 5, 2, 1 },
        /*  1 */ { 1, 2, 1, 3 },
        /*  2 */ { 2, 2, 2, 1 },
        /*  3 */ { 3, 1, 2, 1 },
        /*  4 */ { 2, 0, 2, 1 },
    },

    {   /* 21 Gate of Time (Surface) */
        /*  0 */ { 0, 0, 2, 1 },
    },

    {   /* 22 Surface (Night) */
        /*  0 */ {  0, 2, 3, 1 },
        /*  1 */ {  3, 2, 1, 2 },
        /*  2 */ {  5, 3, 2, 1 },
        /*  3 */ {  7, 3, 1, 1 },
        /*  4 */ {  8, 0, 1, 3 },
        /*  5 */ {  9, 0, 1, 3 },
        /*  6 */ { 10, 0, 2, 1 },
        /*  7 */ { 10, 1, 2, 1 },
        /*  8 */ { 10, 2, 2, 1 },
        /*  9 */ {  4, 2, 1, 2 },
        /* 10 */ {  6, 1, 2, 2 },
        /* 11 */ {  7, 4, 2, 1 },
    },

    {   /* 23 Hell Temple */
        /*  0 */ { 2,  3, 1, 1 },
        /*  1 */ { 2,  2, 2, 1 },
        /*  2 */ { 4,  2, 1, 1 },
        /*  3 */ { 4,  3, 1, 1 },
        /*  4 */ { 3,  0, 2, 1 },
        /*  5 */ { 2,  0, 1, 2 },
        /*  6 */ { 0,  2, 2, 1 },
        /*  7 */ { 0,  5, 1, 1 },
        /*  8 */ { 1,  4, 2, 1 },
        /*  9 */ { 3,  4, 2, 1 },
        /* 10 */ { 4,  5, 1, 2 },
        /* 11 */ { 4,  7, 1, 1 },
        /* 12 */ { 2,  6, 1, 2 },
        /* 13 */ { 2,  5, 1, 1 },
        /* 14 */ { 0,  6, 2, 1 },
        /* 15 */ { 0,  7, 1, 2 },
        /* 16 */ { 0,  9, 1, 1 },
        /* 17 */ { 0, 10, 1, 1 },
        /* 18 */ { 1,  8, 2, 1 },
        /* 19 */ { 2,  9, 1, 1 },
        /* 20 */ { 3,  8, 1, 1 },
        /* 21 */ { 4, 10, 1, 1 },
        /* 22 */ { 2, 10, 2, 1 }
    },

    {   /* 24 Hell Temple */
        /*  0 */ { 0, 3, 1, 2 },
        /*  1 */ { 3, 6, 1, 1 },
        /*  2 */ { 4, 8, 1, 2 },
    },

    {   /* 25 Burning Cavern */
        /*  0 */ { 0,  0, 1, 5 },
        /*  1 */ { 0,  5, 1, 5 },
        /*  2 */ { 0, 10, 1, 5 },
        /*  3 */ { 0, 15, 1, 5 },
    }
};

#ifdef __cplusplus
}
#endif

#endif /* TORUDE_IMPLEMENTED */
#endif /* TORUDE_IMPLEMENTATION */
