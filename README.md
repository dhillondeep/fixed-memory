[![Build Status](https://travis-ci.org/dhillondeep/fixed-memory.svg?branch=master)](https://travis-ci.org/dhillondeep/fixed-memory)

# Overview

Fixed memory is a memory management library that takes care of memory fragmentation and allows for allocations to be safer and faster.
This is achieved with one tradeoff i.e. allocations will have a fixed size that will be specified in the beginning.
User can also use an optional option to allow for a use of memory pool where a memory pool is created in the beginning and then allocations are made from it.
If there is no more enough memory left in memory pool, it is expanded automatically using heap allocation.
This library aims to provide equivalent of `malloc` and `free` so another class name `Memory` is provided that will use Allocator and provide dynamic memory allocation.
In this there is no restriction of the size of memory blocks.

## Allocator

This is a fixed memory block solution where you user specifies the size of memory block and optionally memory pool to be used.
So whenever there is an allocation that is made, Allocator provides access to memory of block size. Examples of constructors are shown below:

```cpp
// memory block size is provided so on ever allocation heap is used to satisfy
// user's need and on de-allocation that memory is kept for recycling and not
// returned back to the system
Allocator allocator{9};
```

```cpp
// memory block size is provided along with size of memory pool. Memory pool
// of this size is created in the begining and the used later on for allocations.
// If the pool runs out of memory, dynamic memory is used to expand it.
Allocator allocator{9, 18};
```

```cpp
// memory block size is provided along with user allocated memory pool. This pool
// could be static or dynamic and is used for allocations. If the pool runs out of memory, 
// dynamic memory is used to expand it.
char memory[18];    // static
Allocator allocator{9, &memory, 18, Allocator::STATIC};

char *memory2 = new char[18]; // dynamic
Allocator allocate2{9, memory2, 18, Allocator::DYNAMIC};
```





