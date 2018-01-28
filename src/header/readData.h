#ifndef readData_h
#define readData_h

// Pour le processus lisant les demandes et les envoyant aux taxis

/**
* Fonction ouvrant le fichier où se trouve les demandes et le passe à "getAndSendDemandes" puis le referme ensuite
*
* @param nbTaxis nombre de taxis à utiliser
*/
void getDemandes(int nbTaxis);

/**
* Fonction lisant le fichier avec les demandes, lis les attentes et les demandes en affichant
* tout cela sur sa fenête et envoyant dans la queue toutes les demandes pour les taxis
*
* @param file fichier à lire avec les demandes
* @param nbTaxis nombre de taxis à utiliser
*/
void getAndSendDemandes(FILE *file, int nbTaxis);

#endif
