#include<iostream>
#include<fstream>
#include<cstdio>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<iomanip>
#define clrscr() system("clear");
using namespace std;


class admin
{
    char user_name[50];
    char password[50];
public:
    char *get_user()
    {
        return user_name;
    }
    char *get_password()
    {
        return password;
    }
    void set_user(char *user)
    {
        strcpy(user_name, user);
        cout<<user_name;
    }
    void set_password(char *pass)
    {
        strcpy(password, pass);
        cout<<password;
    }
    void add_student();
    void remove_student();
    void add_professor();
    void remove_professor();
    void enroll_student();
    void get_gradesheet();
    void get_ranklist();
};

int ad_login()
{
    char user_name[50], pass[50],ch;
    fstream fp;
    admin temp;
    int flag = 0, i=0;
    fp.open("admin.dat",ios::in | ios::binary);
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
    while(fp.read((char *)&temp,sizeof(admin)))
    {
        if(strcmp(user_name,temp.get_user())==0)
        {
            if(strcmp(pass, temp.get_password())==0)
                flag = 1;
            else
                flag = 0;
            break;
        }
    }
    if(!flag)
        cout<<"\n\t\t\tInvalid user name or password.";
    fp.close();
    return flag;
}



void admin::add_student()
{
    clrscr();
    cout<<"\n\n\n\t\t\tADD STUDENT\n\t\t\t============";
    fstream fp;
    fp.open("student.dat", ios::app);
    student temp;
    temp.get_details();
    fp.write((char *)&temp, sizeof(student));
    fp.close();
    getch();
}

void admin::remove_student()
{
    clrscr();
    cout<<"\n\n\n\t\t\tREMOVE STUDENT\n\t\t\t==============";
    fstream fp, f;
    fp.open("student.dat", ios::in);
    f.open("temp.dat", ios::out);
    student temp;
    char id[10];
    int flag=0;
    cout<<"\n\n\tEnter the ID of the student to be deleted : ";
    cin>>id;
    fp.read((char *)&temp, sizeof(student));
    while(!fp.eof())
    {

        if(strcmp(id, temp.get_id())==0)
        {
            char ch;
            cout<<"\n\n\t\tAre you sure you want to delete the student "<<temp.get_name()<<" from the database?(y/n) : ";
            cin>>ch;
            if(ch=='n'||ch=='N')
                f.write((char *)&temp, sizeof(student));
            else
                cout<<"\n\n\t\tThe record has been successfully deleted.";
            flag = 1;
            getchar();
        }
        else
        {
                f.write((char *)&temp, sizeof(student));
        }
    fp.read((char *)&temp, sizeof(student));
    }
    if(flag==0)
        cout<<"\n\n\tNo such record exists.";
    f.close();
    fp.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");

    getch();
}

void admin::add_professor()
{
  clrscr();
  cout<<"\n\n\n\t\t\tADD Faculty\n\t\t\t============";
  fstream fp;
  fp.open("faculty.dat", ios::app);
  Professor temp;
  temp.get_details();
  getch();
  fp.write((char *)&temp, sizeof(Professor));
  fp.close();
}

void admin::remove_professor()
{
  clrscr();
  cout<<"\n\n\n\t\t\tREMOVE FACULTY\n\t\t\t==============";
  fstream fp, f;
  fp.open("faculty.dat", ios::in);
  f.open("temp.dat", ios::out);
  Professor temp;
  char id[10];
  int flag=0;
  cout<<"\n\n\tEnter the ID of the faculty to be deleted : ";
  cin>>id;
  fp.read((char *)&temp, sizeof(Professor));
  while(!fp.eof())
  {

      if(strcmp(id, temp.get_id())==0)
      {
          char ch;
          cout<<"\n\n\t\tAre you sure you want to delete the student "<<temp.get_name()<<" from the database?(y/n) : ";
          cin>>ch;
          if(ch=='n'||ch=='N')
              f.write((char *)&temp, sizeof(Professor));
          else
              cout<<"\n\n\t\tThe record has been successfully deleted.";
          flag = 1;
          getchar();
      }
      else
      {
              f.write((char *)&temp, sizeof(Professor));
      }
  fp.read((char *)&temp, sizeof(Professor));
  }
  if(flag==0)
      cout<<"\n\n\tNo such record exists.";
  f.close();
  fp.close();
  remove("faculty.dat");
  rename("temp.dat", "faculty.dat");

  getch();
}

void admin::enroll_student()
{
  clrscr();
  char id[10];
  cout<<"\n\n\n\t\tEnter the ID of the student : ";
  cin>>id;
  fstream fp, f,a;
  int flag = 0;
  f.open("student.dat", ios::in);
  a.open("temp.dat",ios::app);
  student temp;
  while(f.read((char *)&temp, sizeof(student)))
  {
    if(strcmp(temp.get_id(), id)==0)
    {
      flag = 1;
      break;
    }
    a.write((char *)&temp,sizeof(student));
  }
  if(flag==0)
  {
    cout<<"\n\n\t\tThe ID is invalid.";
    a.close();
    remove("temp.dat");
    f.close();
  }
  else
  {
  fp.open("subject.dat", ios::in);
  subject tem;
  char ch;
  cout<<"\n\n\t\tPlease enter yes or no against the corresponding subject(y/n) :\n\n ";
  while(fp.read((char *)&tem, sizeof(subject)))
  {
    if(temp.course_present(tem.get_code())==-1)
    {
    cout<<"\n\tCourse Code : "<<tem.get_code()<<"      Course Title : "<<tem.get_c()<< "  :";
    cin>>ch;
    if(ch=='y'||ch=='Y')
    {
        temp.add_sub(tem.get_code());
    }
  }
  }
  a.write((char *)&temp,sizeof(student));
  while(f.read((char *)&temp, sizeof(student)))
  {
    a.write((char *)&temp,sizeof(student));
  }

  f.close();
  fp.close();
  a.close();
  remove("student.dat");
  rename("temp.dat", "student.dat");
  }
getch();
}

void admin::get_gradesheet()
{

	char id[10];
	int flag;
	flag=0;
	int i;
	grade a[10];
    int cre[10];
    int h[10];
    int m;
    int tot;
    float tot1;
    subject tem;
  	cout<<"\n\n\n\t\t\tGRADE SHEET\n\t\t\t==============";
	fstream fp,f,g;
	fp.open("student.dat", ios::in);
	f.open("temp.dat", ios::out);
	cout<<"\n\n\tEnter the ID of the student for his/her gradesheet : ";
    cin>>id;
    student temp;
    fp.read((char *)&temp, sizeof(student));
    while(!fp.eof())
    {

        if(strcmp(id, temp.get_id())==0)
        {

            tot=0;
            tot1=0;

            m=temp.get_n();

            for(i=0;i<m;i++)
            {
            	a[i]=temp.get_grade(i);
            	g.open("subject.dat",ios::in);
            	g.read((char*)&tem, sizeof(subject));
            	while(!g.eof())
            	{
            		if(strcmp(a[i].get_c(), tem.get_code())==0)
            			cre[i]=tem.get_credit();
            		g.read((char*)&tem, sizeof(subject));
            	}
            	g.close();
            	tot+=cre[i];
            	h[i]=a[i].get_gra()*cre[i];
            	tot1+=h[i];

            }
            float cgpa;
            cgpa=tot1/tot;

            temp.mod_cgpa(cgpa);
            clrscr();
            cout<<"\n\n\t\t\tGRADE SHEET\n\n\n";
            cout.width(20);cout<<left;
            cout<<"Student name : "<<temp.get_name();
            cout.width(20);cout<<left;
            cout<<"\nRegister Number : "<<temp.get_id();
            cout.width(20);cout<<left;
            cout<<"\nCGPA : "<<cgpa;
            cout<<"\nCourse code\t";
            for(i=0;i<m;i++)
            {
            	cout<<a[i].get_c()<<"\t";
            }
            cout<<"\nYour grade\t";
            for(i=0;i<m;i++)
            {
            	cout<<h[i]/cre[i]<<"\t";
            }
            getch();
            flag=1;
            break;
        }
    fp.read((char *)&temp, sizeof(student));
    }
    f.close();
    fp.close();
    if(flag==0)
    {
    	cout<<"\n\nThe student does not exist\n\n";
    }
}

void admin::get_ranklist()
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
