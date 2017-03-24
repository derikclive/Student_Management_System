#include<iostream>
#include<fstream>
#include<string.h>
#include<cstdio>
using namespace std;

//class grade;
//class subject;

class subject
{
    char title[50];
    char code[10];
    int credits;
    int sem;
public:
    void get_details();
    void disp()
    {
        cout<<endl<<title;
    }
};

void subject::get_details()
{
    cout<<"\n\nEnter the subject code: ";
    cin>>code;
    cout<<"\n\nEnter the subject title: ";
    cin.ignore();
    cin.getline(title, 50);
    cout<<"\n\nEnter the number of credits: ";
    cin>>credits;
    cout<<"\n\nEnter the semester: ";
    cin>>sem;
}

int main()
{
    int ch;
    // fstream fp;
    // fp.open("subject.dat",ios::out);
    subject temp;
    // do
    // {
    // cout<<"\n1. Add Course\n2. Exit\nEnter choice: ";
    // cin>>ch;
    // if(ch==1)
    // {
    //     temp.get_details();
    //     fp.write((char *)&temp, sizeof(subject));
    // }
    // }while(ch!=2);
    // fp.close();
    fstream f;
    f.open("subject.dat", ios::in);
    while(f.read((char *)&temp, sizeof(temp)))
    {
        temp.disp();
    }
    return 0;
}
