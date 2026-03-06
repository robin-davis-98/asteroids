#ifndef PET_MEM_H
#define PET_MEM_H

#include <stdint.h>
#include <stddef.h>

struct Platform_Memory_Block {
    void* base;
    size_t size;
};

Platform_Memory_Block platform_allocate_memory(size_t size);
void platform_free_memory(Platform_Memory_Block block);

struct Arena {
    uint8_t* base;
    size_t size;
    size_t used;
};

struct Scratch {
    Arena* arena;
    size_t used_at_bookmark;
};

void* push_size(Arena* arena, size_t size);

#define push_struct(arena, type) (type*)push_size(arena, sizeof(type))
#define push_array(arena, type, count) (type*)push_size(arena, sizeof(type) * (count))

Scratch scratch_begin(Arena* arena);
void    scratch_end(Scratch scratch);

inline void arena_clear(Arena* arena) {
    arena->used = 0;
}

#endif