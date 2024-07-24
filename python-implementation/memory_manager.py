import random

class Page:

    def __init__(self, id):
        # Unique ID of page
        self.id = id
        # Whether of not page is in memory
        self.in_memory = False
        # Frame number in memory 
        self.frame_number = -1

class MemoryManager:

    DEFAULT_PAGE_SIZE = 4  # Page size in KB
    DEFAULT_MEMORY_SIZE = 16  # Physical memory size in KB
    DEFAULT_SWAP_SIZE = 32  # Swap space size in KB

    def __init__(self, memory_size=DEFAULT_MEMORY_SIZE, page_size=DEFAULT_PAGE_SIZE, swap_size=DEFAULT_SWAP_SIZE):
        # Assign frames and swap spaces in terms of page size.
        self.num_frames = memory_size // page_size
        self.num_swap_pages = swap_size // page_size
        self.frames = [-1] * self.num_frames
        self.free_frames = list(range(self.num_frames))
        self.swap_queue = list(range(self.num_swap_pages))

        # Initialise empty hash tables for pages and sswaps
        self.page_table = {}
        self.swap_space = {}

    def access_page(self, page_id):
        # Save page to page table if not originally there
        if page_id not in self.page_table:
            self.page_table[page_id] = Page(page_id)

        page = self.page_table[page_id]

        # Handle page faults from when page is already in emory.
        if page.in_memory:
            print(f"Page {page_id} is already in memory at frame {page.frame_number}.")
        else:
            self.handle_page_fault(page)

    def handle_page_fault(self, page):
        print(f"Page fault for page {page.id}.")
        if self.free_frames:
            # If we have free frames, use them
            frame_number = self.free_frames.pop(0)
            self.load_page_into_frame(page, frame_number)
        else:
            # If we don't have free frames, swap the memory out
            self.swap_out_page()
            frame_number = self.free_frames.pop(0)
            self.load_page_into_frame(page, frame_number)

    def load_page_into_frame(self, page, frame_number):
        # Load page id into specific frame
        print(f"Loading page {page.id} into frame {frame_number}.")
        self.frames[frame_number] = page.id
        page.in_memory = True
        page.frame_number = frame_number

    def swap_out_page(self):
        # Select a frame at random to swap iut - in practice
        # the least recently used frame will be chosen
        frame_number = random.randint(0, self.num_frames - 1)
        page_id = self.frames[frame_number]
        page = self.page_table[page_id]

        # Swapped page is no longer in memory
        print(f"Swapping out page {page.id} from frame {frame_number} to swap space.")
        page.in_memory = False
        page.frame_number = -1
        if self.swap_queue:
            self.swap_queue.pop(0)
        self.free_frames.append(frame_number)

def main():

    # Create memory manager
    memory_manager = MemoryManager()

    # Access pages. We only have four pages.
    memory_manager.access_page(1)
    memory_manager.access_page(2)
    memory_manager.access_page(3)
    memory_manager.access_page(4)
    memory_manager.access_page(5)  # This will cause a page fault and a swap since memory is full

if __name__ == "__main__":
    main()

