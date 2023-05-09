#ifndef COMMON_HPPGUARD
#define COMMON_HPPGUARD

#define _CRT_SECURE_NO_WARNINGS
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <new>

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include <gdiplus.h>
#include <gdiplusheaders.h>
using namespace Gdiplus;

enum {
    SPACING = 20,

    ITEMS_X = 0,
    ITEMS_Y = 0,
    ITEMS_W = 320,
    ITEMS_H = 600,

    RANDO_X = ITEMS_X + ITEMS_W + SPACING,
    RANDO_Y = 0,
    RANDO_W = 720,
    RANDO_H = 4000,

    DRAW_MIN_W = ITEMS_W + RANDO_W + SPACING,
    DRAW_MIN_H = ITEMS_H,

    BACKGROUND = 0xFF000420U,
    FOREGROUND = 0xFF001337U,
};

struct WindowSizes {
    int client_w;
    int client_h;
    int client_min_w;
    int client_min_h;
};

extern HWND window;
extern WindowSizes size;

extern const wchar_t  CLASS_NAME[];
extern const wchar_t WINDOW_NAME[];

/*
struct String {
    uint8_t length;
    char data[255];

    String(void);
    String(size_t length, const char *data);
    void set(size_t length, const char *data);

    char operator[](const int index);
};
*/
struct String {
    size_t length;
    const char *data;

    String(void);
    String(size_t length, const char *data);
    char operator[](const int index);
};
#define strLit(lit) (String((sizeof (lit)) - 1, (lit)))

bool operator ==(const String &a, const String& b);
bool operator ==(const String &a, const char   *b);
bool operator ==(const char   *a, const String& b);
bool operator !=(const String &a, const String& b);
bool operator !=(const String &a, const char   *b);
bool operator !=(const char   *a, const String& b);

#endif /* COMMON_HPPGUARD */
