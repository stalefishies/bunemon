#include "items.hpp"

BunBitmap items;

enum {
    ITEMS_COUNT_X = 8,
    ITEMS_COUNT_Y = 12,

    ITEM_COL = 0x8000U,
    ITEM_IMG = ~ITEM_COL
};

struct ItemsState {
    uint16_t image;
    uint16_t count;
    uint16_t sub_1;
    uint16_t sub_2;
} cur_istate[ITEMS_COUNT_Y][ITEMS_COUNT_X];

bool operator ==(ItemsState &a, ItemsState &b) {
    return a.image == b.image && a.count == b.count
        && a.sub_1 == b.sub_1 && a.sub_2 == b.sub_2;
}
bool operator !=(ItemsState &a, ItemsState &b) { return !(a == b); }

void updateItems(LMMemory *memory) {
    ItemsState new_istate[ITEMS_COUNT_Y][ITEMS_COUNT_X] = {0};
    uint8_t  *byte = memory->bytes;
    uint16_t *word = memory->words;

#define SET_AT(i, j, NAME)                          \
    for (bool _loop = (                             \
            (new_istate[i][j].image = IMG_##NAME),  \
        true); _loop;)                              \
    for (ItemsState *state = &new_istate[i][j];     \
        _loop; _loop = false)

#define SET_ITEM(i, j, NAME, b, w) do {                         \
    new_istate[i][j].image = IMG_##NAME;                        \
    if (((b) > 0 && byte[b] >= 2) || ((w) > 0 && word[w])) {    \
        new_istate[i][j].image |= ITEM_COL;                     \
    }                                                           \
} while (0)

#define SET_COUNT(i, j, NAME, b, w, n) do {                     \
    new_istate[i][j].image = IMG_##NAME;                        \
    if (((b) > 0 && byte[b] >= 2) || ((w) > 0 && word[w])) {    \
        new_istate[i][j].count = (n);                           \
        new_istate[i][j].image |= ITEM_COL;                     \
        new_istate[i][j].count |= ITEM_COL;                     \
    }                                                           \
} while (0)

#define SET_SUB(i, j, NAME, b, w, SUB_1, b1, w1, SUB_2, b2, w2) do {    \
    new_istate[i][j].image = IMG_##NAME;                                \
    new_istate[i][j].sub_1 = IMG_##SUB_1;                               \
    new_istate[i][j].sub_2 = IMG_##SUB_2;                               \
    if (((b)  > 0 && byte[b]  >= 2) || ((w)  > 0 && word[w] ))          \
    { new_istate[i][j].image |= ITEM_COL; }                             \
    if (((b1) > 0 && byte[b1] >= 2) || ((w1) > 0 && word[w1]))          \
    { new_istate[i][j].sub_1 |= ITEM_COL; }                             \
    if (((b2) > 0 && byte[b2] >= 2) || ((w2) > 0 && word[w2]))          \
    { new_istate[i][j].sub_2 |= ITEM_COL; }                             \
} while (0)

#define SET_COMBO(i, j, NAME, SUB_1, b1, w1, SUB_2, b2, w2) do {            \
    new_istate[i][j].image = IMG_COMBO_##NAME;                              \
    new_istate[i][j].sub_1 = IMG_##SUB_1;                                   \
    new_istate[i][j].sub_2 = IMG_##SUB_2;                                   \
    bool have_1 = ((b1) > 0 && byte[b1] >= 2) || ((w1) > 0 && word[w1]);    \
    bool have_2 = ((b2) > 0 && byte[b2] >= 2) || ((w2) > 0 && word[w2]);    \
    if (have_1 && have_2) { new_istate[i][j].image |= ITEM_COL; }           \
    if (have_1          ) { new_istate[i][j].sub_1 |= ITEM_COL; }           \
    if (have_2          ) { new_istate[i][j].sub_2 |= ITEM_COL; }           \
} while (0)

#define SET_WEDGE(i, j, b, n) do {                              \
    new_istate[i][j].image = IMG_WEDGE_1 + (j);                 \
    if (byte[0x124 + (j)] >= 4) {                               \
        new_istate[i][j].image |= ITEM_COL;                     \
        new_istate[i][j].sub_1 = IMG_WEDGE_BROKEN | ITEM_COL;   \
    } else if (byte[b] >= (n)) {                                \
        new_istate[i][j].image |= ITEM_COL;                     \
        new_istate[i][j].sub_1 = IMG_ANKH | ITEM_COL;           \
    } else if (byte[0x0F6 + (j)] >= 2) {                        \
        new_istate[i][j].image |= ITEM_COL;                     \
    }                                                           \
} while (0)

    SET_AT   (0, 0, WHIP_1) {
        if (byte[0x07E] >= 2 || word[0x02]) {
            state->image = IMG_WHIP_3 | ITEM_COL;
        } else if (byte[0x07D] >= 2 || word[0x01]) {
            state->image = IMG_WHIP_2 | ITEM_COL;
        } else if (word[0x00] != 0xFFFF && memory->zone != 0xFF) {
            state->image = IMG_WHIP_1 | ITEM_COL;
        }
    }
    SET_ITEM (0, 1, KNIFE, 0x07F, 0x03);
    SET_AT   (0, 2, KEY_SWORD_1) {
        if (word[0x07]) {
            state->image = IMG_KEY_SWORD_2 | ITEM_COL;
        } else if (byte[0x080] >= 2 || word[0x04]) {
            state->image = IMG_KEY_SWORD_1 | ITEM_COL;
        }
    }
    SET_ITEM (0, 3, AXE,              0x081, 0x05);
    SET_ITEM (0, 4, KATANA,           0x082, 0x06);
    SET_AT   (0, 5, SHIELD_1) {
        if (byte[0x08D] >= 2 || word[0x12]) {
            state->image = IMG_SHIELD_4 | ITEM_COL;
        } else if (byte[0x08C] >= 2 || word[0x11]) {
            state->image = IMG_SHIELD_3 | ITEM_COL;
        } else if (word[0x4B]) {
            state->image = IMG_SHIELD_2 | ITEM_COL;
        } else if (word[0x10]) {
            state->image = IMG_SHIELD_1 | ITEM_COL;
        }
    }
    SET_AT   (0, 6, ANKH_JEWEL) {
        bool have_any = byte[0x08E] || byte[0x08F] || byte[0x090] || byte[0x091]
            || byte[0x092] || byte[0x093] || byte[0x094] || byte[0x095];
        if (have_any) {
            state->image |= ITEM_COL;
            state->count = word[0x13] | ITEM_COL;
        }
    }
    SET_AT   (0, 7, SACRED_ORB) {
        if (byte[0x354]) {
            state->image |= ITEM_COL;
            state->count = byte[0x354] | ITEM_COL;
        }
    }

    SET_COUNT(1, 0, SHURIKEN,         0x083, 0x08, word[0x6B]);
    SET_COUNT(1, 1, ROLLING_SHURIKEN, 0x084, 0x09, word[0x6C]);
    SET_COUNT(1, 2, EARTH_SPEAR,      0x085, 0x0A, word[0x6D]);
    SET_COUNT(1, 3, FLARE,            0x086, 0x0B, word[0x6E]);
    SET_COUNT(1, 4, BOMB,             0x087, 0x0C, word[0x6F]);
    SET_COUNT(1, 5, CHAKRAM,          0x088, 0x0D, word[0x70]);
    SET_COUNT(1, 6, CALTROPS,         0x089, 0x0E, word[0x71]);
    SET_AT   (1, 7, GUN) {
        if (byte[0x08A] >= 2 || word[0x0F]) { state->image |= ITEM_COL; }
        state->count = ITEM_COL | (word[0x74] % 10) | ((word[0x72] % 10) << 8);
    }

    SET_ITEM (2, 0, HAND_SCANNER,     0x096, 0x14);
    SET_AT   (2, 1, LAMP_OF_TIME_1) {
        if (byte[0x09B] >= 2 || word[0x50]) {
            if (word[0x19]) {
                state->image = IMG_LAMP_OF_TIME_2 | ITEM_COL;
            } else {
                state->image = IMG_LAMP_OF_TIME_1 | ITEM_COL;
            }
        }
    }
    SET_ITEM (2, 2, KEY_OF_ETERNITY,  0x0A2, 0x20);
    SET_ITEM (2, 3, COG_OF_THE_SOUL,  0x09A, 0x18);
    SET_ITEM (2, 4, POCHETTE_KEY,     0x09C, 0x1A);
    SET_ITEM (2, 5, CRYSTAL_SKULL,    0x09E, 0x1C);
    SET_ITEM (2, 6, DJED_PILLAR,      0x097, 0x15);
    SET_AT   (2, 7, VESSEL_1) {
        if (byte[0x10A] >= 2 || word[0x4F]) {
            state->image = IMG_VESSEL_4 | ITEM_COL;
        } else if (byte[0x109] >= 2 || word[0x4E]) {
            state->image = IMG_VESSEL_3 | ITEM_COL;
        } else if (byte[0x108] >= 2 || word[0x4D]) {
            state->image = IMG_VESSEL_2 | ITEM_COL;
        } else if (byte[0x09F] >= 2 || word[0x1D]) {
            state->image = IMG_VESSEL_1 | ITEM_COL;
        }
    }

    SET_ITEM (3, 0, SERPENT_STAFF,    0x0A3, 0x21);
    SET_ITEM (3, 1, DRAGON_BONE,      0x09D, 0x1B);
    SET_ITEM (3, 2, MAGATAMA_JEWEL,   0x099, 0x17);
    SET_AT   (3, 3, WOMAN_STATUE) {
        if (byte[0x10B] >= 2 || word[0x51]) {
            state->image = IMG_MATERNITY_STATUE | ITEM_COL;
        } else if (byte[0x0A1] || word[0x1F]) {
            state->image = IMG_WOMAN_STATUE | ITEM_COL;
        }
    }
    SET_ITEM (3, 4, MINI_DOLL,        0x098, 0x16);
    SET_ITEM (3, 5, PEPPER,           0x0A0, 0x1E);
    SET_AT   (3, 6, INVALID) {
        state->sub_1 = IMG_TALISMAN;
        state->sub_2 = IMG_DIARY;
        state->image = IMG_MULANA_TALISMAN;

        if (byte[0x0A4] >= 2 || word[0x22]) { state->sub_1 |= ITEM_COL; }
        if (byte[0x104] >= 2 || word[0x48]) { state->sub_2 |= ITEM_COL; }
        if (byte[0x105] >= 2 || word[0x49]) { state->image |= ITEM_COL; }
    }

    SET_AT   (4, 0, HOLY_GRAIL_1) {
        if (word[0x52]) {
            state->image = IMG_HOLY_GRAIL_3 | ITEM_COL;
        } else if (word[0x53]) {
            state->image = IMG_HOLY_GRAIL_2 | ITEM_COL;
        } else if (word[0x089] >= 2 || memory->words[0x28]) {
            uint8_t count = 0;
            for (int i = 0x64; i <= 0x75; ++i) {
                if (i == 0x6C) { continue; }
                count += !!byte[i];
            }
            state->image = IMG_HOLY_GRAIL_1 | ITEM_COL;
            state->count = count | ITEM_COL;
        }
    }
    SET_ITEM (4, 1, FEATHER,          0x0B6, 0x35);
    SET_ITEM (4, 2, GRAPPLE_CLAW,     0x0AD, 0x2C);
    SET_ITEM (4, 3, HERMES_BOOTS,     0x0BA, 0x39);
    SET_ITEM (4, 4, ISIS_PENDANT,     0x0AA, 0x29);
    SET_ITEM (4, 5, BRONZE_MIRROR,    0x0AE, 0x2D);
    SET_ITEM (4, 6, OCARINA,          0x0B5, 0x34);
    SET_SUB  (4, 7, MSX_2,            0x000, 0x4C,
                    WATERPROOF_CASE,  0x0A5, 0x24,
                    HEATPROOF_CASE,   0x0A6, 0x25);

    SET_ITEM (5, 0, HELMET,           0x0AC, 0x2B);
    SET_ITEM (5, 1, FRUIT_OF_EDEN,    0x0BB, 0x3A);
    SET_ITEM (5, 2, TWIN_STATUE,      0x0BC, 0x3B);
    SET_ITEM (5, 3, DIMENSIONAL_KEY,  0x0C0, 0x3F);
    SET_ITEM (5, 4, EYE_OF_TRUTH,     0x0AF, 0x2E);
    SET_ITEM (5, 5, PLANE_MODEL,      0x0B4, 0x33);
    SET_ITEM (5, 6, TREASURES,        0x103, 0x47);
    SET_ITEM (5, 7, ANCHOR,           0x0B3, 0x32);

    SET_ITEM (6, 0, SHELL_HORN,       0x0A7, 0x26);
    SET_ITEM (6, 1, GLOVE,            0x0A8, 0x27);
    SET_ITEM (6, 2, SCALESPHERE,      0x0B1, 0x30);
    SET_ITEM (6, 3, ICE_CAPE,         0x0C1, 0x40);
    SET_ITEM (6, 4, BOOK_OF_THE_DEAD, 0x0B7, 0x36);
    SET_ITEM (6, 5, GAUNTLET,         0x0B2, 0x31);
    SET_ITEM (6, 6, RING,             0x0B0, 0x2F);
    SET_ITEM (6, 7, FAIRY_CLOTHES,    0x0B8, 0x37);

    SET_ITEM (7, 0, SCRIPTURES,       0x0B9, 0x38);
    SET_ITEM (7, 1, PERFUME,          0x0BE, 0x3D);
    SET_ITEM (7, 2, CRUCIFIX,         0x0AB, 0x2A);
    SET_ITEM (7, 3, BRACELET,         0x0BD, 0x3C);
    SET_ITEM (7, 4, SPAULDER,         0x0BF, 0x3E);
    SET_ITEM (7, 5, BATHING_SUIT,     0x106, 0x4A);
    SET_COUNT(7, 6, MAP,              0x000, 0x46, word[0x46]);
    SET_ITEM (7, 7, SHRINE_MAP,       0x0DA, 0x00);

    SET_ITEM (8, 0, SEAL_1,           0x0C2, 0x40);
    SET_ITEM (8, 1, SEAL_2,           0x0C3, 0x41);
    SET_ITEM (8, 2, SEAL_3,           0x0C4, 0x42);
    SET_ITEM (8, 3, SEAL_4,           0x0C5, 0x43);
    SET_ITEM (8, 4, READER,           0x0E2, 0x55);
    SET_ITEM (8, 5, MIRAI,            0x0F4, 0x67);
    SET_ITEM (8, 6, TORUDE,           0x0E8, 0x5B);
    SET_ITEM (8, 7, MANTRA,           0x0EA, 0x5D);

    SET_COMBO( 9, 0, IFRAMES,
                     MOVE,      0x0F0, 0x63,
                     DEATHV,    0x0ED, 0x60);
    SET_COMBO( 9, 1, REVIVE,
                     MOVE,      0x0F0, 0x63,
                     RANDC,     0x0EE, 0x61);
    SET_COMBO( 9, 2, WHIP,
                     MOVE,      0x0F0, 0x63,
                     LAMULANA,  0x0F5, 0x68);
    SET_COMBO( 9, 3, NON_WHIP,
                     RANDC,     0x0EE, 0x61,
                     MEKURI,    0x0F1, 0x64);
    SET_COMBO( 9, 4, FAIRY_1,
                     MIRACLE,   0x0F3, 0x66,
                     BOUNCE,    0x0F2, 0x65);
    SET_COMBO( 9, 5, FAIRY_2,
                     MIRACLE,   0x0F3, 0x66,
                     CAPSTAR,   0x0EF, 0x62);
    SET_COMBO( 9, 6, FAIRY_3,
                     MIRACLE,   0x0F3, 0x66,
                     MEKURI,    0x0F1, 0x64);
    SET_COMBO( 9, 7, FAIRY_4,
                     MIRACLE,   0x0F3, 0x66,
                     DEATHV,    0x0ED, 0x60);
    SET_COMBO(10, 0, DEV_ROOMS,
                     MIRACLE,   0x0F3, 0x66,
                     MIRAI,     0x0F4, 0x67);
    SET_SUB  (10, 1, YAGOMAP,   0x0E4, 0x57,
                     INVALID,   0x000, 0x00,
                     YAGOSTR,   0x0E5, 0x58);
    SET_SUB  (10, 2, BUNEMON,   0x0E6, 0x59,
                     INVALID,   0x000, 0x00,
                     BUNPLUS,   0x0E7, 0x5A);
    SET_SUB  (10, 3, EMUSIC,    0x0EB, 0x5E,
                     INVALID,   0x000, 0x00,
                     BEOLAMU,   0x0EC, 0x5F);
    SET_ITEM (10, 6, GUILD,     0x0E9, 0x5C);
    SET_ITEM (10, 7, XMAILER,   0x0E3, 0x56);

    SET_WEDGE(11, 0, 0x133,  5);
    SET_WEDGE(11, 1, 0x164,  1);
    SET_WEDGE(11, 2, 0x178,  5);
    SET_WEDGE(11, 3, 0x19F,  1);
    SET_WEDGE(11, 4, 0x1B4,  4);
    SET_WEDGE(11, 5, 0x1C3,  3);
    SET_WEDGE(11, 6, 0x1E0,  2);
    SET_WEDGE(11, 7, 0x2EC, 11);

    if (memory->zone != memory->prev_zone || memory->room != memory->prev_room
        || memory->screen != memory->prev_screen)
    {
        items.drawBG(0, 0, 320, 43);

        if (memory->zone < FIELD_MAX_ZONE) {
            items.drawCoord(0, 0, memory->zone, memory->room, memory->screen, true);

            String room = {};
            if (memory->room < FIELD_MAX_ROOM && memory->screen < FIELD_MAX_SCREEN) {
                room = fieldRoom(memory->zone, memory->room, memory->screen);
            }

            items.drawText(60, 2, ITEMS_W - 60, field_name[memory->zone]);
            if (room.length > 0) { items.drawText(60, 22, ITEMS_W - 60, room); }
        }
    }

    for (int i = 0; i < ITEMS_COUNT_Y; ++i)
    for (int j = 0; j < ITEMS_COUNT_X; ++j) {
        // pepper, talisman, diary, mulana talisman
        if (i == 3 && j == 5) {
            if (cur_istate[3][5] != new_istate[3][5]
                || cur_istate[3][6] != new_istate[3][6])
            {
                cur_istate[3][5] = new_istate[3][5];
                cur_istate[3][6] = new_istate[3][6];

                int x = 200;
                int y = 200;
                bool pep = cur_istate[3][5].image & ITEM_COL;
                bool tal = cur_istate[3][6].sub_1 & ITEM_COL;
                bool dia = cur_istate[3][6].sub_2 & ITEM_COL;
                bool mul = cur_istate[3][6].image & ITEM_COL;

                items.drawBG(x, y, 120, 40);
                if (!pep) { items.drawImage(x +  0, y, IMG_PEPPER,          false); }
                if (!tal) { items.drawImage(x + 34, y, IMG_TALISMAN,        false); }
                if (!dia) { items.drawImage(x + 50, y, IMG_DIARY,           false); }
                if (!mul) { items.drawImage(x + 80, y, IMG_MULANA_TALISMAN, false); }
                if ( pep) { items.drawImage(x +  0, y, IMG_PEPPER,          true);  }
                if ( tal) { items.drawImage(x + 34, y, IMG_TALISMAN,        true);  }
                if ( dia) { items.drawImage(x + 50, y, IMG_DIARY,           true);  }
                if ( mul) { items.drawImage(x + 80, y, IMG_MULANA_TALISMAN, true);  }
            }

            break;
        }

        if (cur_istate[i][j] == new_istate[i][j]) { continue; }
        cur_istate[i][j] = new_istate[i][j];
        ItemsState *state = &cur_istate[i][j];

        int x = 40 * j;
        int y = 60 + 40 * i;
        if (i >  1) { y += 20; }
        if (i >  7) { y += 20; }
        if (i > 10) { y += 20; }

        int img = state->image & ITEM_IMG;
        int col = state->image & ITEM_COL;
        
        items.drawBG(x, y, 40, 40);
        items.drawImage(x, y, img, col);

        if (col) {
            if (img == IMG_GUN) {
                uint8_t clip = ((state->count >> 8) & 0x7F) % 10;
                uint8_t ammo = ((state->count >> 0) & 0x7F) % 10;
                items.drawImage(x + 16, y + 24, IMG_AMMO_0 + clip);
                items.drawImage(x + 24, y + 24, IMG_AMMO_COLON);
                items.drawImage(x + 30, y + 24, IMG_AMMO_0 + ammo);
            } else if (state->count & ITEM_COL) {
                items.drawCount(x, y, state->count & ITEM_IMG);
            }
        }

        if (img >= IMG_WEDGE_1 && img <= IMG_WEDGE_8) {
            int sub = state->sub_1 & ITEM_IMG;
            if (sub == IMG_ANKH) {
                items.drawImage(x + 10, y + 20, IMG_ANKH, true, 20, 20);
            } else if (sub == IMG_WEDGE_BROKEN) {
                items.drawImage(x, y, IMG_WEDGE_BROKEN, true);
            }
        } else if (state->sub_1 || state->sub_2) {
            int img_1 = state->sub_1 & ITEM_IMG;
            int col_1 = state->sub_1 & ITEM_COL;
            int img_2 = state->sub_2 & ITEM_IMG;
            int col_2 = state->sub_2 & ITEM_COL;

            if (img_2 && !col_2) { items.drawImage(x + 20, y + 20, img_2, false, 20, 20); }
            if (img_1 && !col_1) { items.drawImage(x + 10, y + 20, img_1, false, 20, 20); }
            if (img_2 &&  col_2) { items.drawImage(x + 20, y + 20, img_2, true,  20, 20); }
            if (img_1 &&  col_1) { items.drawImage(x + 10, y + 20, img_1, true,  20, 20); }
        }
    }

    items.update();
}
