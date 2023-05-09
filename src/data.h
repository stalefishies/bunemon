#ifndef DATA_HGUARD
#define DATA_HGUARD

enum {
    MASK_INTERACT = 0x0000001F,
    FLAG_SCROLL_L = 0x00000001,
    FLAG_SCROLL_R = 0x00000002,
    FLAG_SCROLL_U = 0x00000004,
    FLAG_SCROLL_D = 0x00000008,
    FLAG_INPUT    = 0x00000010,

    MASK_COND     = 0x0000FFE0,
    FLAG_EDEN     = 0x00000020,
    FLAG_SKANDA   = 0x00000040,
    FLAG_FAIRY    = 0x00000080,
    FLAG_BOSS_1   = 0x00000100,
    FLAG_BOSS_2   = 0x00000200,
    FLAG_BOSS_3   = 0x00000400,
    FLAG_BOSS_4   = 0x00000800,
    FLAG_BOSS_5   = 0x00001000,
    FLAG_BOSS_6   = 0x00002000,
    FLAG_BOSS_7   = 0x00004000,
    FLAG_4_BOSSES = 0x00008000,

    FLAG_TRACKED  = 0x00010000,
    FLAG_VISIBLE  = 0x00020000,
    FLAG_REVEALED = 0x00040000,
    FLAG_SHOP     = 0x00080000,

    FLAGS_NONE    = 0x00000000,
    FLAGS_L = FLAG_INPUT | FLAG_SCROLL_L,
    FLAGS_R = FLAG_INPUT | FLAG_SCROLL_R,
    FLAGS_U = FLAG_INPUT | FLAG_SCROLL_U,
    FLAGS_D = FLAG_INPUT | FLAG_SCROLL_D,
};


/********
 * TRANSITION DATA
 */

#define X_TRANS                                                             \
    X(INVALID, FLAGS_NONE,                                                  \
        INVALID,                                                            \
        255, 0, 0, 0, 0, 0,                                                 \
        "Invalid transition",                                               \
        "Invalid transition")                                               \
    X(SUR_MAIN, FLAGS_R,                                                    \
        INVALID,                                                            \
        1, 11, 1, 4, 590, 312,                                              \
        "Surface (Entrance to La-Mulana Ruins)",                            \
        "Surface Ruins Entrance")                                           \
    X(SUR_LAD_L, FLAGS_D,                                                   \
        INVALID,                                                            \
        1, 4, 2, 19, 440, 412,                                              \
        "Surface (Sound Canyon)",                                           \
        "Surface Hidden Ladder Left")                                       \
    X(SUR_LAD_R, FLAGS_D,                                                   \
        INVALID,                                                            \
        1, 5, 2, 24, 440, 412,                                              \
        "Surface (Underground Passage)",                                    \
        "Surface Hidden Ladder Right")                                      \
    X(GUI_TOP_L, FLAGS_L,                                                   \
        INVALID,                                                            \
        0, 0, 0, 1, 11, 312,                                                \
        "Gate of Guidance (Pillars Gate)",                                  \
        "Guidance Top Left")                                                \
    X(GUI_TOP_R, FLAGS_U,                                                   \
        INVALID,                                                            \
        0, 2, 1, 15, 540, 16,                                               \
        "Gate of Guidance (Room of Courage)",                               \
        "Guidance Top Right")                                               \
    X(GUI_BOT_L, FLAGS_D,                                                   \
        INVALID,                                                            \
        0, 9, 0, 8, 60, 412,                                                \
        "Gate of Guidance (Monument of Time)",                              \
        "Guidance Bottom Left")                                             \
    X(GUI_BOT_R, FLAGS_D,                                                   \
        INVALID,                                                            \
        0, 7, 1, 11, 540, 412,                                              \
        "Gate of Guidance (Cliff of Radiance)",                             \
        "Guidance Bottom Right")                                            \
    X(MAU_TOP_L, FLAGS_U,                                                   \
        INVALID,                                                            \
        2, 0, 0, 6, 60, 16,                                                 \
        "Mausoleum of the Giants (Last Shrine)",                            \
        "Mausoleum Top Left")                                               \
    X(MAU_BOT_L, FLAGS_L,                                                   \
        INVALID,                                                            \
        2, 8, 0, 30, 11, 312,                                               \
        "Mausoleum of the Giants (Moon Palace of the Giants)",              \
        "Mausoleum Bottom Left")                                            \
    X(MAU_BOT_R, FLAGS_D,                                                   \
        INVALID,                                                            \
        2, 7, 2, 25, 480, 412,                                              \
        "Mausoleum of the Giants (Star Palace of the Giants)",              \
        "Mausoleum Bottom Right")                                           \
    X(SUN_TOP, FLAGS_U,                                                     \
        INVALID,                                                            \
        3, 0, 0, 7, 540, 16,                                                \
        "Temple of the Sun (Watchtower)",                                   \
        "Sun Top")                                                          \
    X(SUN_LEFT, FLAGS_L,                                                    \
        INVALID,                                                            \
        3, 2, 1, 16, 11, 152,                                               \
        "Temple of the Sun (Isis' Anterior Chamber)",                       \
        "Sun Left")                                                         \
    X(SUN_EXT_U, FLAGS_R,                                                   \
        INVALID,                                                            \
        3, 5, 0, 20, 590, 72,                                               \
        "Temple of the Sun (Altar of Mirrors) (Upper)",                     \
        "Sun Bottom Right (Upper)")                                         \
    X(SUN_EXT_L, FLAGS_R,                                                   \
        INVALID,                                                            \
        3, 5, 0, 21, 590, 232,                                              \
        "Temple of the Sun (Altar of Mirrors) (Lower)",                     \
        "Sun Bottom Right (Lower)")                                         \
    X(SPR_MAIN, FLAGS_D,                                                    \
        INVALID,                                                            \
        4, 0, 2, 5, 540, 412,                                               \
        "Spring in the Sky (Mural of Oannes)",                              \
        "Spring Ladder")                                                    \
    X(INF_TOP_R, FLAGS_R,                                                   \
        INVALID,                                                            \
        5, 0, 1, 12, 590, 152,                                              \
        "Inferno Cavern (Statue of the Giant)",                             \
        "Inferno Top Right")                                                \
    X(INF_TOP, FLAGS_U,                                                     \
        INVALID,                                                            \
        5, 1, 0, 28, 60, 16,                                                \
        "Inferno Cavern (Twin's Footstool)",                                \
        "Inferno Top")                                                      \
    X(INF_LAVA, FLAG_SCROLL_D,                                              \
        INVALID,                                                            \
        5, 5, 1, 23, 0, 0,                                                  \
        "Inferno Cavern (Anterior Chamber)",                                \
        "Inferno Lava Pit")                                                 \
    X(INF_ECH, FLAGS_U,                                                     \
        INVALID,                                                            \
        5, 9, 1, 2, 440, 16,                                                \
        "Inferno Cavern (Echidna's Chamber)",                               \
        "Inferno Echidna Right")                                            \
    X(EXT_SUN_U, FLAGS_L,                                                   \
        INVALID,                                                            \
        6, 2, 0, 13, 11, 72,                                                \
        "Chamber of Extinction (Mural of Invocation) (Upper)",              \
        "Extinction Top Left (Upper)")                                      \
    X(EXT_SUN_L, FLAGS_L,                                                   \
        INVALID,                                                            \
        6, 2, 0, 14, 11, 232,                                               \
        "Chamber of Extinction (Mural of Invocation) (Lower)",              \
        "Extinction Top Left (Lower)")                                      \
    X(EXT_MOTHER, FLAGS_U,                                                  \
        INVALID,                                                            \
        6, 7, 1, 35, 300, 16,                                               \
        "Chamber of Extinction (Lake of Life)",                             \
        "Extinction Mother Ladder")                                         \
    X(EXT_PALENQUE, FLAGS_U,                                                \
        INVALID,                                                            \
        6, 1, 1, 18, 440, 16,                                               \
        "Chamber of Extinction (Shiva's Crucifix) ",                        \
        "Extinction Palenque Ladder")                                       \
    X(EXT_MAGATAMA, FLAGS_U,                                                \
        INVALID,                                                            \
        6, 8, 1, 3, 40, 16,                                                 \
        "Chamber of Extinction (Gate of Ox-Head and Horse-Face) ",          \
        "Extinction Magatama Ladder")                                       \
    X(LAB_TOP_L, FLAGS_U,                                                   \
        INVALID,                                                            \
        7, 3, 0, 10, 480, 16,                                               \
        "Twin Labyrinths (Twin's Surrounding Wall)",                        \
        "Twin Top Left (Mausoleum)")                                        \
    X(LAB_TOP_M, FLAGS_U,                                                   \
        INVALID,                                                            \
        7, 9, 1, 37, 300, 16,                                               \
        "Twin Labyrinths (Hero's Approach)",                                \
        "Twin Top Center (Mother)")                                         \
    X(LAB_TOP_R, FLAGS_U,                                                   \
        INVALID,                                                            \
        7, 10, 1, 64, 120, 16,                                              \
        "Twin Labyrinths (Sanctuary)",                                      \
        "Twin Top Right (Skull)")                                           \
    X(LAB_BOT_L, FLAGS_D,                                                   \
        INVALID,                                                            \
        7, 7, 0, 17, 60, 412,                                               \
        "Twin Labyrinths (Idigna's Room)",                                  \
        "Twin Bottom Left (Fairy)")                                         \
    X(LAB_BOT_R, FLAGS_D,                                                   \
        INVALID,                                                            \
        7, 16, 2, 48, 540, 412,                                             \
        "Twin Labyrinths (Poseidon's Room)",                                \
        "Twin Bottom Right (Elevator)")                                     \
    X(END_TOP_R, FLAGS_R,                                                   \
        INVALID,                                                            \
        8, 0, 1, 9, 590, 312,                                               \
        "Endless Corridor (First Endless Corridor)",                        \
        "Endless Top Right")                                                \
    X(END_TOP_L, FLAGS_L,                                                   \
        INVALID,                                                            \
        8, 1, 0, 30, 11, 312,                                               \
        "Endless Corridor (First Endless Corridor) (Left Exit)",            \
        "Endless Top Left (Exit only)")                                     \
    X(END_PHILOSOPHER, FLAGS_U,                                             \
        INVALID,                                                            \
        8, 2, 3, 36, 300, 16,                                               \
        "Endless Corridor (Second Endless Corridor)",                       \
        "Endless Philosopher Ladder")                                       \
    X(END_BOT, FLAGS_D,                                                     \
        INVALID,                                                            \
        8, 5, 3, 34, 420, 412,                                              \
        "Endless Corridor (Fifth Endless Corridor)",                        \
        "Endless Bottom")                                                   \
    X(MOM_TOP, FLAGS_U,                                                     \
        INVALID,                                                            \
        9, 0, 0, 33, 420, 16,                                               \
        "Shrine of the Mother (Amphisbaena's Room)",                        \
        "Mother Top")                                                       \
    X(MOM_BOT, FLAGS_D,                                                     \
        INVALID,                                                            \
        9, 8, 1, 22, 300, 412,                                              \
        "Shrine of the Mother (Bahamut's Room)",                            \
        "Mother Bottom")                                                    \
    X(MOM_SKULL, FLAGS_D,                                                   \
        INVALID,                                                            \
        9, 9, 1, 32, 300, 412,                                              \
        "Shrine of the Mother (Treasury) (Death Seal)",                     \
        "Mother Side Room (Skull Walls)")                                   \
    X(MOM_SMASH, FLAGS_D,                                                   \
        INVALID,                                                            \
        9, 9, 0, 26, 300, 412,                                              \
        "Shrine of the Mother (Treasury) (Map)",                            \
        "Mother Side Room (Smash)")                                         \
    X(ILL_BOT_R, FLAGS_D,                                                   \
        INVALID,                                                            \
        10, 9, 1, 47, 120, 412,                                             \
        "Gate of Illusion (Entrance of Illusion)",                          \
        "Illusion Bottom Right (Eden)")                                     \
    X(ILL_BOT_L, FLAGS_D,                                                   \
        INVALID,                                                            \
        10, 7, 0, 42, 60, 412,                                              \
        "Gate of Illusion (Fool's Confusion Corridor)",                     \
        "Illusion Bottom Left")                                             \
    X(ILL_MID_R, FLAGS_R,                                                   \
        INVALID,                                                            \
        10, 2, 1, 58, 590, 392,                                             \
        "Gate of Illusion (Sacrificial Abyss)",                             \
        "Illusion Middle Right (Chi You)")                                  \
    X(ILL_TOP_R, FLAGS_R,                                                   \
        INVALID,                                                            \
        10, 1, 1, 50, 590, 152,                                             \
        "Gate of Illusion (Children's Room)",                               \
        "Illusion Top Right (Dancing Child)")                               \
    X(GRA_TOP_L, FLAGS_U,                                                   \
        INVALID,                                                            \
        11, 0, 1, 39, 60, 16,                                               \
        "Graveyard of the Giants (First Tomb)",                             \
        "Graveyard Top Left")                                               \
    X(GRA_GRAIL, FLAGS_R,                                                   \
        INVALID,                                                            \
        11, 2, 1, 55, 590, 232,                                             \
        "Graveyard of the Giants (Second Tomb)",                            \
        "Graveyard Grail Room")                                             \
    X(GRA_BOT_L, FLAGS_L,                                                   \
        INVALID,                                                            \
        11, 5, 0, 57, 11, 152,                                              \
        "Graveyard of the Giants (Third Tomb)",                             \
        "Graveyard Bottom Left")                                            \
    X(GRA_TOP_R, FLAGS_U,                                                   \
        INVALID,                                                            \
        11, 9, 1, 51, 540, 16,                                              \
        "Graveyard of the Giants (Altar of Knowledge)",                     \
        "Graveyard Right Side Top")                                         \
    X(GRA_BOT_R, FLAGS_D,                                                   \
        INVALID,                                                            \
        11, 7, 1, 62, 500, 412,                                             \
        "Graveyard of the Giants (Anterior Corridor)",                      \
        "Graveyard Right Side Bottom")                                      \
    X(MOO_TOP_L, FLAGS_U,                                                   \
        INVALID,                                                            \
        12, 1, 0, 38, 120, 16,                                              \
        "Temple of Moonlight (Stairway of Eden)",                           \
        "Moonlight Top Left (Eden)")                                        \
    X(MOO_TOP_R, FLAGS_U,                                                   \
        INVALID,                                                            \
        12, 2, 1, 29, 540, 16,                                              \
        "Temple of Moonlight (Neptune's Feet)",                             \
        "Moonlight Top Right")                                              \
    X(MOO_BOT_L, FLAGS_L,                                                   \
        INVALID,                                                            \
        12, 8, 0, 56, 11, 232,                                              \
        "Temple of Moonlight (Sealed Approach)",                            \
        "Moonlight Bottom Left")                                            \
    X(GOD_SKA_L, FLAGS_L,                                                   \
        INVALID,                                                            \
        13, 7, 0, 41, 11, 152,                                              \
        "Tower of the Goddess (Path to Life)",                              \
        "Goddess Main Tower Top Left")                                      \
    X(GOD_SKA_R, FLAGS_D,                                                   \
        INVALID,                                                            \
        13, 7, 2, 45, 540, 412,                                             \
        "Tower of the Goddess (Path to Power)",                             \
        "Goddess Main Tower Top Right")                                     \
    X(GOD_URD_L, FLAGS_L,                                                   \
        INVALID,                                                            \
        13, 2, 2, 59, 11, 312,                                              \
        "Tower of the Goddess (Urd's Tower)",                               \
        "Goddess Bottom Left")                                              \
    X(GOD_VER_L, FLAGS_U,                                                   \
        INVALID,                                                            \
        13, 4, 0, 60, 80, 16,                                               \
        "Tower of the Goddess (Verdandi's Tower)",                          \
        "Goddess Pipe Tower Top Left")                                      \
    X(GOD_VER_R, FLAGS_NONE,                                                \
        INVALID,                                                            \
        13, 4, 0, 69, 0, 0,                                                 \
        "Tower of the Goddess (Gate of Time exit)",                         \
        "Goddess Pipe Tower Top Secret")                                    \
    X(GOD_PIP_L, FLAGS_L,                                                   \
        INVALID,                                                            \
        13, 8, 0, 43, 11, 232,                                              \
        "Tower of the Goddess (Left Pipe)",                                 \
        "Goddess Transition Pipe Left")                                     \
    X(GOD_PIP_R, FLAGS_R,                                                   \
        INVALID,                                                            \
        13, 8, 0, 49, 590, 232,                                             \
        "Tower of the Goddess (Right Pipe)",                                \
        "Goddess Transition Pipe Right")                                    \
    X(RUI_BOT_R, FLAGS_R,                                                   \
        INVALID,                                                            \
        14, 0, 2, 44, 590, 152,                                             \
        "Tower of Ruin (Fountain of Heat)",                                 \
        "Ruin Bottom Right (Main)")                                         \
    X(RUI_TOP_L, FLAGS_L,                                                   \
        INVALID,                                                            \
        14, 5, 0, 40, 11, 392,                                              \
        "Tower of Ruin (Approach of the Philosophers)",                     \
        "Ruin Top Left")                                                    \
    X(RUI_TOP_R, FLAGS_R,                                                   \
        INVALID,                                                            \
        14, 7, 1, 52, 590, 312,                                             \
        "Tower of Ruin (Burial Chamber of Life)",                           \
        "Ruin Top Right (Medicine)")                                        \
    X(BIR_GRAIL, FLAGS_D,                                                   \
        INVALID,                                                            \
        15, 0, 0, 53, 80, 412,                                              \
        "Chamber of Birth (Deva's Room)",                                   \
        "Birth Top Left (Grail)")                                           \
    X(BIR_SKANDA, FLAGS_R,                                                  \
        INVALID,                                                            \
        15, 3, 1, 63, 590, 312,                                             \
        "Chamber of Birth (Skanda's Room)",                                 \
        "Birth Bottom Right (Skanda Room)")                                 \
    X(BIR_LADDERS, FLAGS_U,                                                 \
        INVALID,                                                            \
        16, 0, 0, 46, 500, 16,                                              \
        "Chamber of Birth (Saraswati's Room)",                              \
        "Birth* Top Left (Ladders)")                                        \
    X(BIR_TO_SKANDA, FLAGS_L,                                               \
        INVALID,                                                            \
        16, 3, 1, 61, 11, 312,                                              \
        "Chamber of Birth (Vishnu's Room)",                                 \
        "Birth* Bottom Right (Door to Skanda)")                             \
    X(DIM_BOT, FLAG_SCROLL_D,                                               \
        INVALID,                                                            \
        17, 0, 1, 27, 0, 0,                                                 \
        "Dimensional Corridor",                                             \
        "Dimensional Corridor Bottom")                                      \
    X(SUR8_MAIN, FLAGS_R,                                                   \
        INVALID,                                                            \
        21, 0, 1, 66, 590, 312,                                             \
        "Gate of Time (Surface to Gate of Guidance)",                       \
        "8-Bit Surface")                                                    \
    X(GUI8_TOP_L, FLAGS_L,                                                  \
        INVALID,                                                            \
        20, 4, 0, 65, 11, 312,                                              \
        "Gate of Time (Gate of Guidance to Surface)",                       \
        "8-Bit Guidance Top Left")                                          \
    X(GUI8_BOT_L, FLAGS_D,                                                  \
        INVALID,                                                            \
        20, 0, 0, 68, 60, 412,                                              \
        "Gate of Time (Gate of Guidance to Mausoleum of the Giants)",       \
        "8-Bit Guidance Bottom Left")                                       \
    X(MAU8_TOP_L, FLAGS_U,                                                  \
        INVALID,                                                            \
        19, 4, 0, 67, 60, 16,                                               \
        "Gate of Time (Mausoleum of the Giants to Gate of Guidance)",       \
        "8-Bit Mausoleum Top Left")                                         \
    X(MAU8_BOT_R, FLAGS_D,                                                  \
        INVALID,                                                            \
        19, 1, 2, 54, 480, 412,                                             \
        "Gate of Time (Mausoleum of the Giants to Tower of the Goddess)",   \
        "8-Bit Mausoleum Bottom Right")


/********
 * BACKSIDE DOOR DATA
 */

#define X_DOORS                                                             \
    X(INVALID, FLAGS_NONE,                                                  \
        INVALID,                                                            \
        0, 0, 0, 0, 0, 0,                                                   \
        "Invalid backside door",                                            \
        "Invalid backside door")                                            \
    X(SUR, FLAG_INPUT | FLAG_BOSS_5,                                        \
        INVALID,                                                            \
        1, 8, 0, 13, 200, 312,                                              \
        "Surface",                                                          \
        "Surface")                                                          \
    X(GUI, FLAG_INPUT | FLAG_BOSS_1,                                        \
        INVALID,                                                            \
        0, 5, 0, 10, 180, 152,                                              \
        "Gate of Guidance",                                                 \
        "Gate of Guidance")                                                 \
    X(MAU, FLAG_INPUT | FLAG_BOSS_2,                                        \
        INVALID,                                                            \
        2, 4, 0, 11, 80, 312,                                               \
        "Mausoleum of the Giants",                                          \
        "Mausoleum of the Giants")                                          \
    X(SUN, FLAG_INPUT | FLAG_BOSS_3,                                        \
        INVALID,                                                            \
        3, 6, 0, 12, 460, 152,                                              \
        "Temple of the Sun",                                                \
        "Temple of the Sun")                                                \
    X(INF, FLAG_INPUT | FLAG_BOSS_4,                                        \
        INVALID,                                                            \
        5, 8, 0, 14, 140, 152,                                              \
        "Inferno Cavern (Darkness Sanctuary)",                              \
        "Inferno Cavern (Viy)")                                             \
    X(ECH, FLAG_INPUT | FLAG_BOSS_7,                                        \
        INVALID,                                                            \
        5, 9, 0, 15, 60, 72,                                                \
        "Inferno Cavern (Echidna's Chamber)",                               \
        "Inferno Cavern (Echidna)")                                         \
    X(EXT, FLAG_INPUT | FLAG_FAIRY,                                         \
        INVALID,                                                            \
        6, 7, 0, 18, 300, 72,                                               \
        "Chamber of Extinction (Path of Life)",                             \
        "Chamber of Extinction (Key Fairy)")                                \
    X(MAG, FLAG_INPUT | FLAG_BOSS_6,                                        \
        INVALID,                                                            \
        6, 0, 0, 16, 40, 72,                                                \
        "Chamber of Extinction (Approach to the Sanctuary)",                \
        "Chamber of Extinction (Magatama)")                                 \
    X(END, FLAGS_NONE,                                                      \
        INVALID,                                                            \
        8, 0, 1, 17, 0, 0,                                                  \
        "Endless Corridor (First Endless Corridor)",                        \
        "Endless Corridor")                                                 \
    X(ILL, FLAG_INPUT | FLAG_BOSS_1,                                        \
        INVALID,                                                            \
        10, 3, 0, 2, 40, 72,                                                \
        "Gate of Illusion",                                                 \
        "Gate of Illusion")                                                 \
    X(GRA, FLAG_INPUT | FLAG_BOSS_2,                                        \
        INVALID,                                                            \
        11, 3, 0, 3, 80, 152,                                               \
        "Graveyard of the Giants",                                          \
        "Graveyard of the Giants")                                          \
    X(MOO, FLAG_INPUT | FLAG_BOSS_3,                                        \
        INVALID,                                                            \
        12, 4, 2, 4, 200, 232,                                              \
        "Temple of Moonlight",                                              \
        "Temple of Moonlight")                                              \
    X(GOD, FLAG_INPUT | FLAG_BOSS_5,                                        \
        INVALID,                                                            \
        13, 0, 1, 1, 300, 392,                                              \
        "Tower of the Goddess",                                             \
        "Tower of the Goddess")                                             \
    X(RUI, FLAG_INPUT | FLAG_BOSS_4,                                        \
        INVALID,                                                            \
        14, 2, 1, 5, 300, 232,                                              \
        "Tower of Ruin (Tower of Babel)",                                   \
        "Tower of Ruin (Bottom)")                                           \
    X(NUW, FLAG_INPUT | FLAG_BOSS_7,                                        \
        INVALID,                                                            \
        14, 8, 1, 6, 300, 112,                                              \
        u8"Tower of Ruin (Nüwa's Pyramid)",                                 \
        "Tower of Ruin (N#wa)")                                             \
    X(BIR, FLAG_INPUT | FLAG_BOSS_6,                                        \
        INVALID,                                                            \
        15, 0, 1, 8, 300, 392,                                              \
        "Chamber of Birth",                                                 \
        "Chamber of Birth")                                                 \
    X(DIM, FLAG_INPUT,                                                      \
        INVALID,                                                            \
        17, 0, 0, 9, 300, 312,                                              \
        "Dimensional Corridor",                                             \
        "Dimensional Corridor")                                             \
    X(TIM, FLAG_INPUT | FLAG_FAIRY,                                         \
        INVALID,                                                            \
        19, 0, 1, 7, 300, 312,                                              \
        "Gate of Time (Mausoleum)",                                         \
        "Gate of Time")

 
/********
 * WALL SEAL DATA
 */

#define X_SEALS                                                             \
    X(INVALID, FLAGS_NONE,                                                  \
        INVALID,                                                            \
        255, 0, 0, 0, 0, 0,                                                 \
        "Invalid wall seal",                                                \
        "Invalid wall seal")                                                \
    X(SUR_COIN, FLAGS_NONE,                                                 \
        INVALID,                                                            \
        1, 1, 0, 3, 280, 252,                                               \
        "Surface coin chest seal",                                          \
        "Surface (Coin Chest)")                                             \
    X(SUR_BIRTH, FLAGS_NONE,                                                \
        INVALID,                                                            \
        1, 7, 1, 1, 480, 212,                                               \
        "Birth Seal chest",                                                 \
        "Surface (Birth Seal)")                                             \
    X(GUI_LIGHTS, FLAGS_NONE,                                               \
        INVALID,                                                            \
        0, 1, 1, 3, 340, 232,                                               \
        "Crucifix chest/Offer 3 lights",                                    \
        "Guidance (Three Lights)")                                          \
    X(SUN_MULBRUK, FLAGS_NONE,                                              \
        INVALID,                                                            \
        3, 3, 0, 1, 460, 292,                                               \
        "Mulbruk's seal",                                                   \
        "Sun (Mulbruk)")                                                    \
    X(SUN_EXT, FLAGS_NONE,                                                  \
        INVALID,                                                            \
        3, 5, 0, 1, 160, 152,                                               \
        "Sun right exits",                                                  \
        "Sun (Extinction)")                                                 \
    X(SUN_SHOP, FLAGS_NONE,                                                 \
        INVALID,                                                            \
        3, 7, 0, 4, 420, 72,                                                \
        "Sun discount shop",                                                \
        "Sun (Bottom Left Shop)")                                           \
    X(SPR_ORB, FLAGS_NONE,                                                  \
        INVALID,                                                            \
        4, 0, 0, 2, 20, 152,                                                \
        "Spring Sacred Orb chest",                                          \
        "Spring (Top Left)")                                                \
    X(SPR_SHOP, FLAGS_NONE,                                                 \
        INVALID,                                                            \
        4, 3, 3, 1, 40, 232,                                                \
        "Mr. Fishman's shop",                                               \
        "Spring (Shop)")                                                    \
    X(SPR_BAHAMUT, FLAGS_NONE,                                              \
        INVALID,                                                            \
        4, 4, 0, 1, 320, 52,                                                \
        "Bahamut's room",                                                   \
        "Spring (Bahamut)")                                                 \
    X(INF_JETS, FLAGS_NONE,                                                 \
        INVALID,                                                            \
        5, 2, 1, 2, 420, 32,                                                \
        "Pazuzu seal",                                                      \
        "Inferno (Fire Jets)")                                              \
    X(EXT_LIFE, FLAGS_NONE,                                                 \
        INVALID,                                                            \
        6, 6, 1, 2, 260, 312,                                               \
        "Life Seal chest",                                                  \
        "Extinction (Life Seal)")                                           \
    X(EXT_LIGHT, FLAGS_NONE,                                                \
        INVALID,                                                            \
        6, 6, 1, 2, 260, 312,                                               \
        "Extinction perma-light, Extinction side",                          \
        "Extinction (Light Extinction)")                                    \
    X(END_SHOP, FLAGS_NONE,                                                 \
        INVALID,                                                            \
        8, 0, 0, 1, 240, 232,                                               \
        "Endless shop seal",                                                \
        "Endless (Shop)")                                                   \
    X(ILL_CHI_YOU, FLAGS_NONE,                                              \
        INVALID,                                                            \
        10, 2, 1, 2, 540, 132,                                              \
        "Chi You seal",                                                     \
        "Illusion (Chi You)")                                               \
    X(GRA_GAUNTLET, FLAGS_NONE,                                             \
        INVALID,                                                            \
        11, 4, 1, 3, 140, 152,                                              \
        "Gauntlet chest",                                                   \
        "Graveyard (Gauntlet)")                                             \
    X(MOO_ANUBIS, FLAGS_NONE,                                               \
        INVALID,                                                            \
        12, 9, 1, 2, 80, 292,                                               \
        "Path to Anubis",                                                   \
        "Moonlight (Above Anubis)")                                         \
    X(RUI_NUWA, FLAGS_NONE,                                                 \
        INVALID,                                                            \
        14, 8, 2, 4, 540, 32,                                               \
        "Nuwa",                                                             \
        "Ruin (Nuwa)")                                                      \
    X(BIR_LIGHT, FLAGS_NONE,                                                \
        INVALID,                                                            \
        15, 3, 0, 3, 540, 32,                                               \
        "Extinction perma-light, Birth side",                               \
        "Birth* (Light Extinction)")                                        \
    X(MOM_SKULL, FLAGS_NONE,                                                \
        INVALID,                                                            \
        9, 1, 0, 3, 460, 312,                                               \
        "Crystal Skull chest",                                              \
        "Mother (Crystal Skull)")                                           \
    X(MOM_LAPTOP, FLAGS_NONE,                                               \
        INVALID,                                                            \
        9, 3, 1, 4, 100, 32,                                                \
        "Shrine Laptop room",                                               \
        "Mother (Laptop)")                                                  \
    X(MOM_ORB_1, FLAGS_NONE,                                                \
        INVALID,                                                            \
        9, 1, 1, 1, 140, 112,                                               \
        "Shrine 4 Seals, Origin edition",                                   \
        "Mother (Orb Top Left)")                                            \
    X(MOM_ORB_2, FLAGS_NONE,                                                \
        INVALID,                                                            \
        9, 1, 1, 2, 460, 112,                                               \
        "Shrine 4 Seals, Birth edition",                                    \
        "Mother (Orb Top Right)")                                           \
    X(MOM_ORB_3, FLAGS_NONE,                                                \
        INVALID,                                                            \
        9, 1, 1, 3, 140, 252,                                               \
        "Shrine 4 Seals, Life edition",                                     \
        "Mother (Orb Bottom Left)")                                         \
    X(MOM_ORB_4, FLAGS_NONE,                                                \
        INVALID,                                                            \
        9, 1, 1, 4, 460, 252,                                               \
        "Shrine 4 Seals, Death edition",                                    \
        "Mother (Orb Bottom Right)")                                        \
    X(MOM_ANKH_1, FLAGS_NONE,                                               \
        INVALID,                                                            \
        18, 3, 0, 4, 300, 392,                                              \
        "Mother Ankh seal, Death edition",                                  \
        "Mother (Ankh Far Left)")                                           \
    X(MOM_ANKH_2, FLAGS_NONE,                                               \
        INVALID,                                                            \
        18, 3, 0, 3, 300, 392,                                              \
        "Mother Ankh seal, Life edition",                                   \
        "Mother (Ankh Middle Left)")                                        \
    X(MOM_ANKH_3, FLAGS_NONE,                                               \
        INVALID,                                                            \
        18, 3, 0, 2, 300, 392,                                              \
        "Mother Ankh seal, Birth edition",                                  \
        "Mother (Ankh Middle Right)")                                       \
    X(MOM_ANKH_4, FLAGS_NONE,                                               \
        INVALID,                                                            \
        18, 3, 0, 1, 300, 392,                                              \
        "Mother Ankh seal, Origin edition",                                 \
        "Mother (Ankh Far Right)")


/********
 * CHARACTER DATA
 */

#define X_CHARS                                                             \
    X(INVALID, FLAGS_NONE,                                                  \
        INVALID,                                                            \
        255, 0, 0, 0, 0, 0,                                                 \
        "Invalid character",                                                \
        "Invalid character")                                                \
    X(XELPUD, FLAG_INPUT,                                                   \
        NPC_XELPUD,                                                         \
        1, 2, 1, 1, 180, 152,                                               \
        "Elder Xelpud",                                                     \
        "Xelpud")                                                           \
    X(SUR_SHOP_1, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_NEBUR,                                                          \
        1, 2, 0, 2, 360, 152,                                               \
        "Nebur",                                                            \
        "Surface Shop (Nebur)")                                             \
    X(SUR_SHOP_2, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_VILLAGER_1,                                                     \
        1, 2, 1, 3, 240, 312,                                               \
        "Sidro",                                                            \
        "Surface Shop (Sidro)")                                             \
    X(SUR_SHOP_3, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_VILLAGER_2,                                                     \
        1, 2, 1, 4, 500, 232,                                               \
        "Modro",                                                            \
        "Surface Shop (Modro)")                                             \
    X(SUR_VILLAGE, FLAG_INPUT,                                              \
        NPC_VILLAGER_2,                                                     \
        1, 2, 0, 5, 220, 312,                                               \
        "Moger",                                                            \
        "Surface (Below Nebur)")                                            \
    X(SUR_ARGUS, FLAG_INPUT,                                                \
        NPC_VILLAGER_1,                                                     \
        1, 0, 2, 6, 500, 152,                                               \
        "Hiner",                                                            \
        "Surface (Argus)")                                                  \
    X(SUR_MEKURI, FLAG_INPUT,                                               \
        NPC_PRIEST,                                                         \
        1, 7, 0, 7, 340, 312,                                               \
        "Former Mekuri Master",                                             \
        "Surface (Mekuri Master)")                                          \
    X(GUI_ELEVATOR, FLAG_INPUT,                                             \
        NPC_PRIEST,                                                         \
        0, 4, 1, 8, 40, 72,                                                 \
        "Priest Zarnac",                                                    \
        "Guidance (Elevator)")                                              \
    X(GUI_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_GHOST,                                                          \
        0, 9, 1, 9, 200, 232,                                               \
        "Penadvent of ghost",                                               \
        "Guidance Shop")                                                    \
    X(MAU_HARDMODE, FLAG_INPUT,                                             \
        NPC_PRIEST,                                                         \
        2, 2, 0, 10, 40, 72,                                                \
        "Priest Xanado",                                                    \
        "Mausoleum (Hard Mode tablet)")                                     \
    X(MAU_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_GHOST,                                                          \
        2, 6, 0, 11, 260, 312,                                              \
        "Greedy Charlie",                                                   \
        "Mausoleum Shop")                                                   \
    X(MULBRUK, FLAG_INPUT,                                                  \
        NPC_MULBRUK,                                                        \
        3, 3, 0, 12, 460, 232,                                              \
        "Mulbruk",                                                          \
        "Mulbruk")                                                          \
    X(SUN_SHOP_1, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_SARCOPHAGUS,                                                    \
        3, 1, 2, 13, 240, 312,                                              \
        "Shalom III",                                                       \
        "Sun Shop (Knife)")                                                 \
    X(SUN_SHOP_2, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_SARCOPHAGUS,                                                    \
        3, 7, 0, 14, 420, 152,                                              \
        "Kingvalley I",                                                     \
        "Sun Shop (Bottom Left)")                                           \
    X(SUN_SHOP_3, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_SARCOPHAGUS,                                                    \
        3, 6, 1, 15, 180, 392,                                              \
        "Usas VI",                                                          \
        "Sun Shop (Bottom Right)")                                          \
    X(SUR_SPRING, FLAG_INPUT,                                               \
        NPC_PRIEST,                                                         \
        3, 4, 2, 16, 480, 72,                                               \
        "Priest Madomono",                                                  \
        "Sun (Below Spring)")                                               \
    X(GILTORIYO, FLAG_INPUT,                                                \
        NPC_GILTORIYO,                                                      \
        4, 0, 1, 17, 40, 312,                                               \
        "Philosopher Giltoriyo",                                            \
        "Giltoriyo")                                                        \
    X(SPR_SHOP_1, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_GYONIN,                                                         \
        4, 3, 3, 18, 580, 152,                                              \
        "Mr. Fishman (Original)",                                           \
        "Spring Shop (Normal)")                                             \
    X(SPR_SHOP_2, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_GYONIN,                                                         \
        4, 3, 3, 19, 180, 72,                                               \
        "Mr. Fishman (Alt)",                                                \
        "Spring Shop (Key Fairy)")                                          \
    X(SPR_GRAIL, FLAG_INPUT,                                                \
        NPC_PRIEST,                                                         \
        4, 6, 1, 20, 300, 152,                                              \
        "Priest Hidlyda",                                                   \
        "Spring (Below Grail)")                                             \
    X(INF_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_PRIEST,                                                         \
        5, 5, 0, 21, 100, 72,                                               \
        "Hot-blooded Nemesistwo",                                           \
        "Inferno Shop")                                                     \
    X(INF_JETS, FLAG_INPUT,                                                 \
        NPC_PRIEST,                                                         \
        5, 2, 1, 22, 400, 232,                                              \
        "Priest Gailious",                                                  \
        "Inferno (Fire Jets)")                                              \
    X(INF_PAZUZU, FLAG_INPUT,                                               \
        NPC_PRIEST,                                                         \
        5, 3, 2, 23, 180, 392,                                              \
        "Priest Romancis",                                                  \
        "Inferno (Before Pazuzu)")                                          \
    X(EXT_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_PRIEST,                                                         \
        6, 8, 1, 24, 280, 232,                                              \
        "Operator Combaker",                                                \
        "Extinction Shop")                                                  \
    X(EXT_GRAIL, FLAG_INPUT,                                                \
        NPC_PRIEST,                                                         \
        6, 6, 0, 25, 120, 72,                                               \
        "Priest Aramo",                                                     \
        "Extinction (Above Grail)")                                         \
    X(EXT_PALENQUE, FLAG_INPUT,                                             \
        NPC_PRIEST,                                                         \
        6, 9, 1, 26, 40, 72,                                                \
        "Priest Triton",                                                    \
        "Extinction (Palenque)")                                            \
    X(LAB_SHOP_1, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_PRIEST,                                                         \
        7, 3, 2, 27, 300, 72,                                               \
        "Yiegah Kungfu",                                                    \
        "Twin Shop (Little Brother)")                                       \
    X(LAB_SHOP_2, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_PRIEST,                                                         \
        7, 12, 2, 28, 300, 72,                                              \
        "Yiear Kungfu",                                                     \
        "Twin Shop (Big Brother)")                                          \
    X(LAB_SHOP_3, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_PRIEST,                                                         \
        7, 6, 1, 29, 560, 72,                                               \
        "Arrogant Metagear",                                                \
        "Twin Shop (Lamp of Time)")                                         \
    X(LAB_SHOP_4, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_PRIEST,                                                         \
        7, 14, 0, 30, 40, 72,                                               \
        "Arrogant Sturdy Snake",                                            \
        "Twin Shop (Bracelet)")                                             \
    X(LAB_TOP_R, FLAG_INPUT,                                                \
        NPC_PRIEST,                                                         \
        7, 10, 1, 31, 300, 312,                                             \
        "Priest Jaguarfiv",                                                 \
        "Twin (Top Right)")                                                 \
    X(FREYA, FLAG_INPUT,                                                    \
        NPC_FREYA,                                                          \
        8, 1, 0, 32, 40, 152,                                               \
        "The Fairy Queen",                                                  \
        "Fairy Queen")                                                      \
    X(END_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_PRIEST,                                                         \
        8, 0, 0, 33, 200, 312,                                              \
        "Affected Knimare",                                                 \
        "Endless Shop")                                                     \
    X(ILL_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_PRIEST,                                                         \
        10, 5, 0, 34, 560, 232,                                             \
        "Mover Athleland",                                                  \
        "Illusion Shop")                                                    \
    X(ILL_FRAUD, FLAG_INPUT,                                                \
        NPC_PRIEST,                                                         \
        10, 8, 0, 35, 40, 72,                                               \
        "Mr. Slushfund",                                                    \
        "Illusion (I @ Fraud)")                                             \
    X(ILL_DOLL, FLAG_INPUT,                                                 \
        NPC_PRIEST,                                                         \
        10, 8, 1, 36, 480, 72,                                              \
        "Priest Alest",                                                     \
        "Illusion (Mini Doll)")                                             \
    X(DUPLEX, FLAG_INPUT,                                                   \
        NPC_DUPLEX,                                                         \
        10, 2, 2, 37, 360, 72,                                              \
        "duplex",                                                           \
        "duplex")                                                           \
    X(GRA_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_GIANT,                                                          \
        11, 0, 0, 38, 100, 392,                                             \
        "Giant Mopiran",                                                    \
        "Graveyard Shop")                                                   \
    X(GRA_BOMBS, FLAG_INPUT,                                                \
        NPC_GIANT,                                                          \
        11, 7, 0, 39, 100, 72,                                              \
        "Giant Thexde",                                                     \
        "Graveyard (Below Bombs)")                                          \
    X(ALSEDANA, FLAG_INPUT,                                                 \
        NPC_ALSEDANA,                                                       \
        12, 6, 0, 40, 180, 72,                                              \
        "Philosopher Alsedana",                                             \
        "Alsedana")                                                         \
    X(MOO_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_SARCOPHAGUS,                                                    \
        12, 7, 0, 41, 520, 72,                                              \
        "Kingvalley II",                                                    \
        "Moonlight Shop")                                                   \
    X(SAMIERU, FLAG_INPUT,                                                  \
        NPC_SAMIERU,                                                        \
        12, 3, 0, 42, 40, 312,                                              \
        "Samieru",                                                          \
        "Samieru")                                                          \
    X(SAMARANTA, FLAG_INPUT,                                                \
        NPC_SAMARANTA,                                                      \
        13, 5, 1, 43, 540, 152,                                             \
        "Philosopher Samaranta",                                            \
        "Samaranta")                                                        \
    X(GOD_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_PRIEST,                                                         \
        13, 4, 1, 44, 360, 392,                                             \
        "Energetic Belmont",                                                \
        "Goddess Shop")                                                     \
    X(NARAMURA, FLAG_INPUT,                                                 \
        NPC_NARAMURA,                                                       \
        13, 6, 3, 45, 560, 332,                                             \
        "Naramura",                                                         \
        "Naramura")                                                         \
    X(RUI_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_ROBOT,                                                          \
        14, 4, 0, 46, 300, 72,                                              \
        "Mechanical Efspi",                                                 \
        "Ruin Shop")                                                        \
    X(RUI_BOT_R, FLAG_INPUT,                                                \
        NPC_PRIEST,                                                         \
        14, 0, 1, 47, 40, 72,                                               \
        "Priest Laydoc",                                                    \
        "Ruin (Bottom Right)")                                              \
    X(BIR_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_MUDMAN,                                                         \
        16, 1, 1, 48, 60, 312,                                              \
        "Mud Man Qubert",                                                   \
        "Birth Shop")                                                       \
    X(BIR_TOP_L, FLAG_INPUT,                                                \
        NPC_PRIEST,                                                         \
        16, 1, 0, 49, 40, 232,                                              \
        "Priest Ashgine",                                                   \
        "Birth (Top Left)")                                                 \
    X(FOBOS, FLAG_INPUT,                                                    \
        NPC_FOBOS,                                                          \
        17, 2, 0, 50, 300, 152,                                             \
        "Philosopher Fobos",                                                \
        "Fobos")                                                            \
    X(XELPUD8, FLAG_INPUT,                                                  \
        NPC_XELPUD8,                                                        \
        21, 0, 0, 51, 180, 152,                                             \
        "8bit Elder",                                                       \
        "8-Bit Xelpud")                                                     \
    X(DRACUET, FLAG_INPUT | FLAG_SHOP,                                      \
        NPC_DRACUET,                                                        \
        23, 8, 1, 52, 0, 0,                                                 \
        "Tailor Dracuet",                                                   \
        "Hell Temple Shop")


/********
 * SHOPS DATA
 */

#define X_SHOPS                                                             \
    X(INVALID, FLAGS_NONE,                                                  \
        INVALID,                                                            \
        255, 0, 0, 0, 0, 0,                                                 \
        "Invalid character",                                                \
        "Invalid character")                                                \
    X(STARTING, FLAG_SHOP,                                                  \
        NPC_XELPUD,                                                         \
        255, 0, 0, 0, 0, 0,                                                 \
        "Starting Shop",                                                    \
        "Starting shop")                                                    \
    X(SUR_SHOP_1, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_NEBUR,                                                          \
        1, 2, 0, 2, 360, 152,                                               \
        "Nebur",                                                            \
        "Surface Shop (Nebur)")                                             \
    X(SUR_SHOP_4BOSS, FLAG_SHOP,                                            \
        NPC_NEBUR,                                                          \
        1, 2, 0, 2, 360, 152,                                               \
        "Nebur (4 Bosses)",                                                 \
        "Surface Shop (Nebur)")                                             \
    X(SUR_SHOP_2, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_VILLAGER_1,                                                     \
        1, 2, 1, 3, 240, 312,                                               \
        "Sidro",                                                            \
        "Surface Shop (Sidro)")                                             \
    X(SUR_SHOP_3, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_VILLAGER_2,                                                     \
        1, 2, 1, 4, 500, 232,                                               \
        "Modro",                                                            \
        "Surface Shop (Modro)")                                             \
    X(GUI_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_GHOST,                                                          \
        0, 9, 1, 9, 200, 232,                                               \
        "Penadvent of ghost",                                               \
        "Guidance Shop")                                                    \
    X(MAU_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_GHOST,                                                          \
        2, 6, 0, 11, 260, 312,                                              \
        "Greedy Charlie",                                                   \
        "Mausoleum Shop")                                                   \
    X(SUN_SHOP_1, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_SARCOPHAGUS,                                                    \
        3, 1, 2, 13, 240, 312,                                              \
        "Shalom III",                                                       \
        "Sun Shop (Knife)")                                                 \
    X(SUN_SHOP_2, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_SARCOPHAGUS,                                                    \
        3, 7, 0, 14, 420, 152,                                              \
        "Kingvalley I",                                                     \
        "Sun Shop (Bottom Left)")                                           \
    X(SUN_SHOP_3, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_SARCOPHAGUS,                                                    \
        3, 6, 1, 15, 180, 392,                                              \
        "Usas VI",                                                          \
        "Sun Shop (Bottom Right)")                                          \
    X(SPR_SHOP_1, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_GYONIN,                                                         \
        4, 3, 3, 18, 580, 152,                                              \
        "Mr. Fishman (Original)",                                           \
        "Spring Shop (Normal)")                                             \
    X(SPR_SHOP_2, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_GYONIN,                                                         \
        4, 3, 3, 19, 180, 72,                                               \
        "Mr. Fishman (Alt)",                                                \
        "Spring Shop (Key Fairy)")                                          \
    X(INF_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_PRIEST,                                                         \
        5, 5, 0, 21, 100, 72,                                               \
        "Hot-blooded Nemesistwo",                                           \
        "Inferno Shop")                                                     \
    X(EXT_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_PRIEST,                                                         \
        6, 8, 1, 24, 280, 232,                                              \
        "Operator Combaker",                                                \
        "Extinction Shop")                                                  \
    X(LAB_SHOP_1, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_PRIEST,                                                         \
        7, 3, 2, 27, 300, 72,                                               \
        "Yiegah Kungfu",                                                    \
        "Twin Shop (Little Brother)")                                       \
    X(LAB_SHOP_2, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_PRIEST,                                                         \
        7, 12, 2, 28, 300, 72,                                              \
        "Yiear Kungfu",                                                     \
        "Twin Shop (Big Brother)")                                          \
    X(LAB_SHOP_3, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_PRIEST,                                                         \
        7, 6, 1, 29, 560, 72,                                               \
        "Arrogant Metagear",                                                \
        "Twin Shop (Lamp of Time)")                                         \
    X(LAB_SHOP_4, FLAG_INPUT | FLAG_SHOP,                                   \
        NPC_PRIEST,                                                         \
        7, 14, 0, 30, 40, 72,                                               \
        "Arrogant Sturdy Snake",                                            \
        "Twin Shop (Bracelet)")                                             \
    X(END_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_PRIEST,                                                         \
        8, 0, 0, 33, 200, 312,                                              \
        "Affected Knimare",                                                 \
        "Endless Shop")                                                     \
    X(ILL_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_PRIEST,                                                         \
        10, 5, 0, 34, 560, 232,                                             \
        "Mover Athleland",                                                  \
        "Illusion Shop")                                                    \
    X(GRA_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_GIANT,                                                          \
        11, 0, 0, 38, 100, 392,                                             \
        "Giant Mopiran",                                                    \
        "Graveyard Shop")                                                   \
    X(MOO_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_SARCOPHAGUS,                                                    \
        12, 7, 0, 41, 520, 72,                                              \
        "Kingvalley II",                                                    \
        "Moonlight Shop")                                                   \
    X(GOD_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_PRIEST,                                                         \
        13, 4, 1, 44, 360, 392,                                             \
        "Energetic Belmont",                                                \
        "Goddess Shop")                                                     \
    X(RUI_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_ROBOT,                                                          \
        14, 4, 0, 46, 300, 72,                                              \
        "Mechanical Efspi",                                                 \
        "Ruin Shop")                                                        \
    X(BIR_SHOP, FLAG_INPUT | FLAG_SHOP,                                     \
        NPC_MUDMAN,                                                         \
        16, 1, 1, 48, 60, 312,                                              \
        "Mud Man Qubert",                                                   \
        "Birth Shop")                                                       \
    X(DRACUET, FLAG_INPUT | FLAG_SHOP,                                      \
        NPC_DRACUET,                                                        \
        23, 8, 1, 52, 0, 0,                                                 \
        "Tailor Dracuet",                                                   \
        "Hell Temple Shop")

#endif /* DATA_HGUARD */
