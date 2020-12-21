
Seth Tummillo
IT 383 - Sec 002



When writing this program the first thing that I focused on was trying to understand exactly how I could get a multi-threaded quicksort
to work and potential algorithms that I could implement. At first I was looking into a way to partition the array multiple times
to try and then be able to merge everything together at the end through concatination. However after some advice from class
I realized that merging subarrays after each has been sorted by grabbing the lowest number from the group of arrays
resulted in a linear merge time. After i decided on my algorithm I needed to ensure that my quicksort worked in general. writing
the quicksort methods, along with the code to open and read the files was fairly straightforward and for the most part the single
thread quicksort worked the first time. When writing the single thread quicksort I also made sure to implement it in a way to where
to change the number of threads you simply need to change the THREAD_COUNT variable. Threads were kept in an array of threads and the
parameters for the functions for each thread were stored in an array of stucts. This struct contained the array, low, and high.

To ensure that I used the least amount of memory as possible, each thread referenced the same array instead of having their own copy.
This made it a little harder to merge the arrays however to solve this I simply modified the variables within the struct that pertained
to each thread.

I will say that the most frustrating part of this program was trying to debug a small issue that ended up taking about an hour. 
When creating the struct I had an issue where there was an addition element to the number array. This was because I had

int currentIndex = size;

instead of

int currentIndex = size-1;

This caused that extra element to be initialized to 0 which messed up the sorting.

As for performance, increasing the number of threads running at once increased the performance by quite a significant bit.

1 thread = ~5seconds
3 threads = ~2-3 seconds
6 threads = 1 second
