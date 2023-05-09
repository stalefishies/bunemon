//#include "common.hpp"

//#define TORUDE_IMPLEMENTATION
//#include "torude.h"

#include "common.cpp"
#include "images.cpp"
#include "bitmap.cpp"
#include "fields.cpp"
#include "memory.cpp"
#include "items.cpp"
#include "rando.cpp"

#pragma comment(lib, "user32")
#pragma comment(lib, "gdiplus")

LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prev_instance, PWSTR cmd_line, int show_command) {
    ULONG_PTR           gdi_token;
    GdiplusStartupInput gdi_input;
    GdiplusStartup(&gdi_token, &gdi_input, NULL);

    WNDCLASSEX window_class = {};
    window_class.cbSize        = sizeof window_class;
    window_class.lpfnWndProc   = &windowProc;
    window_class.hInstance     = instance;
    window_class.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    window_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = NULL;
    window_class.lpszClassName = CLASS_NAME;
    window_class.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&window_class)) {
        MessageBox(NULL, L"Could not register window class", L"ERROR",
            MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    RECT req_rect;
    req_rect.left   = 0;
    req_rect.top    = 0;
    req_rect.right  = DRAW_MIN_W + GetSystemMetrics(SM_CXVSCROLL);
    req_rect.bottom = DRAW_MIN_H;
    AdjustWindowRect(&req_rect, WS_OVERLAPPEDWINDOW, FALSE);

    size.client_min_w = req_rect.right  - req_rect.left;
    size.client_min_h = req_rect.bottom - req_rect.top;
    size.client_w     = size.client_min_w;
    size.client_h     = size.client_min_h;

    HWND window = CreateWindowEx(0,
        CLASS_NAME, WINDOW_NAME,
        WS_OVERLAPPEDWINDOW | WS_VSCROLL,
        CW_USEDEFAULT, CW_USEDEFAULT,
        size.client_w, size.client_h,
        NULL, NULL, instance, NULL);
    if (!window) {
        MessageBox(NULL, L"Could not create window", L"ERROR",
            MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    BunBitmap::init(BACKGROUND, FOREGROUND);
    items.init(ITEMS_X, ITEMS_Y, ITEMS_W, ITEMS_H);
    rando.init(RANDO_X, RANDO_Y, RANDO_W, RANDO_H);

    ShowWindow(window, show_command);
    InvalidateRect(window, NULL, TRUE);

    if (!initRando("spoiler.txt")) {
        MessageBox(window, L"initRando returned false", L"ERROR",
            MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    CreateThread(NULL, 0, &scanThread, NULL, 0, NULL);

    MSG message = {};
    BOOL message_ret = 1;
    while ((message_ret = GetMessage(&message, NULL, 0, 0)) > 0) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    if (message_ret != 0) {
        MessageBox(window, L"GetMessage returned an error", L"ERROR",
            MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    return 0;
}

LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
        default: { return DefWindowProc(window, message, wparam, lparam); } break;

        case WM_CLOSE:   { DestroyWindow(window); } break;
        case WM_DESTROY: { PostQuitMessage(0);    } break;

        case WM_GETMINMAXINFO: {
            MINMAXINFO *minmax = (LPMINMAXINFO)lparam;
            minmax->ptMinTrackSize.x = size.client_min_w;
            minmax->ptMinTrackSize.y = size.client_min_h;
        } break;

        // WM_SIZE handles both window size changes and also rando bitmap size changes
        case WM_SIZE: {
            size.client_w = LOWORD(lparam);
            size.client_h = HIWORD(lparam);

            SCROLLINFO info = {0};
            info.cbSize = sizeof info;
            info.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS | SIF_DISABLENOSCROLL;
            info.nMin   = 0;
            info.nMax   = rando.height - 1;
            info.nPage  = size.client_h;
            info.nPos   = -rando.window_y;
            SetScrollInfo(window, SB_VERT, &info, TRUE);
            rando.window_y = -GetScrollPos(window, SB_VERT);
        } break;

        case WM_LBUTTONDOWN: {
            InvalidateRect(window, NULL, TRUE);
            UpdateWindow(window);
        } break;

        // TODO: https://www.codeproject.com/Articles/1042516/Custom-Controls-in-Win-API-Scrolling
        case WM_MOUSEWHEEL: {
            int delta = GET_WHEEL_DELTA_WPARAM(wparam);
            int old_pos = -rando.window_y;
            int new_pos = old_pos + (delta > 0 ? -44 : 44);

            if (new_pos == old_pos) { return 0; }
            SetScrollPos(window, SB_VERT, new_pos, TRUE);
            rando.window_y = -GetScrollPos(window, SB_VERT);

            RECT rect = {
                RANDO_X, 0, RANDO_X + RANDO_W, size.client_h
            };

            ScrollWindowEx(window, 0, old_pos + rando.window_y,
                &rect, &rect, NULL, NULL, SW_INVALIDATE);
            UpdateWindow(window);
        } break;

        case WM_VSCROLL: {
            int old_pos = -rando.window_y;
            int new_pos = old_pos;

            switch (LOWORD(wparam)) {
                case SB_PAGEUP:        { new_pos += -5 * 22; } break;
                case SB_PAGEDOWN:      { new_pos += +5 * 22; } break;
                case SB_LINEUP:        { new_pos += -1 * 22; } break;
                case SB_LINEDOWN:      { new_pos += +1 * 22; } break;
                case SB_THUMBPOSITION: { new_pos = HIWORD(wparam); } break;
                case SB_THUMBTRACK:    { new_pos = HIWORD(wparam); } break;
            }

            if (new_pos == old_pos) { return 0; }
            SetScrollPos(window, SB_VERT, new_pos, TRUE);
            rando.window_y = -GetScrollPos(window, SB_VERT);

            RECT rect = {
                RANDO_X, 0, RANDO_X + RANDO_W, size.client_h
            };

            ScrollWindowEx(window, 0, old_pos + rando.window_y,
                &rect, &rect, NULL, NULL, SW_INVALIDATE);
            UpdateWindow(window);
        } break;

        case WM_PAINT: {
            PAINTSTRUCT paint;
            HDC window_dc = BeginPaint(window, &paint);
            Gdiplus::Graphics *window_draw = new Graphics(window_dc);

            // Draw background if requested
            if (paint.fErase) {
                RectF rect(paint.rcPaint.left, paint.rcPaint.top,
                    paint.rcPaint.right - paint.rcPaint.left,
                    paint.rcPaint.bottom - paint.rcPaint.top);
                window_draw->FillRectangle(BunBitmap::background, rect);
            }

            items.blit(window_draw, paint.rcPaint);
            rando.blit(window_draw, paint.rcPaint);

            delete window_draw;
            EndPaint(window, &paint);
        } break;
    }

    return 0;
}
