#ifndef RANDO_HPPGUARD
#define RANDO_HPPGUARD

#include "common.hpp"
#include "bitmap.hpp"
#include "memory.hpp"

extern BunBitmap rando;

bool initRando(const char *filename);
void updateRando(LMMemory *memory);

#endif /* RANDO_HPPGUARD */
