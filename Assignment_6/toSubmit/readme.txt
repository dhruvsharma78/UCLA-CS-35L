README

Dhruv Sharma
605-082-988

1. My first challenge was to get a brief idea of what the code was
   doing. I understood that within the main() function,
   computations were being done to get the RGB value of each pixel.

2. Finding what can be parrallelized:
   Sinnce no computation is using data from a previous computation,
   each of them could be computed separately and that would not
   affect the final output image.

3. Parrallelizing:
   I moved the bulk of the code within the main function: the 2 nested
   loops, into its own function and created threads to call it and join
   the threads when done.
   I unrolled the loops so that each thread i, starts from index i of the
   outer loop and increments by nThreads. This causes each thread to work on
   a different set of pixels and ensures that 2 threads never work on the
   same pixel

4. Challenge 1:
   The program wouldn't compile since a lot of the data I was trying to access
   was out of scope. The only viable solution to this was to either pass in each
   of these values to the function as a struct, or to use global variables.
   I chose to use global variables.

5. Challenge 2:
   Printing. I noticed by comparing the output with the baseline that while
   my program output all the pixels, it didn't do it in the right order.
   This was because all my print statements were in the threaded function.
   The solution was to create a global array to store all the pixel color values
   and only print them out in order once all threads are done and joined.

Performance Improvements:

   Time                             THREADS
               1           2           4           8          16
   ----    ---------   ---------   ---------   ---------  ---------
   real    0m41.898s   0m21.215s   0m11.101s   0m5.860s	  0m2.989s
   user    0m41.890s   0m42.093s   0m43.395s   0m44.841s  0m44.672s
   sys     0m0.002s    0m0.001s	   0m0.004s    0m0.001s	  0m.023s


   Increasing the number of threads directly almost by n times where n is the number of threads
   as compared to the single threaded performance.
