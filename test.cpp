#include "student.cpp"

#include<iostream>
#include<fstream>
#include<cstdio>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#define clrscr() system("clear");
using namespace std;

int main(){
  subject sub;
  //cin>>sub;
  cout<<sub.get_credit();
  student s;
  cin>>s;
  cout<<s.get_name();
}
