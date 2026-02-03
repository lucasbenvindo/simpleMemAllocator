#define HEAP_SIZE 4096
static unsigned char heap[HEAP_SIZE]; 

// 

typedef struct chunk {
		size_t size;
		int free;
		struct chunk *next;
} chunk_t;

static chunk_t *heap_start = NULL;

void *my_malloc(size_t size) {
		if(size == 0)
			return NULL;
			
		if(heap_start == NULL) {
				chunk_t *chunk = (chunk_t *)heap;
				
				chunk->size = size;
				chunk->free = 0;
				chunk->next = NULL;
				
				heap_start = chunk;
				
				return (void *)(chunk + 1);
			}
// procurar chunk livre			
			chunk_t *curr = heap_start;
			
			while(curr) {
					if(curr->free && curr->size >=size) {
							curr->free = 0;
							return (void *)(curr + 1);
						}
						curr = curr->next;
				}
				
				return NULL;
			
}

// nao chega a ser muito funcional, ja que eu so consigo alocar uma vez

void my_free(void *ptr) {
		if(!ptr)
			return;
			
		chunk_t *chunk = (chunk_t *)ptr - 1;
		chunk->free = 1;
}


