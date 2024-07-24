#include "MemoryManager.h"

MemoryManager* create_memory_manager(int memory_size,
  int page_size, int swap_size){
  MemoryManager* mm = (MemoryManager*) malloc(sizeof(MemoryManager));
  
  // Assign frames and swap spaces in terms of page size.
  mm->num_frames = memory_size / page_size;
  mm->num_swap_pages = swap_size / page_size;

  // Assign frames and free frames - require num_frames array of ints.
  mm->frames = (int*) malloc(mm->num_frames * sizeof(int));
  mm->free_frames = (int*) malloc(mm->num_frames * sizeof(int));
  // On initialisation, all frames are free.
  mm->free_frame_count = mm->num_frames;

  // Set swap queue - require num_swap_pages array of ints
  mm->swap_queue = (int*) malloc(mm->num_swap_pages * sizeof(int));
  // At first, swap queue is empty
  mm->swap_queue_count = mm->num_swap_pages;

  // Assign memory to page table
  mm->page_table = (Page**) malloc(N_PAGES * sizeof(Page*));

  for (int i = 0; i < mm->num_frames; i++) {
    // No frames currently in use, se to -1
    mm->frames[i] = -1;
    // All frames are free, store indices in free_frames
    mm->free_frames[i] = i;
  }

  for (int i = 0; i < mm->num_swap_pages; i++) {
    // All slots in the swap queue initially free
    mm->swap_queue[i] = i;
  }

  for (int i = 0; i < 100; i++) {
    // Page table is empty as no pages loaded yet
    mm->page_table[i] = NULL;
  }

  return mm;
}

void access_page(MemoryManager *mm, int page_id){
  if (mm->page_table[page_id] == NULL){
    mm->page_table[page_id] = (Page*) malloc(sizeof(Page));
    mm->page_table[page_id]->id = page_id;
    mm->page_table[page_id]->in_memory = 0;
    // The page is no longer in a frame
    mm->page_table[page_id]->frame_number = -1;
  }

  Page *page = mm->page_table[page_id];

  // Handle case where page is already in memory
  if (page->in_memory) {
    printf("Page %d is already in memory at frame %d.\n", page_id, page->frame_number);
  } else {
    handle_page_fault(mm, page);
  }
}

void handle_page_fault(MemoryManager *mm, Page *page){
  printf("Page fault for page %d at address %p.\n", page->id, page);
  if (mm->free_frame_count > 0) {
    // If we have free frames, use them
    printf("Free frame count is %d.\n", mm->free_frame_count);
    int frame_number = mm->free_frames[--mm->free_frame_count];
    load_page_into_frame(mm, page, frame_number);
  } else {
    // If we have no free frames, swap out memory
    printf("Free frame count is %d, swapping memory.\n", mm->free_frame_count);
    swap_out_page(mm);
    int frame_number = mm->free_frames[--mm->free_frame_count];
    load_page_into_frame(mm, page, frame_number);
  }
}

void load_page_into_frame(MemoryManager *mm, Page *page, int frame_number){
  // Load page id into frame
  mm->frames[frame_number] = page->id;
  page->in_memory = 1;
  page->frame_number = frame_number;
  printf("Page %d at address %p is loaded into frame %d.\n", page->id, page, frame_number);
}

void swap_out_page(MemoryManager *mm){
  // Select a frame at random
  int frame_number = rand() % mm->num_frames;
  int page_id = mm->frames[frame_number];
  Page *page = mm->page_table[page_id];

  // Swapped page no longer in memory, written to 'disk'
  printf("Swapping out page %d at address %p from frame %d to swap space.\n", page->id, page, frame_number);
  page->in_memory = 0;
  page->frame_number = -1;

  // If the swap queue is not empty, put page in swap queue
  if (mm->swap_queue_count > 0) {
      mm->swap_queue[--mm->swap_queue_count] = page_id;
  }
  mm->free_frames[mm->free_frame_count++] = frame_number;
}
