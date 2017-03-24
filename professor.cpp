#include<iostream>
#include<string.h>
using namespace std;

char *get_pass(char *);

class Professor
{
  char name[50];
  char id[10];
  char password[50];
  subject sub;
public:

  Professor()
  {
    strcpy(name, "\0");
    strcpy(id,"\0");
    strcpy(password, "\0");
  }

  char *get_id()
  {
    return id;
  }

  char *get_name()
  {
    return name;
  }

  int check_pwd(char *str)
  {
    if(strcmp(str, password)==0)
      return 1;
    return 0;
  }

  void get_password()
  {
    int suc = 0;
    char pass[50], repass[50];
    do {
      cout<<"\n\t\tEnter the password : ";
      strcpy(pass, get_pass(pass));
      cout<<pass;
      cout<<"\n\n\t\tRe-enter password : ";
      strcpy(repass, get_pass(repass));
      cout<<repass;
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

  void get_details();
  void allot_grade();
  void viewstudents();
  void modify_marks();
  void disp();
};

void Professor::get_details()
{
  cin.ignore();
  cout<<"\nEnter the name of the Faculty : ";
  cin.getline(name, 50);
  cout<<"\nEnter the ID : ";
  cin>>id;
}


void Professor::disp()
{
  int swit;
  clrscr();
  do
  {
    cout<<"\n\n\n\t\t1. Modify Students Marks \n\n\t\t2. Allot Grades\n\n\t\t3. View Students \n\n\t\t4. Add Subject\n\n\t\t5. Logout\n\n\t\tEnter Choice : ";
    cin>>swit;
    switch(swit)
   {
      case 1: modify_marks();
                break;
      case 2:
                allot_grade();
                // specify professorobject
                break;
      case 3:
                viewstudents();
              //specify proffesor object

        break;
      case 4:{
                char code[10];
                cout<<"\n\n\t\tEnter the course_code : ";
                cin>>code;
                fstream fp, f;
                int flag = 0;
                subject temp;
                fp.open("subject.dat", ios::in);
                f.open("temp.dat", ios::out);
                while(fp.read((char *)&temp, sizeof(subject)))
                {
                  if(strcmp(temp.get_code(), code)==0)
                  {
                    flag = 1;
                    this->sub = temp;
                    cout<<sub.get_c();
                    // fstream a;
                    // Professor t;
                    // a.open("faculty.dat", ios::in | ios::app);
                    // while(a.read((char *)&t, sizeof(Professor)))
                    // {
                    //   if(strcmp(id, t.get_id())==0)
                    //   {
                    //     break;
                    //   }
                    // }
                    // a.seekp(a.tellg()-sizeof(Professor), ios::beg);
                    // a.write((char *)this, sizeof(Professor));
                    // a.close();
                    f.close();
                    fp.close();
                    remove("temp.dat");
                    break;
                  }
                  f.write((char *)&temp, sizeof(temp));
                }
                if(flag==0)
                {
                  temp.get_details();
                  temp.mod_code(code);
                  this->sub = temp;
                  f.write((char *)&temp, sizeof(temp));
                  while(fp.read((char *)&temp, sizeof(subject)))
                    f.write((char *)&temp, sizeof(temp));
                  f.close();
                  fp.close();
                  remove("subject.dat");
                  rename("temp.dat", "subject.dat");
                  // fstream a;
                  // Professor t;
                  // a.open("faculty.dat", ios::in | ios::app);
                  // while(a.read((char *)&t, sizeof(Professor)))
                  // {
                  //   if(strcmp(id, t.get_id())==0)
                  //   {
                  //     break;
                  //   }
                  // }
                  // a.seekp(a.tellg()-sizeof(Professor), ios::beg);
                  // a.write((char *)this, sizeof(Professor));
                  // a.close();
                }

                  fstream fr, fw;;
                  fr.open("faculty.dat", ios::in);
                  fw.open("temp.dat", ios::out);
                  Professor tem;
                  while(fr.read((char *)&tem, sizeof(Professor)))
                  {
                    if(strcmp(tem.get_id(), id)==0)
                    {  fw.write((char *)this, sizeof(tem));cout<<"laslsal";}
                    else
                      fw.write((char *)&tem, sizeof(tem));
                  }
                  fw.close();
                  fr.close();
                  remove("faculty.dat");
                  rename("temp.dat", "faculty.dat");

      }
        break;

      case 5:main();

          break;
        default:
         break;
   }
 }while(swit!=5);
}

void fac_login()
{
  clrscr();
  char user_name[50], pass[50],ch;
  fstream fp;
  Professor temp;
  int flag = 0, i=0;
  fp.open("faculty.dat",ios::in | ios::binary);
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
  while(fp.read((char *)&temp,sizeof(Professor)))
  {
      if(strcmp(user_name,temp.get_id())==0)
      {
          if(temp.present())
          {
          if(temp.check_pwd(pass)==1)
              flag = 1;
          else
              flag = 0;
          break;
        }
        else
        {
          cout<<"\n\n\t\tPlease register first.";
          return;
        }
      }
  }
  if(!flag)
      cout<<"\n\t\t\tInvalid user name or password.";
  fp.close();
  if(flag)
    temp.disp();
}


int fac_register()
{
  clrscr();
  char user_name[50];
  fstream fp, f;
  Professor temp;
  int flag = 0;
  fp.open("faculty.dat", ios::in | ios::binary);
  f.open("temp.dat", ios::out | ios::binary);
  cout<<"\n\n\t\tEnter your ID : ";
  cin>>user_name;
  while(fp.read((char *)&temp,sizeof(Professor)))
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
      f.write((char *)&temp, sizeof(Professor));
  }
  if(flag == 0)
    cout<<"\n\n\t\tThe entered ID is invalid.";
  f.close();
  fp.close();
  remove("faculty.dat");
  rename("temp.dat", "faculty.dat");
  return flag;
}

char *get_pass(char *pass)
{
  char ch;
  int i=0;
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
  return pass;
}

void Professor::allot_grade()
{ int x,y;
 // Absolute grading  80+ - 10,, 70+ - 9, 60+ - 8, 50- 7,40+ - 6
 // 30+ - 5 20+- 4  else 0;in terms of pointer,
 fstream a,b;
  student temp;
 a.open("student.dat", ios::in);
 b.open("temp.dat",ios::app);

 a.read((char *)&temp, sizeof(student));
while(!a.eof())
  {
      y = temp.course_present(sub.get_code());
    if(y!= -1)
      {
         x = temp.get_marks(y);
     if(x>=80)
        temp.mod_grad(y, 10);
    else if(x>=70)
        temp.mod_grad(y,9);
    else if(x>=60)
        temp.mod_grad(y,8);
    else if(x>=50)
        temp.mod_grad(y,7);
    else if(x>= 40)
        temp.mod_grad(y,6);
    else if(x>=30)
        temp.mod_grad(y,5);
    else if(x>=20)
        temp.mod_grad(y,4);
    else
        temp.mod_grad(y,0);

         b.write((char *)&temp, sizeof(student));
    cout<<"\n\tName : "<<temp.get_name()<<"\tGrade : "<<temp.get_grad(y);
      }
    else
      {
       b.write((char *)&temp, sizeof(student));
      }
     a.read((char *)&temp, sizeof(student));
   }
      a.close();
      b.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
}

void Professor::viewstudents()
  {
    //student temp;
 //   cout<<"\n\nStudents ID\tStudents Name\tMarks\n";
 //   fstream a;
 //   int y;
 //    a.open("student.dat", ios::in);
 //
 //   while(a.read((char *)&temp, sizeof(student)))
 //   {
 //     y = temp.course_present(sub.get_code());
 //     cout<<"aldslf";
 //      if(y != -1)
 //      {
 //        cout<<temp.get_id()<<"\t\t"<<temp.get_name()<<"\t\t"<<temp.get_marks(y)<<endl;
 //      }
 //       a.read((char *)&temp, sizeof(student));
 //   }
 //   a.close();

   fstream a;
     int y;
    student temp;
   a.open("student.dat", ios::in);

   a.read((char *)&temp, sizeof(student));
  while(!a.eof())
    {
        y = temp.course_present(sub.get_code());
      if(y!= -1)
        {

      cout<<temp.get_id()<<"\t\t"<<temp.get_name()<<"\t\t"<<temp.get_marks(y)<<endl;
        }

       a.read((char *)&temp, sizeof(student));
     }
        a.close();

};

void Professor::modify_marks()
{
    fstream a,b;
    int x, y, m;
    student temp;
    char reg[10];
           cout<<"\n\t1. Do you want to modify records of all students? \n";
           cout<<"\n\t2. Do you want to modify record of a particular student?\n\n\tEnter Choice : ";
           cin>>x;
       if(x== 1)
         {

           a.open("student.dat", ios::in);
           b.open("temp.dat",ios::app);

           a.read((char *)&temp, sizeof(student));
        while(!a.eof())
            {
                y = temp.course_present(sub.get_code());
              if(y!= -1)
                {
                   cout<<"\n\n\tStudent : "<<temp.get_name();
                   cout<<"\n\tPresent score of student is : "<<temp.get_marks(y);
                   cout<<"\n\tEnter score  of the student to be added : ";
                   cin >>m;
                   temp.mod_marks(y, m);
                   b.write((char *)&temp, sizeof(student));
                }
              else
                {
                 b.write((char *)&temp, sizeof(student));
                }
               a.read((char *)&temp, sizeof(student));
             }
               a.close();
                b.close();
              remove("student.dat");
              rename("temp.dat", "student.dat");
         }

         else
          {
            cout<<"\n\tEnter the Register number of student to be modified : ";
            cin>>reg;
            //cin.getline(reg,50);  use if required;
            a.open("student.dat", ios::in);
            b.open("temp.dat",ios::app);


         while(a.read((char *)&temp, sizeof(student)))
             {
                 y = temp.course_present(sub.get_code());
               if(y != -1 )
                 {
                   if(strcmp(temp.get_id(),reg)==0)
                  { cout<<"\n\tPresent score of student is : "<<temp.get_marks(y);
                    cout<<"\n\tEnter score to be added : ";
                    cin >>m;
                    temp.mod_marks(y, m);
                    b.write((char *)&temp, sizeof(student));
                 }else
                    b.write((char *)&temp, sizeof(student));
               }
               else
                 {
                  b.write((char *)&temp, sizeof(student));
                 }
              }
                 a.close();
                 b.close();
               remove("student.dat");
               rename("temp.dat", "student.dat");
          }
}
