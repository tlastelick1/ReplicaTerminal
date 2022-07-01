#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

class hist 
{
   private:
     char data[10][100];
     int count;
   public:
     hist();
     void add(char[]);
     void get(int, char[]);
     void display();
     int getCount();
};

hist::hist()
{
   count = 0;
   for (int i = 0; i < 10; ++ i)
     strcpy(data[i], "");
}

void hist::add(char x[])
{
  int i;
  if (count < 10)
  {
     strcpy(data[count], x);
     ++ count;
  }
  else   // shift if it is full
  {
    for (i = 0; i < 9; ++ i)
       strcpy(data[i], data[i+1]);
    strcpy(data[9],x);
  }
  return;       
}

// Puts the specified element in the array given. 
void hist::get(int x, char y[])
{
   if (x <= count)
     strcpy(y, data[x - 1]);
   else
     strcpy (y, "");
   return;
}

void hist::display()
{
  for (int i=0; i<count; i++)
  {
      //printf("i+1 %s\n", data[i]);
      cout << i+1 << " " << data[i] << endl;
  }
}

int hist::getCount()
{
  return count; 
}