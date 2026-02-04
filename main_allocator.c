#include <stdio.h>
#include <stddef.h>
#include <sys/mman.h>


#define HEAP_SIZE 4096
// estrutura da chunk

typedef struct chunk {
		size_t size;
		int free;
		struct chunk *next;
} chunk_t;

void *heap_start = NULL;

void init_heap() {
		heap_start = mmap(NULL, HEAP_SIZE, PROT_READ | PROT_WRITE,  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		
		if(heap_start == MAP_FAILED) {
				printf("error\n");
				heap_start = NULL;
				return;
			}
		
		chunk_t *initial_chunk = (chunk_t*)heap_start;
		
		initial_chunk = (chunk_t *)heap_start;
		initial_chunk->size = HEAP_SIZE - sizeof(chunk_t);
		initial_chunk->free = 1;
		initial_chunk->next = NULL;
}

void *my_malloc(size_t size) {
		if(size == 0)
			return NULL;
			
		if(heap_start == NULL) {
				init_heap();
				if(heap_start == NULL) return NULL;
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
	printf("heap starts  in: %p\n", heap_start);
	printf("a: %d - %p\nb: %d - %p\n", *a, a, *b,  b);
	
	my_free(a);
	my_free(b);
	
	return 0;
}

