/****************************************************************
            Copyright (C) 2014 All rights reserved.
					      									  
    > File Name:         < sigaction.c >
    > Author:            < Shawn Guo >
    > Mail:              < iseanxp+code@gmail.com >
    > Created Time:      < 2014/06/19 >
    > Last Changed: 
    > Description:		sigaction()

	the signal is an event generated by the UNIX and Linux systems in response to some condition, 
	upon receipt of which a process may in turn take some action. 

	#include <signal.h>  
	//sig, 信号; func, 信号处理函数;	
	void (*signal(int sig, void (*func)(int)))(int);  

	sigaction函数的功能是检查或修改与指定信号相关联的处理动作（可同时两种操作）。
	给信号signum设置新的信号处理act， 同时保留该信号原有的信号处理oldact
	//act, sigaction结构体指针, 表示对sig信号的新动作;
	//oact, sigaction结构体指针, 表示对sig信号的旧动作;
	int sigaction(int sig, const struct sigaction *act, struct sigaction *oact); 
	
	sigaction结构体:
		void (*sa_handler)(int);	处理函数指针，相当于signal函数的func参数。
		sigset_t sa_mask; 指定一个信号集，在调用sa_handler所指向的信号处理函数之前， 该信号集将被加入到进程的信号屏蔽字中。
						  信号屏蔽字是指当前被阻塞的一组信号，它们不能被当前进程接收到.
						  sa_mask的值通常是通过使用信号集函数来设置的;
						  sa_mask的意义, 是防止在信号处理函数建立之前, 接受到某类信号, 此时还无法对信号进行处理.(先)
										也可以防止信号处理函数执行期间, 再次遇到信号;
		int sa_flags;	信号处理选项;
						SA_INTERRUPT 由此信号中断的系统调用不会自动重启
						SA_RESTART 由此信号中断的系统调用会自动重启
						SA_SIGINFO 提供附加信息,一个指向siginfo结构的指针以及一个指向进程上下文标识符的指针
		void (*sa_sigaction)(int, siginfo_t *, void *); (只有设置SA_SIGINFO才会用到.)

信号集函数:
	int sigemptyset(sigset_t *set); 		//功能：初始化，清空信号集set 
	int sigfillset(sigset_t *set); 			//功能：将所有信号加入信号集set 
	int sigaddset(sigset_t *set,int signum);//功能：在信号集set中添加一个信号signum
	int	sigdelset(sigset_t *set,int signum); 	//功能：从信号集set中删除一个信号signum
	int sigismember(const sigset_t *set,int signum); //功能：测试信号signum是否属于信号集set

>>>>>>>>>>>>>>>>>

	SIG_IGN	( Ignore the signal. )
	SIG_DFL (Restore default behavior.)
****************************************************************/


#include <stdio.h>
#include <signal.h>		//signal(),  
#include <unistd.h>  

void ouch(int sig)  
{  
	printf("\nOUCH! - I got signal %d\n", sig);  
}  

int main()  
{  
	struct sigaction act;  
	//配置struct sigaction;
	act.sa_handler = ouch;	//设置处理函数 
	//设置屏蔽信号集合(使用信号集函数进行操作)
	//创建空的信号屏蔽字，即不屏蔽任何信息  
	sigemptyset(&act.sa_mask);  

	//sigaddset(&act.sa_mask, SIGQUIT); //这一使用此行一句, 实现在信号处理函数执行期间, 屏蔽SIGQUIT信号;

	//使sigaction函数重置为默认行为  
	act.sa_flags = SA_RESETHAND; 	//调用一次以后, 将信号处理函数还原为默认,即只响应一次信号;

	sigaction(SIGINT, &act, 0); 	//在此调用之前,信号处理函数尚未建立,如何处理信号由sa_mask确定. 

	//因为存在SA_RESETHAND, 此程序只能触发1次ouch.
	while(1)  
	{  
		printf("Hello World!\n");  
		sleep(1);  
	}  

	return 0;  
}  
