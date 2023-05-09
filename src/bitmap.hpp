#ifndef BITMAP_HPPGUARD
#define BITMAP_HPPGUARD

#include "common.hpp"
#include "images.hpp"

enum {
#define X(NAME, X, Y, W, H) IMG_##NAME,
    X_IMAGE
#undef X
    IMG_COUNT
};

RectF image_rect[IMG_COUNT] = {
#define X(NAME, X, Y, W, H) RectF(X, Y, W, H),
    X_IMAGE
#undef X
};

struct BunBitmap {
    static bool             static_init;
    static Color            color_bg;
    static Color            color_fg;
    static SolidBrush      *background;
    static ImageAttributes *greyscale;
    static Bitmap          *images_bitmap;
    static void init(uint32_t bg, uint32_t fg);

    int window_x;
    int window_y;
    int width;
    int height;

    int update_l;
    int update_t;
    int update_r;
    int update_b;

    Bitmap   *bitmap;
    Graphics *draw;

    void init(int x, int y, int width, int height);

    void drawImage(int x, int y, int name,
        bool colour = true,
        float dst_w = 0, float dst_h = 0,
        float src_l = 0, float src_t = 0,
        float src_r = 0, float src_b = 0);
    void drawBG(int x, int y, int w, int h);
    void drawItem(int x, int y, int name, bool colour = false);
    void drawCount(int x, int y, uint8_t count = 0);
    void drawText(int x, int y, int width, String string, bool wide = false);
    void drawCoord(int x, int y, int zone, int room, int screen, bool tall = false);

    void updateReset();
    void updateAll();
    void update();

    void blit(Graphics *window_draw, RECT paint_rect);
};

#endif /* BITMAP_HPPGUARD */
