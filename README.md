# OS-Lab
Solutions to various Operating System (Linux/Unix based) problems.

*Problem 1:*
Write a C program to create a child process using the system call fork( ). From the child process, display
the PID and PPID and then call again the fork( ) to create a grandchild and engage him to display your **some output** From parent display the PID and PPID of all the processes and display the count of total no. of child processes created also the number of grandchild processes created. 

*Problem 2:*
Write a C program and use the system call wait() to synchronize the execution of parent program in the program until child process finishes. Now write a function to print to find out who is logging in the local machine that is partially equivalent to the cmd "w" or "who" and engage the grandchild to print the output into the stdout.

*Problem 3:*
Write a C program and overlay a user designed program into the address space of the child process using execv() system call. Again use wait() system call to synchronize the execution of parent process in your program until child process finishes. Here use the macro WIFEXITED to capture the returned status of the child in parent process.

*Problem 4:*
Write a C program using signal() system call to handle the reception of SIGINT signal which allows to execute a designated (user) function. Here the function is responsible for creating a child process by using fork() system call and then you have to display the PROCESS ID and PARENT PROCESS ID from the parent process as well as from the child process.

*Problem 5:*
Write a C program which will take the Process ID and signal ID as input to demonstrate the use of kill( ) system call.

*Problem 6:*
Write a C program to create a user level thread using system call pthread_create( ) and assign the thread to display the “HELLO WORLD” . Use pthread_exit() in the program for terminating the thread.

*Problem 7:*
Write a C program to handle the reception of INTERRUPT FROM THE KEYBOARD signal by executing a particular (user) function, which function is responsible for creating a child process by using fork() system call. Also, the child process will take an input N (N is the no. of terms to generate the Fibonacci series) from the user and generate the Fibonacci series up to N terms. Then the child process will send the Fibonacci series terms one by one to the parent process by using pipe() system call and the parent process will read the Fibonacci series terms one by one and will display it.

*Problem 8:*
Write a C program which will be able to read a file using read() system call. Now you provide a mechanism to set a lock by using fcntl() system call and to release the lock by using the same fcntl() system call.
Now run the program from two different terminals simultaneously and demonstrate that if one process has got the lock, then that process only can read the file. But the other one is not permitted to read the file until the lock is released by the first process. That means, only one process who acquires the lock can read the file at any instant of time.

*Problem 9:*
Write a C program which is responsible for creating a named PIPE or FIFO with necessary permission for all users by using the mknod( ) system call. Now, you keep the facility to read the information from the FIFO if any other process write some information into the FIFO and as well as keep the facility to write some information into the FIFO, so that Program2 can read it. Again write another C program called Program2 which is responsible for taking the user input and write it back to the FIFO so that Program1 can read it. Provide the facility to read the FIFO in this program.

*Problem 10:*
Write a two C programs to be one client program and one server program so that you can demonstrate the IPC mechanism using Message Queue functionality.

*Problem 11:*
Write a two C programs to demonstrate the concept of shared memory where program1(process1) will be responsible for writing it’s process id and program2 (process2) will be responsible for reading the contents whatever program1(process1) writes and try to remove the shared memory segment that is created for your above mentioned operations properly by using proper system call.

*Problem 12:*
Write a C program to get the process submission time & finished time of a process. The C program will create a child process and writes the submission and finished time of the child process into a file.

*Problem 13:*
Write two C programs which will be responsible for reading the contents of a file (single file). Now use the concept of semaphore to provide synchronization between the processes of program1 and program2, so that program2 can read the contents of the specified file only after reading the contents of the file by program1. Again if the program1 runs for n times, then program2 can read the contents of the file at most n times only, not more than that. Moreover remove the semaphore that is created for above mentioned operations properly by using proper system call.

*Problem 14:*
Write two C programs which will be responsible for reading some value (i.e. say a string “Hello” or any other value of your choice) in a shared memory block. First allow the respective processes of prog1 and prog2 to read and print the content controlled by semaphore. Next perform the necessary modification in the code such that both the processes reflect the Busy-Wait lock (i.e. semaphore based Spin lock). To implement this program use two semaphores variables (say A and B) and implement busy-wait scenario as we discussed in theory). Finally remove the semaphore that is created for the above mentioned operations properly by using proper system call.

*Problem 15:*
Implement malloc() in C as MyOwnMalloc( ) function. Implement free() as MyOwnfree() and use it to free the allocated memory by MyOwnMalloc() 
