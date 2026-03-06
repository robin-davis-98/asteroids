cmake_minimum_required(VERSION 3.20)
project(asteroids)

set(GAME_NAME "Asteroids")
set(GAME_VER_MAJOR 0)
set(GAME_VER_MINOR 1)
set(GAME_VER_PATCH 0)

set(ENGINE_VER_MAJOR 2)
set(ENGINE_VER_MINOR 1)
set(ENGINE_VER_PATCH 0)

set(CMAKE_CXX_STANDARD 20)

add_executable(asteroids)

set(SOURCE_CODE_DIR ${CMAKE_SOURCE_DIR}/src/)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
set(VENDORS_DIR ${CMAKE_SOURCE_DIR}/vendors/)

# COMMON
set(COMMON_CODE_DIR ${SOURCE_CODE_DIR}common/)

set(COMMON_SOURCES
    ${COMMON_CODE_DIR}petrichor_mem.cpp
)

# CORE
set(CORE_CODE_DIR ${SOURCE_CODE_DIR}core/)
set(GRAPHICS_CODE_DIR ${CORE_CODE_DIR}graphics/)
set(PLATFORM_CODE_DIR ${CORE_CODE_DIR}platform/)

set(VULKAN_CODE_DIR ${GRAPHICS_CODE_DIR}backends/vulkan/)

set(VULKAN_SOURCES
        ${VULKAN_CODE_DIR}vulkan_renderer.cpp
)

if (WIN32)
    set(DX12_CODE_DIR ${GRAPHICS_CODE_DIR}backends/dx12/)

    set(DX12_SOURCES
        ${DX12_CODE_DIR}dx12_renderer.cpp
    )

    set(PLATFORM_SOURCES
            ${PLATFORM_CODE_DIR}win32/win32_main.cpp
            ${PLATFORM_CODE_DIR}win32/win32_time.cpp
    )

    add_compile_definitions(asteroids
        PLATFORM_WINDOWS
    )

    target_link_libraries(asteroids
        PRIVATE
            user32
            gdi32
            shell32
            d3d12
            dxgi
            d3dcompiler
    )
    set_target_properties(asteroids PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if(UNIX)
    set(LINUX_BACKEND "Wayland" CACHE STRING "Linux backend (X11 or Wayland)")

    if (LINUX_BACKEND STREQUAL "Wayland")
        target_compile_definitions(asteroids PRIVATE
            PLATFORM_LINUX_WAYLAND
        )
    elseif(LINUX_BACKEND STREQUAL "X11")
        target_compile_definitions(asteroids PRIVATE
            PLATFORM_LINUX_X11
        )
    endif()
endif()

# RUNTIME
set(GAME_CODE_DIR ${SOURCE_CODE_DIR}game/)

# VENDORS
set(VENDOR_SOURCES
    ${CORE_CODE_DIR}vendor_impl.cpp
)

set(VENDOR_INCLUDE
        ${VENDORS_DIR}
        ${VENDORS_DIR}glm
)

# =========================================

target_include_directories(asteroids
    PUBLIC
        ${INCLUDE_DIR}
        ${COMMON_CODE_DIR}
        ${CORE_CODE_DIR}
        ${GAME_CODE_DIR}
    PRIVATE
        ${VENDOR_INCLUDE}
        ${Vulkan_INCLUDE_DIRS}
)

target_sources(asteroids
    PRIVATE
        ${PLATFORM_SOURCES}
        ${COMMON_SOURCES}
        ${VULKAN_SOURCES}
        ${DX12_SOURCES}
        ${VENDOR_SOURCES}
)

find_package(Vulkan REQUIRED)
target_compile_definitions(asteroids PRIVATE
        GAME_NAME=\"${GAME_NAME}\"
        GAME_VER_MAJOR=${GAME_VER_MAJOR}
        GAME_VER_MINOR=${GAME_VER_MINOR}
        GAME_VER_PATCH=${GAME_VER_PATCH}
        ENGINE_VER_MAJOR=${ENGINE_VER_MAJOR}
        ENGINE_VER_MINOR=${ENGINE_VER_MINOR}
        ENGINE_VER_PATCH=${ENGINE_VER_PATCH}
)

target_link_libraries(asteroids
        PRIVATE
            Vulkan::Vulkan
)