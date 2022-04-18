# SL-assignment-4
This repository is a part of Software lab Assignment 4. 
In this assignment, a heap is simulated and the garbage collector is implemented in two methods:

<b>1. Mark-and-Sweep method.</b>

<b>2. Reference Counting method.</b>

### Heap simulation: 
* First-fit algorithm is used to simulate heap.
* Node with start, end indices and id of the block are taken.
* Memory size is user input.
* Allocate and deallocate functions are implemented.

### Garbage Collection: 
* Garbage Collection is a memory management technique. 
* No more in use or unreachable objects are deleted by garbage collector.
* New objects are alloted space in space of unreachable ones.


### Mark-and-sweep Method:
* Mark and sweep algorithm is implemented in two methods.
* The mark phase and the sweep phase.
* #### Mark Phase: All the blocks are iterated and unreachable ones are marked as 1.
* #### Sweep Phase: After marking the unreachable objects, they are swept off the heap.

### Reference Counting Method:
* It is the simplest method of garbage collection.
* Objects with no references are filtered out from the objects.
* At every connection, count is incremented by 1 and while garbage collection, nodes will be disconnected and count will be decremented
* All the nodes with count = 0 at the end of the iterations will be removed
