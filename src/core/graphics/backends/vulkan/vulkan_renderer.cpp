#include "vulkan_renderer.h"
#include <graphics/renderer.h>

void vulkan_create_instance(Renderer* r, const char** extensions, uint32_t extension_count) {
    Vulkan_Context* vk = &r->backend.vk;

    uint32_t engine_version = VK_MAKE_API_VERSION(0, ENGINE_VER_MAJOR, ENGINE_VER_MINOR, ENGINE_VER_PATCH);
    uint32_t game_version   = VK_MAKE_API_VERSION(0, GAME_VER_MAJOR,   GAME_VER_MINOR,   GAME_VER_PATCH);

    VkApplicationInfo app_info = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
    app_info.pApplicationName = GAME_NAME;
    app_info.applicationVersion = game_version;
    app_info.pEngineName = "Petrichor";
    app_info.engineVersion = engine_version;
    app_info.apiVersion = VK_API_VERSION_1_2;

    VkInstanceCreateInfo create_info = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    create_info.pApplicationInfo = &app_info;
    create_info.enabledExtensionCount = extension_count;
    create_info.ppEnabledExtensionNames = extensions;

    vkCreateInstance(&create_info, nullptr, &vk->instance);
}

void vulkan_init(Renderer* r, VkSurfaceKHR surface) {
    Vulkan_Context* vk = &r->backend.vk;
    vk->surface = surface;

    Scratch temporary_mem = scratch_begin(r->arena);

    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(vk->instance, &device_count, nullptr);
    if (device_count != 0) {
        VkPhysicalDevice* devices = push_array(r->arena, VkPhysicalDevice, device_count);
        vkEnumeratePhysicalDevices(vk->instance, &device_count, devices);
        for (uint32_t i = 0; i < device_count; i++) {
            VkPhysicalDeviceProperties props;
            vkGetPhysicalDeviceProperties(devices[i], &props);

            if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                vk->physical_device = devices[i];
                break;
            }
        }

        if (vk->physical_device == VK_NULL_HANDLE) {
            vk->physical_device = devices[0];
        }
    }

    scratch_end(temporary_mem);
}