#include "petrichor_mem.h"

void* push_size(Arena* arena, size_t size) {
    if ((arena->used + size) <= arena->size) {
        void* result = arena->base + arena->used;
        arena->used += size;
        return result;
    }
    return nullptr;
}

Scratch scratch_begin(Arena* arena) {
    Scratch scratch = {};
    scratch.arena = arena;
    scratch.used_at_bookmark = arena->used;
    return scratch;
}

void scratch_end(Scratch scratch) {
    scratch.arena->used = scratch.used_at_bookmark;
}