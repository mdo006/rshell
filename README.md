# RSHELL
Melissa Do, Jeonghyoun Lee

# Overview 
Our RSHELL program executes commands the same way a bash terminal would. It runs basic linux commands, such as echo, ls, mkdir, rm, etc., and keeps prompting the user for input until he or she enters the exit command, which is "exit." It also allows the user to add comments to the input without running the comments. The input should be a command followed by an argument, for example, ls -a, where "ls" is the command and "-a" is the command. Our program also allows the user to enter multiple commands connected by either a SEMICOLON (;), AND (&&), or OR (||). The way these connectors work is, if a command is followed by a SEMICOLON (;), it is always executed. If a command is followed by an AND (&&), then the next command is only executed if the first one succeeds. Lastly, if a command is followed by an OR (||), then the next command is only executed if the first one fails. For invalid commands, our program should print out an error message. 
#To Run
* git clone https://github.com/mdo006/rshell.git
* cd rshell
* git checkout hw2
* make
* bin/rshell

#Bugs/Limitations/Notes
* does not handle redirective command such as ls -a && (does not ask for more input)
* the exit command does not work properly when there is an invalid input in the command line (sometimes the user will have to type "exit" multiple times before the program exits
* does not handle incorrect connectors such as ";;" instead of ";" or "&" instead of "&&" or "|||" instead if "|", etc.
