/* Simple Shell - Holberton School */

#include <stdio.h> /* Pour printf, fprintf, perror, et les fonctions standard d'entrée/sortie */
#include <stdlib.h> /* Pour malloc, free, getenv, exit, et les utilitaires généraux */
#include <unistd.h> /* Pour fork, execve, isatty, et autres appels système POSIX */
#include <string.h> /* Pour strtok, strdup, strlen, et autres opérations sur les chaînes */
#include <sys/types.h> /* Pour les types de données comme pid_t utilisés dans la gestion des processus */
#include <sys/wait.h> /* Pour wait, pour gérer la terminaison des processus enfants */
#include <sys/stat.h> /* Pour stat, pour vérifier les propriétés des fichiers */

extern char **environ; /* Déclare explicitement environ pour assurer la compatibilité */

#define PROMPT "$ "
#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 100

/* Prototypes des fonctions */
void print_prompt(void);
char *read_input(void);
void execute_command(char *input);
void print_env(void);
char *find_in_path(char *command);

/* Point d'entrée principal */
int main(void)
{
	char *input; /* Stocke l'entrée utilisateur provenant de l'entrée standard. */

	while (1)
	{
		print_prompt(); /* Affiche le prompt du shell. */
		input = read_input(); /* Lit l'entrée utilisateur. */
		if (input == NULL)
		{
			break; /* Quitte la boucle en cas de fin de fichier ou d'erreur. */
		}

		/* Gère les commandes intégrées. */
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break; /* Quitte le shell avec la commande "exit". */
		}
		if (strcmp(input, "env") == 0)
		{
			print_env(); /* Affiche les variables d'environnement. */
			free(input);
			continue; /* Continue la boucle pour la commande suivante. */
		}

		execute_command(input); /* Exécute une commande externe. */
		free(input); /* Libère la mémoire allouée pour l'entrée. */
	}

	return (0); /* Indique une exécution réussie. */
}

/* Affiche le prompt du shell si en mode interactif. */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO)) /* Vérifie si l'entrée provient d'un terminal. */
	{
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
	}
}

/* Lit l'entrée de l'utilisateur et la renvoie sous forme de chaîne. */
char *read_input(void)
{
	char *buffer; /* Alloue un tampon pour l'entrée utilisateur. */
	ssize_t bytes_read; /* Stocke le nombre d'octets lus. */

	if (MAX_INPUT_SIZE > 65536) /* Empêche une allocation excessive de mémoire. */
	{
		fprintf(stderr, "Error: MAX_INPUT_SIZE is too large\n");
		exit(EXIT_FAILURE);
	}

	buffer = malloc(MAX_INPUT_SIZE);
	if (!buffer)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	bytes_read = read(STDIN_FILENO, buffer, MAX_INPUT_SIZE - 1); /* Lit l'entrée. */
	if (bytes_read == 0) /* Gère explicitement la fin de fichier. */
	{
		free(buffer);
		return (NULL);
	}
	if (bytes_read < 0) /* Gère les erreurs de lecture. */
	{
		perror("read");
		free(buffer);
		return (NULL);
	}
	if ((size_t)bytes_read >= MAX_INPUT_SIZE - 1) /* Vérifie un dépassement de capacité. */
	{
		fprintf(stderr, "Input too long\n");
		free(buffer);
		return (NULL);
	}

	buffer[bytes_read - 1] = '\0'; /* Termine la chaîne avec un caractère nul. */
	return (buffer);
}

/* Exécute une commande en créant un processus enfant et en appelant execve. */
void execute_command(char *input)
{
	pid_t pid; /* Stocke l'ID du processus créé par fork(). */
	int status; /* Stocke le statut de sortie du processus enfant. */
	char *args[MAX_ARGS]; /* Tableau pour stocker les arguments de la commande. */
	char *token; /* Stockage temporaire pour chaque argument. */
	int i = 0; /* Index pour remplir le tableau args. */
	char *command_path; /* Chemin complet de la commande. */

	/* Découpe la chaîne d'entrée en arguments. */
	token = strtok(input, " ");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}

	args[i] = NULL; /* Termine le tableau d'arguments avec un pointeur nul. */
	if (args[0] == NULL) /* Gère les commandes vides. */
	{
		fprintf(stderr, "No command entered.\n");
		return;
	}

	/* Recherche la commande dans le PATH. */
	command_path = find_in_path(args[0]);
	if (command_path == NULL) /* Commande introuvable. */
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return;
	}

	pid = fork(); /* Crée un nouveau processus. */
	if (pid == -1) /* Gère les erreurs de fork. */
	{
		perror("fork");
		free(command_path);
		return;
	}
	if (pid == 0) /* Processus enfant. */
	{
		if (execve(command_path, args, environ) == -1) /* Exécute la commande. */
		{
			perror(args[0]);
			free(command_path);
			exit(EXIT_FAILURE);
		}
	}
	else /* Processus parent. */
	{
		if (wait(&status) == -1) /* Attend la fin du processus enfant. */
		{
			perror("wait");
		}
		free(command_path);
	}
}

/* Affiche toutes les variables d'environnement. */
void print_env(void)
{
	char **env; /* Déclare la variable itérative en dehors de la boucle pour respecter C90. */

	for (env = environ; *env != NULL; env++) /* Accède aux variables d'environnement globales. */
	{
		printf("%s\n", *env);
	}
}

/* Trouve le chemin complet d'une commande dans la variable d'environnement PATH. */
char *find_in_path(char *command)
{
	char *path;
	char *path_copy;
	char *dir;
	char *full_path;
	struct stat st; /* Stocke les informations sur le fichier pour vérification. */

	path = getenv("PATH"); /* Récupère la variable d'environnement PATH. */
	if (path == NULL || strlen(path) == 0) /* Valide le PATH. */
	{
		fprintf(stderr, "Error: Invalid PATH environment variable\n");
		return (NULL);
	}

	path_copy = strdup(path); /* Duplique PATH pour la tokenisation. */
	if (path_copy == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}

	dir = strtok(path_copy, ":"); /* Divise PATH en répertoires. */
	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2); /* Alloue de la mémoire pour le chemin complet. */

		if (full_path == NULL)
		{
			perror("malloc");
			free(path_copy);
			exit(EXIT_FAILURE);
		}

		sprintf(full_path, "%s/%s", dir, command); /* Construit le chemin complet. */
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR)) /* Vérifie les propriétés du fichier. */
		{
			if (S_ISLNK(st.st_mode)) /* Avertit si la commande est un lien symbolique. */
			{
				fprintf(stderr, "Warning: %s is a symbolic link\n", full_path);
			}
			free(path_copy);
			return (full_path); /* Retourne le chemin valide de la commande. */
		}

		free(full_path); /* Libère la mémoire si le chemin est invalide. */
		dir = strtok(NULL, ":"); /* Passe au répertoire suivant. */
	}

	free(path_copy); /* Libère le PATH dupliqué. */
	return (NULL); /* Retourne NULL si la commande n'est pas trouvée. */
}
