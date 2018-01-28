#include "header/auxiliaire.h"

// LAUNCHER : Permet de lancer un processus lisant les demandes et les envoyant aux taxis ainsi que chaque processus de chaque taxi
// Ce programme fonctionne uniquement sous Linux

/**
* Fonction auxiliaire permettant de vérifier que les arguments donnés par l'utilisateur peuvent être utilisés
*
* @param argc nombre d'arguments
* @param argv liste des arguments
*/
void checkArguments(int argc, char *argv[]){
    if(argc != 2){
        printf("L'application nécessite un argument");
        exit(-1);
    }if(atoi(argv[1]) <= 0){
        printf("Le nombre de taxi doit être supérieur à 0 \n");
        exit(-1);
    }
}

/**
* Fonction main lançant les différent processus
*
* @param argc nombre d'arguments
* @param argv liste des arguments
*/
int main(int argc, char *argv[])
{
    // Vérification des arguments donnés par l'utilisateur
    checkArguments(argc, argv);

    int nbTaxi = atoi(argv[1]);             // Nombre de taxis (et donc de processus) à créer, donné par l'utilisateur
    char nbTaxi_str[5];                     // Conversion de ce nombre en string, utile pour les commandes à envoyer aux 
    sprintf(nbTaxi_str, "%d\"", nbTaxi);    // processus Taxi et readData
    int id = 1;                             // ID du processus créé
    char id_str[5];                         // ID en version string (utile pour les commandes envoyées aux processus)
    char* s;                                // Pour créer les commandes à envoyer dans system()
    char *cmd2 = "xterm -e \"./taxis ";                         // Commande pour ouvrir un processus taxi (il manque juste son id)
    char *cmd  = concat("xterm -e \"./readData ", nbTaxi_str);  // Commande pour ouvrir l'unique processus readData 

    // Pour chaque taxi à créer
    for (int i = 0; i < nbTaxi; ++i) {
        // On demande au parent de créer un nouveau processus
        if (fork() == 0) {
            // On récupère son id, l'ajoute à cmd2
            sprintf(id_str, "%d \"", id);
            s = concat(cmd2, id_str);
            // On demande à ce que le processus ./taxis soit éxecuté dans un nouveau terminal
            system(s);
            free(s);
            exit(0);
        }
        id++; 
    }

    // On demande à ce que le processus ./readData soit éxecuté dans un nouveau terminal
    system(cmd);

    return 0;
}