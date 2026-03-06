#include "win32_common.h"
#include <petrichor_mem.h>

Platform_Memory_Block platform_allocate_memory(size_t size) {
    Platform_Memory_Block block = {};
    block.size = size;

    block.base = VirtualAlloc(0, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    return block;
}