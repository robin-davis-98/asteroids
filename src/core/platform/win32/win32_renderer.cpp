#include "win32_common.h"
#include <graphics/renderer.h>

void win32_init_renderer(Renderer* r, HWND hwnd, HINSTANCE instance, bool using_dx12) {
    if (using_dx12) {
        //dx12_init(r, hwnd, instance);
    } else {
        const char* extensions[] = {
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_WIN32_SURFACE_EXTENSION_NAME
        };
        uint32_t extension_count = sizeof(extensions) / sizeof(extensions[0]);

        vulkan_create_instance(r, extensions, extension_count);

        VkWin32SurfaceCreateInfoKHR surface_info = {
            VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR
        };
        surface_info.hwnd = hwnd;
        surface_info.hinstance = instance;

        VkSurfaceKHR surface;
        if (vkCreateWin32SurfaceKHR(r->backend.vk.instance, &surface_info, nullptr, &surface) != VK_SUCCESS) {
            // Handle error: Surface creation failed
            return;
        }
        vulkan_init(r, surface);
    }
}

void win32_shutdown_renderer(Renderer* r, bool using_dx12) {
    if (using_dx12) {
        // dx12_shutdown(r);
    } else {
        vulkan_shutdown(r);
    }

}