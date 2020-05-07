// dayspassed with Julian Day calculator
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long ul;

// function declarations
int assignparameters(const char *parameter, int *d, int *m, int *y);
int isleapyear(int year);
ul julianday(int d, int m, int y);
void showusage();

// variables
char *myname;
const char separator[2]="/";

int main(int argc, char *argv[])
{
  ul jdn1, jdn2;
  int d1, d2, m1, m2, y1, y2, parseresult;
  myname=argv[0];
 
  // error check and parameters parsing
  if (argc!=3 || !(parseresult=assignparameters(argv[1], &d1, &m1, &y1)) || !(parseresult=assignparameters(argv[2], &d2, &m2, &y2)))
   showusage();
  // result
  jdn1=julianday(d1, m1, y1);
  jdn2=julianday(d2, m2, y2);
  printf("%ld days\n", jdn2-jdn1);
  
 return 0;
}

// assign argv strings to parameters
int assignparameters(const char *parameter, int *d, int *m, int *y)
{
  int i, readnumbers[3]={ 0, 0, 0 };
  char lparameter[strlen(parameter)], *token;
  int daysinmonth=(*m==2) ? (28 + isleapyear(*y)) : 31 - (*m - 1) % 7 % 2;
  strcpy(lparameter, parameter); // strtok won't go down const char*
  
   // equalize number separators
   for (i=0;i<strlen(lparameter);i++)
    if (lparameter[i]=='-' || lparameter[i]=='.')
     lparameter[i]=separator[0];
   // get the first token
   token = strtok(lparameter, separator);
   // walk through other tokens
   i=0;
   while( token != NULL ) {
    readnumbers[i++]=atoi(token);
   token = strtok(NULL, separator); }
   // assign read numbers to pointers
   *d=readnumbers[0]; *m=readnumbers[1]; *y=readnumbers[2];
   // see if there is a mistake in parameters
   if (i<2 || *d>daysinmonth || *d<1 || *m<1 || *m>12 || *y<1 || *y>32767)
    return 0;
   
 return 1;
}

// leap year calculator
int isleapyear(int year)
{
  if( (year%400==0 || year%100!=0) &&(year%4==0)) // is a leap year
   return 1;

 return 0;
}

// Julian Day calculator
ul julianday(int d, int m, int y)
{
 return (1461 * (y + 4800 + (m-14)/12))/4 + (367 * (m-2-12 * ((m - 14)/12)))/12 - (3 * ((y + 4900 + (m - 14)/12)/100))/4 + d - 32075;    
}

// show usage
void showusage()
{
  printf("%s startdate enddate [dd/mm/yyyy or dd-mm-yyyy or dd.mm.yyyy]\n", myname);

 exit(EXIT_FAILURE);    
}
