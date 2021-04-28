# ConcurrentSystemsAndOperatingSystems
 Four assignments for my third year comp eng CS & OS module.
 
	Practical 1 - Intro to pthreads

The object of this simple practical, worth 2%, is to get familiar with using Linux, to the point of being able to compile and run a pthread-based program.

Download the file  sumofhellos.c) attached to this practical.
Modify line 6 (#define USERNAME "username") to replace username with your TCD username.
Compile the code - warnings are OK, but there should be no errors:    cc -o sum sumofhellos.c -pthread
Run the executable (your username should appear seven times, as well as some number between 1 and 6 at the end):    ./sum
Obtain a log of the compilation and running of the program by either:        ./sum > practical1.log
Bundle both your source code and logfile into a "tar" archivetar -r -f P1.tar sumofhellos.c practical1.log
This will create a file called P1.tar.
Submit file P1.tar through Blackboard by the deadline.



	Practical 2 - Mutex Locks
	
This practical is worth 6% of your year-end mark.  It is an exercise in using condition variables and mutexes in a producer/consumer system. 
A single producer thread will continuously update a single global variable pnum with a sequence of different non-zero integer values. It will signal completion by setting that global variable to zero. Once set to zero, its value will remain zero.
In between each producer update, if the value of the global variable pnum satisfies a specific predicate (see below) then a consumer thread will read that value and add it into a global variable csum dedicated for its own use. It will also terminate when the global variable pnum set by the producer has become zero.
When both produce and consumer threads are done, the value of the consumer global variable csum will be output.
You are given four files:
    cond.c - this provides three different functions that compute a condition on their integer input (DO NOT CHANGE).
    1to10.txt - this contains numbers from 1 to 10 followed by a zero. It is a convenient way to get data into the main program.
    1to20.txt - this contains numbers from 1 to 20 followed by a zero. It is a convenient way to get data into the main program.
    practical2.c - the main program. It accepts a stream of integers separated by white space on standard input, and an optional command line argument that specifies which of the condition functions in cond.c should be used (cond1() is the default).
To compile, use cc -o p2 practical2.c -pthread
To run for 1..20 with the default condition (cond1()) :          ./p2 < 1to20.txt    or      ./p2 1 < 1to20.txt
To run for 1..10 with  condition cond2():                             ./p2 2 < 1to10.txt
To run for 1..20 with condition cond3():                              ./p2 3 < 1to20.txt
If you just run ./p2 then you will get an endless stream of print statements from the consumer, busily multiplying 999 by infinity by the process of repeated addition !
Note that the number argument to select the condition needs to occur between ./p2 and < .
The program as given launches both a producer and consumer thread, but they use no form of thread synchronisation. Your task is to use mutexes and condition variables to ensure the right answer is produced.
Do not move, delete, or modify, any printf statement that outputs a string starting with "@" !
You may add your own printf statements, but they should not produce lines that start with "@".
You will need to declare extra global variables, and modify the program mainline, as well as some or all of  produceT, Produce, consumeT and Consume. You should be adding declarations and statements,
To submit, just upload your modified practical2.c file (no zip/tar/gzip/log files required).



	Practical 3 - Promela Frog Game
	
This practical is worth 6% of your year-end mark. It is due at the end of Week 8. It is an exercise in using Promela and SPIN to model a variation of the Jumping Frogs example found on pages 29-32 in the slides for Lecture 11 (Week 4, Tuesday).
We have four frogs (`FROG1` to `FROG4`), with only `FROG1` moving rightwards, while the three other frogs are moving leftwards. We have five positions, numbered 1 through 5.
Initially, FROG1 is in position 1, and FROG2, FROG3 and FROG4 are in positions 3, 4 and 5. Position 2 has no frog present in it.
FROG1 can only move right, while FROG2, FROG3 and FROG4 can only move left. A frog can only move if an empty location is next to it (in the appropriate direction), or reachable by jumping over one other frog.
Your task is to write a Promela model in file  "frogs.pml", that models this example, and which uses `printf` statements to produce output just like that shown below. Note that both frogs and positions here are numbered from one upwards. If you use arrays for anything, make that you report such numbers appropriately.
In addition, your Promela file should make it possible for a SPIN verification run to find a sequence of frog moves that leads to a desirable final state where FROG1 is in position 5, and  frogs 2,3 & 4 are in positions 1,2 and 3 in any order. You should do this by adding an assertion that evaluates to false if the model terminates in such a desirable state. The following command sequence can be used to run the verification and observes its output:
        spin -run -E frogs.pml 
        This should report an assertion violation, and that it wrote frog.pml.trail
        spin -t -T frogs.pml 
        This should show the successful sequence of moves.

Required output format (example)

EMPTY 3, FROG1@1, FROG2@2, FROG3@4, FROG4@5
START FROG 4 AT 5 GOING LEFT
START FROG 3 AT 4 GOING LEFT
START FROG 2 AT 3 GOING LEFT
MOVE FROG2 FROM 3 TO 2
EMPTY 3, FROG1@1, FROG2@2, FROG3@4, FROG4@5
START FROG 1 AT 1 GOING RIGHT
MOVE FROG1 FROM 1 TO 3
EMPTY 1, FROG1@3, FROG2@2, FROG3@4, FROG4@5
...
EMPTY 4, FROG1@5, FROG2@1, FROG3@2, FROG4@3
DONE!

Note that different runs will have different frogs moving in different orders, and most runs will deadlock.

    The line starting with `EMPTY` shows which location has no frog, followed by the locations of each of the four frogs (`FROGn@p` says that `FROG` *n* is at location *p*). Such a line should be the first thing printed.
    The lines above that  start with `START` should be printed for each frog, once only, before they make any moves.
    Lines above that start with `MOVE` should be printed every time a frog makes a move, immediately followed by a line starting with `EMPTY`, that displays the current state of the system.

REMEMBER - the output of printf statements in your model will be used to check the correctness of your model by an automated system. Please ensure you generate output in exactly the format shown above.  See attached template file (frog_printf_template.pml).



	Practical 4 - xv6LoadBalancing
	
This practical is worth 6% of your year-end mark. It is due at the end of Week 12. It is an exercise in changing the xv6 scheduler from a simple round-robin one, to one that also does a simple form of "load balancing"
The material for Practical 4 is contained in p4-distr-2020-21.zip (attached), which contains two markdown files containing instructions and background information. HTML versions of this files are attached here.
To submit, simply upload just the file proc.c to blackboard.


