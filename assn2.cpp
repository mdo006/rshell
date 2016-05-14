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

using namespace std;

void execute (string &pass, int &valid)
{
	char* test[80];
	//valid = 1;
	vector<string> command;
	string temp="";
	int j = 0;
	int i = 0;
	while(i < pass.size())
	{
		for(j = i ; j < pass.size(); ++j)
		{
			if(pass.at(j) ==' ')
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
		command.push_back(temp);
		temp.clear();
		//so we can start basing on where we left off in pass string
		i = j; 
	}
	int k = 0;
	for(; k < command.size() ;++k)
    {
    	string temp_str = command.at(k);
        test[k] = (char*)temp_str.c_str();
    }
    test[k] = '\0';
    
	pid_t pid = fork();
	// after fork(), if the pid comes out as -1 , then our command is valid.
    if(pid > 0)
    {
        if(wait(0) == -1)
        {
        	perror("wait");
            valid = 0;
        }
    }
    if(pid == 0)
    {
        if(execvp(test[0],test) == -1)
        {
        	perror("exec");
        	valid = 0;
        }
    }
	
	command.clear();
}

void parse (vector<string> &input, int &valid)
{
	vector<string> reverse_input;
	
	//reverse the vector of inputs 
	//so we can use pop_back (we could make a quene but we did this instead)
	for (int i = input.size() - 1; i >= 0; --i)
	{
		reverse_input.push_back(input.at(i));
	}
	
	//only one command
	/*if size is 2, that means there is a command and one connector but no 
	other command after the connector*/
	if (reverse_input.size() == 1 || reverse_input.size() == 2) 
	{
		execute(reverse_input.at(0), valid);
		exit(0);
	}
	
	//parse this vector and execute accordingly
	for (int i = reverse_input.size() - 1; i >= 0; i = i - 4)
	{
		//check if exit command is first
		if (reverse_input.at(0) == "exit")
		{
			exit(0); //exit program
		}
	
		//execute first command
		execute(reverse_input.at(i), valid);
			
		if (reverse_input.at(i - 1) == ";")
		{
			if (valid == 1)
			{
				execute(reverse_input.at(i - 2), valid);
				reverse_input.pop_back();
				reverse_input.pop_back();
				reverse_input.pop_back();
			}
					
		}
		else if (reverse_input.at(i - 1) == "&&")
		{
			if (valid == 1) //1st command executed properly
			{
				//execute 2nd command
				// cout << "failed" << endl;
				execute(reverse_input.at(i - 2), valid);
			}
				
			reverse_input.pop_back();
			reverse_input.pop_back();
			reverse_input.pop_back();
		}
		else if (reverse_input.at(i - 1) == "||")
		{
			if (valid == 0) //1st command did not execute 
			{
				execute(reverse_input.at(i - 2), valid);
			}
				
			reverse_input.pop_back();
			reverse_input.pop_back();
			reverse_input.pop_back();
		}
	}
}

int main()
{
	//command line inputted by user
	char userInput[100];
	
	//print a command prompt (e.g. $)
	cout << "$ ";
	//read in command as one line
	cin.getline(userInput, 100);
	
	char userInput_no_comments[100];
	
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
	for (int i = 0; userInput_no_comments[i] != '\0'; ++i)
	{
		if (userInput_no_comments[i] == ';'|| userInput_no_comments[i] == '&' 
			|| userInput_no_comments[i] == '|')
		{
			vector_connectors_separated.push_back(userInput[i]);
		}
	}
	
	//NOW COMBIN & and & into && and | and | into ||
	vector<string> vector_connectors;
	
	for (int i = 0; i < vector_connectors_separated.size(); ++i)
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

	for (int i = 0; i < vector_tokens.size(); ++i)
	{
		char* s = vector_tokens.at(i);
		string str(s);
		vector_tokens_str.push_back(str);
	}
	
	//put everything into one vector called input
	vector<string> input;
	
	for (int i = 0; i < vector_tokens_str.size() - 1; ++i)
	{
		input.push_back(vector_tokens_str.at(i));
		input.push_back(vector_connectors.at(i));
	}
	
	//add in the last command 
	/*if we put this in the for loop above, it would go out of range, because
	  vector_connectors is smalled than vector_tokens_str by one*/
	int size = vector_tokens_str.size();
	input.push_back(vector_tokens_str.at(size - 1));
	
	//run execute on commands
	int valid = 1;
	parse(input, valid);
	
	return 0;
}