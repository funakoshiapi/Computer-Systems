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


int BUFFER = 5 ;  ///> can't exceed 20
int PRODUCER = 1; ///> can't exceed 10


int main(int argc, char* argv[])
{
    readArguments(argc, argv);





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

    int lock = 1;

    for (int i = 1; i < argc ; i++)
    {
         if (argv[1][0] != '-')
         {  
             cout<< endl;
             cout << "Missing Flag indicator: Flag one is missing '-' symbol " << endl;
             cout<< endl;
             return 0;
         }
         if (lock == 1) /// allows to only visit each main if statment at a time, and react to each argument value one at a time
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
                    
                        if (strlen(argv[1]) > 2)
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

         if (lock == 2) /// Process second argument. The integer amout for the number of producer threads
         {

                          
                    if (argc >= 3) // argv[2] -> interger number of producer threads
                    {
                    
                        if ( integerCheck(argv[2]) ) /// check if string 2 is a interger number
                        {
                            int userInput = stoi(argv[2]);
                            if(userInput > 10 || userInput < 1 )
                            {
                                cout << endl;
                                cout<<" Error: Producer thread cannot be greater then 10 nor less then 1. (1-10)" << endl;
                                
                            } 
                        }
                        else
                        {   cout << endl;
                            cout << "Error: -p flag needs to be followed by interger number between 1 and 10"<< endl;
                            cout << endl;
                        }
                        
                        
                    }


         }

        lock += 1;
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


























