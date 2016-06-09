# RSHELL
Melissa Do, Jeonghyoun Lee

# Overview 
Our RSHELL program executes commands the same way a bash terminal would. It runs basic linux commands, such as echo, ls, mkdir, rm, etc., and keeps prompting the user for input until he or she enters the exit command, which is "exit." It also allows the user to add comments to the input without running the comments. The input should be a command followed by an argument, for example, ls -a, where "ls" is the command and "-a" is the command. Our program also allows the user to enter multiple commands connected by either a SEMICOLON (;), AND (&&), or OR (||). The way these connectors work is, if a command is followed by a SEMICOLON (;), it is always executed. If a command is followed by an AND (&&), then the next command is only executed if the first one succeeds. Lastly, if a command is followed by an OR (||), then the next command is only executed if the first one fails. For invalid commands, our program should print out an error message. Our RSHELL program also allows precedence through the use of parentheses, so the user may group commands together. Our program also runs the "test" command, which can be written as: "test -e /test/file/path" or "[ -e /test/file/path ]". We also added input and output redirection as well as piping to our program.

#To Run
* git clone https://github.com/mdo006/rshell.git
* cd rshell
* git checkout hw4
* make
* bin/rshell

#Bugs/Limitations/Notes
* the cd command does not work
* does not handle redirective command such as ls -a && (does not ask for more input)
* does not handle incorrect connectors such as ";;" instead of ";" or "&" instead of "&&" or "|||" instead if "|", etc.
* does not handle the case where a connector is part of the string being echoed, for example echo "hello;"; would echo "hello" instead of "hello;"
* does not get rid of the quotations if the user enters something like echo "hello" (it will output "hello" instead of hello)
* outputs an error message if the user enters multiple spaces 
* still some bugs with the precedence
