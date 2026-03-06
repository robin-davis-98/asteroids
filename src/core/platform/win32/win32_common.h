#ifndef PET_WIN32_COMMON_H
#define PET_WIN32_COMMON_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>

struct Renderer;

void win32_init_renderer(Renderer* r, HWND hwnd, HINSTANCE instance, bool using_dx12);
void win32_shutdown_renderer(Renderer* r, bool using_dx12);

#endif