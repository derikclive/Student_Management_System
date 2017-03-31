#include<iostream>
#include<fstream>
#include<cstdio>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#define clrscr() system("clear");
using namespace std;

class admin;
class subject;
class grade;
class student;
char getch();
int main();

#include "declarations.h"
#include "student.cpp"
#include "professor.cpp"
#include "admin_login.cpp"

int ad_login();
void fac_login();
void display_options();

int main()
{
    clrscr();
    int ch;
    cout<<"\n\n\n\t\t\t1. Admin Login\n\n\t\t\t2. Faculty Login\n\n\t\t\t3. Student Login\n\n\t\tEnter choice : ";
    cin>>ch;
    switch(ch)
    {
      case 1:{
              int valid = ad_login();
              if(valid)
              display_options();
              }
              break;
      case 2:{
                clrscr();
                cout<<"\n\n\n\t\t\t1. Login\n\n\t\t\t2. Register\n\n\t\t\tEnter Choice : ";
                cin>>ch;
                if(ch==1)
                { fac_login();
                }
                else if(ch==2)
                {
                  int sucess = fac_register();
                  if(sucess)
                  {
                     fac_login();
                  }
                }
              }break;
      case 3:{
              clrscr();
              cout<<"\n\n\n\t\t\t1. Login\n\n\t\t\t2. Register\n\n\t\t\tEnter Choice : ";
              cin>>ch;
              if(ch==1)
              {
                stu_login();
              }
              else if(ch==2)
              {
                int sucess = stu_register();
                if(sucess)
                {
                  stu_login();
                }
              }
                break;
            }
      default : cout<<"\n\n\t\tEnter a valid choice.";
    }

    return 0;
}


void display_options()
{

        int ch;
        do
        {
        clrscr();
        cout<<"\n\n\t\t1. Add Student\n\n\t\t2. Remove Student\n\n\t\t3. Add Professor\n\n\t\t4. Remove Professor\n\n\t\t5.Enroll Students \n\n\t\t6.View Gradesheet\n\n\t\t7.Generate Ranklist\n\n\t\t8.Logout\n\n\t\tEnter choice:";
        cin>>ch;
        switch(ch)
        {
            case 1:{
                        admin temp;
                        temp.add_student();
                    }
                    break;
            case 2:{
                        admin temp;
                        temp.remove_student();
                    }
                    break;
            case 3:{
                        admin temp;
                        temp.add_professor();
                    }
                    break;
            case 4:{
                        admin temp;
                        temp.remove_professor();
                    }
                    break;
            case 5:{
                        admin temp;
                        temp.enroll_student();

            }break;

            case 6:{
                     admin temp;
                     temp.get_gradesheet();
                    }
                    break;
            case 7:{
                      admin temp;
                      temp.get_ranklist();
                    }
                    break;
            case 8:{
                      clrscr();
                      cout<<"\nYou have sucessfully logged out.";
                      main();
                    }
                    break;
        }
      }while(ch!=8);
}
