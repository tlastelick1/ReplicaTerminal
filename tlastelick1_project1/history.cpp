#include <stdio.h> 
#include <string.h> 
#include <unistd.h>
#include <stdlib.h> // malloc functions
#include <sys/types.h> 
#include <sys/wait.h> 
#include "hist.cpp"

void tokenize(char str [], char* argv []);
void allocateArgvMemory(char * argv []);
void prompt();
void checkForR(char strCopy [], char* argv [], hist myHistory, string token);


int main()
{
    int pid;        // fork
    char str[200];  // holds input from terminal prompt 
    char* argv[10]; // // holds tokenized commands and flags
    allocateArgvMemory(argv); 
    char* folder;   // path to a command that is to be executed 
    folder = (char*) malloc(200*sizeof(char));  // Allocate 200 character positions
    
    string folder1;
    hist myHistory;
    char strCopy[200];  // identical copy of str that does not get tokenized for r purposes
    char strCopyHist[200];  // used for tokenizing for when hist function is used. 
    //string test1 = "Hello world";
    //string test2;

    //test2 = test1;
    //cout << test2 << endl;
    

    int j = 1;  // to test the loop 4 times
    while (j < 6)
    {       
    
    // Prompt user and get the input into str[]
    prompt();
    if(fgets(str, 200, stdin)==NULL)   // The statement reads a line
    {
       cout << "Error\n";
       return 0;
    } 

    //stringstream (sstream) will not properly transfer strtok(str, " ")

    // How to grab first value only of initial user input ? //
    // char * token1 = strtok(str, " ") properly grabs value of str
    // -Does this mess with the value of str?
    // -- Yes. It grabs the first value that would have been used by tokenizer function
    // --- Solution is to create multiple copies of str from the onset, and use the copies not str
    // 

    // How check that first value we grabbed is indeed hist ? //
    // Does not work
//    if (token1 == "hist")
//     cout << "Token1: " << token1;

    // copy str for use in different functions 
    strcpy(strCopy, str);
    strcpy(strCopyHist, str);   

    

    string token1 = strtok(strCopyHist, " ");
    //cout << "token1: " << token1 << endl;
    //if (token1.compare("hist"))
        //cout << "Yes it worked!";
    //if (strcmp(token1, "hist") != 0) {
    //    "Yes it worked!!";
    //}
    
    //char*
    

    tokenize(str, argv);  //Tokenize to figure out that it is r

    cout << "Just above checkForR statement: " << endl;
    checkForR(strCopy, argv, myHistory, token1);   // Check if user input is r value 
    cout << "Just below checkForR statement: " << endl;

        myHistory.add(strCopy);
        myHistory.display();

        

// How to see what is inside argv[0]?
// See what token is?

        
        strcpy(folder, "/bin/");
        folder = strcat(folder, argv[0]);     // Here the folder is "/bin/ls"

    // Starting Fork block
        pid = getpid();        
        pid = fork();
            if (pid == 0) // Child process executes this block
            {  
                execv(folder, argv);          // call to the function; execute and exit
                printf("Unknown command\n"); // this statement will not be executed if excecv() is successful
                return 0;
            } 
            else   // Parent process executes this block  
            { 
                wait(NULL); // So child process executes first
            }
    j += 1;
    } // end while
        return 0;   // end main
}

void tokenize(char str [], char* argv [])
{
    int i = 1;

// Turn terminal input into a C string
    str[strlen(str) - 1] = '\0';       //  It replaces newline ch with null


    // Returns first token with delimiter space
    char* token = strtok(str, " "); 
    argv[0] = token;    // put first terminal command as the first element
    //cout << "printing the token: " << endl;
    // Fill the remaining elements with additional options (flags) from terminal prompt
    while (token != NULL) 
    { 
        //printf("%s", token);       // shows each token at a time. 
        token = strtok(NULL, " ");   // prevents an infinite loop.
        argv[i] = token;             // fill elements with flags 
        i++;                         // increment space in memory;
    }
}

void allocateArgvMemory(char * argv[])
{
    for (int i=0; i<10; i++)
        argv[i] = (char*) malloc(50*sizeof(char));
}

void prompt()
{
    cout << "This is the prompt: $ "; 

}

void checkForR(char strCopy [], char* argv [], hist myHistory, string token1)
{
    cout << "Does above the if statement print?";
    if (token1.compare("r"))
        {   
            cout << "Does inside R even print??" << endl;
            // Find the last known history address
            int count = 0;       
            count = myHistory.getCount(); 

            // strCopy now equals the last command
            myHistory.get(count, strCopy);   

            // tokenize strCopy so it can be executed like normally
            tokenize(strCopy, argv);
            
        }
    else if (*argv[0] == 'r' && *argv[1] != NULL)
    {
        cout << "strCopy: " << strCopy[0] << strCopy[1] << strCopy[2];
stringstream str11;

    // converts character into an integer.
    str11 << *argv[1];
    int x = 0;
    str11 >> x;

       // *argv[1] = atoi(*argv[1]);
        myHistory.get(x, strCopy);
        cout << "Do I get it??";


        tokenize(strCopy, argv);
    }


}