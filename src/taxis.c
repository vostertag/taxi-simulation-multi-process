#include "header/taxis.h"
#include "header/auxiliaire.h"

// Une vue plus globale de chaque fonction est disponible dans les commentaires se trouvant dans header/taxis.h

// Affiche le numéro de taxi puis démarre la fonction réceptionnant les demandes
int main(int argc,char* argv[]){
    int nbTaxi = atoi(argv[1]);
    printf("Taxi numéro %d \n", nbTaxi);
    receive();
    return 0;
}

// Fonction réceptionnant et prenant en charge les demandes
void receive(){
    // Réupértation de la message queue
    int msqid;
    key_t key;
    struct msgbuf rcvbuffer;
    size_t buflen;
    setUpMsgQueue(&key, &msqid, &rcvbuffer, &buflen);

    // Varaibles utiles
    char *nom = malloc(MAXSIZE);    // nom d'un client
    int attente;                    // temps de la course
    bool continu = true;            // Pour s'avoir quand arrêter ce processus (quand readData aura été interrompu par l'utilisateur)

    // Tant qu'aucun message indiquant qu'il faut arrêter par readData est envoyé
    while(continu){
        if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 1, 0) < 0)
            exit(0);
        if(strcmp(rcvbuffer.mtext, "end") == 0){            // Signal d'arrêt
            continu = false;                                // On stop le processus
        }else{
            sscanf(rcvbuffer.mtext, "%s ;%d", nom, &attente);   // Lecture du message envoyé 
            printf("Prise en charge de la demande de %s, de retour dans %d secondes... \n", nom, attente);  // affichage
            compteARebours(attente);    // Le processus dort et affiche un compte à rebours le temps de la course
            printf("De retour ! \n");
            attente = 0;                // Le taxi est prêt, il n'y a plus d'attente car sa course est maintenant finie
        }
    }

}