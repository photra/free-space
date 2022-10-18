#include "memory.hpp"

AllocationResult *AllocationResult::succeeded()
{
  if (success == -1)
  {
    success = true;
  }

  return this;
}

AllocationResult *AllocationResult::failed()
{
  if (success == -1)
  {
    success = false;
  }

  return this;
}

AllocationResult *AllocationResult::with_address(int new_address)
{
  if (address == -1)
  {
    address = new_address;
  }

  return this;
}

AllocationResult *AllocationResult::with_size(int new_size)
{
  if (size == -1)
  {
    size = new_size;
  }

  return this;
}

AllocationResult *AllocationResult::with_search_time(int new_search_time)
{
  if (searchTime == -1)
  {
    searchTime = new_search_time;
  }

  return this;
}

bool AllocationResult::is_successful()
{
  return success;
}

int AllocationResult::get_address()
{
  return address;
}

int AllocationResult::get_size()
{
  return size;
}

int AllocationResult::get_search_time()
{
  return searchTime;
}