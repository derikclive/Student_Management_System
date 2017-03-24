#include<iostream>
#include<cstdio>
using namespace std;

class subject
{
    char title[50];
    char code[10];
    int credits;
    int sem;
public:

    subject()
    {
      strcpy(title, "\0");
      strcpy(code, "\0");
      credits = 0;
      sem = 1;
    }

    char *get_code()
    {
      return code;
    }
    char *get_c()
    {
      return title;
    }
    void get_details()
    {
        cout<<"\n\nEnter the subject title: ";
        cin.ignore();
        cin.getline(title, 50);
        cout<<"\n\nEnter the number of credits: ";
        cin>>credits;
        cout<<"\n\nEnter the semester: ";
        cin>>sem;
    }
    int get_credit()
    {
        return credits;
    }
    void mod_code(char *str)
    {
      strcpy(code, str);
    }
    //void get_details(char *);
};

class grade
{
    char course_code[10];
    int grd;
    int marks;
public:

    grade()
    {
      strcpy(course_code, "\0");
      grd = 0;
      marks = 0;
    }

    void get_course(int);
    char *get_c()
    {
      return course_code;
    }
    void mod(int gra)
    {
      grd = gra;
    }
    void mod_m(int m)
    {
      marks+=m;
    }
    int get_mark()
    {
      return marks;
    }
    void add_course(char *str)
    {
      strcpy(course_code, str);
    }
    int get_gra()
    {
      return grd;
    }
};

class student
{
    char name[50];
    char section;
    grade grad[10];
    float cgpa;
    int sem;
    int n;
public:

    student()
    {
      strcpy(name, "\0");
      n=0;
      cgpa=0.0;
      sem = 1;
    }

    void get_details();
    char reg_no[50];
    char *get_id()
    {
        return reg_no;
    }
    char *get_name()
    {
        return name;
    }

    void mod_marks(int y,int marks)
    {
      grad[y].mod_m(marks);
    }
    void mod_grad(int y, int gra)
    {
        grad[y].mod(gra);
    }
    int get_marks(int y)
    {
      return grad[y].get_mark();
    }

    int course_present(char *code)
    {
      for(int i=0;i<n;i++)
      {
        if(strcmp(code, grad[i].get_c())==0)
          return i;
      }
      return -1;
    }

    void add_sub(char *code)
    {
      grad[n++].add_course(code);
    }

    int get_grad(int y)
    {
      return grad[y].get_gra();
    }
    grade get_grade(int i)
    {
        return grad[i];
    }

    int get_n()
    {
        return n;
    }

    void mod_cgpa(float h)
    {
        cgpa=h;
    }

};



inline void grade::get_course(int i)
{
    cout<<"\n\t"<<i<<". Enter the Course Code : ";
    cin>>course_code;
}



inline void student::get_details()
{
    int n;
    //cin>>noskipws;
    cin.ignore();
    cout<<"\n\n\t\tEnter the student name : ";
    cin.getline(name,50);
    cout<<"\n\n\t\tEnter the registration number : ";
    cin>>reg_no;
    cout<<"\n\n\t\tEnter the section : ";
    cin>>section;
    cout<<"\n\n\t\tEnter the semester :";
    cin>>sem;
}
