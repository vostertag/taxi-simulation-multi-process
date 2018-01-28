#include <stdbool.h>
#include "header/auxiliaire.h"
#include "header/readData.h"

// Une vue plus globale de chaque fonction est disponible dans les commentaires se trouvant dans header/taxis.h

// Fonction main
int main(int argc, char* argv[]){
    int nbTaxis = atoi(argv[1]);    // nombre total de taxi
    getDemandes(nbTaxis);
    return 0;
}

// Fonction ouvrant le fichier où se trouve les demandes et le passant à la fonction les traitant
void getDemandes(int nbTaxis){
	FILE *file;
    file = fopen("data/demandes.dat", "r"); // Ouverture du fichier
    getAndSendDemandes(file, nbTaxis);      // Envoie à la fonction les traitant
    fclose(file);                           // Fermeture du fichier
}

void getAndSendDemandes(FILE *file, int nbTaxis)
{
    // Initialisation de la queue de message
    key_t key;
    int msqid; 
    msgbuf sbuf; 
    size_t buflen;
    setUpMsgQueue(&key, &msqid, &sbuf, &buflen);

    // Variables utiles
    bool attente = true;            // Pour savoir si on récupère un temps d'attente ou une nouvelle commande
    int attenteTemps;               // Temps à attendre avant une nouvelle demande
    char *nom = malloc(MAXSIZE);    // Stockera le nom du client

    // Tant que le fichier n'est pas lu en entier
    printf("Demandes : \n");
    while(!feof(file)){
        // Si on a pas encore lu un temps d'attente avant la prochaine course
        if(attente){
            fscanf(file, "%d ", &attenteTemps);                 // On récupère le temps d'attente 
            printf("En attente d'un nouveau client... \n");
            compteARebours(attenteTemps);                       // On affiche ce temps d'attente avec un compte à rebours
            attente = false;    // On indique que la prochaine ligne sera une demande, pas un temps d'attente
        // Sinon, on a une nouvelle demande à traiter
        }else{
            fscanf(file, "%[^\n]%*c", sbuf.mtext);              // Lecture de la demande
            buflen = strlen(sbuf.mtext) + 1 ;                   // Taille du message à envoyer dans la queue
            attente = true;                                     // On indique qu'à la prochaine ligne du fichier, on récupèrera un temps d'attente
            // Envoie de la demande aux taxis dans la queue
            if(msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT)<0){
                printf("loupé \n");
            }else{
                sscanf(sbuf.mtext, "%s ;%d", nom, &attenteTemps);       // Récupération des informations utiles pour la demande et affichage
                printf("\n%s demande une course d'une durée de %d secondes \n\n", nom, attenteTemps);
                attenteTemps = 0;
            }
        }
    }

    // On a fini de lire le fichier, on se prépare donc à envoyer un message d'arrêt aux taxis quand l'utilisateur le voudra
    strcpy(sbuf.mtext, "end");
    buflen = strlen(sbuf.mtext) + 1 ;

    // Dès que l'utilisateur entre une touche, on arrêtera le programme
    printf("Appuyez sur ENTREE pour finir le programme... \n");  
    getchar(); 

    // Envoie des messages de stop. Un pour chaque taxi
    for(int i=0; i<nbTaxis; i++){
        msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT);
    }
}
