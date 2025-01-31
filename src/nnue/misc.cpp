/*
  Thanks to Yu Nasu, Hisayori Noda. This implementation adapted from R. De Man
  and Daniel Shaw's Cfish nnue probe code https://github.com/dshawul/nnue-probe

  modified as follows via clang cpp core guidelines:
  declaration and assignment joined
  deprecated C++ headers replaced [modernize-deprecated-headers]
  macros used to declare a constant changed to 'constexpr' constant [cppcoreguidelines-macro-usage]
  parameters made const
  c-style casts replaced with C++ casts
  name does not match rule 'Global constants'
  name does not match rule 'Enum members'
  auto used when initializing with a cast to avoid duplicating the type name [modernize-use-auto]
  zero constants replaced with nullptr
  local variables made const
  cast from 'const char *' to 'char *' dropped const qualifier [clang-diagnostic-cast-qual]
  redundant C-style casts removed
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
#include <cstdio>
#include <cctype>

#include "misc.h"

FD open_file(const char* name)
{
#ifndef _WIN32
	return open(name, O_RDONLY);
#else
	return CreateFile(name, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
	                  FILE_FLAG_RANDOM_ACCESS, nullptr);
#endif
}

void close_file(const FD fd)
{
#ifndef _WIN32
	close(fd);
#else
	CloseHandle(fd);
#endif
}

size_t file_size(const FD fd)
{
#ifndef _WIN32
	struct stat statbuf;
	fstat(fd, &statbuf);
	return statbuf.st_size;
#else
	DWORD size_high;
	const DWORD size_low = GetFileSize(fd, &size_high);
	return (static_cast<uint64_t>(size_high) << 32) | size_low;
#endif
}

const void* map_file(const FD fd, map_t* map)
{
#ifndef _WIN32
	* map = file_size(fd);
	void* data = mmap(NULL, *map, PROT_READ, MAP_SHARED, fd, 0);
#ifdef MADV_RANDOM
	madvise(data, *map, MADV_RANDOM);
#endif
	return data == MAP_FAILED ? NULL : data;

#else
	DWORD size_high;
	const DWORD size_low = GetFileSize(fd, &size_high);
	*map = CreateFileMapping(fd, nullptr, PAGE_READONLY, size_high, size_low, nullptr);
	if (*map == nullptr)
		return nullptr;
	return MapViewOfFile(*map, FILE_MAP_READ, 0, 0, 0);
#endif
}

void unmap_file(const void* data, map_t map)
{
	if (!data) return;

#ifndef _WIN32
	munmap((void*)data, map);
#else
	UnmapViewOfFile(data);
	CloseHandle(map);
#endif
}
