#include "fields.hpp"

bool fieldCoord(int zone, int room, int screen, int *x, int *y) {
    FieldPosition pos = {0};
    if (zone >= 0 && zone < FIELD_MAX_ZONE
        && room >= 0 && room < FIELD_MAX_ROOM)
    { pos = field_pos[zone][room]; }

    if (pos.exists) {
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
                *x = pos.x + screen % pos.w;
            }
        }

        if (y) { *y = pos.y + screen / pos.w; }
        return true;
    }

    return false;
}

const String field_name[FIELD_MAX_ZONE] = {
    /*  0 */ strLit("Gate of Guidance"),
    /*  1 */ strLit("Surface"),
    /*  2 */ strLit("Mausoleum of the Giants"),
    /*  3 */ strLit("Temple of the Sun"),
    /*  4 */ strLit("Spring in the Sky"),
    /*  5 */ strLit("Inferno Cavern"),
    /*  6 */ strLit("Chamber of Extinction"),
    /*  7 */ strLit("Twin Labyrinths"),
    /*  8 */ strLit("Endless Corridor"),
    /*  9 */ strLit("Shrine of the Mother"),
    /* 10 */ strLit("Gate of Illusion"),
    /* 11 */ strLit("Graveyard of the Giants"),
    /* 12 */ strLit("Temple of Moonlight"),
    /* 13 */ strLit("Tower of the Goddess"),
    /* 14 */ strLit("Tower of Ruin"),
    /* 15 */ strLit("Chamber of Birth"),
    /* 16 */ strLit("Chamber of Birth"),
    /* 17 */ strLit("Dimensional Corridor"),
    /* 18 */ strLit("Shrine of the Mother"),
    /* 19 */ strLit("Gate of Time"),
    /* 20 */ strLit("Gate of Time"),
    /* 21 */ strLit("Gate of Time"),
    /* 22 */ strLit("Surface"),
    /* 23 */ strLit("Hell Temple"),
    /* 24 */ strLit("Hell Temple"),
    /* 25 */ strLit("Burning Cavern")
};

const uint8_t field_width[FIELD_MAX_ZONE] = {
    /*        0   1   2   3   4   5   6   7   8   9 */
    /* 00 */  7, 12,  8,  7,  5,  7,  9, 10,  5,  6,
    /* 10 */  7,  7,  6,  5,  7,  9,  9,  4,  6,  7,
    /* 20 */  7,  7, 12,  5,  5,  1
};

const uint8_t field_height[FIELD_MAX_ZONE] = {
    /*        0   1   2   3   4   5   6   7   8   9 */
    /* 00 */  6,  5,  6,  6, 10,  6,  5,  5,  5,  6,
    /* 10 */  6,  6,  6,  9,  6,  6,  6,  7,  6, 11,
    /* 20 */ 11, 11,  5, 11, 11, 20
};

const LMRoomPosition field_pos[FIELD_MAX_ZONE][FIELD_MAX_ROOM] = {
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

const uint8_t field_rooms[FIELD_MAX_ZONE] = {
    /*        0   1   2   3   4   5   6   7   8   9 */
    /* 00 */ 10, 12, 10,  9,  9, 10, 10, 17,  6, 10,
    /* 10 */ 10, 10, 11,  9,  9,  5,  5, 11, 10,  5,
    /* 20 */  5,  1, 11, 23,  3,  4
};

const String room_names_00[10] = {
    strLit("Pillar's Gate"),
    strLit("Heavenly Temple of the Cross"),
    strLit("Room of Courage"),
    strLit("Heavenly Corridor"),
    strLit("Pit of the Holy Grail"),
    strLit("Door to Eden"),
    strLit("Gate of Giant Faces"),
    strLit("Monument of Oannes"),
    strLit("Snake's Sanctuary"),
    strLit("Monument of Time")
};

const String room_names_01[12] = {
    strLit("Altar Hill"),
    strLit("Cliff in front of the Altar"),
    strLit("Village of Departure"),
    strLit("Gate of Departure"),
    strLit("Sound Canyon"),
    strLit("Gazing Hill"),
    strLit("Bahrun's Waterfall"),
    strLit("Bahrun's Waterfall"),
    strLit("Waterfall of the Goddess"),
    strLit("Outskirts of the Village"),
    strLit("Foothill"),
    strLit("Mother's Split Gate")
};

const String room_names_02[10] = {
    strLit("Last Shrine"),
    strLit("Approach of the Giants"),
    strLit("Room of Redemption"),
    strLit("Shrine of the Giants"),
    strLit("Zebu's Room"),
    strLit("Shaft to the Heavens"),
    strLit("Monument to Hermes"),
    strLit("Star Palace of the Giants"),
    strLit("Moon Palace of the Giants"),
    strLit("Nebra Sky Disk")
};

const String room_names_03[9] = {
    strLit("Watchtower"),
    strLit("Altar of War"),
    strLit("Isis' Room"),
    strLit("Thoth's Room"),
    strLit("Great Colonnade, Left-Side Room"),
    strLit("Altar of Mirrors"),
    strLit("Sanctuary"),
    strLit("Horus' Room of Pillars"),
    strLit("Aten's Room")
};

const String room_names_04[9] = {
    strLit("Mural of Oannes"),
    strLit("Goddess' Water Jug"),
    strLit("Sacred Lake"),
    strLit("Waterfall Approach"),
    strLit("Sanctuary"),
    strLit("Room of Origin"),
    strLit("Mirror Waterfall"),
    strLit("Oannes' Waterfall"),
    strLit("Anunnaki's Stone Basin")
};

const String room_names_05[10] = {
    strLit("Statue of the Giant"),
    strLit("Twin's Footstool"),
    strLit("Pit of Fire"),
    strLit("Pazuzu's Room"),
    strLit("Serdab of Light"),
    strLit("Anterior Chamber"),
    strLit("Hall of Worship"),
    strLit("Treasury of Ice"),
    strLit("Darkness Sanctuary"),
    strLit("Echidna's Chamber")
};

const String room_names_06[10] = {
    strLit("Approach to the Sanctuary"),
    strLit("Gate of Ox-Head and Horse-Face"),
    strLit("Mural of Invocation"),
    strLit("Darkness Approach"),
    strLit("Mural Depicting the Power of Words"),
    strLit("Side Path"),
    strLit("Mural of Light"),
    strLit("Path of Life"),
    strLit("Shiva's Crucifix"),
    strLit("Anterior Chamber")
};

const String room_names_07[17] = {
    strLit("Hero's Approach"),
    strLit("Sanctuary"),
    strLit("Zodiac"),
    strLit("Twin's Surrounding Wall"),
    strLit("Demon Altar"),
    strLit("Zu's Room"),
    strLit("Treasury"),
    strLit("Idigna's Room"),
    strLit("Hero's Surrounding Wall"),
    strLit("Hero's Approach"),
    strLit("Sanctuary"),
    strLit("Zodiac"),
    strLit("Twin's Surrounding Wall"),
    strLit("Demon Altar"),
    strLit("Treasury"),
    strLit("Hero's Surrounding Wall"),
    strLit("Poseidon's Room")
};

const String room_names_08[6] = {
    strLit("First Endless Corridor"),
    strLit("First Endless Corridor"),
    strLit("Second Endless Corridor"),
    strLit("Third Endless Corridor"),
    strLit("Fourth Endless Corridor"),
    strLit("Fifth Endless Corridor")
};

const String room_names_09[10] = {
    strLit("Amphisbaena's Room"),
    strLit("Sakit's Room"),
    strLit("Ellmac's Room"),
    strLit("Home of the Mother"),
    strLit("Baphomet's Room"),
    strLit("Palenque's Room"),
    strLit("Viy's Room"),
    strLit("Beelzebub's Room"),
    strLit("Bahamut's Room"),
    strLit("Treasury")
};

const String room_names_10[10] = {
    strLit("Bird's Room"),
    strLit("Children's Room"),
    strLit("Sacrificial Abyss"),
    strLit("Doorway to Guidance"),
    strLit("Chapel"),
    strLit("Lizard's Room"),
    strLit("Mausoleum of Fairies"),
    strLit("Fool's Confusion Corridor"),
    strLit("Sacred Lake of the Sky"),
    strLit("Entrance of Illusion")
};

const String room_names_11[10] = {
    strLit("First Tomb"),
    strLit("White Silver Altar"),
    strLit("Second Tomb"),
    strLit("Abuto's Tomb"),
    strLit("Path to the Graveyard"),
    strLit("Third Tomb"),
    strLit("Altar of Power"),
    strLit("Anterior Chamber"),
    strLit("Spirit of Language Altar"),
    strLit("Altar of Knowledge")
};

const String room_names_12[11] = {
    strLit("Boneyard"),
    strLit("Stairway of Eden"),
    strLit("Neptune's Feet"),
    strLit("Serdab of Power"),
    strLit("Moon-Gazing Pit"),
    strLit("Moon Pyramid: Burial Chamber"),
    strLit("Moon Watchtower"),
    strLit("Serdab of Treasure"),
    strLit("Sealed Approach"),
    strLit("Path to the Underworld"),
    strLit("Underworld Palace")
};

const String room_names_13[9] = {
    strLit("Urtharbrunnr"),
    strLit("Anterior Chamber"),
    strLit("Urd's Tower"),
    strLit("Verdandi's Tower"),
    strLit("Verdandi's Tower"),
    strLit("Scales of the Heart"),
    strLit("Skuld's Tower"),
    strLit("Skuld's Tower"),
    strLit("Urd's Tower")
};

const String room_names_14[9] = {
    strLit("Fountain of Heat"),
    strLit("Monument of Name"),
    strLit("Tower of Babel"),
    strLit("Serdab of Time"),
    strLit("One Who Reads Tablets"),
    strLit("Approach of the Philosophers"),
    strLit("Approach of Life"),
    strLit("Burial Chamber of Life"),
    strLit("N#wa's Pyramid")
};

const String room_names_15[5] = {
    strLit("Saraswati's Room"),
    strLit("Surrounding Wall of Spikes"),
    strLit("Shiva's Room"),
    strLit("Vishnu's Room"),
    strLit("Parvati's Room")
};

const String room_names_16[5] = {
    strLit("Deva's Room"),
    strLit("Brahma's Room"),
    strLit("Asura's Room"),
    strLit("Skanda's Room"),
    strLit("Hanuman's Room")
};

const String room_names_17[11] = {
    strLit("Ashnar's Room"),
    strLit("Ea's Room"),
    strLit("Kuusarikku's Room"),
    strLit("Ushum's Room"),
    strLit("Lahmu's Room"),
    strLit("Ugallu's Room"),
    strLit("Mushussu's Room"),
    strLit("Urmahlullu's Room"),
    strLit("Marduk's Room"),
    strLit("Tiamat's Room"),
    strLit("Anu's Room")
};

const String room_names_19[5] = {
    strLit("Shaft to the Heavens"),
    strLit("Star Palace of the Giants"),
    strLit("Zebu's Room"),
    strLit("Room of Redemption"),
    strLit("Last Shrine")
};

const String room_names_20[5] = {
    strLit("Monument of Time"),
    strLit("Pit of the Holy Grail"),
    strLit("Heavenly Corridor"),
    strLit("Heavenly Temple of the Cross"),
    strLit("Pillar's Gate")
};

const String room_names_21[1] = {
    strLit("Village of Departure"),
};

const String room_names_23[23] = {
    strLit("Room 0"),
    strLit("Room 1"),
    strLit("Room 3"),
    strLit("HELL"),
    strLit("Room 6"),
    strLit("Room 7"),
    strLit("Room 10"),
    strLit("HELL"),
    strLit("13"),
    strLit("15"),
    strLit("17"),
    strLit("HELL"),
    strLit("Room 20"),
    strLit("Room 21"),
    strLit("Room 24"),
    strLit("Room 25"),
    strLit("HELL"),
    strLit("HELL"),
    strLit("Room 27"),
    strLit("Room 29"),
    strLit("Room 30"),
    strLit("Room 33"),
    strLit("Room 35")
};

const String room_names_24[3] = {
    strLit("Room 11"),
    strLit("Room 19"),
    strLit("Room 31")
};

const String room_names_25[4] = {
    strLit("?"),
    strLit("?"),
    strLit("?"),
    strLit("?")
};

const String *room_names[FIELD_MAX_ZONE] = {
    room_names_00, room_names_01, room_names_02, room_names_03,
    room_names_04, room_names_05, room_names_06, room_names_07,
    room_names_08, room_names_09, room_names_10, room_names_11,
    room_names_12, room_names_13, room_names_14, room_names_15,
    room_names_16, room_names_17, room_names_09, room_names_19,
    room_names_20, room_names_21, room_names_01, room_names_23,
    room_names_24, room_names_25
};

const String fieldRoom(int zone, int room, int screen) {
    const String invalid = {};
    if (zone < 0 || zone >= FIELD_MAX_ZONE
        || room < 0 || room >= field_rooms[zone]
        || screen < 0 || screen >= FIELD_MAX_SCREEN)
    { return invalid; }

    if      (zone == 18) { zone = 9; }
    else if (zone == 22) { zone = 1; }

    if      (zone ==  0 && room ==  6 && screen == 1) { return strLit("Room of the Strong");               }
    else if (zone ==  0 && room ==  7 && screen == 1) { return strLit("Cliff of Radiance");                }
    else if (zone ==  1 && room ==  5 && screen == 2) { return strLit("Underground Passage");              }
    else if (zone ==  1 && room == 10 && screen == 3) { return strLit("Gate of Departure");                }
    else if (zone ==  1 && room == 11 && screen == 1) { return strLit("Entrance to La-Mulana Ruins");      }
    else if (zone ==  2 && room ==  6 && screen == 1) { return strLit("Dolphin's Room");                   }
    else if (zone ==  3 && room ==  1 && screen == 0) { return strLit("Hathor's Room");                    }
    else if (zone ==  3 && room ==  2 && screen == 1) { return strLit("Isis' Anterior Chamber");           }
    else if (zone ==  3 && room ==  4 && screen == 1) { return strLit("Sun Pyramid");                      }
    else if (zone ==  3 && room ==  4 && screen == 4) { return strLit("Sun Pyramid: Burial Chamber");      }
    else if (zone ==  3 && room ==  4 && screen == 2) { return strLit("Great Colonnade, Right-Side Room"); }
    else if (zone ==  3 && room ==  4 && screen == 5) { return strLit("Great Colonnade, Right-Side Room"); }
    else if (zone ==  4 && room ==  2 && screen == 1) { return strLit("Goddess' Water Jug");               }
    else if (zone ==  5 && room ==  3 && screen == 0) { return strLit("Pylon of Power");                   }
    else if (zone ==  6 && room ==  7 && screen == 1) { return strLit("Lake of Life");                     }
    else if (zone ==  6 && room ==  9 && screen == 1) { return strLit("Palenque's Coffin");                }
    else if (zone ==  7 && room == 15 && screen == 2) { return strLit("Buranun's Room");                   }
    else if (zone ==  7 && room == 16 && screen == 0) { return strLit("Peryton's Room");                   }
    else if (zone ==  9 && room ==  3 && screen == 1) { return strLit("Tiamat's Room");                    }
    else if (zone == 10 && room ==  0 && screen == 1) { return strLit("Cog of Life");                      }
    else if (zone == 10 && room ==  2 && screen == 2) { return strLit("Chi You's Room");                   }
    else if (zone == 12 && room ==  5 && screen == 1) { return strLit("Moon Pyramid");                     }
    else if (zone == 13 && room ==  7 && screen == 0) { return strLit("Path of Life");                     }
    else if (zone == 13 && room ==  7 && screen == 2) { return strLit("Path of Power");                    }
    else if (zone == 14 && room ==  3 && screen == 1) { return strLit("Tower of Babilu");                  }
    else if (zone == 14 && room ==  4 && screen == 1) { return strLit("Concubine");                        }
    else if (zone == 16 && room ==  4 && screen == 1) { return strLit("Ganesha's Room");                   }
    else if (zone == 16 && room ==  4 && screen == 2) { return strLit("Lakshimi's Room");                  }
    else if (zone == 17 && room ==  0 && screen == 1) { return strLit("Kishar's Room");                    }
    else if (zone == 17 && room ==  1 && screen == 1) { return strLit("Kulullu's Room");                   }
    else if (zone == 17 && room ==  2 && screen == 1) { return strLit("Girtablilu's Room");                }
    else if (zone == 17 && room ==  4 && screen == 1) { return strLit("Lahamu's Room");                    }
    else if (zone == 17 && room ==  5 && screen == 1) { return strLit("Abzu's Room");                      }
    else if (zone == 17 && room ==  7 && screen == 1) { return strLit("Enlil's Room");                     }
    else if (zone == 17 && room ==  8 && screen == 1) { return strLit("Mushnahhu's Room");                 }
    else if (zone == 17 && room ==  9 && screen == 1) { return strLit("Umu Dabrutu's Room");               }
    else if (zone == 17 && room == 10 && screen == 1) { return strLit("Ushumgallu's Room");                }
    else if (zone == 19 && room ==  2 && screen == 1) { return strLit("Shaft to the Heavens");             }
    else if (zone == 21 && room ==  0 && screen == 1) { return strLit("Entrance to La-Mulana Ruins");      }
    else if (zone == 23 && room ==  1 && screen == 1) { return strLit("Room 2");                           }
    else if (zone == 23 && room ==  2 && screen == 1) { return strLit("Room 4");                           }
    else if (zone == 23 && room ==  4 && screen == 1) { return strLit("Room 5");                           }
    else if (zone == 23 && room ==  5 && screen == 1) { return strLit("Room 8");                           }
    else if (zone == 23 && room ==  6 && screen == 1) { return strLit("Room 9");                           }
    else if (zone == 23 && room ==  8 && screen == 1) { return strLit("Room 14");                          }
    else if (zone == 23 && room ==  9 && screen == 1) { return strLit("Room 16");                          }
    else if (zone == 23 && room == 10 && screen == 1) { return strLit("Room 18");                          }
    else if (zone == 23 && room == 12 && screen == 1) { return strLit("Room 22");                          }
    else if (zone == 23 && room == 14 && screen == 1) { return strLit("Room 23");                          }
    else if (zone == 23 && room == 15 && screen == 1) { return strLit("Room 26");                          }
    else if (zone == 23 && room == 18 && screen == 1) { return strLit("Room 28");                          }
    else if (zone == 23 && room == 22 && screen == 1) { return strLit("Room 34");                          }
    else if (zone == 24 && room ==  0 && screen == 1) { return strLit("Room 12");                          }
    else if (zone == 24 && room ==  2 && screen == 1) { return strLit("Room 32");                          }
    else { return room_names[zone][room]; }
}
