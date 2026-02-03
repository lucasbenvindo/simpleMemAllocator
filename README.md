Memory allocator based on Linked List, a classical approach.
`
if(heap_start == NULL) {
    chunk_t *chunk = (chunk_t *)heap;
    chunk->size = size;
    chunk->free = 0;
    chunk->next = NULL;
    heap_start = chunk;
    return (void *)(chunk + 1);
}
`
The problem here is that I am not able to allocate memory 2 times.
Trying to figure out how I can improve my algorithm.
