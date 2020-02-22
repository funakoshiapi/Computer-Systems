// Name: Funakoshi SIlva
//Project #6


#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <semaphore.h>
#include <iterator>
#include <iomanip>
#include <vector>
#include <exception>
#include <cstring>

//     2. When the program begins execution, it will read zero or more lines from the input file named "accounts.old" to
// initialize the set of customer accounts. Each line of that file will contain an account number (integer number) and
// account balance (real number). When the program halts execution, it will write the updated set of accounts to the
// output file named "accounts.new". 


using namespace std;

int readArguments(const int& argc, char* argv[]);
bool integerCheck (string value);
void pFlagCheck(int i , char * argv[]);
void bFlagCheck(int i , char * argv[]);


int BUFFER = 5 ;  ///> can't exceed 20
int PRODUCER_THREAD_COUNT = 1; ///> can't exceed 10


int main(int argc, char* argv[])
{
    readArguments(argc, argv);

    //cout << " number of threads "<< PRODUCER_THREAD_COUNT << endl;





}


int readArguments(const int& argc, char* argv[])
{

     if (argc >= 6)  /// if more than 4 arguments. Since I check argc te computer understands the total arguments is  plus 1 the total ( 5+1  = 6)
    {
                    cout<< endl;
                    cout << " Error: too many arguments "<< endl;
                    cout<< endl;
                    return 0;
    }


    if (argc ==1)  /// check if arguments are missing
	{
		cout << endl << "Missing argument" << endl << endl;
        return 0;
		
	}

  
    for (int i = 1; i < argc ; i++)
    {
         if (argv[1][0] != '-')
         {  
             cout<< endl;
             cout << "Missing Flag indicator: Flag one is missing '-' symbol " << endl;
             cout<< endl;
             return 0;
         }
         if (i == 1) /// allows to only visit each main if statment at a time, and react to each argument value one at a time
         {
             pFlagCheck(i, argv); /// check if the -p flag is formated correctly
         }

         if (i == 2) /// Process second argument. The integer amout for the number of producer threads
         {

                          
                    if (argc >= 3) // argv[2] -> interger number of producer threads
                    {
                    
                        if ( integerCheck(argv[i]) ) /// check if string 2 is a interger number
                        {
                            int userInput = stoi(argv[i]);
                            if(userInput > 10 || userInput < 1 )
                            {
                                cout << endl;
                                cout<<" Error: Producer thread cannot be greater then 10 nor less then 1. (1-10)" << endl;
                                
                            }
                            else
                            {
                                /// store value of procucer thread
                                PRODUCER_THREAD_COUNT = userInput;
                            } 
                        }
                        else
                        {   cout << endl;
                            cout << "Error: -p flag needs to be followed by interger number between 1 and 10"<< endl;
                            cout << endl;
                        }
                        
                        
                    }
         }

        if (i == 3) /// Process third argument. Buffer flag
        {
               bFlagCheck(i , argv); /// check if the -b flag is formated correctly
        }

         
        if (i == 4) /// Process fourth argument. Buffer value
        {
                if ( integerCheck(argv[i]) ) /// check if string 4 is a interger number
                {
                    int userInput = stoi(argv[i]);
                    if(userInput > 20 || userInput < 5 )
                    {
                        cout << endl;
                        cout<<" Error: Buffer cannot be greater then 20 nor less then 5. (5-20)" << endl;
                        
                    }
                    else
                    {
                        /// store value of procucer thread
                        BUFFER = userInput;
                    } 
                }
                else
                {   cout << endl;
                    cout << "Error: -b flag needs to be followed by interger number between 5 and 20"<< endl;
                    cout << endl;
                }

        }


    }

}

bool integerCheck (string value)
{
    for( int i = 0; i < value.length(); i++)
    {
        if (isdigit(value[i]) == false )
        {
            return false;
        }
    }

    return true;
}


void pFlagCheck(int i , char * argv[])
{

                         /// strings are characters so  argv[1][0] means the first character in the second string. ///
                if (argv[i][0] == '-') 
                {
                    try
                    {
                        if (argv[i][1] != 'p')
                        {
                            /// later update to display the actual user input
                            string message = " Error, unsupported flag. Use '-p' to set the number of producer threads ";
                            throw message;
                        }
                    
                        if (strlen(argv[i]) > 2) /// Reminder : i makes reference to the what string is being processed.
                        {   
                            cout<< endl;
                            cout<< "Invalid Flag: " << argv[1]<< " is not supported" << endl;
                            cout << "Use '-p' to set the number of producer threads "<< endl;
                            cout<< endl;
                        }
            
                    }
                    catch( string message) /// first flag was not -p
                    {   
                        cout<< endl;
                        cout<< message << endl;
                        cout<< endl;
                    }
                
                }



}


void bFlagCheck(int i , char * argv[])
{

                /// strings are characters so  argv[1][0] means the first character in the second string. ///
                if (argv[i][0] == '-') 
                {
                    try
                    {
                        if (argv[i][1] != 'b')
                        {
                            /// later update to display the actual user input
                            string message = " Error, unsupported flag. Use '-b' to set the number of producer threads ";
                            throw message;
                        }
                    
                        if (strlen(argv[i]) > 2) /// Reminder : i makes reference to the what string is being processed.
                        {   
                            cout<< endl;
                            cout<< "Invalid Flag: " << argv[i]<< " is not supported" << endl;
                            cout << "Use '-b' to set the buffer size "<< endl;
                            cout<< endl;
                        }
            
                    }
                    catch( string message) /// first flag was not -b
                    {   
                        cout<< endl;
                        cout<< message << endl;
                        cout<< endl;
                    }
                
                }



}












                //  /// continue with code check of size of producer thread


               



                // if (argc >= 4) // argv[3] -> buffer for the flag
                // {
                //     cout << "it exist"<< endl;
                //      cout << argv[3]<< endl;
                    
                    
                // }


                // if (argc >= 5) // argv[4] -> integer number for the size of the buffer
                // {
                //     cout << "it exist"<< endl;
                //      cout << argv[4]<< endl;
                    
                // }


























