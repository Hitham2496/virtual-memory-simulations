#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PAGE_SIZE 4   // Page size in KB
#define DEFAULT_MEMORY_SIZE 16 // Physical memory size in KB
#define DEFAULT_SWAP_SIZE 32   // Swap space size in KB
#define N_PAGES 100 // Total number of pages in page table

typedef struct Page {
    // Unique ID of page
    int id;
    // Whether (1) or not (0) page is in memory
    int in_memory;
    // Frame number in memory
    int frame_number;
} Page;

typedef struct MemoryManager {
    // Total number of frames
    int num_frames;
    // Size of swap space
    int num_swap_pages;
    // Current frames in use
    int *frames;
    // Current free frames
    int *free_frames;
    // Current number of free frames
    int free_frame_count;
    // Current page IDs in swap space
    int *swap_queue;
    // Number of pages in swap space
    int swap_queue_count;
    // Array of pointers to Page structs
    Page **page_table;
} MemoryManager;

// Constructor for MemoryManager struct
MemoryManager* create_memory_manager(int memory_size,
  int page_size, int swap_size);

// Simulates accessing a page from the ID
void access_page(MemoryManager *mm, int page_id);

// Handle case where virtual address is not mapped, or is swapped
void handle_page_fault(MemoryManager *mm, Page *page);

// Lods page into specified frame on 'physical' memory
void load_page_into_frame(MemoryManager *mm, Page *page, int frame_number);

// Simulates swap from 'physical' memory to 'disk'
void swap_out_page(MemoryManager *mm);

#endif /* MEMORYMANAGER_H */
