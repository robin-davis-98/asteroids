#include "win32_common.h"
#include <petrichor_mem.h>
#include <petrichor_time.h>
#include <graphics/renderer.h>
#include "game.h"

static bool g_Running = true;

LRESULT CALLBACK win32_event_callback(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CLOSE: {
            g_Running = false;
            return 0;
        } break;
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        } break;
    }
    return DefWindowProcA(handle, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmd_line, int show_cmd) {
    Platform_Memory_Block main_mem = platform_allocate_memory(10 * 1024 * 1024);

    Arena main_arena = {};
    main_arena.size = main_mem.size;
    main_arena.base = (uint8_t*)main_mem.base;

    Renderer* renderer = (Renderer*)push_size(&main_arena, sizeof(Renderer));
    renderer->width = 800;
    renderer->height = 600;
    renderer->arena = &main_arena;

    bool use_dx12 = false;
    if (strstr(cmd_line, "--dx12")) use_dx12 = true;

    WNDCLASSA wc = {};
    wc.hInstance = instance;
    wc.lpszClassName = "PetrichorWindowClass";
    wc.lpfnWndProc = win32_event_callback;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassA(&wc)) {
        return -1;
    }

    HWND hwnd = CreateWindowExA(
        0,
        wc.lpszClassName,
        GAME_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        0, 0, instance, 0);

    if (!hwnd) {
        return -1;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    win32_init_renderer(renderer, hwnd, instance, use_dx12);

    Timer game_timer = {};
    time_init(&game_timer);

    while (g_Running) {
        MSG msg;
        while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                g_Running = false;
            }
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }

    win32_shutdown_renderer(renderer, use_dx12);
    platform_free_memory(main_mem);
}