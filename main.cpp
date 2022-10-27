#include "header.h"
string home;
string apphome;
void resize(int sig)
{
    if(SIGWINCH==sig)
    {
        listFiles(get_current_dir_name());
        navigate();
    }
}
int main()
{
    struct passwd* pw=getpwuid(getuid());
    home=string(pw->pw_dir);
    apphome=string(get_current_dir_name());
    signal(SIGWINCH,resize);
    noncanonicalMode(); 
    return 0;
}