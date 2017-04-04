#include<iostream>
#include<fstream>
#include<string.h>
#include<cstdio>
using namespace std;

//class grade;
//class subject;
#include "user.cpp"

class admin:public user
{
public:
    char *get_user()
    {
        return id;
    }
    char *get_password()
    {
        return password;
    }
    void set_user(char *user)
    {
        strcpy(id, user);
    }
    void set_password(char *pass)
    {
        strcpy(password, pass);
        cout<<password;
    }
};



int main()
{
    admin a;
    a.set_user("admin");
    a.set_password("admin");
    fstream f;
    f.open("admin.dat", ios::out|ios::binary);
    f.write((char *)&a, sizeof(admin));
    f.close();
    return 0;
}
