#ifndef VMSTATS_H
#define VMSTATS_H


// vmstats.h : définition des statistiques mémoire
// Explication :
// Cette structure est envoyée du noyau vers le programme utilisateur.
// Chaque champ représente un indicateur de l'état mémoire courant.


struct vmstats {
int pages_allocated; // pages physiques utilisées
int pages_free; // pages physiques libres
int page_faults; // défauts de page du processus courant
int heap_size; // taille du heap (sbrk)
int mymetric; // métrique personnelle
};


#endif