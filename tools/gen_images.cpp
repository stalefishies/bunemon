#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define UNICODE
#define _UNICODE
#include <windows.h>
#include <gdiplus.h>
#include <gdiplusheaders.h>
#pragma comment(lib, "user32")
#pragma comment(lib, "gdiplus")

using namespace Gdiplus;

#define BITMAP_W 640
#define BITMAP_H 502
static Bitmap   *bitmap;
static Graphics *graphics;

static int draw_x = 0;
static int draw_y = 0;
static int draw_h = 0;

static Image *base = NULL;
static ImageAttributes *base_attr = NULL;
static int base_x = 0;
static int base_y = 0;
static int base_w = 1;
static int base_h = 1;
static int base_j = 1;
static int base_i = 1;

void imageSet(Image &new_base, int x = 0, int y = 0,
    int w = 1, int h = 1, int j = 0, int i = 0)
{
    base = &new_base;
    base_x = (x > 0 ? x : 0);
    base_y = (y > 0 ? y : 0);
    base_w = (w > 1 ? w : 1);
    base_h = (h > 1 ? h : 1);
    base_j = (j > base_w ? j : base_w);
    base_i = (i > base_h ? i : base_h);
}

void imageLine(int w = -1) {
    if (w < 0 || draw_x + w > BITMAP_W) {
        draw_y += draw_h;
        draw_x = 0;
        draw_h = 0;
    }
}

void imageDraw(Image *base,
    int src_x, int src_y, int src_w, int src_h,
    int dst_x, int dst_y, int dst_w, int dst_h)
{
    graphics->DrawImage(base,
        Rect(dst_x, dst_y, dst_w, dst_h),
        src_x, src_y, src_w, src_h,
        UnitPixel, base_attr);
}

#define DRAW(name, w, h) for (                          \
    bool _loop = (imageLine(w), true);                  \
    _loop;                                              \
    (_loop = false),                                    \
        (fprintf(hpp,                                   \
            " \\\n    X(%16s, %3u, %3u, %3u, %3u)",     \
            #name, draw_x, draw_y, w, h)),              \
        (draw_x += w),                                  \
        (draw_h = (h > draw_h ? h : draw_h))            \
)

#define draw_w(name, x, y, w) do {          \
    DRAW(name, w, base_h) {                 \
        int src_x = base_x + x * base_j;    \
        int src_y = base_y + y * base_i;    \
        imageDraw(base,                     \
            src_x,  src_y,  w, base_h,      \
            draw_x, draw_y, w, base_h);     \
    }                                       \
} while (0)

#define draw(name, x, y) draw_w(name, x, y, base_w)

int main(void) {
    ULONG_PTR           gdi_token;
    GdiplusStartupInput gdi_input;
    GdiplusStartup(&gdi_token, &gdi_input, NULL);

    Rect output_bounds = Rect(0, 0, BITMAP_W, BITMAP_H);
    bitmap   = new Bitmap(BITMAP_W, BITMAP_H, PixelFormat32bppPARGB);
    graphics = new Graphics(bitmap);
    graphics->SetCompositingMode(CompositingModeSourceOver);
    graphics->SetInterpolationMode(InterpolationModeNearestNeighbor);
    graphics->Clear(0x00000000);
    
    base_attr = new ImageAttributes();
    base_attr->SetToIdentity(ColorAdjustTypeBitmap);

    FILE *hpp = fopen("images.hpp", "w");
    FILE *cpp = fopen("images.cpp", "w");

    fprintf(hpp,
        "#ifndef IMAGES_HGUARD\n"
        "#define IMAGES_HGUARD\n"
        "\n"
        "/* IMAGES.HPP\n"
        " * \n"
        " * This file is automatically generated.\n"
        " */\n"
        "\n"
        "enum {\n"
        "    IMAGES_W     = %u,\n"
        "    IMAGES_H     = %u,\n"
        "    IMAGES_BYTES = %u,\n"
        "    IMAGES_FONT_ASC  = %u,\n"
        "    IMAGES_FONT_BASE = %u,\n"
        "    IMAGES_FONT_DESC = %u,\n"
        "    IMAGES_WIDE_ASC  = %u,\n"
        "    IMAGES_WIDE_BASE = %u,\n"
        "    IMAGES_WIDE_DESC = %u\n"
        "};\n"
        "\n"
        "extern const unsigned char images_data[IMAGES_BYTES];\n"
        "\n",

        BITMAP_W, BITMAP_H, 4 * BITMAP_W * BITMAP_H,
        0, 16, 20, 2, 18, 20
    );

    fprintf(cpp,
        "#include \"images.hpp\"\n"
        "\n"
        "/* IMAGES.CPP\n"
        " * \n"
        " * This file is automatically generated.\n"
        " */\n"
        "\n"
        "const unsigned char images_data[IMAGES_BYTES] = {\n"
    );


#define LMDATA(path)                                                            \
        L"X:\\Applications\\Games\\Steam\\steamapps\\common\\La-Mulana\\data\\" \
        L##path
    Image base_menu(LMDATA("graphics\\00\\01menu.png"));
    Image base_misc(LMDATA("graphics\\00\\00item.png"));
    Image base_prof(LMDATA("graphics\\00\\00prof.png"));
    Image base_char(LMDATA("graphics\\00\\02shop.png"));
    Image base_font(LMDATA("language\\en\\font00.png"));
    Image base_fontlm(LMDATA("language\\en\\font01.png"));
    Image base_shrine(LMDATA("graphics\\00\\map09_1.png"));
    Image base_effect(LMDATA("graphics\\00\\01effect.png"));
#undef LMDATA

    fprintf(hpp, "#define X_IMAGE                            ");
    DRAW(INVALID, 0, 0);
    imageSet(base_menu, 620, 0, 40, 40);

    // Main weapons
    draw(WHIP_1, 0, 0);
    draw(WHIP_2, 1, 0);
    draw(WHIP_3, 2, 0);
    draw(KNIFE, 3, 0);
    draw(KEY_SWORD_1, 4, 0);
    draw(KEY_SWORD_2, 7, 0);
    draw(AXE, 5, 0);
    draw(KATANA, 6, 0);
    draw(SHIELD_1, 6, 1);
    draw(SHIELD_2, 5, 7);
    draw(SHIELD_3, 7, 1);
    draw(SHIELD_4, 8, 1);
    draw(ANKH_JEWEL, 9, 1);
    draw(SACRED_ORB, 9, 6);

    // Subweapons
    draw(SHURIKEN, 8, 0);
    draw(ROLLING_SHURIKEN, 9, 0);
    draw(EARTH_SPEAR, 0, 1);
    draw(FLARE, 1, 1);
    draw(BOMB, 2, 1);
    draw(CHAKRAM, 3, 1);
    draw(CALTROPS, 4, 1);
    draw(GUN, 5, 1);

    // Usable items 1
    draw(HAND_SCANNER, 0, 2);
    draw(LAMP_OF_TIME_1, 0, 8);
    draw(LAMP_OF_TIME_2, 5, 2);
    draw(KEY_OF_ETERNITY, 2, 3);
    draw(COG_OF_THE_SOUL, 4, 2);
    draw(POCHETTE_KEY, 6, 2);
    draw(CRYSTAL_SKULL, 8, 2);
    draw(DJED_PILLAR, 1, 2);
    draw(VESSEL_1, 9, 2);
    draw(VESSEL_2, 7, 7);
    draw(VESSEL_3, 8, 7);
    draw(VESSEL_4, 9, 7);

    // Usable items 2
    draw(SERPENT_STAFF, 3, 3);
    draw(DRAGON_BONE, 7, 2);
    draw(MAGATAMA_JEWEL, 3, 2);
    draw(WOMAN_STATUE, 1, 3);
    draw(MATERNITY_STATUE, 1, 8);
    draw(MINI_DOLL, 2, 2);
    draw(PEPPER, 0, 3);
    draw(TALISMAN, 4, 3);
    draw(DIARY, 2, 7);
    draw(MULANA_TALISMAN, 3, 7);

    // Treasures 1
    draw(MSX_1, 5, 3);
    draw(MSX_2, 6, 7);
    draw(WATERPROOF_CASE, 6, 3);
    draw(HEATPROOF_CASE, 7, 3);
    draw(HOLY_GRAIL_1, 0, 4);
    draw(HOLY_GRAIL_2, 3, 8);
    draw(HOLY_GRAIL_3, 2, 8);
    draw(FEATHER, 3, 5);
    draw(GRAPPLE_CLAW, 4, 4);
    draw(HERMES_BOOTS, 7, 5);
    draw(ISIS_PENDANT, 1, 4);
    draw(BRONZE_MIRROR, 5, 4);
    draw(OCARINA, 2, 5);

    // Treasures 2
    draw(HELMET, 3, 4);
    draw(FRUIT_OF_EDEN, 8, 5);
    draw(TWIN_STATUE, 9, 5);
    draw(DIMENSIONAL_KEY, 3, 6);
    draw(EYE_OF_TRUTH, 6, 4);
    draw(PLANE_MODEL, 1, 5);
    draw(TREASURES, 1, 7);
    draw(ANCHOR, 0, 5);

    // Treasures 3
    draw(SHELL_HORN, 8, 3);
    draw(GLOVE, 9, 3);
    draw(SCALESPHERE, 8, 4);
    draw(ICE_CAPE, 4, 6);
    draw(BOOK_OF_THE_DEAD, 4, 5);
    draw(GAUNTLET, 9, 4);
    draw(RING, 7, 4);
    draw(FAIRY_CLOTHES, 5, 5);

    // Treasures 4
    draw(SCRIPTURES, 6, 5);
    draw(PERFUME, 1, 6);
    draw(CRUCIFIX, 2, 4);
    draw(BRACELET, 0, 6);
    draw(SPAULDER, 2, 6);
    draw(BATHING_SUIT, 4, 7);
    draw(MAP, 0, 7);
    DRAW(SHRINE_MAP, 40, 40) {
        imageDraw(&base_menu,
            620, 280, 40, 40,
            draw_x, draw_y, 40, 40);
        imageDraw(&base_effect,
            433, 604, 13, 19,
            draw_x + 10, draw_y + 10, 13, 19);
    }

    // Seals
    draw(SEAL_1, 5, 6);
    draw(SEAL_2,  6, 6);
    draw(SEAL_3,   7, 6);
    draw(SEAL_4,  8, 6);
    imageSet(base_misc, 0, 86, 40, 40);
    draw(WALL_SEAL_1, 1, 0);
    draw(WALL_SEAL_2, 2, 0);
    draw(WALL_SEAL_3, 3, 0);
    draw(WALL_SEAL_4, 4, 0);
    imageSet(base_menu, 620, 0, 40, 40);

    // Software
    draw(READER,   0,  9);
    draw(XMAILER,  1,  9);
    draw(YAGOMAP,  2,  9);
    draw(YAGOSTR,  3,  9);
    draw(BUNEMON,  4,  9);
    draw(BUNPLUS,  5,  9);
    draw(TORUDE,   6,  9);
    draw(GUILD,    7,  9);
    draw(MANTRA,   8,  9);
    draw(EMUSIC,   9,  9);
    draw(BEOLAMU,  0, 10);
    draw(DEATHV,   1, 10);
    draw(RANDC,    2, 10);
    draw(CAPSTAR,  3, 10);
    draw(MOVE,     4, 10);
    draw(MEKURI,   5, 10);
    draw(BOUNCE,   6, 10);
    draw(MIRACLE,  7, 10);
    draw(MIRAI,    8, 10);
    draw(LAMULANA, 9, 10);

    // Software icons
    DRAW(COMBO_DEV_ROOMS, 40, 40) {
        imageDraw(&base_char, 978, 130, 40, 40, draw_x, draw_y, 40, 40);
    }
    DRAW(COMBO_IFRAMES, 40, 40) {
        imageDraw(&base_prof, 600, 244, 40, 40, draw_x, draw_y, 40, 40);
    }
    DRAW(COMBO_REVIVE, 40, 40) {
        imageDraw(&base_prof, 522, 144, 40, 40, draw_x, draw_y, 40, 40);
    }
    DRAW(COMBO_NON_WHIP, 40, 40) {
        imageDraw(&base_menu, 940, 6, -40, 34, draw_x, draw_y, 40, 34);
        imageDraw(&base_menu, 820, 0,  40, 40, draw_x, draw_y, 40, 40);
        imageDraw(&base_menu, 900, 0, -40, 38, draw_x, draw_y, 40, 38);
        imageDraw(&base_menu, 748, 0,  32, 40, draw_x, draw_y, 32, 40);
    }
    DRAW(COMBO_WHIP, 40, 40) {
        imageDraw(&base_menu, 710, 0, 30, 40, draw_x,     draw_y, 30, 40);
        imageDraw(&base_menu, 664, 0, 36, 40, draw_x,     draw_y, 36, 40);
        imageDraw(&base_menu, 620, 0, 38, 40, draw_x + 2, draw_y, 38, 40);
    }
    DRAW(COMBO_FAIRY_1, 40, 40) {
        imageDraw(&base_misc, 320, 170, 40, 40, draw_x, draw_y, 40, 40);
        imageDraw(&base_misc,   0, 170, 40, 40, draw_x, draw_y, 40, 40);
    }
    DRAW(COMBO_FAIRY_2, 40, 40) {
        imageDraw(&base_misc, 320, 170, 40, 40, draw_x, draw_y, 40, 40);
        imageDraw(&base_misc,   0, 210, 40, 40, draw_x, draw_y, 40, 40);
    }
    DRAW(COMBO_FAIRY_3, 40, 40) {
        imageDraw(&base_misc, 320, 170, 40, 40, draw_x, draw_y, 40, 40);
        imageDraw(&base_misc,   0, 250, 40, 40, draw_x, draw_y, 40, 40);
    }
    DRAW(COMBO_FAIRY_4, 40, 40) {
        imageDraw(&base_char, 860, 130, 40, 40, draw_x, draw_y, 40, 40);
    }

    // Guardian wedges
    DRAW(WEDGE_1, 40, 40) {
        imageDraw(&base_shrine,  40, 500, 100, 100, draw_x, draw_y, 40, 40);
    }
    DRAW(WEDGE_2, 40, 40) {
        imageDraw(&base_shrine, 140, 500, 100, 100, draw_x, draw_y, 40, 40);
    }
    DRAW(WEDGE_3, 40, 40) {
        imageDraw(&base_shrine, 240, 500, 100, 100, draw_x, draw_y, 40, 40);
    }
    DRAW(WEDGE_4, 40, 40) {
        imageDraw(&base_shrine, 340, 500, 100, 100, draw_x, draw_y, 40, 40);
    }
    DRAW(WEDGE_5, 40, 40) {
        imageDraw(&base_shrine, 440, 500, 100, 100, draw_x, draw_y, 40, 40);
    }
    DRAW(WEDGE_6, 40, 40) {
        imageDraw(&base_shrine, 540, 500, 100, 100, draw_x, draw_y, 40, 40);
    }
    DRAW(WEDGE_7, 40, 40) {
        imageDraw(&base_shrine, 640, 500, 100, 100, draw_x, draw_y, 40, 40);
    }
    DRAW(WEDGE_8, 40, 40) {
        imageDraw(&base_shrine, 740, 500, 100, 100, draw_x, draw_y, 40, 40);
    }
    DRAW(WEDGE_BROKEN, 40, 40) {
        imageDraw(&base_shrine, 840, 500, 100, 100, draw_x, draw_y, 40, 40);
    }

    // Guardian ankh
    imageSet(base_effect, 880, 0, 40, 40);
    draw(ANKH, 0, 0);

    // Weights, ammo, secret treasure of life
    imageSet(base_menu, 620, 0, 40, 40);
    draw(WEIGHT,         6, 8);
    draw(BULLETS,        5, 8);
    draw(SECRET_OF_LIFE, 4, 8);

    // Ammo counts
    draw_x = 0;
    draw_y = 360;
    imageSet(base_misc, 0, 0, 10, 16);
    draw(AMMO_0, 0, 0);
    draw(AMMO_1, 1, 0);
    draw(AMMO_2, 2, 0);
    draw(AMMO_3, 3, 0);
    draw(AMMO_4, 4, 0);
    draw(AMMO_5, 5, 0);
    draw(AMMO_6, 6, 0);
    draw(AMMO_7, 7, 0);
    draw(AMMO_8, 8, 0);
    draw(AMMO_9, 9, 0);
    DRAW(AMMO_COLON, 6, 16) {
        imageDraw(&base_misc, 136, 0, 6, 16, draw_x, draw_y, 6, 16);
    }
    draw_x = 120;
    draw_y = 320;

    // NPCs
    imageSet(base_char, 0, 660, 40, 60);
    draw(NPC_XELPUD,       0, 4);
    draw(NPC_MULBRUK,      0, 5);
    draw(NPC_FREYA,       18, 2);
    draw(NPC_VILLAGER_1,   1, 0);
    draw(NPC_VILLAGER_2,   0, 1);
    draw(NPC_NEBUR,        0, 3);
    draw(NPC_PRIEST,       0, 2);
    draw(NPC_GHOST,        0, 0);
    draw(NPC_SARCOGHAGUS,  7, 0);
    draw(NPC_GYONIN,       9, 1);
    draw(NPC_MUDMAN,      13, 1);
    draw(NPC_ROBOT,       19, 1);
    draw(NPC_STRAY_FAIRY, 21, 1);
    imageSet(base_char, 980, 120, 40, 60);
    draw(NPC_GILTORIYO,    0,  7);
    draw(NPC_ALSEDANA,     0,  8);
    draw(NPC_SAMARANTA,    0,  9);
    draw(NPC_FOBOS,        0, 10);
    draw(NPC_NARAMURA,     0,  0);
    draw(NPC_DUPLEX,       0,  1);
    draw(NPC_SAMIERU,      0,  2);
    draw(NPC_XELPUD8,      0,  3);
    draw(NPC_FAIRY8,       0,  4);
    draw(NPC_DRACUET,      0,  5);
    imageSet(base_char, 480, 440, 40, 60);
    draw(NPC_MULBRUK_S,    0,  0);
    draw(NPC_PHIL_S,       1,  0);
    imageSet(base_char, 304, 580, 40, 60);
    draw(NPC_GIANT,        0,  0);

    imageLine();

    // Alphabet
    imageSet(base_font, 0, 0, 20, 20, 21, 21);
    draw(WIDE_A, 38, 20);
    draw(WIDE_B, 39, 20);
    draw(WIDE_C, 40, 20);
    draw(WIDE_D, 41, 20);
    draw(WIDE_E, 42, 20);
    draw(WIDE_F, 43, 20);
    draw(WIDE_G, 44, 20);
    draw(WIDE_H, 45, 20);
    draw(WIDE_I, 46, 20);
    draw(WIDE_J, 47, 20);
    draw(WIDE_K,  0, 21);
    draw(WIDE_L,  1, 21);
    draw(WIDE_M,  2, 21);
    draw(WIDE_N,  3, 21);
    draw(WIDE_O,  4, 21);
    draw(WIDE_P,  5, 21);
    draw(WIDE_Q, 42, 21);
    draw(WIDE_R,  6, 21);
    draw(WIDE_S,  7, 21);
    draw(WIDE_T,  8, 21);
    draw(WIDE_U,  9, 21);
    draw(WIDE_V, 10, 21);
    draw(WIDE_W, 11, 21);
    draw(WIDE_X, 12, 21);
    draw(WIDE_Y, 13, 21);
    draw(WIDE_Z, 43, 21);
    draw(WIDE_0, 28, 20);
    draw(WIDE_1, 29, 20);
    draw(WIDE_2, 30, 20);
    draw(WIDE_3, 31, 20);
    draw(WIDE_4, 32, 20);
    draw(WIDE_5, 33, 20);
    draw(WIDE_6, 34, 20);
    draw(WIDE_7, 35, 20);
    draw(WIDE_8, 36, 20);
    draw(WIDE_9, 37, 20);
    imageSet(base_fontlm, 588, 420, 20, 20, 21, 21);
    draw(LM_0, 0, 0);
    draw(LM_1, 1, 0);
    draw(LM_2, 2, 0);
    draw(LM_3, 3, 0);
    draw(LM_4, 4, 0);
    draw(LM_5, 5, 0);
    draw(LM_6, 6, 0);
    draw(LM_7, 7, 0);
    draw(LM_8, 8, 0);
    draw(LM_9, 9, 0);

    DRAW(LM_1_FLIP, 20, 20) {
        imageDraw(&base_fontlm, 630, 420, -20, 20, draw_x, draw_y, 20, 20);
    }
    DRAW(LM_2_FLIP, 20, 20) {
        imageDraw(&base_fontlm, 651, 420, -20, 20, draw_x, draw_y, 20, 20);
    }
    DRAW(LM_3_FLIP, 20, 20) {
        imageDraw(&base_fontlm, 672, 420, -20, 20, draw_x, draw_y, 20, 20);
    }
    DRAW(LM_4_FLIP, 20, 20) {
        imageDraw(&base_fontlm, 693, 420, -20, 20, draw_x, draw_y, 20, 20);
    }
    DRAW(LM_5_FLIP, 20, 20) {
        imageDraw(&base_fontlm, 714, 420, -20, 20, draw_x, draw_y, 20, 20);
    }
    DRAW(LM_6_FLIP, 20, 20) {
        imageDraw(&base_fontlm, 735, 420, -20, 20, draw_x, draw_y, 20, 20);
    }
    DRAW(LM_7_FLIP, 20, 20) {
        imageDraw(&base_fontlm, 756, 420, -20, 20, draw_x, draw_y, 20, 20);
    }
    DRAW(LM_8_FLIP, 20, 20) {
        imageDraw(&base_fontlm, 777, 420, -20, 20, draw_x, draw_y, 20, 20);
    }

    DRAW(KEY_DOOR, 20, 20) {
        ColorMatrix matrix_white = {
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        base_attr->SetColorMatrix(&matrix_white, 
            ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
        imageDraw(&base_effect, 480, 604, 14, 20, draw_x, draw_y, 14, 20);
        base_attr->SetToIdentity(ColorAdjustTypeBitmap);
    }

    DRAW(ARROWR, 20, 20) {
        imageDraw(&base_font, 294, 504, 14, 20, draw_x + 5, draw_y, 14, 20);
    }
    DRAW(ARROWLR, 20, 20) {
        imageDraw(&base_font, 336, 504, 14, 20, draw_x + 0, draw_y, 14, 20);
        imageDraw(&base_font, 294, 504, 14, 20, draw_x + 5, draw_y, 14, 20);
    }

    imageSet(base_font, 0, 0, 20, 21, 21, 21);
    draw_w(0, 10, 0, 10);
    DRAW(1, 10, 20) {
        imageDraw(&base_font, 229, 0, 10, 20, draw_x, draw_y, 10, 20);
    }
    draw_w(2, 12, 0, 10);
    draw_w(3, 13, 0, 10);
    draw_w(4, 14, 0, 10);
    draw_w(5, 15, 0, 10);
    draw_w(6, 16, 0, 10);
    draw_w(7, 17, 0, 10);
    draw_w(8, 18, 0, 10);
    draw_w(9, 19, 0, 10);
    draw_w(A, 22, 0, 12);
    draw_w(B, 23, 0, 10);
    draw_w(C, 24, 0, 12);
    draw_w(D, 25, 0, 12);
    draw_w(E, 26, 0,  9);
    draw_w(F, 27, 0,  9);
    draw_w(G, 28, 0, 12);
    draw_w(H, 29, 0, 12);
    draw_w(I, 30, 0,  5);
    draw_w(J, 31, 0,  8);
    draw_w(K, 32, 0, 11);
    draw_w(L, 33, 0,  9);
    draw_w(M, 34, 0, 15);
    draw_w(N, 35, 0, 13);
    draw_w(O, 36, 0, 12);
    draw_w(P, 37, 0,  9);
    draw_w(Q, 38, 0, 13);
    draw_w(R, 39, 0, 10);
    draw_w(S, 40, 0,  8);
    draw_w(T, 41, 0, 10);
    draw_w(U, 42, 0, 12);
    draw_w(V, 43, 0, 12);
    draw_w(W, 44, 0, 17);
    draw_w(X, 45, 0, 12);
    draw_w(Y, 46, 0, 11);
    draw_w(Z, 47, 0, 10);
    draw_w(a,  4, 1,  8);
    draw_w(b,  5, 1,  9);
    draw_w(c,  6, 1,  8);
    draw_w(d,  7, 1,  9);
    draw_w(e,  8, 1,  8);
    draw_w(f,  9, 1,  6);
    draw_w(g, 10, 1, 10);
    draw_w(h, 11, 1,  9);
    draw_w(i, 12, 1,  4);
    draw_w(j, 13, 1,  4);
    draw_w(k, 14, 1,  9);
    draw_w(l, 15, 1,  4);
    draw_w(m, 16, 1, 13);
    draw_w(n, 17, 1,  9);
    draw_w(o, 18, 1,  8);
    draw_w(p, 19, 1,  9);
    draw_w(q, 20, 1,  9);
    draw_w(r, 21, 1,  6);
    draw_w(s, 22, 1,  6);
    draw_w(t, 23, 1,  6);
    draw_w(u, 24, 1,  9);
    draw_w(v, 25, 1,  9);
    draw_w(w, 26, 1, 12);
    draw_w(x, 27, 1,  8);
    draw_w(y, 28, 1,  8);
    draw_w(z, 29, 1,  7);

    DRAW(u_NUWA, 12, 20) {
        imageDraw(&base_font, 235, 527, 12, 20, draw_x, draw_y, 12, 20);
    }
    DRAW(PERIOD, 5, 20) {
        imageDraw(&base_font, 168, 0, 6, 20, draw_x, draw_y, 6, 20);
    }
    DRAW(COMMA, 5, 20) {
        imageDraw(&base_font, 126, 0, 5, 20, draw_x, draw_y, 5, 20);
    }
    DRAW(ELLIPSIS, 19, 20) {
        imageDraw(&base_font, 631, 16, 19, 20, draw_x, draw_y, 19, 20);
    }
    DRAW(HYPHEN, 8, 20) {
        imageDraw(&base_font, 147, 0, 6, 20, draw_x, draw_y, 6, 20);
    }
    DRAW(COLON, 5, 20) {
        imageDraw(&base_font, 491, 421, 5, 20, draw_x, draw_y, 5, 20);
    }
    DRAW(APOSTROPHE, 5, 20) {
        imageDraw(&base_font, 62, 0, 5, 20, draw_x, draw_y, 5, 20);
    }
    DRAW(ASTERISK, 9, 20) {
        imageDraw(&base_font, 274, 530, 9, 20, draw_x, draw_y, 9, 20);
    }
    DRAW(PAREN_L, 7, 20) {
        imageDraw(&base_font, 476, 483, 7, 20, draw_x, draw_y, 7, 20);
    }
    DRAW(PAREN_R, 7, 20) {
        imageDraw(&base_font, 483, 483, 7, 20, draw_x, draw_y, 7, 20);
    }
    DRAW(QUESTION, 12, 20) {
        imageDraw(&base_font, 529, 420, 12, 20, draw_x, draw_y, 12, 20);
    }
    DRAW(HEART, 18, 20) {
        imageDraw(&base_font, 252, 525, 18, 20, draw_x, draw_y, 18, 20);
    }

    BitmapData bitmap_data;
    bitmap->LockBits(&output_bounds, ImageLockModeRead,
        PixelFormat32bppPARGB, &bitmap_data);

    for (int i = 0; i < bitmap_data.Height; ++i) {
        fprintf(cpp, "\n");
        char *scan = (char *)bitmap_data.Scan0 + i * bitmap_data.Stride;
        for (int j = 0; j < bitmap_data.Width; ++j) {
            unsigned char pixel[4];
            pixel[0] = *scan++;
            pixel[1] = *scan++;
            pixel[2] = *scan++;
            pixel[3] = *scan++;
            fprintf(cpp, "0x%02X,0x%02X,0x%02X,0x%02X,\n",
                pixel[0], pixel[1], pixel[2], pixel[3]);
        }
    }

    fprintf(hpp, "\n\n#endif /* IMAGES_HGUARD */\n");
    fprintf(cpp, "\n};\n");

    fflush(hpp);
    fflush(cpp);

#if 1
    CLSID enc_bitmap;
    UINT enc_count = 0, enc_size = 0;
    GetImageEncodersSize(&enc_count, &enc_size);
    ImageCodecInfo *enc_info = (ImageCodecInfo *)malloc(enc_size);
    GetImageEncoders(enc_count, enc_size, enc_info);

    for (int i = 0; i < enc_count; ++i) {
        if (!wcscmp(enc_info[i].MimeType, L"image/bmp")) {
            enc_bitmap = enc_info[i].Clsid;
            break;
        }
    }

    bitmap->Save(L"images.bmp", &enc_bitmap, NULL);
    free(enc_info);
#endif

    GdiplusShutdown(gdi_token);
}
