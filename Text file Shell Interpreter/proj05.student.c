// Name: Funakoshi SIlva
// Course: CSE 325



#include <stdio.h>
#include <string.h>
#include <iterator>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

using namespace std;
const char* userName = cuserid(NULL);
const int MAX_LINE_LENGTH = 128;
 int count; // will represent the count of number of lines
 bool flag;

// Function declaration
vector<string> fileReader(string);
void interpreter(vector<string>,bool, bool);
void indicator();
void aceptableCommands(string, bool);

int main(int argc, char *argv[], char * envp[])
{
    string readLine;
    vector<string> arguments;
    bool behaviour = true;
    bool exit = false;
    bool terminate = false;
    vector<string> tokens;
    int countFiles=1;
    
  


    cout<< endl;

    while (!exit)
    {

    
        // Read Command line arguments and store  them on a vector
        for(int i=1; i<argc; i++)
        {
            arguments.push_back(argv[i]);
        }

        // Decides if silence mode is off or on
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

            // opens the file and interprets its content

            if (condition != "-v" && condition != "-s")
            {    count= 1; // first line of file
                 flag = false; // don't output anything when exit argument is used
                 tokens = fileReader(condition);
                 interpreter(tokens, behaviour, exit);
                 
            }
           

            // terminates the program once all the files are read
             if (countFiles == arguments.size())
             {
                exit = true;
                break;
             }
             countFiles++;

        }  
      
        
       
        
    
    }


cout<< endl;


return 0;
}



/** Reads open, reads as file and closes the file.
 *  @param fileName the name of the file to be read
 *  @return tokens return a vecot of tokens
 */
vector<string> fileReader(string fileName)
{
    string line;
    ifstream document; 
    document.open(fileName);
    vector<string> tokens;
    string hold;

    cout << endl;
    cout << endl;
    cout << "__________ " <<"Displaying " << fileName  << " __________"  << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    if (document.is_open())
    {

    
        while( getline(document, line) )
        {       
            //cout << line << endl;
            if ( line.length() > MAX_LINE_LENGTH )
            {
                cout << endl;
                indicator();
                cout<<" :( ---->  "<< "Maximun length for line " <<count<<" was exceeded. Maximum lenght for line is  128 characters."<<endl;
                cout << endl;
                
            }

            // do stok and append the first string in index zero
            istringstream content(line);
        
            while(content)
            {   
                string tokenized;
                
                getline( content, tokenized);
                // when cd store all of the arguments in the line
                if (tokenized == "cd")
                {
                    tokens.push_back(tokenized);
                    break;
                   
                }
                else
                {
                    getline( content, tokenized, ' ' );
                    tokens.push_back(tokenized);
                    break;
                }

                
               
                 
            }

        }

    }

    else
    {
                cout << endl;
                cout<<"    :( ---->" << fileName << " does not exits in the current directory."<<endl;
                cout << endl;

    }
   
    document.close();
    return tokens;
    
    
}

/** Decides when to execute the display of number lines 
 * and call helper functions to interpret a arguments
 *  @param tokens first string found in the txt file 
 *  @param behaviour boolean value that control if silence mode is on or not
 *  @param exit boolean value that decides the termination of the program 
 *  @return None
 */
void interpreter(vector<string> tokens, bool behaviour,bool exit)
{   
    int index = 0;
    for (auto argument : tokens)
    {  
        //cout << argument<< endl;
        if (flag==false)
        {

        
            if (behaviour)
            {   
                indicator();



                aceptableCommands(argument, exit);
            }

            else
            {
                aceptableCommands(argument, exit); 
            }
        
        }
        index += 1;
        
    }



   
}

/** prints the number of line of the txt file
 *  
 *  
 *  @return None
 */
void indicator( )
{

    cout << "<"<< count <<">";
    count = count + 1;


}


/** Decision making for aceptable commands.
 *  @param argument reference to the commands in the text file
 *  @param exit boolean value that decides the termination of the program
 *  @return None
 */
void aceptableCommands(string argument, bool exit)
{
    if ( argument == "exit")
    {
        cout<< " exit : " << " Interpreter terminated " << endl;
        flag = true;

    }


    if (flag==false)  
    {
            istringstream ss(argument); 
            vector<string> save;
            while (ss)
            {
                string separate;
                ss >> separate;
              
                save.push_back(separate);
                
             
            }

            
            
            if ( save[0] == "cd" )
            {       

                    int pathCheck ; /// to test if path exist
  
                    char s[100]; 

                    if (save.size() == 2 || save[1]== "~") 
                    {
                        
                        cout<< " " << argument <<" : ";
                        /// cout<< " directory changed from "<< getcwd(s,100) ;
                        chdir(getenv("HOME"));
                        cout<< getcwd(s,100)<<endl;
                        
                    }

                    /// starter path to be used
                    string tilda = save[1].substr(0,1); ///> tilda character
                    string userInput = save[1].substr(1);    ///> possible username
                    string dir = save[1].substr(0);
                    string pathUser = "/home/";
                    string pathDir = "/home/" + dir;
                    int dirCheck = chdir(pathDir.c_str());
                    //cout << dir << endl;
                    //  cout << tilda << endl;
                    
                    if (tilda == "~")   /// user name check
                    {
                        if (userName == userInput)
                    
                        {    
                            pathUser += userInput;   
                            chdir(pathUser.c_str());
                            cout<< " " << argument << " : ";
                            cout << getcwd(s,100) << endl;    
                        }

                        else 
                        {
                            cout<<" " << argument<<" : " << " Username is invalid. Failed to move to home directory" << endl;
                        }
                    }

                    else if (  dirCheck == 0 ) /// directory name check
                    {
                         cout<< " " << argument << " : ";
                         cout << getcwd(s,100) << endl;
                    }

                    else
                    {
                        cout<<" " << argument << " : " << " Directory does not exist" << endl;
                    }

                

                    


                
            }
         
           
           if ( argument == "date")
           {  
                
                time_t systemTime = time(0);
                char* time = ctime(&systemTime);

                cout<< " date : " << " " << time;
               
           }

            else if ( argument == "env")
            {
               
               for (char **env = environ; *env; env++){

					char* systemEnv = *env;

					cout<< " env : "<< " " << systemEnv;
                    cout<< endl;   
				}
    
        
            }

           else if ( argument == "path")
            {
               
                const char* env_p = std::getenv("PATH");
                    
                cout << " path : " << env_p;
                cout<< endl;   
        
            }

           else if ( argument == "cwd")
            {
               
               	char buffer[MAX_LINE_LENGTH];
				getcwd(buffer, MAX_LINE_LENGTH);
				cout<< " cdw : " <<" "<< buffer;
                cout<< endl;   
        
            }


            else
            {
                cout<<endl;
            }
            

            

    }

           
       cout<< endl;      
}
