#include "memory.hpp"
#include <iostream>

WorstFreeList::WorstFreeList(int input_memory_size, int input_header_size)
{
  memory_size = input_memory_size;
  header_size = input_header_size;

  FreeSpace f(0, memory_size);
  free_addresses.push(f);
}

AllocationResult *WorstFreeList::RequestAllocation(int size_in_bytes)
{
  int total_size = size_in_bytes + header_size;
  AllocationResult *result = new AllocationResult();

  if (free_addresses.size() > 0)
  {
    FreeSpace largest_block = free_addresses.top();
    if (largest_block.get_size() >= total_size)
    {
      free_addresses.pop();
      int starting_address = largest_block.get_address() + header_size;
      FreeSpace allocated_block(starting_address, total_size);

      int remaining_memory = largest_block.get_size() - allocated_block.get_size();
      if (remaining_memory > 0)
      {
        FreeSpace resized_block(starting_address + size_in_bytes, remaining_memory);
        free_addresses.push(resized_block);
      }

      result->succeeded()
          ->with_address(starting_address)
          ->with_size(size_in_bytes)
          ->with_search_time(1);

      allocated[starting_address] = result;

      return result;
    }
  }
  return result->failed()->with_search_time(1);
}

bool WorstFreeList::FreeAllocation(int memory_address)
{
  if (allocated.count(memory_address) == 0)
  {
    return false;
  }

  AllocationResult *prev_allocation = allocated[memory_address];
  FreeSpace regained_memory(prev_allocation->get_address() - header_size, prev_allocation->get_size() + header_size);

  free_addresses.push(regained_memory);
  allocated.erase(memory_address);

  return true;
}

int WorstFreeList::get_length()
{
  return free_addresses.size();
}

string WorstFreeList::to_string()
{
  string res = "";
  priority_queue<FreeSpace, vector<FreeSpace>, less<FreeSpace>> new_free_addresses;

  while (!free_addresses.empty())
  {
    FreeSpace current = free_addresses.top();
    new_free_addresses.push(current);
    free_addresses.pop();

    if (res == "")
    {
      res = current.to_string();
    }
    else
    {
      res = res + " --> " + current.to_string();
    }
  }

  free_addresses = new_free_addresses;

  return res;
}