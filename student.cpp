#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

char *get_pass(char *);
//class user;

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

    friend istream &operator >> (istream& is, subject &sub);

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

  istream &operator >> (istream& is, subject &sub){
    cout<<"\n\nEnter the subject title: ";
    cin.ignore();
    cin.getline(sub.title, 50);
    cout<<"\n\nEnter the number of credits: ";
    cin>>sub.credits;
    cout<<"\n\nEnter the semester: ";
    cin>>sub.sem;
  }

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
    void display()
    {
      cout<<"Course Code: "<<course_code;
      cout<<"\nGrade: "<<grd<<endl;
      cout<<"Marks: "<<marks<<endl;
    }

    friend istream& operator >> (istream &i, grade &g);
};

class student :public user
{
    char name[50];
    char section;
    grade grad[10];
    float cgpa;
    int sem;
    int n;
public:
    int login();
    int Register();
    void disp();
    student()
    {
      strcpy(name, "\0");
      n=0;
      cgpa=0.0;
      sem = 1;
      strcpy(password, "\0");
    }

    student(char id[10], char password[10], char name[50], char section, grade grad[10], float cgpa, int sem, int n):user(id,password){
      strcpy(this->name,name);
      this->section=section;
      //copy all grades
      this->cgpa=cgpa;
      this->sem=sem;
      this->n=n;
    }

    void get_details();

    char *get_id()
    {
        return id;
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

    int chk_password(char *str)
    {
      return strcmp(str, password)==0;
    }

    void get_password()
    {
      int suc = 0;
      char pass[50], repass[50];
      do {
        cout<<"\n\t\tEnter the password : ";
        strcpy(pass, get_pass(pass));
        cout<<"\n\n\t\tRe-enter password : ";
        strcpy(repass, get_pass(repass));
        if(strcmp(pass, repass)==0)
        {
          if(strlen(pass)<7)
            cout<<"\n\nPassword length is too short.";
          else
          {
            suc = 1;
            strcpy(password, pass);
          }
        }
        else
          cout<<"\n\nPasswords dont match.";
      } while(!suc);
    }

    int present()
    {
      if(strcmp(password, "\0")==0)
       return 0;
     return 1;
    }

    friend istream& operator >> (istream &i, student &s);
    void get_ranklist();
};



inline void grade::get_course(int i)
{
    cout<<"\n\t"<<i<<". Enter the Course Code : ";
    cin>>course_code;
}
istream& operator >> (istream &i, grade &g){

  cout<<"\n\t"<<i<<". Enter the Course Code : ";
  cin>>g.course_code;

  return i;
}



inline void student::get_details()
{
    //cin>>noskipws;
    cin.ignore();
    cout<<"\n\n\t\tEnter the student name : ";
    cin.getline(name,50);
    cout<<"\n\n\t\tEnter the registration number : ";
    cin>>id;
    cout<<"\n\n\t\tEnter the section : ";
    cin>>section;
    cout<<"\n\n\t\tEnter the semester :";
    cin>>sem;
}
istream& operator >> (istream &i, student &s){
  //cin>>noskipws;
  cin.ignore();
  cout<<"\n\n\t\tEnter the student name : ";
  cin.getline(s.name,50);
  cout<<"\n\n\t\tEnter the registration number : ";
  cin>>s.id;
  cout<<"\n\n\t\tEnter the section : ";
  cin>>s.section;
  cout<<"\n\n\t\tEnter the semester :";
  cin>>s.sem;
}


int student::login()
{
  clrscr();
  char user_name[50], pass[50],ch;
  fstream fp;
  student temp;
  int flag = 0, i=0;
  fp.open("student.dat",ios::in);
  cout<<"\n\n\n\t\t\tUser_Name : ";
  cin>>user_name;
  cout<<"\n\n\t\t\tPassword : ";
  ch = getch();
  while(ch!=10)
  {
      if(ch == 127)
      {
          if(i!=0)
          {
              cout<<"\b \b";
              i--;
          }
      }
      else
      {
          pass[i++] = ch;
          cout<<'*';
      }
      ch = getch();
  }
  pass[i] = '\0';
  while(fp.read((char *)&temp,sizeof(student)))
  {
      if(strcmp(user_name,temp.get_id())==0)
      {
          if(temp.present())
          {
          if(temp.chk_password(pass)==1)
              flag = 1;
          else
              flag = 0;
          break;
        }
        else
        {
          cout<<"\n\n\t\tPlease register first.";
          return 0;
        }
      }
  }
  if(!flag)
      cout<<"\n\t\t\tInvalid user name or password.";
  fp.close();
  if(flag)
    {
      cout<<"\nLogged in.";
      temp.disp();
    }
    return 1;
}


int student::Register()
{
  clrscr();
  char user_name[50];
  fstream fp, f;
  student temp;
  int flag = 0;
  fp.open("student.dat", ios::in);
  f.open("temp.dat", ios::out);
  cout<<"\n\n\t\tEnter your ID : ";
  cin>>user_name;
  while(fp.read((char *)&temp,sizeof(student)))
  {
      if(strcmp(user_name,temp.get_id())==0)
      {
        if(temp.present())
        {
           cout<<"\n The ID "<<user_name<<" has aldready been registerd.";
           return 1;
        }
        else
        {
          flag = 1;
          temp.get_password();
        }
      }
      f.write((char *)&temp, sizeof(student));
  }
  if(flag == 0)
    cout<<"\n\n\t\tThe entered ID is invalid.";
  f.close();
  fp.close();
  remove("student.dat");
  rename("temp.dat", "student.dat");
  return flag;
}

inline void student::disp()
{
  int ch;
  do
  {
    cout<<"\n\n1. View Report Card\n2. View Ranklist\n3.Logout\n\n";
    cin>>ch;
    switch(ch)
    {
      case 1:
        {
          cout<<"\n";
          cout<<"Name: "<<name<<endl;
          cout<<"Section: "<<section<<endl;
          cout<<"ID: "<<id<<endl;
          cout<<"CGPA: "<<cgpa<<endl;
          cout<<"Grades: \n";
          for (int i = 0; i < n; ++i)
          {
            grad[i].display();
          }


        }
        break;
      case 2:
        {
          get_ranklist();
        }
        break;
      default: 
        cout<<"Invalid choice\n";
    }

  }while(ch!=3);
  
}