Fixed memory is a memory management library that takes care of memory fragmentation and allows for allocations to be safer and faster.
This is achieved with one tradeoff i.e. allocations will have a fixed size that will be specified in the beginning.
User can also use an optional option to allow for a use of memory pool where a memory pool is created in the beginning and then allocations are made from it.
If there is no more enough memory left in memory pool, it is expanded automatically using heap allocation.
This library aims to provide equivalent of `malloc` and `free` so another class name `Memory` is provided that will use Allocator and provide dynamic memory allocation.
In this there is no restriction of the size of memory blocks.






