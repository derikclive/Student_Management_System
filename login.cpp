#include<iostream>
#include<fstream>
#include<cstdio>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#define clrscr() system("clear");
using namespace std;


class user;
class admin;
class subject;
class grade;
class student;

char getch();
int main();

#include "user.cpp"
#include "declarations.h"
#include "student.cpp"
#include "professor.cpp"
#include "admin_login.cpp"


int ad_login();
void fac_login();
void display_options();
template <class T>
void swap(T *a, T *b){
  T temp = *a;
  *a = *b;
  *b = temp;
}

template void swap<float>(float*, float*);
template void swap<student>(student*, student *);

int main()
{
    clrscr();
    int ch;
    cout<<"\n\n\n\t\t\t1. Admin Login\n\n\t\t\t2. Faculty Login\n\n\t\t\t3. Student Login\n\n\t\t\t4. Exit\n\n\t\tEnter choice : ";
    cin>>ch;
    user *u;
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
                Professor p;
                u = &p;
                break;
              }
      case 3:{
              clrscr();
              student s;
              u = &s;
              break;
            }
      case 4:
      	{
      		exit(0);
      	}
      default : cout<<"\n\n\t\tEnter a valid choice.";
    }
    if(ch==2||ch==3)
    {
      cout<<"\n\n\n\t\t\t1. Login\n\n\t\t\t2. Register\n\n\t\t\tEnter Choice : ";
      cin>>ch;
      if(ch==1)
        u->login();
      else if(ch==2)
      {
        int sucess = u->Register();
        if(sucess)
        {
           u->login();
        }
      }
    }

    return 0;
}


void display_options()
{

        int ch;
        do
        {
        clrscr();
        cout<<"\n\n\t\t1. Add Student\n\n\t\t2. Remove Student\n\n\t\t3. Add Professor\n\n\t\t4. Remove Professor\n\n\t\t5. Enroll Students \n\n\t\t6. View Gradesheet\n\n\t\t7. Generate Ranklist\n\n\t\t8. Search\n\n\t\t9. Logout\n\n\t\tEnter choice:";
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
            case 9:{
                      clrscr();
                      cout<<"\nYou have sucessfully logged out";
                      getch();
                      main();
                    }
                    break;
            case 8:
                    {
                      clrscr();
                      admin temp;
                      temp.search();
                    }
                    break;
        }
      }while(ch!=9);
}
void student::get_ranklist()
{
  clrscr();
  int i,j;
  grade a[10];
    int cre[10];
    int h[10];
    int m;
    int tot;
    float tot1;
    int d;
    float cgpa, cg[1000], t;
    d=0;
    subject tem;
     cout<<"\n\n\n\t\t\t\t\tRANKLIST\n\t\t\t\t===============";
      fstream fp, f, g;
     fp.open("student.dat", ios::in);

    student temp;
    student b[1000];
    g.open("subject.dat", ios::in);

    while(fp.read((char *)&temp, sizeof(student)))
    {
        tot=0;
        tot1=0;


        m=temp.get_n();

        for(i=0;i<m;i++)
        {
        a[i]=temp.get_grade(i);

        g.seekg(0, ios::beg);
        g.read((char*)&tem, sizeof(subject));
        while(!g.eof())
        {
            if(strcmp(a[i].get_c(),tem.get_code())==0)
            {cre[i]=tem.get_credit();break;}
            g.read((char*)&tem, sizeof(subject));
        }

            tot+=cre[i];
            h[i]=a[i].get_gra()*cre[i];
            tot1+=h[i];

        }
        cgpa=tot1/tot;
        cg[d]=cgpa;
        temp.mod_cgpa(cgpa);
        b[d]=temp;
        d++;
    }
    g.close();
    fp.close();

    for(i=0;i<d;i++)
    {
      for(j=0;j<d-i-1;j++)
      {
        if(cg[j]<cg[j+1])
        {
          t=cg[j];
          cg[j]=cg[j+1];
          cg[j+1]=t;

          temp=b[j];
          b[j]=b[j+1];
          b[j+1]=temp;
        }
      }
    }
    cout.width(30);cout<<left;
    cout<<"\nStudent name";
    cout.width(20);cout<<left;
    cout<<"  CGPA";
    for(i=0;i<d;i++)
    {
      cout<<"\n";
      cout.width(30);cout<<left;
      cout<<b[i].get_name();
      cout.width(20);cout<<left;
      cout<<cg[i];
    }
    getch();
}
