-----------
Performance
-----------
The implementation of SRT I believe certainly
made improvements in the performance.

--------------------------
time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m42.440s
user	0m42.434s
sys	0m0.000s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real	0m21.458s
user	0m42.710s
sys	0m0.004s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real	0m11.221s
user	0m44.527s
sys	0m0.002s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m5.767s
user	0m44.679s
sys	0m0.001s
mv 8-test.ppm.tmp 8-test.ppm

-----------------------------
As illustrated above, the improvements to the
Existing code continuously reduced the time it took
By approximately half the time. Clearly the real time
Was much more efficient especially with more threads. 
Parallelization of handling the tasks is evident though
I noticed the user time did increase, and system time
had an interesting spike but its behavior appears to be 
Returning to the initial state of a single thread.

------------------------------
Issues, Ideas, Thought process
------------------------------
It took me quite a bit of time to figure everything out.
I realized that in order to create the pthreads I had to
Create a function from the snippet of code in main. 
I did this so that I could pass it in as an argument to
Pthread create.
Likewise, I updated the iteration for the loop
In my function  to account for multithreading. 
I also made sure to utilize a global  array of 3 dimensions 
so that I could store values from the
function calls for later use. Afterwards, I
 made my pthreads and joined them.
I incorporate a simple error handling  during the
Join threads function call as a check. 
Afterwards, it was just simply outputting
The "pixels". Then deallocating whatever memory I did 
allocate. 

Some issues I faced were figuring out what POSIX threads
Were utilized and figuring out how to interpret the 
documentation. Another issue I had was an issue when
I ran 'make clean check'.
I received errors when I made the call but it
was because I added an additional character }
Which took some time to realize. Most of the issues I 
faced were small things related to syntax.
Lastly, interpreting the main.c code and figuring out 
What needed to be modified took some time to figure out
As well. 


