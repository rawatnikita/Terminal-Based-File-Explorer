#include "header.h"
#define BUFSIZE 2048

string getDest(string d)
{
  string dest="";
  if(d[0]=='/')
  dest=d;
  else if(d[0]=='~') //~ stands for directory where application was started
  dest=apphome+d.substr(1);
  else if(d==".")
  dest=string(get_current_dir_name());
  else if(d[0]=='.')//for inputs like ./file.txt
  dest=string(get_current_dir_name())+d.substr(1);
  else  //for inputs like filename.txt
  dest=string(get_current_dir_name())+"/"+d;
  //cout<<dest<<endl;
 return dest;
}
void copyfile(string s,string d)
{
   int fd=open(s.c_str(),O_RDONLY,0);
    if(fd==-1)
    { 
      printf("%s\n",strerror(errno));
      return;
    }
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH|S_IWGRP|S_IWOTH;
      int fd2=open(d.c_str(),O_WRONLY|O_CREAT|O_TRUNC,mode);
      ssize_t len;
      char buff[BUFSIZ];
      struct stat arr;
      while ((len = read(fd, buff, BUFSIZ)) > 0)
      {
        write(fd2, buff, len);
      }
     
      lstat(s.c_str(),&arr);
      chmod(d.c_str(),arr.st_mode);
      close(fd);
      close(fd2);

}   
void copyDirectory(string src,string dest)
{
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH|S_IWGRP|S_IWOTH;
  int  fd=mkdir(dest.c_str(),mode);
  if(fd==-1)
  exit(0);
  DIR *cur=opendir(src.c_str());
  if(cur)
  {
    struct dirent *f;
    while((f=readdir(cur))!=NULL)
    {
      string s,d;
      s=src+"/"+string(f->d_name);
      d=dest+"/"+string(f->d_name);
      struct stat buf;
      lstat(s.c_str(),&buf);
      if(strcmp(f->d_name,".")==0 || strcmp(f->d_name,"..")==0)
      continue;
      else if(S_ISDIR(buf.st_mode))
      copyDirectory(s,d);
      else if(S_ISREG(buf.st_mode))
      copyfile(s,d);
    }
    closedir(cur);
  }
}
void searchFiles(string curdir,string filename,bool *x)
{ 
  if(*x==true)
  return;
  DIR* homed=opendir(curdir.c_str());
  if(homed==NULL)
  return; 
  struct dirent *f;
  while((f=readdir(homed))!=NULL)
  {
    if(*x==true)
    break;
      if((strcmp(f->d_name,".")==0) || (strcmp(f->d_name,".."))==0)
      continue;
      struct stat buf;
      string path=curdir+"/"+f->d_name;
      lstat(path.c_str(),&buf);
        if(strcmp(f->d_name,filename.c_str())==0)
        {
        *x=true; 
        break;
        }
      else if(S_ISDIR(buf.st_mode))
      searchFiles(path,filename,x);   
  }
    closedir(homed);
}

         
      
void movefd(vector<string> &cmd)
{
    string dest=getDest(cmd[cmd.size()-1]);
    string temp=dest;
    for(int i=1;i<cmd.size()-1;i++) //loop to move multiple files/directories
    {
      dest+="/"+cmd[i];
      if(rename(cmd[i].c_str(),dest.c_str())==-1)
      printf("%s\n",strerror(errno));
      dest=temp;
    }
}
void deleteDirectory(string path)
{
    DIR* curdir=opendir(path.c_str());
    if(curdir==NULL)
    return;
    struct dirent* f;
    while((f=readdir(curdir))!=NULL)
    {
      if((strcmp(f->d_name,".")==0) || (strcmp(f->d_name,"..")==0))
      continue;
      struct stat buf;
      string s=path+"/"+f->d_name;
      lstat(s.c_str(),&buf);
      if(S_ISDIR(buf.st_mode))
      deleteDirectory(s);
      else if(S_ISREG(buf.st_mode))
      unlink(s.c_str());
      
    }
    rmdir(path.c_str());
    closedir(curdir);
}
void createDirectory(vector<string> &cmd)
{
    string dest=getDest(cmd[cmd.size()-1]);
    string temp=dest;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH|S_IWGRP|S_IWOTH;
    for(int i=1;i<cmd.size()-1;i++)
    {
    dest+="/"+cmd[i]; 
    if(mkdir(dest.c_str(),mode)==-1)
    printf("%s\n",strerror(errno));
    dest=temp;
    }
  
}
void createfile(vector<string> &cmd)
{
    string dest=getDest(cmd[cmd.size()-1]);
    for(int i=1;i<cmd.size()-1;i++)
    {
      string p=dest+"/"+cmd[i];
      mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH|S_IWGRP|S_IWOTH;
     char ph[100];
      strcpy(ph,p.c_str());
      int fd=open(ph, O_WRONLY|O_CREAT|O_TRUNC, mode);
      if(fd==-1)
      printf("%s\n",strerror(errno));
      close(fd);
    }
}
void gotoDirectory(string path)
{
  string dest=getDest(path);
  if(chdir(dest.c_str())==-1)
  printf("%s\n",strerror(errno));
}
void executeCommand(vector<string> &cmd)
{
  if(cmd[0]=="create_file")
  createfile(cmd);
  else if(cmd[0]=="copy")
  {
    string s,d;
    //s=getDest(cmd[1]);
    d=getDest(cmd[cmd.size()-1]);
    for(int i=1;i<cmd.size()-1;i++)
    {
      string temp;
      temp=d+"/"+cmd[i];
      s=getDest(cmd[i]);
      struct stat buf;
      lstat(s.c_str(),&buf);
      if(S_ISDIR(buf.st_mode))
      copyDirectory(s,temp);
      else
      copyfile(s,temp);  
    }
  }
  else if(cmd[0]=="rename")
  {if((rename(cmd[1].c_str(),cmd[2].c_str()))==-1)
  printf("%s\n",strerror(errno));
  }
  else if(cmd[0]=="create_dir")
  createDirectory(cmd);
  else if(cmd[0]=="move")
  movefd(cmd);
  else if(cmd[0]=="delete_file")
  {
    for(int i=1;i<cmd.size();i++)
    {
    string s=getDest(cmd[i]);
    if(unlink(s.c_str())==-1)
    printf("%s\n",strerror(errno));
    }
  }
  else if(cmd[0]=="delete_dir")
  deleteDirectory(getDest(cmd[1]));
  else if(cmd[0]=="goto")
  {
    bkd.push(get_current_dir_name());
    gotoDirectory(cmd[1]);
  }
  else if(cmd[0]=="search")
  {
    bool x=false;
    char cur[256];
    getcwd(cur,256);
  searchFiles(string(cur),cmd[1],&x);
  if(x==true)
    printf("True\n");
    else
    printf("False\n");
  
  }  

}
void cmdMode()
{
    canonicalMode();
    int r,c;
    printf("\x1b[999B");//move the cursor to end of terminal
    printf(":");
    string command;
    vector<string> v;
    string s="";
    
   while(true)
    {
      cin>>s;
      v.push_back(s);
      if(s=="\x1b")
    {
      noncanonicalMode();
      listFiles(get_current_dir_name());
    break;
    }
    if(s=="q")
    {
      
    exit(0);
    break;
    }
      if(cin.peek()=='\n')//whenever enter is pressed we execute the command
     { 
       if(v.size()!=0)
       executeCommand(v);
       v.clear();
       s="";

    }

    }
   
 
}
