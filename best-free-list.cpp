#include "memory.hpp"
#include <iostream>

BestFreeList::BestFreeList(int input_memory_size, int input_header_size)
{
  memory_size = input_memory_size;
  header_size = input_header_size;

  FreeSpace f(0, memory_size);
  free_addresses.push(f);
}

AllocationResult *BestFreeList::RequestAllocation(int size_in_bytes)
{
  int total_size = size_in_bytes + header_size;
  deque<FreeSpace> iterated;
  AllocationResult *result = new AllocationResult();
  int search_time = 0;

  while (free_addresses.size() > 0)
  {
    search_time++;
    FreeSpace current = free_addresses.top();
    free_addresses.pop();
    iterated.push_back(current);
    int min_difference = memory_size;

    if (current.get_size() >= total_size)
    {
      int difference = current.get_size() - total_size;

      // found a more optimal block
      if (difference < min_difference)
      {
        min_difference = difference;

        // edge case: last block is optimal
        if (free_addresses.empty())
        {
          while (iterated.size() > 1)
          {
            free_addresses.push(iterated.front());
            iterated.pop_front();
          }

          FreeSpace optimal_block = iterated.front();
          int starting_address = optimal_block.get_address() + header_size;

          int remaining_memory = optimal_block.get_size() - total_size;
          if (remaining_memory > 0)
          {
            FreeSpace resized_block(starting_address + size_in_bytes, remaining_memory);
            free_addresses.push(resized_block);
          }

          result->succeeded()
              ->with_address(starting_address)
              ->with_size(size_in_bytes)
              ->with_search_time(search_time);

          allocated[starting_address] = result;

          return result;
        }
      }
      else
      {
        // found most optimal block
        free_addresses.push(iterated.back());
        iterated.pop_back();

        while (iterated.size() > 1)
        {
          free_addresses.push(iterated.front());
          iterated.pop_front();
        }

        FreeSpace optimal_block = iterated.front();
        int starting_address = optimal_block.get_address() + header_size;

        result->succeeded()
            ->with_address(starting_address)
            ->with_size(size_in_bytes)
            ->with_search_time(search_time);

        allocated[starting_address] = result;

        return result;
      }
    }
  }

  // no blocks large enough, return result
  while (!iterated.empty())
  {
    free_addresses.push(iterated.front());
    iterated.pop_front();
  }

  return result->failed()->with_search_time(search_time);
}

bool BestFreeList::FreeAllocation(int memory_address)
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

int BestFreeList::get_length()
{
  return free_addresses.size();
}

string BestFreeList::to_string()
{
  string res = "";
  priority_queue<FreeSpace, vector<FreeSpace>, greater<FreeSpace>> new_free_addresses;

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