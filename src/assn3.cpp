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
#include <sys/stat.h>

using namespace std;

void test_dir(string &);
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

void parse (vector<string> &input, int& flag)
{
	//check if the 1st command is exit
	//if it is, exit the program
	if (input.at(0) == "exit")
	{
		input.clear();
		exit(0);
	}
	
	bool  valid;
	
	//execute 1st command;
	unsigned i = 0;
	
	if (input.at(i) != "&&" || input.at(i) != "||" || input.at(i) != ";")
	{
		valid = execute(input.at(0));
		
		if (valid == false)
		{
			flag = 1;
		}
		else if (valid == true)
		{
			flag = 0;
		}
		// else if(input.at(0).at(0) == '[' || input.at(0).substr(0,4) =="test")
		// {
		// 	cout << "PLZ " << endl;
		test_dir(input.at(0));
		// }
		
		++i;
		// test_dir(input.at(i));
	}
	
	//parse this vector and execute accordingly
	for (; i < input.size(); i = i + 1)
	{
		if (input.at(i) == ";")
		{
			//check for exit command
			if (input.at(i + 1) == "exit")
			{	
				execute(input.at(i + 1));
			}
			
			//always execute a command that follows a semicolon
			execute(input.at(i + 1));
			
		}
		else if (input.at(i) == "&&")
		{
			if (valid == true) //1st command executed properly
			{
				//check for exit command
				if (input.at(i + 1) == "exit")
				{	
					execute(input.at(i + 1));
				}
				
				//execute 2nd command
				execute(input.at(i + 1));
				flag = 0;
			}
			else if (valid == false)
			{
				//valid is false
				flag = 1;
			}
		}
		else if (input.at(i) == "||")
		{
			if (valid == false) //1st command did not execute 
			{
				//check for exit command
				if (input.at(i + 1) == "exit")
				{	
					execute(input.at(i + 1));
				}
				
				execute(input.at(i + 1));
				
				flag = 1;
			}
			else if (valid == true)
			{
				flag = 0;
			}
		}
		else if(input.at(i).at(0) == '[' || input.at(i).substr(0,4) =="test")
		{
			test_dir(input.at(i));
		}
	}
}

//token and combine the input the way we did in assn 2
//connector_flag: 1 = "&&", 2 = "||", 3 = ";"
void combine_input (string combined_input, int& flag, int& connector_flag)
{
	//need to convert string to char array to user strtok
	char arr[100];
		
	string temp = combined_input;
	strcpy(arr, temp.c_str());
		
	//get connectors from userInput and store it into a vector
	//but in this vector && and || are stored as & & and | |
	vector<char> vector_connectors_separated;
		
	//FIX THIS LATER IF THERE IS TIME 
	//DOES NOT ACCOUNT FOR JUST '&', JUST '|', OR MORE THAN TWO '&'s OR '|'s
	//ALSO DOES NOT ACCOUNT FOR MORE THAN ONE ';' IN A ROW
	for (unsigned i = 0; arr[i] != '\0'; ++i)
	{
		if (arr[i] == ';'|| arr[i] == '&' || arr[i] == '|')
		{
			vector_connectors_separated.push_back(arr[i]);
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
	tokens = strtok(arr, delimiters);
		
	//stores all the commands and its arguments as separate "tokens"
	vector<char*> vector_tokens;
		
	while (tokens != NULL)
	{
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

	if (temp.at(0) == '&') 
	{
		if (vector_tokens_str.size() == 1 && vector_connectors.size() == 1)
		{
			input.push_back(vector_connectors.at(0));
			input.push_back(vector_tokens_str.at(0));
		}
		else
		{
			for (unsigned i = 0; i < vector_tokens_str.size() - 1; ++i)
			{
				input.push_back(vector_connectors.at(i));
				input.push_back(vector_tokens_str.at(i));
			}
		
		
			//add in the last command 
			/*if we put this in the for loop above, it would go out of range, because
			  vector_connectors is smalled than vector_tokens_str by one*/
			int size = vector_tokens_str.size();
			
			//if its a whitespace, don't add it to the vector
			if (vector_tokens_str.at(size - 1) != "")
			{
				input.push_back(vector_tokens_str.at(size - 1));
			}
		}
	}
	else if (temp.at(0) == '|')
	{
		if (vector_tokens_str.size() == 1 && vector_connectors.size() == 1)
		{
			input.push_back(vector_connectors.at(0));
			input.push_back(vector_tokens_str.at(0));
		}
		else
		{
			for (unsigned i = 0; i < vector_tokens_str.size() - 1; ++i)
			{
				input.push_back(vector_connectors.at(i));
				input.push_back(vector_tokens_str.at(i));
			}
		
			//add in the last command 
			/*if we put this in the for loop above, it would go out of range, because
			  vector_connectors is smalled than vector_tokens_str by one*/
			int size = vector_tokens_str.size();
			
			//if its a whitespace, don't add it to the vector
			if (vector_tokens_str.at(size - 1) != "")
			{
				input.push_back(vector_tokens_str.at(size - 1));
			}
		}
	}
	else if (temp.at(0) == ';')
	{
		if (vector_tokens_str.size() == 1 && vector_connectors.size() == 1)
		{
			input.push_back(vector_connectors.at(0));
			input.push_back(vector_tokens_str.at(0));
		}
		else
		{
			for (unsigned i = 0; i < vector_tokens_str.size() - 1; ++i)
			{
				input.push_back(vector_connectors.at(i));
				input.push_back(vector_tokens_str.at(i));
			}
			
			//add in the last command 
			/*if we put this in the for loop above, it would go out of range, because
			  vector_connectors is smalled than vector_tokens_str by one*/
			int size = vector_tokens_str.size();
			
			//if its a whitespace, don't add it to the vector
			if (vector_tokens_str.at(size - 1) != "")
			{
				input.push_back(vector_tokens_str.at(size - 1));
			}
		}
	}
	else
	{
		for (unsigned i = 0; i < vector_tokens_str.size() - 1; ++i)
		{
			input.push_back(vector_tokens_str.at(i));
			input.push_back(vector_connectors.at(i));
		}
		
		//add in the last command 
		/*if we put this in the for loop above, it would go out of range, because
		  vector_connectors is smalled than vector_tokens_str by one*/
		int size = vector_tokens_str.size();
		
		//if its a whitespace, don't add it to the vector
		if (vector_tokens_str.at(size - 1) != "")
		{
			input.push_back(vector_tokens_str.at(size - 1));
		}
	}
	

	//clearing everyyything
	vector_tokens_str.clear();
	vector_connectors.clear();
	vector_connectors_separated.clear();

	//output vector of input for testing
	// cout << "Entire Input: " << endl;
	// for (int i = 0; i < input.size(); ++i)
	// {
	// 	cout << input.at(i) << endl;
	// }
	
	bool valid = true;

	//ex: echo hello && or
	//ex: || echo hello
	if (input.size() == 2)
	{
		if (input.at(0) == "&&") 
		{
			if (flag == 0)
			{
				execute(input.at(1));
			}
		}
		else if (input.at(0) == "||")
		{
			if (flag == 1)
			{
				execute(input.at(1));
			}
		}
		else if (input.at(0) == ";")
		{
			execute(input.at(1));
		}
		
		else
		{
			valid = execute(input.at(0));
			
			if (valid == false)
			{
				flag = 1;
			}
			else if (valid == true)
			{
				flag = 0;
			}
			
			if (input.at(1) == "&&")
			{
				connector_flag = 1;
			}
			else if (input.at(1) == "||")
			{
				connector_flag = 2;
			}
			else if (input.at(1) == ";")
			{
				connector_flag = 3;
			}
		}
		
		return;
	}
	// for(unsigned h= 0; h < input.size() ; ++h)
	// {
	// 	// cout <<  << endl;
	// 	// string check = 
	// 	if(input.at(h).at(0) == '[' || input.at(h).substr(0,4) =="test")
	// 	{
	// 		test_dir(input.at(h));
	// 	}
	// }
	if (input.at(0) == "&&") 
	{
		if (flag == 0)
		{
			input.erase(input.begin());
			parse(input, flag);
		}
		return;
	}
	else if (input.at(0) == "||")
	{
		if (flag == 1)
		{
			input.erase(input.begin());
			parse(input, flag);
		}
		return;
	}
	else if (input.at(0) == ";")
	{
		input.erase(input.begin());
		parse(input, flag);
		return;
	}
	
	//run execute on commands
	
	parse(input, flag);
}

void token_input (vector<string> &token)
{
	int flag = 0; //executed
	int connector_flag = 0;
	unsigned i = 0;

	//vector of size 1 means input looks something like this: (echo A && echo B)
	//we can treat this input the same way we did in assn 2
	if (token.size() == 1)
	{
		combine_input(token.at(0), flag, connector_flag);
	
	}
	else //size of token is greater than one
	{
		combine_input(token.at(0), flag, connector_flag);
		
		if (connector_flag == 1 && flag != 1) //&&
		{
			combine_input(token.at(i + 1), flag, connector_flag);
			i = i + 2;
		}
		else if (connector_flag == 1 && flag == 1) //&&
		{
			//don't execute if the command before it did not
			i = i + 2;
		}
		else if (connector_flag == 2 && flag == 1) //||
		{
			combine_input(token.at(i + 1), flag, connector_flag);
			i = i + 2;
		}
		else if (connector_flag == 2 && flag != 1) //||
		{
			//don't execute if the command before it executed
			i = i + 2;
		}
		else if (connector_flag == 3) //;
		{
			//execute regardless	
			combine_input(token.at(i + 1), flag, connector_flag);
			i = i + 2;
		}
		else
		{
			++i;
		}
		
		for (; i < token.size(); i = i + 2)
		{
			if (token.at(i) == "; " || token.at(i) == ";")
			{
				combine_input(token.at(i + 1), flag, connector_flag);
			}
			else if (token.at(i) == "&& " || token.at(i) == "&&")
			{
				//first group of commands executed
				if (flag != 1)
				{
					combine_input(token.at(i + 1), flag, connector_flag);
				}
			}
			else if (token.at(i) == "|| " || token.at(i) == "||")
			{
				//first group of commands did not execute
				if (flag == 1)
				{
					combine_input(token.at(i + 1), flag, connector_flag);
				}
			}
			//the case where token.at(i) is not a connector 
			//ex: token.at(i) is && echo hello
			//need to isoalte the connector
			else
			{
				combine_input(token.at(i), flag, connector_flag);
				++i; 
			}
		}
	}
}

void test_dir(string &pass)
{
	if(pass.at(0) == '[')
	{
		if(pass.size() < 4)
		{
			cout << "(FALSE)" << endl;
			return;
		}
		pass = pass.substr(1,pass.size() - 3);
	}
	else if(pass.substr(0,4) == "test")
	{
		pass = pass.substr(pass.find(" ") + 1);
	}
	else{
		return;
	}
	string flag = pass.substr(0,pass.find(" "));
	// cout << flag << endl;
	struct stat sb;
	if(pass.at(pass.size() - 1) == ' ')
	{
		pass = pass.substr(pass.find(" ") + 1, pass.size() - 4);	
	}
	else {
		pass = pass.substr(pass.find(" ") + 1, pass.size() - 1);
	}
	// cout << pass <<"e"<< endl;
	char* temp = (char*) pass.c_str();
	// -f checks if the file/directory exists and is a regular file
	
	if (flag == "-f")
	{
		stat(temp, &sb);
		// stat(pathname, &sb)
	 	if (S_ISREG(sb.st_mode))
	 	{
    	cout << "(True)" << endl ; 
    	pass = "true";
    	return;
	 }
	}
	// -d checks if the file/directory exists and is a directory
	else if (flag == "-d")
	{
		stat(temp, &sb);
	 	if (S_ISDIR(sb.st_mode))
	 	{
	    	cout << "(True)" << endl ;
	    	pass ="true";
	    	return;
	 	}
	}
	else if(flag != "-e")
	{
		//don't do anything
	}
	else
	{
	 	if (stat(temp, &sb) == 0)
	 	{
	 		cout << "(True)" << endl;
	 		pass = "true";
	    	return;
	 	}
	}
	cout << "(False)" << endl; 
	pass = "false";
	// -e checks if the file/directory exists	
	//also if there is no flag, then always do -e
	return;
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
		
		//checks for if the user just presses ENTER
		if (userInput[0] != '\0')
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
			
			//use strtok to separate input into "tokens"
			//token by parentheses to group them
			char* tokens; //command and its arguments
			char delimiters[] = "()";
			tokens = strtok(userInput_no_comments, delimiters);
			
			//stores all the commands and its arguments as separate "tokens"
			vector<char*> vector_tokens;
			
			while (tokens != NULL)
			{
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
				
				if (str != "")
				{
					vector_tokens_str.push_back(str);
				}
			}
			
			//call function
			token_input(vector_tokens_str);
		}
	}
	
	return 0;
}