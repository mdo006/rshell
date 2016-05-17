#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h> 
#include <errno.h>
// #include<signal>

using namespace std;

bool execute (string pass)
{
	bool valid = true;
	
	char* test[80];
	//valid = 1;
	vector<string> command;
	string temp= "";
	unsigned j = 0;
	unsigned i = 0;
	
	while (i < pass.size())
	{
		for (j = i ; j < pass.size(); ++j)
		{
			if (pass.at(j) ==' ')
			{
				//this means we are moving to next word.
				++j;
				break;
			}
			else
			{
				temp = temp + pass.at(j);
			}
		}
		
		if (temp == "exit")
		{
			command.clear();
			temp.clear();
			exit(0);
		}
		
		command.push_back(temp);
		temp.clear();
		
		//so we can start basing on where we left off in pass string
		i = j; 
	}
	
	unsigned k = 0;
	
	for(; k < command.size() ;++k)
    {
    	string temp_str = command.at(k);
        test[k] = (char*)temp_str.c_str();
    }
    
    test[k] = '\0';
    
	pid_t pid = fork();
	
	//if pid is less than 0, then fork failed
 	if (pid < 0)
 	{
 		perror("Fork failed");
 		exit(-1);
 	}
	
	/*run execvp in the child because execvp automatically terminates all 
	  processes after it executes*/
 	if (pid == 0) //child process
    {
    	//if execvp returns -1, the command did not execute
        if (execvp(test[0], test) == -1)
        {
        	perror("exec");
        	exit(errno);
        	valid = false;
        }
        else
        {
        	//successful completion
        	exit(0);
        }
    }
    
	int num = 0;
	//tells parent to wait
	wait(&num);
	
	int num2 = WEXITSTATUS(num);
	
	//if errno > 0, it did not work
	if (num2 > 0)
	{
		valid = false;
	}
	
	//successful completion
	if (num2 == 0)
	{
		valid = true;
	}
    
	command.clear();
	return valid;
}

void parse (vector<string> &input)
{
	vector<string> reverse_input;
	
	//reverse the vector of inputs 
	//so we can use pop_back (we could make a quene but we did this instead)
	for (int i = input.size() - 1; i >= 0; --i)
	{
		reverse_input.push_back(input.at(i));
	}
	
	//check if the 1st command is exit
	//if it is, exit the program
	if (input.at(0) == "exit")
	{
		input.clear();
		reverse_input.clear();
		exit(0);
	}
	
	//execute 1st command;
	bool  valid;
	int size = reverse_input.size();
	valid = execute(reverse_input.at(size - 1));
	reverse_input.pop_back();
	
	//parse this vector and execute accordingly
	for (int i = reverse_input.size() - 1; i >= 0; i = i - 2)
	{
		if (reverse_input.at(i) == ";")
		{
			//check for exit command
			if (reverse_input.at(i - 1) == "exit")
			{	
				execute(reverse_input.at(i - 1));
			}
			
			//always execute a command that follows a semicolon
			execute(reverse_input.at(i - 1));
			reverse_input.pop_back();
			reverse_input.pop_back();
		}
		else if (reverse_input.at(i) == "&&")
		{
			if (valid == true) //1st command executed properly
			{
				//check for exit command
				if (reverse_input.at(i - 1) == "exit")
				{	
					execute(reverse_input.at(i - 1));
				}
				
				//execute 2nd command
				execute(reverse_input.at(i - 1));
			}
			//if the 1st command is NOT valid, we do NOT want to execute the 2nd one
			/*whether we execute or not, we still want to pop_back() 3 times to
			  move to the next command*/
			reverse_input.pop_back();
			reverse_input.pop_back();
		}
		else if (reverse_input.at(i) == "||")
		{
			if (valid == false) //1st command did not execute 
			{
				//check for exit command
				if (reverse_input.at(i - 1) == "exit")
				{	
					execute(reverse_input.at(i - 1));
				}
				
				execute(reverse_input.at(i - 1));
			}
			
			//if the 1st command is VALID, we do NOT want to execute the 2nd one
			/*whether we execute or not, we still want to pop_back() 3 times to
			  move to the next command*/	
			reverse_input.pop_back();
			reverse_input.pop_back();
		}
	}
}

int main()
{
	//loop until the user exits
	while (1)
	{
		//command line inputted by user
		char userInput[100];
		
		//to hold the user input after the comments are removed
		char userInput_no_comments[100];
//====================EXTRA CREDIT======================================		
		//get hostname (extra credit)
		char hostname[80];
	    gethostname(hostname, sizeof hostname);
	    //get username 
	    char *name;
	    name = getenv("USER");
    	printf("%s@",name);
		//print a command prompt (e.g. $)
		printf("%s $ ", hostname);
//==========================================================		
		//read in command as one line
		cin.getline(userInput, 100);
		
		if(userInput[0] != '\0' || userInput[0] != ' ')
		{
			//ignore everything after '#' (everything after '#' is a comment)
			for (int i = 0; userInput[i] != '\0'; ++i)
			{
				if (userInput[i] == '#')
				{
					break;
				}
				
				userInput_no_comments[i] = userInput[i];
				userInput_no_comments[i + 1] = '\0';
			}
			
			
			//get connectors from userInput and store it into a vector
			//but in this vector && and || are stored as & & and | |
			vector<char> vector_connectors_separated;
			
			//FIX THIS LATER IF THERE IS TIME 
			//DOES NOT ACCOUNT FOR JUST '&', JUST '|', OR MORE THAN TWO '&'s OR '|'s
			//ALSO DOES NOT ACCOUNT FOR MORE THAN ONE ';' IN A ROW
			for (unsigned i = 0; userInput_no_comments[i] != '\0'; ++i)
			{
				if (userInput_no_comments[i] == ';'|| userInput_no_comments[i] == '&' 
					|| userInput_no_comments[i] == '|')
				{
					vector_connectors_separated.push_back(userInput[i]);
				}
			}
			
			//NOW COMBIN & and & into && and | and | into ||
			vector<string> vector_connectors;
			
			for (unsigned i = 0; i < vector_connectors_separated.size(); ++i)
			{
				if (vector_connectors_separated.at(i) == '&')
				{
					vector_connectors.push_back("&&");
					++i;
				}
				else if (vector_connectors_separated.at(i) == '|')
				{
					vector_connectors.push_back("||");
					++i;
				}
				else if (vector_connectors_separated.at(i) == ';')
				{
					vector_connectors.push_back(";");
				}
			}
			
			//use strtok to separate input into "tokens"
			char* tokens; //command and its arguments
			char delimiters[] = ";&&||";
			tokens = strtok(userInput_no_comments, delimiters);
			
			//stores all the commands and its arguments as separate "tokens"
			vector<char*> vector_tokens;
			
			while (tokens != NULL)
			{
				// int position =0;
				// while(())
				//remove first whitespace in token
				if (tokens[0] == ' ')
				{
					++tokens; //go to next character (ignore 1st white space)
				}
				
				vector_tokens.push_back(tokens);
				tokens = strtok(NULL, delimiters);
			}
			
			//convert the tokens from char* to string
			vector<string> vector_tokens_str;
		
			for (unsigned i = 0; i < vector_tokens.size(); ++i)
			{
				char* s = vector_tokens.at(i);
				string str(s);
				vector_tokens_str.push_back(str);
			}
			
			//put everything into one vector called input
			vector<string> input;
			
			for (unsigned i = 0; i < vector_tokens_str.size() - 1; ++i)
			{
				input.push_back(vector_tokens_str.at(i));
				input.push_back(vector_connectors.at(i));
			}
			
			//add in the last command 
			/*if we put this in the for loop above, it would go out of range, because
			  vector_connectors is smalled than vector_tokens_str by one*/
			int size = vector_tokens_str.size();
			input.push_back(vector_tokens_str.at(size - 1));
			
			//clearing everyyything
			vector_tokens_str.clear();
			vector_connectors.clear();
			vector_connectors_separated.clear();
			// userInput = "";
			//delete[] userInput;
			// userInput_no_comments("");
			
			//run execute on commands
			parse(input);
		}
	}
	
	return 0;
}