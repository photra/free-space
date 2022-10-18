#include "memory.hpp"

FreeSpace::FreeSpace(int input_address, int input_size)
{
  address = input_address;
  size = input_size;
}

int FreeSpace::get_size()
{
  return size;
}

int FreeSpace::get_address()
{
  return address;
}

bool FreeSpace::operator<(FreeSpace const other) const
{
  return size < other.size;
}

bool FreeSpace::operator>(FreeSpace const other) const
{
  return size > other.size;
}

string FreeSpace::to_string()
{
  return "[" + std::to_string(address) + "]:" + std::to_string(size);
}