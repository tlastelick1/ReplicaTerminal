# ReplicaTerminal
A shell that allows the user to run several other commands on a system (just like an actual terminal/shell)!

*********************************************************
Explanation of files in folder. 
*********************************************************

To run the GNU Island Shell program first the makefile. 
Simply type: make. 
This will execute the makefile and create two additional files: gnuIslandShell.o and gnuIslandShell
To run the program execute ./gnuIslandShell
The gnuIslandShell.cpp file contains all code and documenation of every function and process happening in the program.
The hist.h file contains a class responsible for keeping the history list within the program.
It is responible for being able to run the 'hist' command. 
readMe.txt contains all documentation (sources) used to answer all the questions to this program.

*********************************************************
Documentation.
*********************************************************

// Shell organization idea
https://www.youtube.com/watch?v=z4LEuxMGGs8

// How to invoke function from external .c file in C 
https://stackoverflow.com/questions/21260735/how-to-invoke-function-from-external-c-file-in-c

// Manipulating C strings and arrays. 
https://www.cplusplus.com/reference/cstring/
https://stackoverflow.com/questions/9726922/how-to-print-the-array


// Understanding fork(), parent and child processes. 
https://unix.stackexchange.com/questions/428124/what-codes-are-copied-to-the-child-process
https://www.tutorialspoint.com/unix_system_calls/waitpid.htm
https://stackoverflow.com/questions/40541831/c-child-process-not-executing
https://www.youtube.com/watch?v=kCGaRdArSnA						// understanding wait() 
https://www.tutorialspoint.com/unix_system_calls/waitpid.htm				// understanding wait()
https://www.tutorialspoint.com/unix_system_calls/getpid.htm	// parent/child functions 
https://www.geeksforgeeks.org/fork-system-call/						// fork()
https://www.tutorialspoint.com/fork-in-c							// fork() in C

// Using pointers 
https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm
https://www.youtube.com/watch?v=mw1qsMieK5c
https://www.tutorialspoint.com/cplusplus/cpp_pointer_to_an_array.htm
https://www.tutorialspoint.com/cplusplus/cpp_return_arrays_from_functions.htm

// Dynamic Prompt
https://www.youtube.com/watch?v=5fnVr-zH-SE						// Sending std out to an external file 

//Executing programs in other programs
https://www.youtube.com/watch?v=OVFEWSP7n8c

// Error checking
http://www.microhowto.info/howto/capture_the_output_of_a_child_process_in_c.html

// Reading input 
https://www.tutorialspoint.com/What-does-int-argc-char-argv-mean-in-C-Cplusplus // argc, char *argv[] explanation
https://man7.org/linux/man-pages/man3/stdout.3.html	// stdin, stdout, stderr 
https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm	// fgets()
https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm	// strtok()

// System functions / processes / envrionment 
https://www.tutorialspoint.com/unix_system_calls/index.htm
https://www.tutorialspoint.com/unix/unix-processes.htm
https://www.tutorialspoint.com/unix/unix-environment.htm

// Compiling 
https://www.geeksforgeeks.org/difference-between-gcc-and-g/	   			 // Difference between gcc and g++
https://www.incredibuild.com/integrations/gcc				   	 // What is GCC?
https://www.geeksforgeeks.org/linker/					         // Linking system libraries 

// Memory Allocation
http://www.cplusplus.com/doc/tutorial/dynamic/		                          // Dynamic memory allocation using c++
https://www.cplusplus.com/reference/cstdlib/malloc/	                          // Memory allocation using C
https://www.educba.com/malloc-in-c-plus-plus/		                          // How to use <cstdlib> library in c++
https://www.geeksforgeeks.org/new-and-delete-operators-in-cpp-for-dynamic-memory     // c++ delete and new operators
https://stackoverflow.com/questions/763520/deleting-a-char-array		         // Deleting character array memory
https://www.geeksforgeeks.org/vector-erase-and-clear-in-cpp/		         // Clearing vector contents
http://www.cplusplus.com/forum/general/78326/				         // Clearing charater array memory

// Type conversions
https://www.softwaretestinghelp.com/cpp-character-conversion-functions/	   	 // converting char to into
https://www.py4u.net/discuss/65856						 // converting char * to string

// String comparison 
https://www.cplusplus.com/reference/string/string/compare/				// comparing strings 

// Check if integer
https://www.tutorialspoint.com/cplusplus-program-to-check-if-input-is-an-integer-or-a-string        // checkNumber function
https://www.cplusplus.com/reference/string/stoi/		                                         // string to integer conversion 
