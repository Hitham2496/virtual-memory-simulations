#include "MemoryManager.h"

int main(){
  // Create memory manager
  MemoryManager *memory_manager = create_memory_manager(DEFAULT_MEMORY_SIZE, DEFAULT_PAGE_SIZE, DEFAULT_SWAP_SIZE);

  // Access pages. we only have four pages (see MemoryManager.h for definition of DEFAUL_PAGE_SIZE)
  access_page(memory_manager, 1);
  access_page(memory_manager, 2);
  access_page(memory_manager, 3);
  access_page(memory_manager, 4);

  // Accessing a fifth page causes a page fault requiring a swap since memory is full
  access_page(memory_manager, 5);

  // Free allocated memory
  for (int i = 0; i < N_PAGES; i++) {
      if (memory_manager->page_table[i] != NULL) {
          free(memory_manager->page_table[i]);
      }
  }
  free(memory_manager->page_table);
  free(memory_manager->frames);
  free(memory_manager->free_frames);
  free(memory_manager->swap_queue);
  free(memory_manager);

  return 0;
}
