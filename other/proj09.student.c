   /*
        Funakoshi Silva
        CSEE 325
    */
   
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>


struct entre_structure{
	unsigned char command;
	unsigned short size_frame;
};

int readArguments(const int& argc, char* argv[]);
void pageTableInitialization();
int ReadFile();
void coutTable();
void header();
void tableValues (int i);
void pageTableHelper(int i);

struct entre_structure page_table[8];
 
using namespace std;


bool debugFlag = false;
string file_name = "";
int R_count = 0;
int W_count = 0;

const unsigned  V_shift_n = 2;
const unsigned R_mask_n = 0x2;
const unsigned  mask_offset = 0x1fff;
const unsigned  V_mask_n = 0x4;
const unsigned  r_shift_n = 1;
const unsigned  M_mask_n = 0x1;
const unsigned  page_mask_n = 0xe000;
const unsigned  page_shift_n = 13;
const unsigned P_mask_n = 0x2;
const unsigned  p_shift_n = 1;




int main(int argc, char* argv[]){
    /*
        calls mutiple auxilary funtions
        in order to replicate memory virtualization
        :return type int
    */

	pageTableInitialization();
    
	int approved = readArguments(argc, argv);

	if (approved == 0) 
    {
        return 0;
    }

    coutTable();
    
	approved = ReadFile();

	if (approved == 0)
    {
        return 0;
    }
    
	header();
	coutTable();

}



int readArguments(const int& argc, char* argv[]){

    /*
        Reads argument from terminal
        process arguments, and error handle
        cases
        :return type int
    */

    int i = 1;

    do
    {   
        if (argc == 1 or argc == 2 )
        {
            cout << "incorrect arguments"<< endl;
            
            return 0;
        }

		if (argv[i][0] == '-')
        {

			string tokenizer(argv[i]);

			tokenizer = tokenizer.substr(1);

			if (tokenizer.compare("refs") == 0)
            {
				if ( argv[i+1][0] == '-' )
                {
					cout<<"Missing memory reference after flag"<<endl;
					return 0;
				}
                
                else
                {
					string temp(argv[i+1]);

					file_name = temp;
					i++;
				}
			}
            else if (tokenizer.compare("debug") == 0)
            {
				debugFlag = true;
			}
            else
            {
				cout<<"Command line conflict. Please change argumnet  -->" << tokenizer <<endl;
				return 0;
			}
		}
        
        else
        {
			cout<<"Command line conflict. Please change argumnet " << argv[i] << endl;
			return 0;
		}

        i++;

	} 
    
    while( i < argc);


	return 1;

}



void pageTableInitialization()
      /*
        displays initialization of page table values 
        formats the display of data
        :return type None
    */
{
    int i = 0;

    do
    {
		pageTableHelper(i);
 
        i++;

	} while (i < 8);


    

}

void coutTable(){
       /*
        displays page table values 
        formats the display of data
        :return type None
    */

    cout<< endl;
	cout<< "I V P R M frame" << endl;
    cout << "-------------" << endl;
    int i = 0;

    do
    {
        tableValues(i);

        i += 1;

	} while(i < 8);

	cout<<endl;

}


int ReadFile(){
    /*
        Reads memory reference file with intruction related
        to virtual memory
        :return type int
    */
    
    ifstream document; 
    document.open(file_name);

	if (document.is_open())
    {

        cout << "__________ " <<"Displaying " << file_name  << " __________"  << endl;
        cout << endl;
        cout << endl;

		string line;

		while (getline(document,line))
        {
			istringstream iss(line);

			vector<string> list_of_tokens;

    		copy(istream_iterator<string>(iss), 
    
        			istream_iterator<string>(),

      				back_inserter(list_of_tokens));

			int  address_value = strtoul(list_of_tokens[0].c_str(),NULL,16);
			int  page_value = ((address_value & page_mask_n) >> page_shift_n);
			int  offset_value = (address_value & mask_offset);

            if (debugFlag)
            {
                coutTable();
            } 

			if (list_of_tokens[1].compare("R") != 0)
            {


                printf("%04x %d %04x W\n",
                address_value,page_value,offset_value);
				W_count++;
			}

            else
            {
				printf("%04x %d %04x R\n",address_value,page_value,offset_value);
				R_count++;
			}

		
		}
	}
    else
    {
		        cout << endl;
                cout<<"    :( ----> " << file_name << " does not exits in the current directory."<<endl;
                cout << endl;

		return 0;
	}

	return 1;

}



void header()
    /*
        Contain the header to be displayed 
        Read operation
        Write operation
        Memory Operation
        :return type None
    */
    
{
    cout<< "_________________________________________";
    cout << endl;
    cout<<"Read Operation: "<<R_count<<endl;
	cout<<"Write Operation: "<<W_count<<endl;
	cout<<"Memory Reference: "<<R_count + W_count<<endl;
    cout << endl;
}


void tableValues (int i)
    /*
        auxilary function to manipulates v, r, m page table 
        instructions
        :return type None
    */
{
        unsigned char v = ((page_table[i].command & V_mask_n) >> V_shift_n);
        unsigned char p = ((page_table[i].command & P_mask_n) >> p_shift_n);
		unsigned char r = ((page_table[i].command & R_mask_n) >> r_shift_n);
		unsigned char m = (page_table[i].command & M_mask_n);

		printf("%d %d %0x %0x %0x %03x\n",i,v,p, r,m,page_table[i].size_frame);
        // printf( "%d ",page_table[i].size_frame);
}

void pageTableHelper(int i)
    /*
        auxilary function to manipulates page table 
        instructions
        :return type None
    */
{
    page_table[i].command = 0;
	page_table[i].size_frame = 0;
}