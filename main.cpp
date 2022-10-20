#include "memory.hpp"
#include <iostream>
#define NUMALLOCS 3
#define NUMBYTES 10

using namespace std;

void testBestFreeList()
{
  cout << "### BEST FREE LIST ###" << endl;
  BestFreeList list(64, 2);
  vector<AllocationResult *> allocations;

  for (int i = 0; i < NUMALLOCS; i++)
  {
    allocations.push_back(list.RequestAllocation(NUMBYTES + i));
  }

  cout << boolalpha;

  for (int j = 0; j < NUMALLOCS; j++)
  {
    cout << "** Allocation #" + to_string(j) + " **" << endl;
    cout << "Success: " << allocations.at(j)->is_successful() << endl;
    cout << "Address: " << allocations.at(j)->get_address() << endl;
    cout << "Size: " << allocations.at(j)->get_size() << endl;
    cout << "Search time: " << allocations.at(j)->get_search_time() << endl;
    cout << endl;
  }

  for (int k = 0; k < NUMALLOCS; k++)
  {
    cout << "** Freeing address: " + to_string(allocations.at(k)->get_address()) + " **" << endl;
    cout << "Free successful: " << list.FreeAllocation(allocations.at(k)->get_address()) << endl;
    cout << endl;
  }

  cout << "** Free List State **" << endl;
  cout << list.to_string() << endl;
  cout << endl;
}

void testWorstFreeList()
{
  cout << "### WORST FREE LIST ###" << endl;
  WorstFreeList list(64, 2);
  vector<AllocationResult *> allocations;

  for (int i = 0; i < NUMALLOCS; i++)
  {
    allocations.push_back(list.RequestAllocation(NUMBYTES + i));
  }

  cout << boolalpha;

  for (int j = 0; j < NUMALLOCS; j++)
  {
    cout << "** Allocation #" + to_string(j) + " **" << endl;
    cout << "Success: " << allocations.at(j)->is_successful() << endl;
    cout << "Address: " << allocations.at(j)->get_address() << endl;
    cout << "Size: " << allocations.at(j)->get_size() << endl;
    cout << "Search time: " << allocations.at(j)->get_search_time() << endl;
    cout << endl;
  }

  for (int k = 0; k < NUMALLOCS; k++)
  {
    cout << "** Freeing address: " + to_string(allocations.at(k)->get_address()) + " **" << endl;
    cout << "Free successful: " << list.FreeAllocation(allocations.at(k)->get_address()) << endl;
    cout << endl;
  }

  cout << "** Free List State **" << endl;
  cout << list.to_string() << endl;
  cout << endl;
}

void testFirstFreeList()
{
  cout << "### FIRST FREE LIST ###" << endl;
  FirstFreeList list(64, 2);
  vector<AllocationResult *> allocations;

  for (int i = 0; i < NUMALLOCS; i++)
  {
    allocations.push_back(list.RequestAllocation(NUMBYTES + i));
  }

  cout << boolalpha;

  for (int j = 0; j < NUMALLOCS; j++)
  {
    cout << "** Allocation #" + to_string(j) + " **" << endl;
    cout << "Success: " << allocations.at(j)->is_successful() << endl;
    cout << "Address: " << allocations.at(j)->get_address() << endl;
    cout << "Size: " << allocations.at(j)->get_size() << endl;
    cout << "Search time: " << allocations.at(j)->get_search_time() << endl;
    cout << endl;
  }

  for (int k = 0; k < NUMALLOCS; k++)
  {
    cout << "** Freeing address: " + to_string(allocations.at(k)->get_address()) + " **" << endl;
    cout << "Free successful: " << list.FreeAllocation(allocations.at(k)->get_address()) << endl;
    cout << endl;
  }

  cout << "** Free List State **" << endl;
  cout << list.to_string() << endl;
  cout << endl;
}

int main(int argc, char const *argv[])
{
  testBestFreeList();
  testWorstFreeList();

  return 0;
}
