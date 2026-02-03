#include <stdio.h>
#include <stddef.h>

#define HEAP_SIZE 4096
static unsigned char heap[HEAP_SIZE]; 

// estrutura da chunk

typedef struct chunk {
		size_t size;
		int free;
		struct chunk *next;
} chunk_t;

static chunk_t *heap_start = NULL;

void init_heap() {
		heap_start = (chunk_t *)heap;
		heap_start->size = HEAP_SIZE - sizeof(chunk_t);
		heap_start->free = 1;
		heap_start->next = NULL;
}

void *my_malloc(size_t size) {
		if(size == 0)
			return NULL;
			
		if(heap_start == NULL) {
				init_heap();
			}
			
// procurar chunk livre			
			chunk_t *curr = heap_start;
			
			while(curr) {
					if(curr->free && curr->size >=size) {
						if(curr->size >= size + sizeof(chunk_t) + 1) {
							// calcula aonde comeca o novo bloco
								chunk_t *new_chunk =  (chunk_t*) ((unsigned char *)curr + sizeof(chunk_t) + size);
								
								new_chunk->size = curr->size - size - sizeof(chunk_t);
								new_chunk->free = 1;
								new_chunk->next = curr->next;
								
								curr->size = size;
								curr->next = new_chunk;
							}
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

// teste

int main() {
	int *a = my_malloc(sizeof(int));
	*a =  10;
	
	
	int *b = my_malloc(sizeof(int));
	*b = 20;
	
	printf("a: %d - %p\nb: %d - %p\n", *a, &a, *b,  &b);
	
	my_free(a);
	my_free(b);
	
	return 0;
}

