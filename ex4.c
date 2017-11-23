#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds) // cross-platform sleep function
{
	#ifdef WIN32
	    Sleep(milliseconds);
	#elif _POSIX_C_SOURCE >= 199309L
	    struct timespec ts;
	    ts.tv_sec = milliseconds / 1000;
	    ts.tv_nsec = (milliseconds % 1000) * 1000000;
	    nanosleep(&ts, NULL);
	#else
	    usleep(milliseconds * 1000);
	#endif
}

void fonction(int s)
{
	printf("signal %d reçu \n",s);
}

int main()
{
	int s;
	int pid = 0;
	system("ps aux");
	printf("\nentrer un pid (NSIG = %d)\n", NSIG);
	scanf("%d", &pid);

	for (s = 1 ; s < NSIG ; s++)
	{  
		if(s != 9 && s != 19 && s != 32 && s != 33)
		{
			if(kill(pid, s) < 0)
			{
				perror("kill ");
				exit(EXIT_FAILURE);
			}
		}
		else
			printf("attention signal %d!\n", s);
		sleep_ms(500);
	}
	kill(pid, 9);
}