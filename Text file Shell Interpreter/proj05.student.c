// Name: Funakoshi SIlva
// Course: CSE 325


#include <pthread.h>
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
void externalCommands (string argument, char * value);
void * systeam_interpreter(void * pointer);

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

    pthread_exit(NULL);


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
                
                }
                else
                {
                    getline( content, tokenized, ' ' );

                    tokens.push_back(tokenized);
    
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
    
    string tilda;
    string userInput;
    string dir;
    string pathUser;
    string pathDir;
    int dirCheck;



    if ( argument == "exit")
    {
        cout<< " exit : " << " Interpreter terminated " << endl;
        flag = true;

    }


    if (flag==false)  
    {       
            /// prepear argument to be handled by cd
            istringstream ss(argument); 
            vector<string> save;
            string separate;
            while (ss)
            {
                
                ss >> separate;
                save.push_back(separate);
              
            }
           
           if ( separate == "date")
           {  
                
                time_t systemTime = time(0);
                char* time = ctime(&systemTime);

                cout<< " date : " << " " << time;
               
           }

            else if ( separate == "env")
            {
               
               for (char **env = environ; *env; env++){

					char* systemEnv = *env;

					cout<< " env : "<< " " << systemEnv;
                    cout<< endl;   
				}
    
        
            }

           else if ( separate == "path")
            {
               
                const char* env_p = std::getenv("PATH");
                    
                cout << " path : " << env_p;
                cout<< endl;   
        
            }

           else if ( separate == "cwd")
            {
               
               	char buffer[MAX_LINE_LENGTH];
				getcwd(buffer, MAX_LINE_LENGTH);
				cout<< " cdw : " <<" "<< buffer;
                cout<< endl;   
        
            }
            /// allocate interpretation of  cd
            else if ( save[0] == "cd" )
            {       

                    char s[100]; 

                    if (save.size() == 2) 
                    {
                        
                        cout<< " " << argument <<" : ";
                        /// cout<< " directory changed from "<< getcwd(s,100) ;
                        chdir(getenv("HOME"));
                        string home = "/user/";
                        home += userName;
                        setenv("PWD", home.c_str(), 1);

                        cout<< getcwd(s,100)<<endl;
                        
                    }
                    // save contais cd and one more command
                    if (save.size() > 2)
                    {
                        tilda = save[1].substr(0,1); ///> tilda character
                        userInput = save[1].substr(1);    ///> possible username
                        dir = save[1].substr(0);

                        //cout<< "-->"<< userInput << endl;

                        pathUser = "/user/";
                        pathDir = "/user/" + dir;
                        dirCheck = chdir(pathDir.c_str());
                    }
                    

                  
                    // save contains cd and one more command the third value on the vector correspond to white space
                    if (save.size() == 3)
                    {
                        if (tilda == "~")   /// user name check
                        {
                            if (userName == userInput)
                    
                            {    
                                pathUser += userInput;   
                                chdir(pathUser.c_str());
                                setenv("PWD", pathUser.c_str(), 1);
                                cout<< " " << argument << " : ";
                                cout << getcwd(s,100) << endl;    
                            }
                            else if (userInput == "")
                            {
                                cout<< " " << argument <<" : ";
                                /// cout<< " directory changed from "<< getcwd(s,100) ;
                                chdir(getenv("HOME"));
                                string home = "/user/";
                                home += userName;
                                setenv("PWD", home.c_str(), 1);
                                cout<< getcwd(s,100)<<endl;
                            }

                            else 
                            {   
                                cout<<" " << argument<<" : " << " Username is invalid. Failed to move to home directory" << endl;
                            }
                        }

                        else if (  dirCheck == 0 ) /// directory name check
                        {   
                            setenv("PWD", pathDir.c_str(), 1);
                            cout<< " " << argument << " : ";
                            cout << getcwd(s,100) << endl;
                        }

                        
                        else
                        {
                            cout<<" " << argument << " : " << " Directory does not exist" << endl;
                        }
                    }

                    if (save.size() > 3)
                    {

                         cout<< " " << argument << " : Error! to many arguments after cd ";
                         cout<<endl;

                    }
                
                
            }
            /// allocate interpretation of set 
            else if (save[0] == "set")
            { 

                 if (save.size() < 3)
                 {
                     cout<< " " << argument << " : Missing arguments. Try 'set Var Value' to set to a value or  'set var' to remove variable" << endl;
                 }

                 if (save.size() == 3) // theres a white space stored at the end of vector save therefore size is 3 and not 2
                {
                    string var = save[1];
                    int check = unsetenv(var.c_str());  

                    if (check == 0)
                    {
                         cout<< " " << argument << " : Success! Environment variable is now removed" << endl;
                    }
                    else
                    {
                        cout<< " " << argument << " : Error!  Failed to remove environment variable" << endl;
                    }

                }
               
                if (save.size() == 4)
                {
                    string var = save[1];
                    string value = save[2]; 
                    int check = setenv(var.c_str(), value.c_str(), 1);

                    if (check == 0)
                    {
                        cout<< " " << argument << " : Environment variable is now set to its corresponding value " << endl;


                    }
                    else
                    {
                        cout<< " " << argument; 
                        cout<< "Error! Failed to set environment variable to its value"<< endl;
                    }
                    
                }
               

            }


        
            else if ( argument != "")
            {
                    
                 //externalCommands (argument, value);
                    cout<< " " << argument  << " : check bellow" <<endl;

                    pthread_t side_thread;
                    char *value = new char[argument.length() + 1];
                    strcpy(value, argument.c_str());

                    int check = pthread_create(&side_thread, NULL, systeam_interpreter, (void*)value);

                    if (check != 0)
                    {
                        cout<< "A problem happend while creating a thread" << endl;
                    }
                    

            }

            else
            {
                    if (argument != "")
                    {
                            cout<< " Not accepted command -----> " << argument;
                            cout<<endl;
                    }

                    if( argument == "")
                    {
                         cout<<endl;
                    }
                    
                   
            }
                
               
        
            
    }

           
       cout<< endl;      
}

// void externalCommands (string argument, char * value)
// {
//        pthread_t side_thread;
//         strcpy(value,argument.c_str());
//         pthread_create(&side_thread, NULL, systeam_interpreter, (void*) value);
//         //pthread_join( side_thread, NULL);

// }


void * systeam_interpreter(void * pointer)
{

    
    char *argument;

    argument = (char *) pointer;

   // cout << argument << endl;

     system(argument);

     pthread_exit(NULL);
}
