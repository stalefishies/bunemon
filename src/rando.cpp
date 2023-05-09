#include "fields.hpp"
#include "bitmap.hpp"
#include "rando.hpp"
#include "data.h"

BunBitmap rando;

#define X(NAME, ...) TRANS_##NAME,
enum { X_TRANS TRANS_COUNT };
#undef X

#define X(NAME, ...) DOORS_##NAME,
enum { X_DOORS DOORS_COUNT };
#undef X

#define X(NAME, ...) CHARS_##NAME,
enum { X_CHARS CHARS_COUNT };
#undef X

#define X(NAME, ...) SEALS_##NAME,
enum { X_SEALS SEALS_COUNT };
#undef X

#define X(NAME, ...) SHOPS_##NAME,
enum { X_SHOPS SHOPS_COUNT };
#undef X

enum {
    RANDO_TRANS         = 0x00000001,
    RANDO_DOORS         = 0x00000002,
    RANDO_CHARS         = 0x00000004,
    RANDO_SEALS         = 0x00000008,
    RANDO_STARTING_SHOP = 0x00000010,
    RANDO_DRACUET_SHOP  = 0x00000020,
};

// Each place to mark as a check is a Location
struct Location {
    uint32_t flags;
    uint8_t  zone;
    uint8_t  room;
    uint8_t  screen;
    uint8_t  loc;
    float    x;
    float    y;
};

struct ShopData {
    uint16_t image[3];
    uint8_t  count[3];
    uint8_t  index;
};

struct RandoState {
    uint32_t flags;
    Location trans[TRANS_COUNT];
    Location doors[DOORS_COUNT];
    Location seals[SEALS_COUNT];
    Location chars[CHARS_COUNT];
    ShopData shops[SHOPS_COUNT];
};

RandoState vanilla_rstate = {
    .flags = 0,

#define X(TAG, FLAGS, IMG, Z, R, S, L, X, Y, STR_1, STR_2)  \
    { FLAGS, Z, R, S, L, X, Y },
    .trans = { X_TRANS },
    .doors = { X_DOORS },
    .seals = { X_SEALS },
    .chars = { X_CHARS },
#undef X

#define X(TAG, FLAGS, IMG, Z, R, S, L, X, Y, STR_1, STR_2)  \
    { {0}, {0}, L },
    .shops = { X_SHOPS }
#undef X
};

RandoState cur_rstate = vanilla_rstate;

struct LocData {
    uint32_t x;
    uint32_t y;
    String name;
    String spoiler;
};

#define X(TAG, FLAGS, IMG, Z, R, S, L, X, Y, STR_1, STR_2)  \
    { 0, 0, strLit(STR_2), strLit(STR_1) },
struct {
    LocData trans[TRANS_COUNT], doors[DOORS_COUNT],
        seals[SEALS_COUNT], chars[CHARS_COUNT];
} dat = {
    .trans = { X_TRANS },
    .doors = { X_DOORS },
    .seals = { X_SEALS },
    .chars = { X_CHARS }
};
#undef X

struct Parser {
    size_t length;
    const char *data;
    const char *at;

    Parser(const char *filename):
        length(0), data(NULL), at(NULL)
    {
        FILE *file = fopen(filename, "rb");
        if (file) {
            fseek(file, 0, SEEK_END);
            size_t filesize = ftell(file);
            fseek(file, 0, SEEK_SET);

            char *buffer = new (std::nothrow) char[filesize + 1];
            if (buffer) {
                size_t read_count = fread(buffer, 1, filesize, file);
                if (read_count == filesize) {
                    at = data = buffer;
                    length = filesize;
                    buffer[filesize] = '\0';
                } else {
                    delete[] buffer;
                }
            }

            fclose(file);
        }
    }

    ~Parser() {
        if (data) { delete[] data; }
    }

    void skipLine() {
        while (*at != '\r' && *at != '\n' && *at != '\0') { ++at; }
        while (*at == '\r' || *at == '\n') { ++at; }
        if (at > data + length) { at = data + length; }
    }

    void skipWhitespace() {
        while (*at == ' ' || *at == '\r' || *at == '\n') { ++at; }
        if (at > data + length) { at = data + length; }
    }

    bool findSection(String header) {
        const char *at_init = at;
        at = data;

        for (;;) {
            if (at + header.length > data + length) {
                at = at_init;
                return false;
            }

            bool match = true;
            for (int i = 0; match && i < header.length; ++i, ++at) {
                match = (*at == header.data[i]);
            }

            while (*at == ' ' && at < data + length) { ++at; }
            match = (match && (*at == '\r' || *at == '\n'));
            skipLine();

            if (match) { return true; }
        }
    }

    bool peek(String string) {
        if (at + string.length > data + length) { return false; }

        bool match = true;
        for (int i = 0; match && i < string.length; ++i) {
            match = (at[i] == string.data[i]);
        }

        return match;
    }

    bool accept(String string) {
        bool match = peek(string);
        if (match) { at += string.length; }
        return match;
    }

    int acceptLocation(size_t count, const LocData *list) {
        int index  = 0;
        int length = 0;

        for (int i = 0; i < count; ++i) {
            if (list[i].spoiler.length <= length) { continue; }
            if (peek(list[i].spoiler)) {
                index  = i;
                length = list[i].spoiler.length;
            }
        }

        at += length;
        return index;
    }

    int acceptTrans() { return acceptLocation(TRANS_COUNT, dat.trans); }
    int acceptDoors() { return acceptLocation(DOORS_COUNT, dat.doors); }
    int acceptSeals() { return acceptLocation(SEALS_COUNT, dat.seals); }
    int acceptChars() { return acceptLocation(CHARS_COUNT, dat.chars); }
};

// TODO: start with all transitions marked visible
// any transitions we see in the file are then marked not visible
// we end with vanilla transitions marked visible
// use those to mark the overall rstate flags with what is randomised
bool parseTrans(Parser &parser) {
    Location *trans = cur_rstate.trans;
    uint32_t mask = ~(FLAG_VISIBLE | FLAG_REVEALED);

    for (;;) {
        int index_lhs = parser.acceptTrans();
        if (index_lhs == 0) { break; }

        parser.skipWhitespace();
        bool pipe = parser.accept(strLit("<==(Pipe)==>"));
        if (!pipe) {
            if (!parser.accept(strLit("===========>"))
                && !parser.accept(strLit("<==========>")))
            { return false; }
        }

        parser.skipWhitespace();
        int index_rhs = parser.acceptTrans();
        if (index_rhs == 0) { return false; }

        uint32_t flags = FLAG_TRACKED;

        if (pipe) {
            if (trans[index_lhs].flags & FLAG_SCROLL_R) {
                trans[index_lhs].loc = TRANS_GOD_PIP_L;
                trans[index_lhs].flags &= mask;
                trans[index_lhs].flags |= flags;

                trans[TRANS_GOD_PIP_R].loc = index_rhs;
                trans[TRANS_GOD_PIP_R].flags &= mask;
                trans[TRANS_GOD_PIP_R].flags |= flags;
            } else if (trans[index_lhs].flags & FLAG_SCROLL_L) {
                trans[index_lhs].loc = TRANS_GOD_PIP_R;
                trans[index_lhs].flags &= mask;
                trans[index_lhs].flags |= flags;

                trans[TRANS_GOD_PIP_L].loc = index_rhs;
                trans[TRANS_GOD_PIP_L].flags &= mask;
                trans[TRANS_GOD_PIP_L].flags |= flags;
            } else { return false; }
        } else {
            trans[index_lhs].loc = index_rhs;
            trans[index_lhs].flags &= mask;
            trans[index_lhs].flags |= flags;

            if (index_rhs == TRANS_INF_LAVA) {
                trans[TRANS_INF_LAVA].loc = index_lhs;
                trans[TRANS_INF_LAVA].flags &= mask;
                trans[TRANS_INF_LAVA].flags |= flags;
            }
        }

        parser.skipLine();
    }

    return true;
}

bool parseDoors(Parser &parser) {
    Location *doors = cur_rstate.doors;
    uint32_t mask = ~(MASK_COND | FLAG_VISIBLE | FLAG_REVEALED);

    for (;;) {
        int index_lhs = parser.acceptDoors();
        if (index_lhs == 0) { break; }

        if (!parser.accept(strLit(" => "))) { return false; }

        uint32_t flags = FLAG_TRACKED;
        if      (parser.accept(strLit("Amphisbaena"))) { flags |= FLAG_BOSS_1; }
        else if (parser.accept(strLit("Sakit")      )) { flags |= FLAG_BOSS_2; }
        else if (parser.accept(strLit("Ellmac")     )) { flags |= FLAG_BOSS_3; }
        else if (parser.accept(strLit("Bahamut")    )) { flags |= FLAG_BOSS_4; }
        else if (parser.accept(strLit("Viy")        )) { flags |= FLAG_BOSS_5; }
        else if (parser.accept(strLit("Palenque")   )) { flags |= FLAG_BOSS_6; }
        else if (parser.accept(strLit("Baphomet")   )) { flags |= FLAG_BOSS_7; }
        else if (parser.accept(strLit("Key Fairy")  )) { flags |= FLAG_FAIRY;  }
        else if (!parser.accept(strLit("(Open)"))) { return false; }

        if (!parser.accept(strLit(" => "))) { return false; }

        int index_rhs = parser.acceptDoors();
        if (index_rhs == 0) { return false; }

        doors[index_lhs].loc    = index_rhs;
        doors[index_lhs].flags &= mask;
        doors[index_lhs].flags |= flags;

        if (index_rhs == DOORS_END) {
            doors[index_rhs].loc    = index_lhs;
            doors[index_rhs].flags &= mask;
            doors[index_rhs].flags |= (flags & ~FLAG_TRACKED);
        }

        parser.skipLine();
    }

    return true;
}

bool parseSeals(Parser &parser) {
    Location *seals = cur_rstate.seals;
    uint32_t mask = ~(FLAG_VISIBLE | FLAG_REVEALED);

    String headers[] = {
        strLit("Origin Seal:"),
        strLit("Birth Seal:"),
        strLit("Life Seal:"),
        strLit("Death Seal:")
    };

    for (int seal = 0; seal < 4; ++seal) {
        parser.findSection(headers[seal]);

        for (;;) {
            int index = parser.acceptSeals();
            if (index == 0) { break; }

            seals[index].loc    = seal;
            seals[index].flags &= mask;
            seals[index].flags |= FLAG_TRACKED;

            parser.skipLine();
        }
    }

    return true;
}

/*
bool parseShops(FILE *file, char buffer[256]) {
    ShopData *shops = cur_rstate.shops;

    shops[SHOPS_DRACUET].image[0] = IMG_FLARE;
    shops[SHOPS_DRACUET].count[0] = 0;
    shops[SHOPS_DRACUET].image[1] = IMG_BOMBS;
    shops[SHOPS_DRACUET].count[1] = 0;
    shops[SHOPS_DRACUET].image[2] = IMG_AMMO;
    shops[SHOPS_DRACUET].count[2] = 0;

    for (;;) {
        int index = SHOPS_INVALID;
        for (int i = 0; i < SHOPS_COUNT; ++i) {
            if (parse.accept(shops_spoiler[i])) {
                index = i;
                break;
            }
        }

        if (index <= SHOPS_INVALID || index >= SHOPS_COUNT) { break; }
    }

}
*/

bool initRando(const char *filename) {
    for (int i = 0; i < TRANS_COUNT; ++i) { cur_rstate.trans[i] = vanilla_rstate.trans[i]; }
    for (int i = 0; i < DOORS_COUNT; ++i) { cur_rstate.doors[i] = vanilla_rstate.doors[i]; }
    for (int i = 0; i < SEALS_COUNT; ++i) { cur_rstate.seals[i] = vanilla_rstate.seals[i]; }
    for (int i = 0; i < CHARS_COUNT; ++i) { cur_rstate.chars[i] = vanilla_rstate.chars[i]; }
    std::memset(cur_rstate.shops, 0x00, SHOPS_COUNT * sizeof cur_rstate.shops[0]);

    Parser parser(filename);
    if (!parser.data) { return false; }

    bool error = false;

    /*
    bool found_shops = false;
    fseek(file, 0, SEEK_SET);
    while (!feof(file) && fgets(buffer, 256, file)) {
        if (!strcmp(buffer, "Shops:\n")) {
            found_shops = parseShops(file, buffer);
            break;
        }
    }
    if (!found_shops) { return false; }
    */

    if (parser.findSection(strLit("Transitions:"))) {
        if (!parseTrans(parser)) { error = true; }
        cur_rstate.flags |= RANDO_TRANS;
    }

    if (parser.findSection(strLit("Backside Doors:"))) {
        if (!parseDoors(parser)) { error = true; }
        cur_rstate.flags |= RANDO_DOORS;
    }

    if (parser.findSection(strLit("Origin Seal:"))
        || parser.findSection(strLit("Birth Seal:"))
        || parser.findSection(strLit("Life Seal:"))
        || parser.findSection(strLit("Death Seal:")))
    {
        if (!parseSeals(parser)) { error = true; }
        cur_rstate.flags |= RANDO_SEALS;
    }

    cur_rstate.flags |= RANDO_CHARS;

    // TODO: resize rando
    rando.drawBG(0, 0, rando.width, rando.height);

    int centre = rando.width / 2;
    int y = 0;

    if (cur_rstate.flags & RANDO_TRANS) {
        rando.drawText(0, y, 0, strLit("TRANSITIONS"), true);
        y += 44;

        for (int i = 0; i < TRANS_COUNT; ++i) {
            if (!(cur_rstate.trans[i].flags & FLAG_TRACKED)) { continue; }
            rando.drawText(0, y, RANDO_W, dat.trans[i].name);

            rando.drawCoord(centre - 70, y, 
                cur_rstate.trans[i].zone,
                cur_rstate.trans[i].room,
                cur_rstate.trans[i].screen);
            rando.drawImage(centre - 10, y, IMG_ARROWR);
            rando.drawImage(centre + 20, y, IMG_QUESTION);

            dat.trans[i].x = 0;
            dat.trans[i].y = y;
            y += 22;
        }
    }

    if (cur_rstate.flags & RANDO_DOORS) {
        y += 44;
        rando.drawText(0, y, 0, strLit("BACKSIDE DOORS"), true);
        y += 44;

        for (int i = 0; i < DOORS_COUNT; ++i) {
            if (!(cur_rstate.doors[i].flags & FLAG_TRACKED)) { continue; }
            rando.drawText(0, y, RANDO_W, dat.doors[i].name);

            rando.drawCoord(centre - 80, y, 
                cur_rstate.doors[i].zone,
                cur_rstate.doors[i].room,
                cur_rstate.doors[i].screen);

            if (cur_rstate.doors[i].flags & MASK_COND) {
                if (cur_rstate.doors[i].flags & FLAG_BOSS_1) {
                    rando.drawImage(centre - 10, y, IMG_WEDGE_1, true, 20, 20);
                } else if (cur_rstate.doors[i].flags & FLAG_BOSS_2) {
                    rando.drawImage(centre - 10, y, IMG_WEDGE_2, true, 20, 20);
                } else if (cur_rstate.doors[i].flags & FLAG_BOSS_3) {
                    rando.drawImage(centre - 10, y, IMG_WEDGE_3, true, 20, 20);
                } else if (cur_rstate.doors[i].flags & FLAG_BOSS_4) {
                    rando.drawImage(centre - 10, y, IMG_WEDGE_4, true, 20, 20);
                } else if (cur_rstate.doors[i].flags & FLAG_BOSS_5) {
                    rando.drawImage(centre - 10, y, IMG_WEDGE_5, true, 20, 20);
                } else if (cur_rstate.doors[i].flags & FLAG_BOSS_6) {
                    rando.drawImage(centre - 10, y, IMG_WEDGE_6, true, 20, 20);
                } else if (cur_rstate.doors[i].flags & FLAG_BOSS_7) {
                    rando.drawImage(centre - 10, y, IMG_WEDGE_7, true, 20, 20);
                } else if (cur_rstate.doors[i].flags & FLAG_FAIRY) {
                    rando.drawImage(centre - 10, y, IMG_KEY_DOOR);
                }
            } else {
                rando.drawImage(centre - 10, y, IMG_ARROWR);
            }

            rando.drawImage(centre + 40, y, IMG_QUESTION);

            dat.doors[i].x = 0;
            dat.doors[i].y = y;
            y += 22;
        }
    }

    if (cur_rstate.flags & RANDO_SEALS) {
        y += 44;
        rando.drawText(0, y, 0, strLit("WALL SEALS"), true);
        y += 44;

        int count[4] = {};
        for (int i = 0; i < SEALS_COUNT; ++i) {
            if (!(cur_rstate.seals[i].flags & FLAG_TRACKED)) { continue; }
            ++count[cur_rstate.seals[i].loc];
        }

        int top   = y;
        int bot_1 = y;
        int bot_2 = y;

        for (int seal = 0; seal < 4; ++seal) {
            int x = (seal % 2 ? centre : 0);
            if (seal <= 1) { y = top;        }
            if (seal >= 2) { y = bot_1 + 22; }

            for (int i = 0; i < SEALS_COUNT; ++i) {
                if (!(cur_rstate.seals[i].flags & FLAG_TRACKED)) { continue; }
                if (cur_rstate.seals[i].loc != seal) { continue; }

                rando.drawImage(x, y, IMG_LM_1 + seal);
                rando.drawText(x + 30, y, RANDO_W, dat.seals[i].name);

                dat.trans[i].x = x;
                dat.seals[i].y = y;

                y += 22;
            }

            if (seal <= 1 && y > bot_1) { bot_1 = y; }
            if (seal >= 2 && y > bot_2) { bot_2 = y; }
        }

        y = bot_2;
    }

    if (cur_rstate.flags & RANDO_CHARS) {
        y += 44;
        rando.drawText(0, y, 0, strLit("NPCS"), true);
        y += 44;

        for (int i = 0; i < CHARS_COUNT; ++i) {
            //if (!(cur_rstate.chars[i].flags & FLAG_TRACKED)) { continue; }
            rando.drawText(0, y, RANDO_W, dat.chars[i].name);
            dat.chars[i].x = 0;
            dat.chars[i].y = y;
            y += 22;
        }
    }

    rando.update();

    return !error;
}

void updateRando(LMMemory *memory) {
    for (int i = 1; i < TRANS_COUNT; ++i) {
        Location *loc = &cur_rstate.trans[i];
        if (loc->loc <= 0 || loc->loc > TRANS_COUNT) { continue; }
        Location *dest = &cur_rstate.trans[loc->loc];

        bool redraw = false;
        if (loc->flags != FLAGS_NONE
            && memory->prev_zone   == loc->zone
            && memory->prev_room   == loc->room
            && memory->prev_screen == loc->screen
            && memory->zone        == dest->zone
            && memory->room        == dest->room
            && memory->screen      == dest->screen
            && ((loc->flags & FLAG_INPUT
                    && memory->prev_x >= loc->x - 20
                    && memory->prev_x <= loc->x + 20
                    && memory->prev_y >= loc->y - 20
                    && memory->prev_y <= loc->y + 20)
                || (loc->flags & FLAG_SCROLL_L && memory->prev_x <    0)
                || (loc->flags & FLAG_SCROLL_R && memory->prev_x >= 600)
                || (loc->flags & FLAG_SCROLL_U && memory->prev_y <   -8)
                || (loc->flags & FLAG_SCROLL_D && memory->prev_y >= 432)))
        {
            redraw = true;
            loc->flags |= FLAG_VISIBLE;
            if (i != TRANS_END_TOP_L) { dest->flags |= FLAG_VISIBLE; }
        }

        if (redraw) {
            int y = dat.trans[i].y;
            rando.drawBG(0, y, rando.width, 20);

            rando.drawImage(300, y, IMG_ARROWR);
            rando.drawText(320, y, RANDO_W - 320, dat.trans[loc->loc].name);
        }
    }

    rando.update();
}
