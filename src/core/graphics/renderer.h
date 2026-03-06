#ifndef PET_RENDERER_H
#define PET_RENDERER_H

#include <stdint.h>
#include <petrichor_mem.h>
#include "backends/vulkan/vulkan_renderer.h"

#if defined(PLATFORM_WINDOWS)
    #include "backends/dx12/dx12_renderer.h"
#endif

struct Renderer {
    uint32_t width, height;
    Arena* arena;

    union {
        Vulkan_Context vk;
        #if defined (PLATFORM_WINDOWS)
          DX12_Context dx12;
        #endif
    } backend;
};

struct Render_Functions {
    void (*begin_frame)(struct Renderer* r);
    void (*end_frame)(struct Renderer* r);
    void (*on_resize)(struct Renderer* r);
    void (*shutdown)(struct Renderer* r);
};

void vulkan_init(Renderer* r, VkSurfaceKHR surface);

#endif