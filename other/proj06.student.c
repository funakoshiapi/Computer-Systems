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
#include<pthread.h>

// deal with accout files

using namespace std;

bool readArguments(const int& argc, char* argv[]);
bool integerCheck (string value);
bool pFlagCheck(int i , char * argv[]);
bool bFlagCheck(int i , char * argv[]);
vector<string> fileReader(string fileName);
void *producer_thread(void* str);
void *consumer_thread(void* str);
void outputAccountNew();
void outputAccounLog_S(int thread, string transaction,
int account, double amount_value, double balance);
void outputAccounLog_F( int thread, string transaction,
 int account, double amount_value);

sem_t S;
sem_t N;
sem_t E;

int BUFFER = 5 ;  ///> can't exceed 20
int buffer_in = 0;
int buffer_out = 0;



int PRODUCER_THREAD_COUNT = 1; ///> can't exceed 10
const string INPUT_F = "accounts.old";
const string OUTPUT_F = "accounts.new";
const string LOG_F = "accounts.log";
const string FILE_HEAD = "trans";
vector<string> accountListValues;

/// Thread managment

int in_use = 0;
int taken = 0;
const int ARGUMENTS[10] = {0,1,2,3,4,5,6,7,8,9};



struct accountData{
	int account_number;  
	string transaction; /// can be a withdrawl or a Deposit
	double amount_value;
	int thread;  /// coresponding active thread values
};

struct accountData bSt[20];

int main(int argc, char* argv[])
{
    
   bool process; 
   process = readArguments(argc, argv);

    if (process == true)
    {
       accountListValues = fileReader(INPUT_F);

        pthread_t consumer, producer;

        sem_init(&S,0,1);
	    sem_init(&N,0,0);
	    sem_init(&E,0,BUFFER);

        vector<pthread_t> list;

        for (int i=0; i < PRODUCER_THREAD_COUNT;i++)
        {
            pthread_t produce;
            list.push_back(produce);
            pthread_create(&(list[i]),NULL,producer_thread,(void*) &(ARGUMENTS[i]));
	    }

        	
            pthread_create(&consumer,NULL,consumer_thread,NULL);
            for (int i=0; i< list.size();i++)
            {
		        pthread_join(list[i],NULL);
	        }

            pthread_join(consumer,NULL);
            outputAccountNew();

    }

}

void *producer_thread(void* str)

{   
    in_use++;
    int *test;
    test = (int*) str;
    int number_of_threads = *test;
    const string filename = FILE_HEAD + to_string(number_of_threads);

    struct accountData info;
    info.account_number = stoi( accountListValues[0]);
    info.transaction =  accountListValues[1];
    info.amount_value = stoi( accountListValues[2]);
    info.thread = number_of_threads;

    sem_wait(&E);
	sem_wait(&S);
    bSt[buffer_in]= info;
    buffer_in +=1;
    buffer_in = buffer_in % BUFFER;

    taken += 1;
    sem_post(&S);
	sem_post(&N);

    in_use++;
    pthread_exit(NULL);

}


void *consumer_thread(void* str)
{
    ofstream outLogs;
    outLogs.open(LOG_F);
    /// taken - is busy
    /// in_use is number of active threads
    while (taken > 0)
    {
     
        sem_wait(&N);
		sem_wait(&S);

		struct accountData info = bSt[buffer_out];
		buffer_out = (buffer_out+1) % BUFFER;
		taken-= 1;

		sem_post(&S);
		sem_post(&E);

       int condition = info.transaction.compare("deposit");
       int condition2 = info.transaction.compare("withdraw");

       /// when no exceptionn
        if (condition == 0)
        {
            if(info.amount_value >= 0)
            {
                for (int i = 0 ; i < accountListValues.size(); i++)
                {
                    
                    if(stoi(accountListValues[0]) == info.account_number)
                    {
                        
                        int balance = stoi(accountListValues[2]) + info.amount_value;

                        outputAccounLog_S(info.thread, info.transaction, info.account_number, info.amount_value, balance);
                        break;
                    }
                }
            }
             else
             {
                outputAccounLog_F(info.thread, info.transaction, info.account_number, info.amount_value);
                cout<<endl;
                cout<< "Error, negative amout number" << endl;
                break;
            }

        }

        if (condition2 == 0)
        {
            if(info.amount_value >= 0)
            {
                for (int i = 0 ; i < accountListValues.size(); i++)
                {
                    
                    if(stoi(accountListValues[0]) == info.account_number)
                    {
                        
                        if ( stoi(accountListValues[2]) > info.amount_value)
                        {
                            int balance = stoi(accountListValues[2]) - info.amount_value;

                            outputAccounLog_S(info.thread, info.transaction, info.account_number, info.amount_value, balance);
                            break;
                        }
                        else
                            {
                                outputAccounLog_F(info.thread, info.transaction, info.account_number, info.amount_value);
                                cout<<endl;
                                cout<< "Error, negative amout number" << endl;
                                break;
                            }
                    }

                                else
                        {
                            outputAccounLog_F(info.thread, info.transaction, info.account_number, info.amount_value);
                            cout<<endl;
                            cout<< "Error, negative amout number" << endl;
                            break;
                        }
                }
            }
             

        }




    }

    pthread_exit(NULL);

}




bool readArguments(const int& argc, char* argv[])
{

     if (argc >= 6)  /// if more than 4 arguments. Since I check argc te computer understands the total arguments is  plus 1 the total ( 5+1  = 6)
    {
                    cout<< endl;
                    cout << " Error: too many arguments "<< endl;
                    cout<< endl;
                    return false;
    }

    else if (argc == 1 || argc < 5)  /// check if arguments are missing
	{
		
                    cout<< endl;
                    cout << " Error: Missing arguments. Arguments should have a flag and a corresponding value. Example: '-p 3 -b 6' "<< endl;
                    cout<< endl;
                    return false;
		
	}
  
    for (int i = 1; i < argc ; i++)
    {
         if (argv[1][0] != '-')
         {  
             cout<< endl;
             cout << "Missing Flag indicator: Flag one is missing '-' symbol " << endl;
             cout<< endl;
             return false;
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
                                return false;
                                
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
                            return false;
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
                        return false;
                        
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
                    return false;
                }

        }


    }
    return true;
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


bool pFlagCheck(int i , char * argv[])
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
                            return false;
                        }
            
                    }
                    catch( string message) /// first flag was not -p
                    {   
                        cout<< endl;
                        cout<< message << endl;
                        cout<< endl;
                        return false;
                    }
                
                }



}


bool bFlagCheck(int i , char * argv[])
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
                            return false;
                        }
            
                    }
                    catch( string message) /// first flag was not -b
                    {   
                        cout<< endl;
                        cout<< message << endl;
                        cout<< endl;
                        return false;
                    }
                
                }



}

vector<string> fileReader(string fileName)
{
    string line;
    ifstream document; 
    document.open(fileName);
    vector<string> tokens;
    string separate;

    if (document.is_open())
    {
        while( getline(document, line) )
        {       
            // do stok and append the first string in index zero
            istringstream content(line);
        
            while(content)
            {
                 string separate;
                content >> separate;
                tokens.push_back(separate);
    
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


void outputAccountNew()
{
    ofstream outLogs ;
	outLogs.open(OUTPUT_F);
	for (int i=0; i<accountListValues.size(); i++)
    {
		outLogs<<setw(6)<<setfill(' ');

        if(i==0)
        {
            outLogs<<" " <<accountListValues[i];
        }

        if(i==1)
        {
            outLogs<<" " <<accountListValues[i];
        }

        if(i == 2)
        {
            outLogs <<" "<<accountListValues[i]<<endl;
        }
        
       
	}
	outLogs.close();
}

// LOG_F

void outputAccounLog_S( int thread, string transaction, int account, double amount_value, double balance)
{   
    ofstream outLogs ;
	outLogs.open(LOG_F);

	outLogs<<"|  Thread "
    <<thread<<"| Transaction \""
    <<transaction<<"\" on Account \""
    <<setw(4)<<setfill(' ')
    <<account
    <<"\" Succeeded\n\t Amount: $"
    <<amount_value
    <<"\tCurrent Balance: $"
	<<balance
    <<endl<<endl;

    outLogs.close();
}

void outputAccounLog_F( int thread, string transaction, int account, double amount_value)
{   
    ofstream outLogs ;
	outLogs.open(LOG_F);

	outLogs<<"|  Thread "
    <<thread<<"| Transaction \""
    <<transaction<<"\" on Account \""
    <<setw(4)<<setfill(' ')
    <<account
    <<"\" of Amount $"
    <<amount_value
    << " Failed"
    <<endl<<endl;

    outLogs.close();
}