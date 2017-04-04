#include<cstring>
class user{
protected:
  char id[10];
  char password[50];
public:
  user(){
    password[0]=id[0]='\0';
  }
  user(char id[10],char password[40]){
    strcpy(this->id,id);
    strcpy(this->password,password);
  }

  virtual int login()
  {
    //do nothing
  }

  virtual int Register()
  {
    //do nothing
  }

  char* getUserid(){
    return id;
  }

  char* getPassword(){
    return password;
  }
};
