// Easter Sundays calculator
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *myname;
const char *religions[]={ "Old Calendar Orthodox", "New Calendar Orthodox", "Catholic" };
const char *months[]={ "March", "April", "May" };
void showusage();

int main(int argc,char *argv[])
{
   int date, month, year, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12;
   int religion, cc;
   strcpy((myname=malloc(sizeof(argv[0]))), argv[0]);

    // parse command line options
    while ((cc = getopt(argc, argv, ":o:c")) != -1)
     switch (cc) {
      case 'o':
       if (*optarg!='O' && *optarg!='N')
        showusage();
       religion=79-*optarg;
      break;
  	  case 'c':
       religion=2;
      break;
      case '?':
       showusage();
      break;
      default:
       abort();
    break; }
    if (optind==argc || argc<3)
     showusage();
    year=atoi(argv[optind]);
    if (year<0 || year>32767)
     showusage();

     // calculations
     if (religion<2) { // Orthodox
      u1=year%19;
      u2=year%4;
      u3=year%7;
      u4=((19*u1)+16)%30;
      u5=((2*u2)+(4*u3)+(6*u4))%7;
      date=3+u4+u5;
      month=2;
      if (date>30) {
       date-=30;
      ++month; }
      if (!religion) {
       date-=13;
      if (date<1) {
       date+=(month==2) ? 31 : 30;
     --month; } } }
     else { // Catholic
      u1=year%19;
      u2=year/100;
      u3=year%100;
      u4=u2/4;
      u5=u2%4;
      u6=(u2+8)/25;
      u7=(u2-u6+1)/3;
      u8=(19*u1+u2-u4-u7+15)%30;
      u9=u3/4;
      u10=u3%4;
      u11=(32+2*u5+2*u9-u8-u10)%7;
      u12=(u1+11*u8+22*u11)/451;
      month=((u8+u11-7*u12+114)/31)-2;
     date=((u8+u11-7*u12+114)%31)+1; }
   
    // result
    printf("%s Easter is on %d of %s %d\n", religions[religion], date, months[month-1], year);
    
 return 0;
}

// show usage
void showusage()
{
  printf("%s -oΝ [Orthodox New Calendar] -oΟ [Orthodox Old Calendar] -c [Catholic] year [0..32767]\n", myname);
  exit(EXIT_FAILURE);
}
