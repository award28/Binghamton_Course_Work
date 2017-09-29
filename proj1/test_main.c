/*
 * Binghamton CS 451/551 Project "Memory manager".
 * You do not need to turn in this file.	
 */

#include "memory_manager.h"
#include "interposition.h"

int main(int argc, char * argv[])
{
	unsigned char bitmap[] = {0xF7, 0xF0};
	printf("pos: %i\n", bitmap_find_first_bit(bitmap, sizeof(bitmap), 0));
	printf("Bit_val at 3: %i\n", bitmap_bit_is_set(bitmap, sizeof(bitmap), 3));
	bitmap_set_bit(bitmap, sizeof(bitmap), 3);
	printf("Bit_val at 3: %i\n", bitmap_bit_is_set(bitmap, sizeof(bitmap), 3));
	bitmap_clear_bit(bitmap, sizeof(bitmap), 0);
	bitmap_print_bitmap(bitmap, sizeof(bitmap));
	// Your code

    mem_mngr_init();


	// test your code here.


    mem_mngr_leave();

    return 0;
}


