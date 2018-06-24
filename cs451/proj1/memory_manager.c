/*
 * Binghamton CS 451/551 Project "Memory manager".
 * This file needs to be turned in.
 */

#include "memory_manager.h"

static STRU_MEM_LIST* mem_pool = NULL;

/*
 * Print out the current status of the memory manager.
 * Reading this function may help you understand how the memory manager
 * organizes the memory.
 * Do not change the implementation of this function. It will be used to help
 * the grading.
 */
void mem_mngr_print_snapshot(void) {
	STRU_MEM_LIST* mem_list = NULL;

	printf("============== Memory snapshot ===============\n");

	mem_list = mem_pool;  // Get the first memory list
	while (NULL != mem_list) {
		STRU_MEM_BATCH* mem_batch =
			mem_list->first_batch;  // Get the first mem batch from the list

		printf("mem_list %p slot_size %d batch_count %d free_slot_bitmap %p\n",
				mem_list, mem_list->slot_size, mem_list->batch_count,
				mem_list->free_slots_bitmap);
		bitmap_print_bitmap(mem_list->free_slots_bitmap, mem_list->bitmap_size);

		while (NULL != mem_batch) {
			printf("\t mem_batch %p batch_mem %p\n", mem_batch,
					mem_batch->batch_mem);
			mem_batch = mem_batch->next_batch;  // get next mem batch
		}

		mem_list = mem_list->next_list;
	}

	printf("==============================================\n");
}


int resize_bitmap(unsigned char * bitmap, int bitmap_size, int batch_count) {
	unsigned char * replacement =
		calloc(batch_count, sizeof(unsigned char)*(MEM_BATCH_SLOT_COUNT/BIT_PER_BYTE));
	free(bitmap);
	//bitmap = replacement;
	memcpy(replacement + (MEM_BATCH_SLOT_COUNT / BIT_PER_BYTE),
			bitmap, batch_count - 1);
	return bitmap_size + (MEM_BATCH_SLOT_COUNT/BIT_PER_BYTE);
}

/*
 * Initialize the memory manager.
 * You may add your code related to initialization here if there is any.
 */
void mem_mngr_init(void) 
{ 
	mem_pool = NULL; 
}

/*
 * Clean up the memory manager (e.g., release all the memory allocated)
 */
void mem_mngr_leave(void) 
{ 
	STRU_MEM_LIST* pool_to_delete = mem_pool;
	STRU_MEM_BATCH* batch_to_delete;

		while (mem_pool) {
			while (mem_pool->first_batch) {
				batch_to_delete = mem_pool->first_batch;
				mem_pool->first_batch = batch_to_delete->next_batch;
				free(batch_to_delete->batch_mem);
				free(batch_to_delete);
			}
			pool_to_delete = mem_pool;
			mem_pool = mem_pool->next_list;
			free(pool_to_delete->free_slots_bitmap);
			free(pool_to_delete);
		}
}

/*
 * Allocate a chunk of memory
 */
void* mem_mngr_alloc(size_t size) 
{
	if (size == 0) return NULL;
	int slot_size = SLOT_ALLINED_SIZE(size);
	STRU_MEM_LIST* last_pool = mem_pool;
	STRU_MEM_LIST* pool = mem_pool;

	while (pool) {
		if (slot_size == pool->slot_size) break;
		last_pool = pool;
		pool = pool->next_list;
	}

	if (pool == NULL) {
		STRU_MEM_BATCH* batch = malloc(sizeof(STRU_MEM_BATCH));
		batch->batch_mem = calloc(MEM_BATCH_SLOT_COUNT, slot_size);
		batch->next_batch = NULL;

		STRU_MEM_LIST* list = malloc(sizeof(STRU_MEM_LIST));
		list->slot_size = slot_size;
		list->batch_count = 1;
		list->free_slots_bitmap = calloc(1, sizeof(unsigned char) * (MEM_BATCH_SLOT_COUNT/BIT_PER_BYTE));
		list->bitmap_size = (MEM_BATCH_SLOT_COUNT/BIT_PER_BYTE);
		list->first_batch = batch;
		list->next_list = NULL;

		if (!mem_pool) {
			mem_pool = list;
			pool = mem_pool;
		} else {
			last_pool->next_list = list;
			pool = last_pool->next_list;
		}
	}

	int free_bit = bitmap_find_first_bit(pool->free_slots_bitmap, pool->bitmap_size, 0);

	if (free_bit == BITMAP_OP_NOT_FOUND) {
		pool->batch_count++;
		pool->bitmap_size = resize_bitmap(pool->free_slots_bitmap, pool->bitmap_size, ++pool->batch_count);

		free_bit = bitmap_find_first_bit(pool->free_slots_bitmap, pool->bitmap_size, 0);

		STRU_MEM_BATCH* new_batch = malloc(sizeof(STRU_MEM_BATCH));
		new_batch->batch_mem = calloc(MEM_BATCH_SLOT_COUNT, slot_size);
		new_batch->next_batch = NULL;

		STRU_MEM_BATCH* last_batch = pool->first_batch;

		while (last_batch->next_batch) {
			last_batch = last_batch->next_batch;
		}
		last_batch->next_batch = new_batch;
	}

	STRU_MEM_BATCH* batch = pool->first_batch;
	for (int i = 0; i < free_bit/MEM_BATCH_SLOT_COUNT; i++) {
		batch = batch->next_batch;
	}
	bitmap_set_bit(pool->free_slots_bitmap, pool->bitmap_size, free_bit);
	return batch->batch_mem + (size * (free_bit % MEM_BATCH_SLOT_COUNT));
}

/*
 * Free a chunk of memory pointed by ptr
 */
void mem_mngr_free(void* ptr) 
{
	STRU_MEM_LIST* pool = mem_pool;

	while (pool) {
		STRU_MEM_BATCH* batch = pool->first_batch;
		int current_slot = 0;

		while (batch) {
			int slot_size = pool->slot_size;
			void* bound = batch->batch_mem + MEM_BATCH_SLOT_COUNT * slot_size;

			if (ptr >= batch->batch_mem && ptr < bound) {
				current_slot += (ptr - batch->batch_mem) / slot_size;
				if (!bitmap_bit_is_set(pool->free_slots_bitmap, pool->bitmap_size, current_slot)) {
					fprintf(stderr, "Error: Double free at %p\n", ptr);
					exit(1);
				}
				bitmap_clear_bit(pool->free_slots_bitmap, pool->bitmap_size, current_slot);
				return;
			}
			current_slot += MEM_BATCH_SLOT_COUNT;
			batch = batch->next_batch;
		}
		pool = pool->next_list;
	}
	fprintf(stderr, "Error: Memory not allocated at %p\n", ptr);
}
