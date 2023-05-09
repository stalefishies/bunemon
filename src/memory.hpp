#ifndef MEMORY_HPPGUARD
#define MEMORY_HPPGUARD

#include "common.hpp"

enum {
    LM_MEMORY_SIZE_BYTES = 4096,
    LM_MEMORY_SIZE_WORDS = 512,
    LM_MEMORY_SIZE_FLAGS = 20,
    LM_MEMORY_SIZE_XYZRS = 184,
};

typedef struct LMMemory {
    uint8_t  bytes[LM_MEMORY_SIZE_BYTES];
    uint16_t words[LM_MEMORY_SIZE_WORDS / 2];
    uint8_t  flags[LM_MEMORY_SIZE_FLAGS];

    union {
        uint8_t xyzrs[LM_MEMORY_SIZE_XYZRS];
        struct {
            float    x;
            uint8_t _unused_1[26];
            uint8_t  room;
            uint8_t  screen;
            uint8_t _unused_2[38];
            uint8_t  zone;
            uint8_t _unused_3[109];
            float    y;
        };
    };

    float   prev_x;
    float   prev_y;
    uint8_t prev_zone;
    uint8_t prev_room;
    uint8_t prev_screen;

    bool valid;
} LMMemory;

DWORD WINAPI scanThread(void *);

#endif /* MEMORY_HPPGUARD */
