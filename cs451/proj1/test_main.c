/*
 * Binghamton CS 451/551 Project "Memory manager".
 * You do not need to turn in this file.	
 */

#include "memory_manager.h"
#include "interposition.h"
#include "assert.h"

int main(int argc, char * argv[])
{
	unsigned char bitmap[] = {0xF7, 0xF0};

	//Check on correct data
	assert(3 == bitmap_find_first_bit(bitmap, sizeof(bitmap), 0));
	printf("Found correct first 0 bit.\n");
	assert(1 == bitmap_bit_is_set(bitmap, sizeof(bitmap), 15));
	printf("Found correct last bit is 1.\n");
	assert(0 == bitmap_set_bit(bitmap, sizeof(bitmap), 3));
	printf("Set the 3rd bit to 1.\n");
	assert(1 == bitmap_bit_is_set(bitmap, sizeof(bitmap), 3));
	printf("Correctly set the 3rd bit to 1.\n");
	assert(0 == bitmap_clear_bit(bitmap, sizeof(bitmap), 0));
	printf("Cleared the first bit to 0.\n");
	assert(0 == bitmap_bit_is_set(bitmap, sizeof(bitmap), 0));
	printf("Correctly cleared the first bit to 0.\n");
	assert(0 == bitmap_print_bitmap(bitmap, sizeof(bitmap)));
	printf("Print worked correctly.\n");

	//Check on incorrect data

    mem_mngr_init();

    int *count = malloc(50 * sizeof(int));

    for (int i = 0; i < 50; i++)
	    count[i] = i;

    mem_mngr_print_snapshot();
    for (int i = 0; i < 50; i++)
	    assert(count[i] == i);
    printf("Memory allocated.\n");
   	 
    for (int i = 0; i < 50; i++)
	    free(count[i]);

    mem_mngr_print_snapshot();
    mem_mngr_leave();

    return 0;
}
