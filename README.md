custom-shell
============

This project was done as part of my Academic project at Indian Institute of Technology Patna (IIT Patna) in 
System Programming Lab course in 2nd Year

Objective
============

Create a command interpreter / shell. 
The basic functionality of a shell was
1. parse input
2. execute the command specified by the input (terminate the shell if the input command is "exit")
3. wait for the command to finish execution
4. after execution finishes, print the shell prompt again and back to step 1.

  The shell created a new process for each command. This practice increased
concurrency and protected the shell process from getting corrupted by possible
misbehaviours by the command.

Idea of Implementation
==========================

I had a directory (mydir) which contained my own C implementations of the command: pwd. When the user specified 
any command with arguments, my shell first checked whether a custom implementation was available in mydir. 
If not then it ran the appropriate built-in program with the arguments and finally printed the output to the screen. 
My implementation for the three commands supported the following command format.

1. [optional space]exit[optional space]
2. [optional space]pwd[optional space]
3. [optional space]cd[optional space]
4. [optional space]cd[one or more space]dir[optional space]

* When implementing exit, simply the exit(0) function was called.
* When I run "cd" (without arguments), my shell changed the working directory to the path stored in the 
$HOME environment variable. System call "getenv("HOME")" was used to obtain this. When a user changed the current 
working directory (e.g. "cd somepath"), my implementation simply used system call "chdir()" to change to the 
directory to somepath.
* When a user typed pwd, my implementation simply called "getcwd()".

Support for redirection
==========================

My shell also supported redirection using my custom implementation (not the built-in implementation). 
For example,
1. "command > file" created file if it does not exist and wrote the output of command into file. 
If file exists, then contents were overwritten.
2. "command > " printed error message.


Idea of Implementation for redirection
=========================================

1. used open() system call to open "file"
2. copied file descriptor for "file" into file descriptor entry for stdout using dup2 system call
3. closed "file" using close() system call

Support for batch mode execution
===================================

Shell supported a batch mode of execution. In interactive mode, I displayed a prompt and the user of the shell 
typed in one or more commands at the prompt. In batch mode, my shell was started by specifying a batch file on its
command line. The batch file contained the same list of commands as one would have typed in the interactive mode. 
In batch mode, I have not displayed a prompt. I printed each line I read from the batch file back to the user
before executing it. 

In both interactive and batch mode, my shell terminated whenever it saw the exit command on a line or 
reaches the end of the input stream (i.e., the end of the batch file).
