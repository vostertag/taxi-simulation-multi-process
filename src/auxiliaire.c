#include "header/auxiliaire.h"

// Une vue plus globale de chaque fonction est disponible dans les commentaires se trouvant dans header/auxiliaire.h
// Contient des fonctions utiles à tous les autres programmes

// Fonction permettant de faire et afficher un compte à rebours de t secondes
void compteARebours(int t){
    printf("Secondes restantes : %d ", t);
    fflush(stdout);
    for(int i=t; i>0; i--){
        sleep(1);			// on attend une seconde
        t--;
        printf("%d ", t);	// On affiche le temps restant
        fflush(stdout);
    }
    printf("\n");
}

// Permet de mettre en place la message queue
void setUpMsgQueue(key_t* key,int* msqid, msgbuf* sbuf, size_t* buflen){
    int msgflg = IPC_CREAT | 0666;
    *key = 1234;
    if ((*msqid = msgget(*key, msgflg )) < 0)   //Get the message queue ID for the given key
        exit(0);
    sbuf->mtype = 1;
}

// Permet d'obtenir result = s1 + s2
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}