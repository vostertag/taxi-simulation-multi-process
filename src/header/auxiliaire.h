#ifndef auxiliaire_h
#define auxiliaire_h
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define _GNU_SOURCE
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#define MAXSIZE     128

/**
*	Regroupe certaines fonctions à utiliser plusieurs fois dans le programme
*/

// Structure d'un message dans le queue
typedef struct msgbuf
{
    long    mtype;
    char    mtext[MAXSIZE];
} msgbuf;

/**
* Fonction permettant de faire un compte à rebours de t secondes et de l'afficher
* 
* @param t temps (en secondes) du compte à rebous
*/
void compteARebours(int t);

/**
* Fonction permettant de mettre en place correctement la queue dans les processus
*
*	@param key clé de la queue
*	@param msqid id de la queue
*	@param sbuf message de la queue
*	@param buflen taille du message à envoyer
*/
void setUpMsgQueue(key_t* key,int* msqid, msgbuf* sbuf, size_t* buflen);

/**
* Fonction permettant de concaténer s1 et s2
*
* @param s1 string à concaténer avec s2
* @param s2 string à concaténer avec s1
* @return nouvelle string = s1 + s2
*/
char* concat(const char *s1, const char *s2);

#endif