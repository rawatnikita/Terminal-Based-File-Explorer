#include "header.h"
string getFileMode(struct  stat buf)
{
    string fmode="";
    if (S_ISREG(buf.st_mode))
    fmode+='r';
    else if(S_ISDIR(buf.st_mode))
    fmode+='d';
    else
    fmode+='-';
    if(buf.st_mode & S_IRUSR)
     fmode+="r";
     else
     fmode+="-";
    if(buf.st_mode & S_IWUSR)
            fmode+="w";
    else
    fmode+="-";
   if(buf.st_mode &  S_IXUSR)
            fmode+="x";
    else
    fmode+="-";
      if(buf.st_mode & S_IRGRP)
     fmode+="r";
     else
     fmode+="-";
    if(buf.st_mode & S_IWGRP)
            fmode+="w";
    else
    fmode+="-";
    if(buf.st_mode & S_IXGRP)
            fmode+="x";
    else
    fmode+="-";
      if(buf.st_mode & S_IROTH)
     fmode+="r";
     else
     fmode+="-";
    if(buf.st_mode & S_IWOTH)
            fmode+="w";
    else
    fmode+="-";
    if(buf.st_mode & S_IXOTH)
            fmode+="x";
    else
    fmode+="-";
    //fmode+="\t";
    return fmode;

}
vector<char*> path;
void listFiles(const char* dirname)
{ 
        DIR* lst=opendir(dirname);
        if(lst==NULL)
        return;
        if(chdir(dirname)==-1)
        return; 
        struct dirent* contents;
        path.clear();

        while((contents=readdir(lst))!=NULL) //store file and directory names in vector
        path.push_back(contents->d_name); 
        int x,y;
        windowSize(&x,&y);
        x-=1;
        int len=x<path.size()?x:path.size();
       display(0,len);
}
void positionCursor(int x,int y)
{
cout<<"\033["<<x<<";"<<y<<"H";
}
void display(int start,int end)
{
       cout<<"\033c";
        for(int i=start;i<end;i++)
        {
        struct stat buf;
        stat(path[i],&buf);
        string fmode="";
        fmode=getFileMode(buf);
        string s=string(path[i]);
        if(s.length()>12)
        s=s.substr(0,12)+"...";
        cout<<std::left<<std::setw(20) <<s;
        cout<<std::left<<std::setw(20) <<fmode;
        cout<<std::left<<std::setw(10) <<buf.st_uid;
        cout<<std::left<<std::setw(10) <<buf.st_gid;
        int size=buf.st_size/1024;
        s=to_string(size)+" KB";
        cout<<std::left<<std::setw(10) <<s;
        cout<<std::left<<std::setw(10) <<ctime(&buf.st_mtime);
        } 
      
}

