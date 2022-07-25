#include <string>   //for to_string and stoi functions
#include <stdlib.h> //for rand and srand functions
#include <time.h>   //for time function
#include <iostream> //for cin/cout
#include <vector> 
#include <algorithm> //for string reverse
#include "pageFaultSimulation.h"

using namespace std;

int main() {

    int page_ref_length = 200,//number of pages in page reference string
        page_ref_max = 50,
        max_table_size = 30;

    //page_ref contains a random order of numbers between 0 and page_ref_max - 1
    string page_ref = generatePageReference(page_ref_length, page_ref_max);
    
    cout << "\nUsing a string that represents a stream of " << page_ref_length
         << " virtual addresses entering a page table that can store 1 through " 
         << max_table_size << " entries";
    
    //for table_size 1 to n, calculate how many page faults occur for the fifo, 
    //lru, and optimal page replacement algorithms
    for (int table_size = 1; table_size <= max_table_size; table_size++) {
        int fifo_page_faults = fifo(page_ref, table_size);
        int lru_page_faults = lru(page_ref, table_size);
        int opt_page_faults = 
                   optimal(page_ref, table_size, page_ref_max, page_ref_length);

        cout << "\n------\ntable size: " << table_size << "\nfifo page faults: " 
             << fifo_page_faults << "\nlru page faults: " << lru_page_faults 
             << "\nopt page faults: " << opt_page_faults;
    }
    
    return 0;
}