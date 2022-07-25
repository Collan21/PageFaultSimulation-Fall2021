#ifndef __PAGEFAULTSIMULATION_H__
#define __PAGEFAULTSIMULATION_H__

#include <string>
using namespace std;

string generatePageReference(int, int);
int fifo(string, int);
int lru(string, int);
int optimal(string, int, int, int);

#endif /* __PAGEFAULTSIMULATION_H__ */
