#include <iostream>
#include <string>
#include <cassert>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>
#include "Sort.hpp"

#define SMALL_SIZE 20
#define SORTED_SIZE 1000
#define RANDOM_SIZE 1000
#define IDENTICAL_SIZE 100

#define OPTIMIZED_SIZE 100

using namespace std;

bool isSorted(int * array, int size){
    for(int i = 0; i < size - 1; i++){
        if(array[i] > array[i+1])
            return false;
    }
    return true;
}

int main(){
	std::srand ( unsigned ( std::time(0) ) );


    int small[SMALL_SIZE], sorted[SORTED_SIZE], random[RANDOM_SIZE], identical[IDENTICAL_SIZE];
    for(int i = 0; i< RANDOM_SIZE; i++){
        random[i] = rand() % 10000;
        if(i < SMALL_SIZE){
            small[i] = rand() % 100;
        }
        if(i < SORTED_SIZE){
            sorted[i] = i;
        } 
        if(i < IDENTICAL_SIZE){
            identical[i] = 42; 
        }
    }
    Sort sort_machine;


    int one[] = {0};
	cerr << "\n\tTEST #1: Array of 1 handled" << endl;
	sort_machine.sortA(one, 1);
	sort_machine.sortB(one, 1);
	cerr << "\n\t========================PASS========================\n" << endl;

    struct timeval start, stop;

    //*********************************************************************//
    //                                SORT A                               //
    //*********************************************************************//
    cerr << "\n\tTEST #2: SortA - Sorting an array of " << SMALL_SIZE << " elements" << endl;
    int * test_small = new int[SMALL_SIZE];  
    memcpy(test_small, small, sizeof(int) * SMALL_SIZE);
    
    gettimeofday(&start, NULL);
    test_small = sort_machine.sortA(test_small, SMALL_SIZE);
    gettimeofday(&stop, NULL);

    assert(isSorted(test_small, SMALL_SIZE));
    delete[] test_small;
    test_small = NULL;

    unsigned long start_time = (start.tv_sec* 1000000) + start.tv_usec;
    unsigned long stop_time = (stop.tv_sec* 1000000) + stop.tv_usec;
    unsigned long final_time = stop_time - start_time;
    
    cerr << "SortA completed sorting an unsorted array of " << SMALL_SIZE << " elements in " << final_time << " nanoseconds\n" << endl;    
    cerr << "\n\t========================PASS========================\n" << endl;


    cerr << "\n\tTEST #3: SortA - Sorting an array of " << SORTED_SIZE<< " sorted elements" << endl;
    int * test_sorted = new int[SORTED_SIZE];
    memcpy(test_sorted, sorted, sizeof(int) * SORTED_SIZE);

    gettimeofday(&start, NULL);
    test_sorted = sort_machine.sortA(test_sorted, SORTED_SIZE);
    gettimeofday(&stop, NULL);

    assert(isSorted(test_sorted, SORTED_SIZE));
    delete[] test_sorted; 

    start_time = (start.tv_sec* 1000000) + start.tv_usec;
    stop_time = (stop.tv_sec* 1000000) + stop.tv_usec;
    final_time = stop_time - start_time;
    cerr << "SortA completed sorting an array of " << SORTED_SIZE << " sorted elements in " << final_time << " nanoseconds\n" << endl;    
    cerr << "\n\t========================PASS========================\n" << endl;


    cerr << "\n\tTEST #4: SortA - Sorting an array of " << RANDOM_SIZE << " random elements" << endl;
    int * test_random = new int[RANDOM_SIZE];
    memcpy(test_random, random, sizeof(int) * RANDOM_SIZE);

    gettimeofday(&start, NULL);
    test_random = sort_machine.sortA(test_random, RANDOM_SIZE);
    gettimeofday(&stop, NULL);
    start_time = (start.tv_sec* 1000000) + start.tv_usec;
    stop_time = (stop.tv_sec* 1000000) + stop.tv_usec;
    final_time = stop_time - start_time;
 
    assert(isSorted(test_random, RANDOM_SIZE));
    delete[] test_random;
    
    cerr << "SortA completed sorting an unsorted array of " << RANDOM_SIZE << " random elements in " << final_time << " nanoseconds\n" << endl;    
    cerr << "\n\t========================PASS========================\n" << endl;
  

    cerr << "\n\tTEST #5: SortA - Sorting an array of " << IDENTICAL_SIZE<< " identical elements" << endl;
    int * test_identical = new int[IDENTICAL_SIZE];
    memcpy(test_identical, identical, sizeof(int) * IDENTICAL_SIZE);

    gettimeofday(&start, NULL);
    test_identical = sort_machine.sortA(test_identical, IDENTICAL_SIZE);
    gettimeofday(&stop, NULL);
    start_time = (start.tv_sec* 1000000) + start.tv_usec;
    stop_time = (stop.tv_sec* 1000000) + stop.tv_usec;
    final_time = stop_time - start_time;
    
    assert(isSorted(test_identical, IDENTICAL_SIZE));
    delete[] test_identical;     
 
    cerr << "SortA completed sorting an array of " << IDENTICAL_SIZE << " identical elements in " << final_time << " nanoseconds\n" << endl;    
    cerr << "\n\t========================PASS========================\n" << endl;

    //*********************************************************************//
    //                                SORT B                               //
    //*********************************************************************//


    cerr << "\n\tTEST #6: SortB - Sorting an array of " << SMALL_SIZE << " elements" << endl;
    test_small = new int[SMALL_SIZE];
    memcpy(test_small, small, sizeof(int) * SMALL_SIZE);
    gettimeofday(&start, NULL);
    test_small = sort_machine.sortB(test_small, SMALL_SIZE);
    gettimeofday(&stop, NULL);

    assert(isSorted(test_small, SMALL_SIZE));

    delete [] test_small;
    test_small = NULL;
    
    start_time = (start.tv_sec* 1000000) + start.tv_usec;
    stop_time = (stop.tv_sec* 1000000) + stop.tv_usec;
    final_time = stop_time - start_time;
    
    cerr << "SortB completed sorting an unsorted array of " << SMALL_SIZE << " elements in " << final_time << " nanoseconds\n" << endl;    
    cerr << "\n\t========================PASS========================\n" << endl;


    cerr << "\n\tTEST #7: SortB - Sorting an array of " << SORTED_SIZE<< " sorted elements" << endl;
    test_sorted = new int[SORTED_SIZE];
    memcpy(test_sorted, sorted, sizeof(int) * SORTED_SIZE);

    gettimeofday(&start, NULL);
    test_sorted = sort_machine.sortB(test_sorted, SORTED_SIZE);
    gettimeofday(&stop, NULL);

    assert(isSorted(test_sorted, SORTED_SIZE));
    delete[] test_sorted; 
    test_sorted = NULL;

    start_time = (start.tv_sec* 1000000) + start.tv_usec;
    stop_time = (stop.tv_sec* 1000000) + stop.tv_usec;
    final_time = stop_time - start_time;
    cerr << "SortB completed sorting an array of " << SORTED_SIZE << " sorted elements in " << final_time << " nanoseconds\n" << endl;    
    cerr << "\n\t========================PASS========================\n" << endl;


    cerr << "\n\tTEST #8: SortB - Sorting an array of " << RANDOM_SIZE << " random elements" << endl;
    test_random = new int[RANDOM_SIZE];
    memcpy(test_random, random, sizeof(int) * RANDOM_SIZE);

    gettimeofday(&start, NULL);
    test_random = sort_machine.sortB(test_random, RANDOM_SIZE);
    gettimeofday(&stop, NULL);
    start_time = (start.tv_sec* 1000000) + start.tv_usec;
    stop_time = (stop.tv_sec* 1000000) + stop.tv_usec;
    final_time = stop_time - start_time;
 
    assert(isSorted(test_random, RANDOM_SIZE));
    delete[] test_random;
    test_random = NULL;

    cerr << "SortB completed sorting an unsorted array of " << RANDOM_SIZE << " random elements in " << final_time << " nanoseconds\n" << endl;    
    cerr << "\n\t========================PASS========================\n" << endl;
  

    cerr << "\n\tTEST #9: SortB - Sorting an array of " << IDENTICAL_SIZE<< " identical elements" << endl;
    test_identical = new int[IDENTICAL_SIZE];
    memcpy(test_identical, identical, sizeof(int) * IDENTICAL_SIZE);

    gettimeofday(&start, NULL);
    test_identical = sort_machine.sortB(test_identical, IDENTICAL_SIZE);
    gettimeofday(&stop, NULL);
    start_time = (start.tv_sec* 1000000) + start.tv_usec;
    stop_time = (stop.tv_sec* 1000000) + stop.tv_usec;
    final_time = stop_time - start_time;
    
    assert(isSorted(test_identical, IDENTICAL_SIZE));
    delete[] test_identical;     
    test_identical = NULL;

    cerr << "SortB completed sorting an array of " << IDENTICAL_SIZE << " identical elements in " << final_time << " nanoseconds\n" << endl;    
    cerr << "\n\t========================PASS========================\n" << endl;

    /************************************PART B - TBD*****************************************/
    cerr << "\n\tTEST #10: PART B - Run several tests on various data sets. \n\t ====THESE ARE NOT THE FINAL DATA SETS====" << endl;
 /*  
    int total_time = 0;
    int RUN_TEST = 10;
    for(int i = 0; i < RUN_TEST; i++){
        int test1[OPTIMIZED_SIZE], test2[OPTIMIZED_SIZE], test3[OPTIMIZED_SIZE];
        for(int i = 0; i< OPTIMIZED_SIZE; i++){
            test1[i] = rand() % 10000;
            test2[i] = (int) i % (OPTIMIZED_SIZE/8);
            test3[i] = i;
        }
        gettimeofday(&start, NULL);
        int * testptr1 = sort_machine.sortOptimized(test1, OPTIMIZED_SIZE);
        gettimeofday(&stop, NULL);
        assert(isSorted(testptr1, OPTIMIZED_SIZE));

        start_time = (start.tv_sec* 1000000) + start.tv_usec;
        stop_time = (stop.tv_sec* 1000000) + stop.tv_usec;
        final_time = stop_time - start_time;
        total_time += final_time;
        //cerr << "SortOptimized completed second test in " << final_time << " nanoseconds\n" << endl;    
        
        gettimeofday(&start, NULL);
        int * testptr2 = sort_machine.sortOptimized(test2, OPTIMIZED_SIZE);
        gettimeofday(&stop, NULL);
        assert(isSorted(testptr2, OPTIMIZED_SIZE));
        start_time = (start.tv_sec* 1000000) + start.tv_usec;
        stop_time = (stop.tv_sec* 1000000) + stop.tv_usec;
        final_time = stop_time - start_time;
        total_time += final_time;
        //cerr << "SortOptimized completed second test in " << final_time << " nanoseconds\n" << endl;    
        
        gettimeofday(&start, NULL);
        int * testptr3 = sort_machine.sortOptimized(test3, OPTIMIZED_SIZE);
        gettimeofday(&stop, NULL);
        assert(isSorted(testptr3, OPTIMIZED_SIZE));
        start_time = (start.tv_sec* 1000000) + start.tv_usec;
        stop_time = (stop.tv_sec* 1000000) + stop.tv_usec;
        final_time = stop_time - start_time;
        total_time += final_time;
        //cerr << "SortOptimized completed second test in " << final_time << " nanoseconds\n" << endl;    
    }

    int average = total_time / (RUN_TEST * 3);
    cerr << "Average of SortOptimized tests is " << average << " nanoseconds\n" << endl;    
*/
	return 0;
}
