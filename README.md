[![Build Status](https://travis-ci.org/dhillondeep/fixed-memory.svg?branch=master)](https://travis-ci.org/dhillondeep/fixed-memory)

# Overview

Fixed memory is a memory management library that takes care of memory fragmentation and allows for allocations to be safer and faster.
This is achieved with one trade off i.e. allocations will have a fixed size that will be specified in the beginning. User can also use an optional option to allow for a use of memory pool where a memory pool is created in the beginning and then allocations are made from it. If there is no more enough memory left in memory pool, it is expanded automatically using heap allocation. This library aims to provide equivalent of `malloc` and `free` so another class named `Memory` is provided which will use Allocator and provide dynamic memory allocation. Using `Memory` there are no restriction on the size of memory blocks.

This library is inspired by **David Lafreniere's [xallocator](https://www.codeproject.com/Articles/1084801/Replace-malloc-free-with-a-fast-fixed-block-memory)** library


## Why Allocator and Memory
This library is very useful when working with embedded systems where memory is limited and hence memory fragmentation can occur very easily. Heap cannot be used all the times if stability is a concern on a system. Using this library will eliminate safety issues while still having flexibility of dynamic allocation. This library can be easily used on `Arduino` boards and it is tested to be memory friendly and effective for that platform. On regular computers this library can have uses when writing safety critical code.
 

## Allocator class

This is a fixed memory block solution where you user specifies the size of memory block and optionally memory pool to be used.
So whenever there is an allocation that is made, Allocator provides access to memory of block size. Examples of constructors are shown below:

```cpp
// memory block size is provided so on allocations heap is used to satisfy
// user's needs and on de-allocation that memory is kept for recycling and not
// returned back to the system
Allocator allocator{9};
```

```cpp
// memory block size is provided along with size of memory pool. Memory pool
// of this size is created in the begining and then used later on for allocations.
// If the pool runs out of memory, dynamic memory is used to expand it
Allocator allocator{9, 18};
```

```cpp
// memory block size is provided along with user allocated memory pool. This pool
// could be static or dynamic and is used for allocations. If the pool runs out of memory, 
// dynamic memory is used to expand it
char memory[18];    // static
Allocator allocator{9, memory, 18, Allocator::STATIC};

char *memory2 = new char[18]; // dynamic
Allocator allocate2{9, memory2, 18, Allocator::DYNAMIC};
```

## Memory Class
This is meant to replace ``malloc``, ``free`` and ``realloc`` by using ``Allocator`` behind the screen. It allocates fixed blocks of different sizes and provides them to the user when asked for a memory block. Size of the block given could be larger than the size asked for the because fixed allocation is being used.


```cpp
// allocates an array of chars but size allocated will be 8 plus the size of a pointer. This varies
// based on the machine
auto char* array = (char*)memory_alloc(8);
```

```cpp
// frees the array of chars but the memory is not returned to the system but rather used by program
// to allocate next time asked for a block of similar size
memory_free(array);
```

```cpp
// reallocates the array based on the new size
auto char* array2 = (char*)memory_realloc(array, 16);
```

Classes can also overload ``new`` and ``delete`` operators so that these operators can be used instead of ``memory_alloc`` and ``memory_free``

```cpp
class Example{
  // macro defined in Memory.h
  MEMORY_OVERLOAD
}
```

The macro overloads the operator and the class can now be created with new and delete





