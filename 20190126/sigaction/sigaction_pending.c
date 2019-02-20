#include <func.h>
//sigaction实现2号信号，屏蔽3号信号的执行效果
//同时在2号信号的信号处理流程中，判断3号信号是否被挂起
void sigfunc(int signum,siginfo_t *p,void *p1)
{
    printf("before sleep %d is coming\n",signum);
    sleep(3);
    sigset_t pendSignal;
    sigpending(&pendSignal);
    if(sigismember(&pendSignal,SIGQUIT))
    {
        printf("SIGQUIT is pending\n");
    }else{
        printf("SIGQUIT is not pending\n");
    }
    printf("after sleep %d is coming\n",signum);
}
int main()
{
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_sigaction=sigfunc; 
    act.sa_flags=SA_SIGINFO;
    sigaddset(&act.sa_mask,SIGQUIT);
    int ret;
    ret=sigaction(SIGINT,&act,NULL);
    if(-1==ret)
    {
        perror("sigaction");
        return -1;
    }
    sigaction(SIGQUIT,&act,NULL);
    while(1);
    return 0;
}

