// Name: Funakoshi SIlva
// Course: CSE 325
// APID: A51837997


#include <stdio.h>
#include <string.h>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <fstream>
#include <cstdlib>

using namespace std;

const int MAX_LINE_LENGTH = 128;

// Function declaration
vector<string> fileReader(string);
void interpreter(vector<string>,bool, bool);
void indicator(int);
void aceptableCommands(string, bool);

int main(int argc, char *argv[], char * envp[])
{
    string readLine;
    vector<string> arguments;
    bool behaviour = true;
    bool exit = false;
    bool terminate = false;
    vector<string> commands = {"exit","date", "env", "path","cwd"};
    vector<string> tokens;
    int countFiles=1;
  

     cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CSE 325 MICHIGAN STATE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;
     cout<< endl;
     
    while (!exit)
    {

    
        // Read Command line arguments and store  the no a vector
        for(int i=1; i<argc; i++)
        {
            arguments.push_back(argv[i]);
        }

        for (auto condition : arguments)
        {    
        
            if ( condition == "-s")
            {   
                behaviour = false;
        
            }

            if ( condition == "-v")
            {   
                behaviour = true;
      
            }

            if (condition != "-v" && condition != "-s")
            {
                 tokens = fileReader(condition);
                 interpreter(tokens, behaviour, exit);
            }
           

       
             if (countFiles == arguments.size())
             {
                exit = true;
                break;
             }
             countFiles++;

        }  
      
        
       
        
    
    }


cout<< endl;
cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CSE 325 MICHIGAN STATE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;

return 0;
}




vector<string> fileReader(string fileName)
{
    string line;
    ifstream document; 
    document.open(fileName);
    vector<string> tokens;
    string hold;

    if (document.is_open())
    {

    
        while( getline(document, line) )
        {       

            if ( line.length() > MAX_LINE_LENGTH )
            {
                cout << endl;
                cout<< "Maximun length of file was exceeded. Maximum number of lines is 128."<<endl;
                cout << endl;
                break;
            }

            // do stok and append the first string in index zero
            istringstream tokenized(line);

            while(tokenized>>hold)
            {
                tokens.push_back(hold);
                break;
            }

        }

    }

    else
    {
                cout << endl;
                cout<<"     ---->" << fileName << " does not exits in the current directory."<<endl;
                cout << endl;

    }
   
    document.close();
    return tokens;
    
    
}


void interpreter(vector<string> tokens, bool behaviour,bool exit)
{   
    int count = 1;

    for (auto argument : tokens)
    {  
        if (behaviour)
        {   
            indicator(count);

            aceptableCommands(argument, exit);
        }

        else
         {
            aceptableCommands(argument, exit); 
         }
        
         count++;
    }



   
}


void indicator(int count)
{
    cout << "<"<< count <<">";
}



void aceptableCommands(string argument, bool exit)
{
    if ( argument == "exit")
           {
               exit = true;
        
           }

           if ( argument == "date")
           {  
                
                time_t systemTime = time(0);
                char* time = ctime(&systemTime);

                cout << " " << time;
               
           }

            if ( argument == "env")
            {
               
               for (char **env = environ; *env; env++){

					char* systemEnv = *env;

					cout<< " " << systemEnv;
                    cout<< endl;   
				}
    
        
            }

            if ( argument == "path")
            {
               
                const char* env_p = std::getenv("PATH");
                    
                cout << " PATH is: " << env_p;
                cout<< endl;   
        
            }

            if ( argument == "cwd")
            {
               
               	char buffer[MAX_LINE_LENGTH];
				getcwd(buffer, MAX_LINE_LENGTH);
				cout <<" "<< buffer;
                cout<< endl;   
        
            }

           
       cout<< endl;      
}