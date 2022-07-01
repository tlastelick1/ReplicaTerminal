// Trevor Lastelick
// Dr. Dulal Kar
// COSC 3346 - 001
// GNU Island Shell
// ************
//
// This program prompts the user for terminal input. If the command/flags are in the 
// /bin/ folder they will be executed on a single case basis. Several custom commands
// can be run even though they are not in the /bin/ folder. These commands are r, hist,
// exit, and r n where n is an integer between 1-10. r will run the previously executed
// command. hist will display a history of up to the 10 most recent commands and the order in which 
// they were executed. exit will end the program. r n, where n is an integer between 1 
// and 10, will run the corresponding command shown in the history list.
//
// *************

#include <stdio.h> 
#include <string.h> 
#include <unistd.h>
#include <stdlib.h> // malloc functions
#include <sys/types.h> 
#include <sys/wait.h> 
#include "hist.h" // command history functions 
#include <vector>

void tokenizeIntoChar(char str [], char * argv []);
// Function to turn terminal input into tokenized strings that can be read
// and executed in the /bin/ folder. 
// Precondition: Terminal input must first be read-into str delimeted by spaces.
// Allocated memory (char * argv []) to hold the commands given by terminal input (char str []).
// Postcondition: All spaces have been removed within str. Each argv index holds a string of
// characters that was separated by a space. 

void allocateArgvMemory(char * argv []);
// Allocates memory for each array within argv. 
// Precondition: A pointer to an array of character arrays of size 10 must exist.
// Postcondition: Each index of that array will have memory of 50 characters allocated to it.

void prompt(hist myHistory);
// Provides the current history command the user is on. Lets the user know 
// where they are to enter terminal input.
// Precondition: An object of the hist class must exist.
// Postcondition: Provides a text prompt for the user to follow.  

int checkInput(char str [], hist myHistory, char strCopyHist [], char * argv [], int flag);
// Handles all special commands given by terminal input. Also, handles all error / improper
// use situation by those special commands.  
// Precondition: The terminal input must be inputed into str. An object of the history class must exist.
// strCopyHist must have an identical copy of str before entering this function. 
// argv must first have all indexes allocated memory. And flag must equal 0 to function properly. 

bool checkNumber(string str);
// Checks if a string value can be converted into a number. 
// Precondition: str must have some input.
// Postcondition: returns true if the input can be converted into an integer, false otherwise.

int main()
{
    
    hist myHistory;     // Runs functions from "hist.cpp". 
    int pid;            // Fork.
    int flag = 0;       // Handles special command cases.

    // While terminal input is not "exit"
    while (flag != 6)
    {       

    // Allocate memory 
    char * argv[10];                     // Holds tokenized commands and flags.
    allocateArgvMemory(argv);            // Allocate memory space for each argv index.  
    char * folder = new char[200];       // Path to a command that is to be executed.
    char str [200];                      // Holds initial input from terminal prompt.
    char strCopyHist [200];              // Keeps original terminal input to be used by hist.cpp class. 
    vector<string> vec;                  // Holds tokenized terminal input. Index's are used to check 
                                         // terminal input commands for r, r n, hist, exit.

    
    // Handles the special cases r, r n, hist, exit
    // by running cooresponding functions.  
    int flag = 0;

    // Prompt user for terminal input.
    prompt(myHistory);

    // Read terminal input from user.
    if(fgets(str, 200, stdin)==NULL)   // The statement reads a line
    {
       cout << "Error\n";
       return 0;
    } 

    // Turn terminal input into a C string
    str[strlen(str) - 1] = '\0';       //  Replaces newline ch with null

    // Create identical copy of un-tokenized user input. 
    strcpy(strCopyHist, str);   
 
    // Check to see if terminal input is special command, r, r n, hist, exit.
    // Will change flag number accordingly. 
    flag = checkInput(str, myHistory, strCopyHist, argv, flag);
    
    // If r, r n, or hist is not typed run the normal command. 
    if (flag == 0)
    {
        myHistory.add(strCopyHist);             // Add the command/flags to the history list.
        tokenizeIntoChar(strCopyHist, argv);    // Give argv proper command/flags to run.
    }

    // If r is given and it is NOT the first command given.
    else if (flag == 2)
    {
        myHistory.add(strCopyHist);
        tokenizeIntoChar(strCopyHist, argv);
    }

    // If <= 10 and > than 0, run the r n function. 
    else if (flag == 3)
    {
        // Check if r n retrieved hist command from history list. 
        char hist [5] = {'h', 'i', 's', 't', '\0'};

        // If n is "hist" command, run the special hist function.  
        if (strcmp(strCopyHist, hist) == 0)               
            flag = 5;

        // Otherwise, treat n like a normal command. 
        else
        {
        myHistory.add(strCopyHist);
        tokenizeIntoChar(strCopyHist, argv);
        }
    }

    // If the history command is chosen add it to the list then display the list.
    else if (flag == 5)
    {
        myHistory.add(strCopyHist);
        myHistory.display();
    }

    // If exit is typed into terminal quit program.
    else if (flag == 6)
        return 0;

    // Path to where commands are to be executed.   
    strcpy(folder, "/bin/");
    // Append the command onto the path.
    folder = strcat(folder, argv[0]);     
        
    // Starting Fork block
        pid = getpid();        
        pid = fork();
            if (pid == 0) // Child process executes this block
            {   
                // If r is the first command run, do not try to execute a command
                if (flag == 1)
                {
                    cout << "No previous commands to run." << endl;
                    break;
                }

                // Or if r n, n>10 or n<1, do not try to execute a command,
                else if (flag == 4) 
                {
                    cout << "Unknown command\n";
                    break;
                }
                
                // Or if the hist command was called, do not try to execute a command. 
                else if (flag == 5)
                    break;

                // Otherwise try to execute the command. 
                else
                {
                execv(folder, argv);            // Execute the command/flags given by argv. 
                printf("Unknown command\n");    // This statement will not be executed if excecv() is successful.
                return 0;
                }
            } 
            else   // Parent process executes this block  
            { 
                wait(NULL);                 // So child process executes first.
            }
    } // end while
        return 0;   // end main
}

// Take terminal input and copy it into str. 
void tokenizeIntoChar(char str [], char * argv [])
{
    int i = 1;  // Increments argv[] array. 
    
    char* token = strtok(str, " "); // Returns first token with delimiter space
    argv[0] = token;                // Put user command as the first element.

    // Fill the remaining elements with additional options (flags) 
    // from terminal prompt.
    while (token != NULL) 
    { 
        token = strtok(NULL, " ");   // Prevents an infinite loop.
        argv[i] = token;             // Fill elements with flags for command.
        i++;                         // Increment space in argv memory.
    }
}

// Create the available memory for commands and options to be stored in.
void allocateArgvMemory(char * argv[])
{
    for (int i=0; i<10; i++)
        argv[i] = new char[50]; //(char*) malloc(50*sizeof(char));  // Allocate 50 character positions. 
}

// Prompt the user to start entering command/flags. 
void prompt(hist myHistory)
{
    cout << "Prompt@History Number " << myHistory.getCount() <<  " $ ";
}

// Check to see if the command/flags are r, r n, or hist
int checkInput(char str [], hist myHistory, char strCopyHist [], char * argv [], int flag)
{   
    // User command/flags will be broken down into strings (elements) of this vector.
        vector<string> vec;    

    // Add the first command the user typed. 
    // The command will be vec[0]. 
        char* token = strtok(str, " "); 
        vec.push_back(token);
    
    // Fill the remaining elements with additional flags from terminal prompt.
    while (token != NULL) 
    { 
        token = strtok(NULL, " ");   // Prevents an infinite loop.
        
        // Otherwise vec will break if tries to push_back a null.
        if (token == NULL)
            break;
        
        vec.push_back(token);       // Add additional flags starting at vec[1].
    }

    // Check to see if user input was only r 
    if (vec[0].compare("r") == 0 && vec.size() == 1)
        {
            // Count will equal the number of command/flags given during this session
            // not exceeding 10.
            int count = myHistory.getCount(); 

            // Let the user know that no previous commands have been given.
            if (count == 0)
            {
                // Flag = 1 executes this special case in another function. 
                flag = 1;
                return flag;
            }    

            // If there have been previous command/flags then choose 
            // the previous command/flags. 
            else if (count > 0)
            {
            // Flag = 2 executes this special case in another function. 
            flag = 2;
            
            // strCopyHist now equals the previous command/flags.
            myHistory.get(count, strCopyHist);
            
            // To compare with strCopyHist.
            char hist [5] = {'h', 'i', 's', 't', '\0'};
                    
            // If r n returns hist from history list.
            if (strcmp(strCopyHist, hist) == 0)
                flag = 5;
            
            myHistory.add(strCopyHist);     // Add hist to history list.
            return flag;
            }  
        } // End check for single r value.

    // Check for r n value.
    else if (vec[0].compare("r") == 0 && vec.size() == 2)
        {
        // Check if the n value is an integer. 
        if (checkNumber(vec[1]) == 1)
            {
                int nValue = stoi(vec[1]);      // Convert n value to an integer. 
                
                // If less than equal to 10 and greater than 0, run the r n function. 
                if (nValue <= 10 && nValue >= 1)
                {
                    // Flag = 3 executes this special case in another function. 
                    flag = 3;
                    myHistory.get(nValue, strCopyHist);     // Get n command from hist list.

                    // To compare with strCopyHist.
                    char hist [5] = {'h', 'i', 's', 't', '\0'};

                    // If r n returns hist from history list.
                    if (strcmp(strCopyHist, hist) == 0)
                        flag = 5;       // Flag = 5 executes this special case in another function. 


                    return flag;
                }

                // r n command where n is not an integer or is greater than 10
                // or is less than 1.
                else
                {
                    flag = 4;       // Flag = 4 executes this special case in another function. 
                    return flag;
                }
            }
        } // End check for r n value.

    // Check to see if terminal input was only hist command.
    else if (vec[0].compare("hist") == 0 && vec.size() == 1)
        {
        flag = 5;       // Flag = 5 executes this special case in another function. 
        return flag;
        }

    // Check to see if terminal input was only exit command.
    else if (vec[0].compare("exit") == 0 && vec.size() == 1)
        flag = 6;       // Flag = 6 executes this special case in another function. 


    return flag;

}   // end checkInput()

// Checks to see if a string value is a number or not 
bool checkNumber(string str) 
{
   for (int i = 0; i < str.length(); i++)
   if (isdigit(str[i]) == false)
      return false;
      return true;
}