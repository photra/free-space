#include "memory.hpp"
#include <iostream>

FirstFreeList::FirstFreeList(int input_memory_size, int input_header_size)
{
  memory_size = input_memory_size;
  header_size = input_header_size;

  FreeSpace f(0, memory_size);
  free_addresses_vec.push_back(f);
}

AllocationResult *FirstFreeList::RequestAllocation(int size_in_bytes)
{
  int total_size = size_in_bytes + header_size;
  AllocationResult *result = new AllocationResult();
  int index = 0;

  while (index <= free_addresses_vec.size() - 1)
  {
    FreeSpace curr_space = free_addresses_vec[index];
    // if we find a free space that is big enough
    if (curr_space.get_size() >= total_size)
    {
      // initailize result success, address and size file
      result->succeeded()
          ->with_address(curr_space.get_address() + header_size)
          ->with_size(total_size);

      // check if the free space is exactly the required space or not.
      if (curr_space.get_size() != total_size)
      {
        // if there are space left, then:
        // resizing and relocating the original free space
        FreeSpace newFreeSpace(curr_space.get_address() + total_size, curr_space.get_size() - total_size);
        free_addresses_vec[index] = newFreeSpace;
      }
      else
      {
        // if the whole space is used, then delete it from the free space list
        free_addresses_vec.erase(free_addresses_vec.begin() + index);
      }
      index += 1;
      result->with_search_time(index);
      allocated[result->get_address()] = result;
      return result;
    }
    else
    {
      index += 1;
    }
  }

  result->failed()->with_search_time(index);
  return result;
}

bool FirstFreeList::FreeAllocation(int memory_address)
{
  if (allocated.count(memory_address) == 0)
  {
    return false;
  }

  AllocationResult *prev_allocation = allocated[memory_address];
  FreeSpace regained_memory(prev_allocation->get_address() - header_size, prev_allocation->get_size() + header_size);
  // insert at the front of the vector
  auto position = free_addresses_vec.begin() + (allocated[memory_address]->get_search_time() - 1);
  free_addresses_vec.insert(position, regained_memory);
  allocated.erase(memory_address);

  return true;
}

int FirstFreeList::get_length()
{
  return free_addresses_vec.size();
}

string FirstFreeList::to_string()
{
  string res = "";

  for (int i = 0; i < free_addresses_vec.size(); i++)
  {
    if (res == "")
    {
      res = free_addresses_vec[i].to_string();
    }
    else
    {
      res = res + " --> " + free_addresses_vec[i].to_string();
    }
  }

  return res;
}