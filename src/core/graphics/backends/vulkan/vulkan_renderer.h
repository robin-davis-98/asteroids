#ifndef PET_VULKAN_RENDERER_H
#define PET_VULKAN_RENDERER_H

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

struct Vulkan_Context {
    VkInstance instance;
    VkPhysicalDevice physical_device;
    VkDevice device;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapchain;
};

#endif