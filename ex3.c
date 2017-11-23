#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>

void fonction(int s)
{
	printf("signal %d reçu \n",s);
}

int main()
{
	int s;
	for (s = 1; s < NSIG; s++)
	{  
		if(signal(s,fonction) == SIG_ERR)
			printf("impossible d'attraper le signal no%d \n", s);
	}
	
	while(1) 
		pause();
}