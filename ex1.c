#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

int main()
{
	int tube[2], pid, state, taille_message = 50;
	char message[taille_message];

	if(pipe(tube))
	{
		perror("tube ");
		exit(EXIT_FAILURE);
	}

	pid = fork();

	if(pid < 0)
	{
		perror("fork ");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0)
	{
		read(tube[0], message, taille_message);
		printf("Je suis le fils. Voici le message : %s\n", message);
		close(tube[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("Saisir un message.\n");
		scanf("%49s", message);
		write(tube[1], message, taille_message);
		close(tube[1]);
		waitpid(&pid, &state, NULL);
	}
}