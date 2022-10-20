#pragma once
#include <queue>
#include <map>
#include <string>

using namespace std;

class AllocationResult
{
  int success = -1;
  int address = -1;
  int size = -1;
  int searchTime = -1;

public:
  AllocationResult *succeeded();

  AllocationResult *failed();

  AllocationResult *with_address(int new_address);

  AllocationResult *with_size(int new_size);

  AllocationResult *with_search_time(int new_search_time);

  bool is_successful();

  int get_address();

  int get_size();

  int get_search_time();
};

class FreeSpace
{
  int address;
  int size;

public:
  FreeSpace(int input_address, int input_size);

  int get_size();

  int get_address();

  bool operator<(FreeSpace const other) const;

  bool operator>(FreeSpace const other) const;

  string to_string();
};

class FreeList
{
protected:
  int memory_size;
  int header_size;
  map<int, AllocationResult *> allocated;
  priority_queue<FreeSpace> free_address;

public:
  virtual AllocationResult *RequestAllocation(int size_in_bytes) = 0;

  virtual bool FreeAllocation(int memory_address) = 0;

  virtual int get_length() = 0;

  virtual string to_string() = 0;
};

class BestFreeList : public FreeList
{
  priority_queue<FreeSpace, vector<FreeSpace>, greater<FreeSpace>> free_addresses;

public:
  BestFreeList(int input_memory_size, int input_header_size);

  AllocationResult *RequestAllocation(int size_in_bytes);

  bool FreeAllocation(int memory_address);

  int get_length();

  string to_string();
};

class WorstFreeList : public FreeList
{
  priority_queue<FreeSpace, vector<FreeSpace>, less<FreeSpace>> free_addresses;

public:
  WorstFreeList(int input_memory_size, int input_header_size);

  AllocationResult *RequestAllocation(int size_in_bytes);

  bool FreeAllocation(int memory_address);

  int get_length();

  string to_string();
};

class FirstFreeList : public FreeList
{
  vector<FreeSpace> free_addresses_vec;

public:
  FirstFreeList(int input_memory_size, int input_header_size);

  AllocationResult *RequestAllocation(int size_in_bytes);

  bool FreeAllocation(int memory_address);

  int get_length();

  string to_string();
};