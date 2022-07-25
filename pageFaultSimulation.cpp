#include <string>  
#include <stdlib.h>
#include <time.h>  
#include <iostream>
#include <vector> 
#include <algorithm>

using namespace std;

string generatePageReference(int page_ref_length, int page_ref_max) {
    string page_ref = "";
    srand(time(NULL)); //creates a random seed

    for (int i = 0; i < page_ref_length; i++) {
        page_ref += to_string(rand() % page_ref_max);
        page_ref += " ";
    }

    return page_ref;
}

int fifo(string page_ref, int table_size) {
    int page_table[table_size];
    int pages_processed = 0,
        page_faults = 0,
        current_page = 0;

    //initialize the page_table
    for (int i = 0; i < table_size; i++)
        page_table[i] = -1;

    for (int i = 0; i < page_ref.length(); i++) {
        if (page_ref[i] != ' ') {
            //ex: read in "12 ": current_page = 0; 0 * 10 = 0; 0 + 1 = 1; 
            //1 * 10 = 10; 10 + 2 = 12; space detected;
            current_page *= 10;
            //any digit as a char, is that number away from the char '0'
            current_page += (page_ref[i] - '0'); 
        }

        //if there is an instance of ' ' then a page has been read in
        else {
            bool found = false;
            for (int j = 0; j < table_size; j++) {
                //if current page is in the page table
                if (page_table[j] == current_page) {
                    found = true;
                    j = table_size; //break
                }
            }

            if (found == false) {
                //need to replace the least recently used page
                page_table[page_faults % table_size] = current_page;
                page_faults++;
            }

            //else: do nothing
            pages_processed++;
            current_page = 0; //reset current page
        }
    }
    return page_faults;
}

int lru(string page_ref, int table_size) {
    int page_table[table_size][2];
    int pages_processed = 0,
        page_faults = 0,
        current_page = 0;

    //initialize the page_table
    for (int i = 0; i < table_size; i++) {
        page_table[i][0] = -1;
        page_table[i][1] = -1;
    }

    for (int i = 0; i < page_ref.length(); i++) {
        if (page_ref[i] != ' ') {
            current_page *= 10;
            current_page += (page_ref[i] - '0');
        }

        else {
            for (int j = 0; j < table_size; j++) {
                if (page_table[j][1] != -1) {
                    //need to update count since last use, for all non-empty 
                    //pages in table
                    page_table[j][1]++;
                }
            }

            bool found = false;
            int found_index = -1;
            for (int j = 0; j < table_size; j++) {
                if (page_table[j][0] == current_page) {
                    found = true;
                    found_index = j; //break
                }
            }

            if (found == false) {
                int least_recent = page_table[0][1];
                int lru_index = 0;

                for (int j = 0; j < table_size; j++) {
                    //if any of the frames in the table are empty then fill
                    //next available frame
                    if (page_table[j][1] == -1) {
                        lru_index = j;
                        j = table_size; //break
                    }

                    //find max value for how many processes ago a page was used
                    else if (page_table[j][1] > least_recent) {
                        least_recent = page_table[j][1];
                        lru_index = j;
                    }
                }

                //replace least recently used page in table
                page_table[lru_index][0] = current_page;
                //set count for how many pages have processed since current
                //process to 0
                page_table[lru_index][1] = 0;
                page_faults++;
            }

            else //page found in table
                //reset count for how many pages have processed since 
                //current process
                page_table[found_index][1] = 0; 

            pages_processed++;
            current_page = 0; //reset current page for next page
        }
    }
    return page_faults;
}

int optimal(string page_ref, int table_size, int page_ref_max, 
                                                        int page_ref_length) {
    int page_table[table_size][2];
    vector <int> next_page_occurences[page_ref_max];
    int page_faults = 0;
        
    //initialize page table
    for (int i = 0; i < table_size; i++) {
        page_table[i][0] = -1;
        page_table[i][1] = -1;
    }

    int pages_processed = 0;
    string curr_page = "";
    //reverse the page reference string so that the vectors can add the future
    //indices of occurences in reverse order (easier to use the included funtion
    //pop_back() then to write a function for pop_front())
    string rev_page_ref = page_ref;
    reverse(rev_page_ref.begin(), rev_page_ref.end() - 1);

    for (int i = 0; i < rev_page_ref.length(); i++) {
        if (rev_page_ref[i] != ' ') {
            curr_page += rev_page_ref[i];
        }
    
        else {
            //since pages are read in reverse, the numbers are also reversed
            reverse(curr_page.begin(), curr_page.end());
            next_page_occurences[stoi(curr_page)]
                            .push_back(page_ref_length - pages_processed - 1);
            pages_processed++;
            curr_page = ""; //reset curr_page for next page
        }
    }    

    int current_page = 0;
    pages_processed = 0;
    for (int i = 0; i < page_ref.length(); i++) {
        if (page_ref[i] != ' ') {
            current_page *= 10;
            current_page += (page_ref[i] - '0');
        }

        else {
            bool found = false;
            int found_index = -1;

            for (int j = 0; j < table_size; j++) {
                //if current_page is in the page table
                if (page_table[j][0] == current_page) {
                    found = true;
                    found_index = j; //break
                }
            }

            if (found == false) {
                int most_optimal = page_table[0][1];
                int opt_index = 0;

                bool frame_empty = false;
                for (int j = 0; j < table_size; j++) {
                    if (page_table[j][0] == -1) {
                        opt_index = j;
                        frame_empty = true;
                        j = table_size; //break
                    }
                }
                //if there are no empty frames in table check if any of the
                //current pages in the table have no future occurences
                if (frame_empty == false) {
                    for (int j = 0; j < table_size; j++) {
                        if (page_table[j][1] == -1) {
                            opt_index = j;
                            j = table_size; //break
                        }
                        //if page_table[j] occurs later than the current
                        //furthest occurence
                        else if (page_table[j][1] > most_optimal) {
                            most_optimal = page_table[j][1];
                            opt_index = j;
                        }
                    }
                }

                page_table[opt_index][0] = current_page;
                //pop_back() because the vector stores occurences in
                //reverse order, so the current occurence is removed
                next_page_occurences[current_page].pop_back();

                //if there are no more occurences for the current page, then
                //set the corresponding page_table information accordingly
                if (next_page_occurences[current_page].empty()) {
                    page_table[opt_index][1] = -1;
                }
                //else set the corresponding next occurence in the page table
                //to the correct next occurence
                else {
                    page_table[opt_index][1] = 
                                    next_page_occurences[current_page].back();
                }
                page_faults++;
            }

            else { //found == true
                next_page_occurences[current_page].pop_back();
                if (next_page_occurences[current_page].empty()) {
                    page_table[found_index][1] = -1;
                }
                else {
                    page_table[found_index][1] = 
                                    next_page_occurences[current_page].back();
                }
            }           

            pages_processed++;
            current_page = 0;
        }
    }

    return page_faults; 
}