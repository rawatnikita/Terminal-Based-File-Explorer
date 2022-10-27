#include "header.h"
stack<char*> bkd;
stack <char*> fwd;
void windowSize(int *rows,int *cols)//find size of terminal
{
  struct winsize ws;
  if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&ws)!=-1 && ws.ws_col!=0)
  {
    *rows=ws.ws_row;
    *cols=ws.ws_col;
  }
}

void openEditor(char *name)
{
  char *args[3];
  string vim="vi";
  args[0]=(char*)vim.c_str();
  args[1]=name;
  args[2]=(char*)0;
  pid_t pid=fork();
  if(pid == 0)
  {
    if(execvp(args[0],args)== -1)
    {
      perror("exec");
    }
    exit(0);
  }
  if(pid>0)
  {
    wait(0);
 // listFiles(get_current_dir_name());
  }
}

void navigate()
{
    int rows,col;
    printf("\x1b[1H");
    char c;
    int cursorRow=1;//stores location of cursor
    int start=0,end;//indices that determine which valus of vector should be displayed
    windowSize(&rows,&col);
    rows-=1;
    end=rows<path.size()?rows:path.size();//check if number of directory entries exceed the terminal size
    while(true)
    {
        char c=getchar();
        if(c=='\x1b')
        {
            c=getchar();
            if(c=='[')
            {
                c=getchar();
                if(c=='A')//up arrow key
                {
                    if(cursorRow>1)
                    {
                        cursorRow--;
                        printf("\x1b[1A");
                    }
                    else if(cursorRow==1 && start>0)
                    {
                        start--;
                        end--;
                        display(start,end);
                        printf("\033[H");
                    }
                }
                else if(c=='B')//down  arrow key
                {
                    if(cursorRow<(end-start))
                    {
                      cursorRow++;
                      printf("\x1b[1B");
                    }
                    else if(cursorRow==(end-start) && end<path.size())
                    {
                      start++;
                      end++;
                      display(start,end);
                      positionCursor(cursorRow,1);
                    }
                }
                else if(c=='D')//left arrow key
                {
                    if(!bkd.empty())
                    {
                      char* s=bkd.top();
                      fwd.push(bkd.top());
                      bkd.pop();
                      listFiles(s);
                      cursorRow=1;
                      start=0;
                      end=rows<path.size()?rows:path.size();
                      printf("\033[H");
                    }
                }
                else if(c=='C')//right arrow
                {
                   if(!fwd.empty())
                    {
                      char* s=fwd.top();
                      bkd.push(get_current_dir_name());
                      fwd.pop();
                      listFiles(s);
                      cursorRow=1;
                      start=0;
                      end=rows<path.size()?rows:path.size();
                      printf("\033[H");
                    }
                }
            }
        }
       else if(c=='k')
       {  
         if(cursorRow>1)
          {
             cursorRow--;
             printf("\x1b[1A");
          }
           else if(cursorRow==1 && start>0)
           {
              start--;
              end--;
              display(start,end);
              printf("\033[H");
           }
       }
        else if(c=='l')
        {
        if(cursorRow<(end-start))
           {
            cursorRow++;
               printf("\x1b[1B");
            }
        else if(cursorRow==(end-start) && end<path.size())
          {
               start++;
              end++;
             display(start,end);
               positionCursor(cursorRow,1);
           }
        }
        else if((int)c==10)
        {
            
            if(strcmp(path[start+cursorRow-1],".")==0)
            continue;
            else
            {
                struct stat buf;
                stat(path[start+cursorRow-1],&buf);
                if(S_ISDIR(buf.st_mode))
                {
                  bkd.push(get_current_dir_name());
                  listFiles(path[start+cursorRow-1]);
                  cursorRow=1;
                  start=0;
                  end=rows<path.size()?rows:path.size();
                  printf("\033[H");
                }
                else if(S_ISREG(buf.st_mode))
                {
                openEditor(path[start+cursorRow-1]);
                //cursorRow=1;
                }

            }
        }
        else if(c==':')
        {
            cmdMode();
        }
        else if(c=='h')
        {
           if(strcmp(get_current_dir_name(),apphome.c_str())!=0)
          {
            while(!fwd.empty())
            fwd.pop();
            bkd.push(get_current_dir_name());
            listFiles(apphome.c_str());
            cursorRow=1;
            start=0;
            end=rows<path.size()?rows:path.size();
            printf("\033[H");
          }
        }
        else if(c==(char)127)//backspace
        {
          
          if(strcmp(get_current_dir_name(),home.c_str())!=0)
          {
          while(!fwd.empty())
          fwd.pop();
         bkd.push(get_current_dir_name());
        listFiles("..");
        cursorRow=1;
        start=0;
        end=rows<path.size()?rows:path.size();
        printf("\033[H");
          }
        }
        else if(c=='q')
        exit(0);
       fflush(stdin); 
    }

}


