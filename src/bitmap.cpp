#include "bitmap.hpp"
#include "fields.hpp"

bool             BunBitmap::static_init    = false;
Color            BunBitmap::color_bg       = Color(0xFF000000U);
Color            BunBitmap::color_fg       = Color(0xFFFFFFFFU);
SolidBrush      *BunBitmap::background     = NULL;
ImageAttributes *BunBitmap::greyscale      = NULL;
Bitmap          *BunBitmap::images_bitmap  = NULL;

void BunBitmap::init(uint32_t bg, uint32_t fg) {
    if (static_init) { return; }

    color_bg = Color(bg);
    color_fg = Color(fg); 
    background = new SolidBrush(color_bg);

    greyscale  = new ImageAttributes();
    ColorMatrix matrix = {
        0.2f, 0.1f, 0.1f, 0.0f, 0.0f,
        0.1f, 0.2f, 0.1f, 0.0f, 0.0f,
        0.1f, 0.1f, 0.2f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    greyscale->SetColorMatrix(&matrix,
        ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

    images_bitmap = new Bitmap(IMAGES_W, IMAGES_H, PixelFormat32bppPARGB);
    Rect images_rect = Rect(0, 0, IMAGES_W, IMAGES_H);
    BitmapData images_info = {};
    images_bitmap->LockBits(&images_rect, ImageLockModeWrite,
        PixelFormat32bppPARGB, &images_info);
    std::memcpy(images_info.Scan0, images_data, IMAGES_BYTES);
    images_bitmap->UnlockBits(&images_info);

    static_init = true;
}


void BunBitmap::init(int _x, int _y, int _w, int _h) {
    width    = _w;
    height   = _h;
    window_x = _x;
    window_y = _y;
    bitmap   = new Bitmap(width, height, PixelFormat32bppPARGB);
    draw     = new Graphics(bitmap);

    draw->SetCompositingMode(CompositingModeSourceOver);
    draw->SetInterpolationMode(InterpolationModeNearestNeighbor);
    draw->Clear(color_bg);

    updateAll();
}

void BunBitmap::drawBG(int x, int y, int w, int h) {
    draw->FillRectangle(background, RectF(x, y, w, h));

    if (x     < update_l) { update_l = x;     }
    if (y     < update_t) { update_t = y;     }
    if (x + w > update_r) { update_r = x + w; }
    if (y + h > update_b) { update_b = y + h; }
}

void BunBitmap::drawImage(int x, int y, int name,
    bool colour, float dst_w, float dst_h,
    float src_l, float src_t, float src_r, float src_b)
{
    RectF src   = image_rect[name];
    float src_x = src.X + src_l;
    float src_y = src.Y + src_t;
    float src_w = src.Width  - src_l + src_r;
    float src_h = src.Height - src_t + src_b;

    if (dst_w <= 0) { dst_w = src.Width;  }
    if (dst_h <= 0) { dst_h = src.Height; }

    draw->DrawImage(images_bitmap, RectF(x, y, dst_w, dst_h),
        src_x, src_y, src_w, src_h,
        UnitPixel, (colour ? NULL : greyscale));

    int dst_l = (x         < 0      ? 0      : x);
    int dst_t = (y         < 0      ? 0      : y);
    int dst_r = (x + dst_w > width  ? width  : x + dst_w);
    int dst_b = (y + dst_h > height ? height : y + dst_h);

    if (dst_l < update_l) { update_l = dst_l; }
    if (dst_t < update_t) { update_t = dst_t; }
    if (dst_r > update_r) { update_r = dst_r; }
    if (dst_b > update_b) { update_b = dst_b; }
}

void BunBitmap::drawItem(int x, int y, int name, bool colour) {
    drawBG(x, y, 40, 40);
    drawImage(x, y, name, colour);
}

void BunBitmap::drawCount(int x, int y, uint8_t count) {
    if (count >= 100) {
        drawImage(x + 14, y + 24, IMG_AMMO_0 + (count / 100) % 10);
    }
    if (count >= 10) {
        drawImage(x + 22, y + 24, IMG_AMMO_0 + (count / 10) % 10);
    }
    drawImage(x + 30, y + 24, IMG_AMMO_0 + count % 10);
}

static const int space_width = 8;

static int charImage(char c) {
    int index = 0;

    if      (c >= 'A' && c <= 'Z') { index = IMG_A + c - 'A'; }
    else if (c >= 'a' && c <= 'z') { index = IMG_a + c - 'a'; }
    else if (c >= '0' && c <= '9') { index = IMG_0 + c - '0'; }
    else if (c ==  '.') { index = IMG_PERIOD;     }
    else if (c ==  ',') { index = IMG_COMMA;      }
    else if (c ==  '-') { index = IMG_HYPHEN;     }
    else if (c ==  ':') { index = IMG_COLON;      }
    else if (c == '\'') { index = IMG_APOSTROPHE; }
    else if (c ==  '*') { index = IMG_ASTERISK;   }
    else if (c ==  '(') { index = IMG_PAREN_L;    }
    else if (c ==  ')') { index = IMG_PAREN_R;    }
    else if (c ==  '?') { index = IMG_QUESTION;   }
    else if (c ==  '#') { index = IMG_u_NUWA;     }
    else if (c ==  '@') { index = IMG_HEART;      }

    return index;
}

static int charWidth(char c) {
    if (c == ' ') {
        return space_width;
    } else {
        return (int)(image_rect[charImage(c)].Width);
    }
}

void BunBitmap::drawText(int x, int y, int width, String string, bool wide) {
    int length = string.length;
    if (width > 0) {
        int pos = 0;
        for (length = 0; length < string.length; ++length) {
            char c = string.data[length];
            if (!c) { break; }

            int w = charWidth(c);
            if (pos + w > width) { break; }
            pos += w;
        }

        if (length < string.length) {
            int ell_w = (int)(image_rect[IMG_ELLIPSIS].Width);

            while (pos + ell_w > width) {
                if (length == 0) { break; }
                char c = string.data[length - 1];
                pos -= charWidth(c);
                --length;
            }

            while (length > 0) {
                char c = string.data[length - 1];
                if (c >= 'A' && c <= 'Z'
                    || c >= 'a' && c <= 'z'
                    || c >= '0' && c <= '9'
                    || c == '#' || c == '@')
                { break; }
                --length;
            }
        }
    }

    int cursor = x;
    for (int i = 0; i < length; ++i) {
        char c = string.data[i];
        if (c == 0) { break; }

        int image = IMG_INVALID;
        if (wide) {
            if      (c >= 'A' && c <= 'Z') { image = IMG_WIDE_A + c - 'A'; }
            else if (c >= 'a' && c <= 'z') { image = IMG_WIDE_A + c - 'a'; }
            else if (c >= '0' && c <= '9') { image = IMG_WIDE_0 + c - '0'; }
            else if (c == ' ') { cursor += 20; }
        } else if (c == ' ') {
            cursor += space_width;
        } else {
            image = charImage(c);
        }

        if (image > IMG_INVALID && image < IMG_COUNT) {
            drawImage(cursor, y, image);
            cursor += (int)(image_rect[image].Width);
        }
    }

    if (width > 0 && length < string.length
        && cursor + (int)(image_rect[IMG_ELLIPSIS].Width) <= x + width)
    { drawImage(cursor, y, IMG_ELLIPSIS); }
}

static const int zone_images[FIELD_MAX_ZONE] = {
    IMG_LM_1, IMG_LM_0, IMG_LM_2, IMG_LM_3, IMG_LM_4,
    IMG_LM_5, IMG_LM_6, IMG_LM_7, IMG_LM_8, IMG_LM_9,
    IMG_LM_1_FLIP, IMG_LM_2_FLIP, IMG_LM_3_FLIP, IMG_LM_4_FLIP, IMG_LM_5_FLIP,
    IMG_LM_6_FLIP, IMG_LM_6_FLIP, IMG_LM_8_FLIP, IMG_LM_9, IMG_LM_2,
    IMG_LM_1, IMG_LM_0, IMG_LM_0, IMG_LM_0, IMG_LM_0, IMG_LM_0
};

void BunBitmap::drawCoord(int x, int y, int zone, int room, int screen, bool tall) {
    if (tall) { drawBG(x, y, 40, 40); } else { drawBG(x, y, 60, 20); }

    int room_x = -1;
    int room_y = -1;
    bool valid = fieldCoord(zone, room, screen, &room_x, &room_y);

    if (!valid) {
        if (tall) {
            drawImage(x + 14, y + 10, IMG_QUESTION);
        } else {
            drawImage(x + 24, y +  0, IMG_QUESTION);
        }
        return;
    }

    int img_x = IMG_WIDE_A + room_x;
    int img_z = zone_images[zone];
    if (zone == 7 && room > 8) { img_z = IMG_LM_7_FLIP; }

    ++room_y;
    int img_y1 = IMG_INVALID;
    int img_y2 = IMG_INVALID;

    if (room_y < 10) {
        img_y1 = IMG_WIDE_0 + room_y;
    } else {
        img_y1 = IMG_0 + (room_y / 10) % 10;
        img_y2 = IMG_0 + (room_y /  1) % 10;
    }

    if (tall) {
        drawImage(x + 10, y, img_z);
        drawImage(x, y + 20, img_x);

        if (img_y2) {
            drawImage(x + 21, y + 22, img_y1);
            drawImage(x + 30, y + 20, img_y2);
        } else {            
            drawImage(x + 20, y + 20, img_y1);
        }
    } else {
        drawImage(x, y, img_z);
        drawImage(x + 20, y, img_x);

        if (img_y2) {
            drawImage(x + 41, y + 2, img_y1);
            drawImage(x + 50, y + 2, img_y2);
        } else {            
            drawImage(x + 40, y, img_y1);
        }
    }
}

void BunBitmap::updateReset() {
    update_l = width;
    update_t = height;
    update_r = 0;
    update_b = 0;
}

void BunBitmap::updateAll() {
    update_l = 0;
    update_t = 0;
    update_r = width;
    update_b = height;
}

void BunBitmap::update() {
    if (update_l < update_r && update_t < update_b) {
        RECT rect;
        rect.left   = window_x + update_l;
        rect.right  = window_x + update_r;
        rect.top    = window_y + update_t;
        rect.bottom = window_y + update_b;
        InvalidateRect(window, &rect, FALSE);
    }

    updateReset();
}

void BunBitmap::blit(Graphics *wdraw, RECT rect) {
    if (bitmap) {
        INT client_l = max(rect.left,   window_x);
        INT client_r = min(rect.right,  window_x + width);
        INT client_t = max(rect.top,    window_y);
        INT client_b = min(rect.bottom, window_y + height);

        if (client_l < client_r && client_t < client_b) {
            wdraw->DrawImage(bitmap, client_l, client_t,
                client_l - window_x, client_t - window_y,
                client_r - client_l, client_b - client_t, UnitPixel);
        }
    }
}
