#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

/*void Fork(int* fils)
{
	*fils = fork();
	if(fils < 0)
	{
		perror("fork ");
		exit(EXIT_FAILURE);
	}
	else if(fils == 0)
	{

		exit(EXIT_SUCCESS);
	}
}*/

int main()
{
	int tube1[2], tube2[2], pidf1, pidf2, state, taille_message = 50;
	char message[taille_message];
	char recu[taille_message];

	//Initialisation des tubes
	if(pipe(tube1))
	{
		perror("tube ");
		exit(EXIT_FAILURE);
	}
	
	if(pipe(tube2))
	{
		perror("tube ");
		exit(EXIT_FAILURE);
	}

	//On lance les forks
	pidf1 = fork();
	if(pidf1 < 0)
	{
		perror("fork ");
		exit(EXIT_FAILURE);
	}
	else if(pidf1 == 0)
	{
		printf("saisir un message\n");
		scanf("%s", message);
		write(tube1[1], message, taille_message);
		read(tube2[0], recu, taille_message);
		printf("fils 1 msg recu : %s\n", recu);

		close(tube1[1]);
		close(tube2[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		pidf2 = fork();
		if(pidf2 < 0)
		{
			perror("fork ");
			exit(EXIT_FAILURE);
		}
		else if(pidf2 == 0)
		{
			read(tube1[0], recu, taille_message);
			printf("fils 2 msg recu : %s\n", recu);
			write(tube2[1], recu, taille_message);

			close(tube1[0]);
			close(tube2[1]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(&pidf1, &state, NULL);
			waitpid(&pidf2, &state, NULL);
		}
	}
}