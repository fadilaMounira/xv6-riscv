# Projet XV6 : Conception d’un système d’exploitation avancé

## Auteur
LANGOUL FADILA MARIAMA MOUNIRA 

---

## 1. Description du projet

Ce projet a pour objectif de modifier et d’étendre le noyau xv6 pour explorer des fonctionnalités avancées de systèmes d’exploitation. 
Il comprend trois axes principaux : 

1. l'ajout de l'**Appel système** : `getvmstats()`
   - Fournit un instantané des statistiques mémoire globales.
   - Champs retournés :
     - `pages_allocated` : nombre de pages physiques utilisées
     - `pages_free` : nombre de pages libres
     - `page_faults` : nombre total de défauts de page depuis le démarrage
     - `heap_size` : taille du heap utilisateur
     - `metric` : champ réservé pour métriques supplémentaires
 

2. **Ordonnanceur expérimental** : **Lottery Scheduler**
   - Chaque processus se voit attribuer un nombre de tickets.
   - La sélection du processus à exécuter est aléatoire, pondérée par les tickets.  
   - Permet de tester la répartition CPU entre plusieurs processus avec différents nombres de tickets.  

3. **Extension mémoire avancée** : **Lazy Allocation** 
   - Les pages sont réservées via `sbrk()` mais **non allouées physiquement**. 
   - La première écriture sur une page déclenche un **défaut de page** et provoque son allocation. 
   - Objectif pédagogique : comparer l’état mémoire avant/après pour observer l’efficacité de la stratégie et le comportement des défauts de page.

---
compilation:
vous devez disposer d'un environnement qemu remplissant ces critères:
QEMU = qemu-system-riscv64
MIN_QEMU_VERSION = 7.2(version minimale)

Lancer l'exécution de xv6-riscv dans le shell:
cd xv6-riscv
make clean
make
make qemu


Dans le shell de xv6:
Appel système des statistiques mémoires 
$./memalloc

test ordonnancement lottery scheduler
$./lotterytest

test allocation paresseuse de la mémoire
$./lazytest
