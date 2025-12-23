#include "kernel/types.h"
#include "user/user.h"
#include "../kernel/vmstats.h"

#define PAGE 4096      // taille d'une page


// Programme de test pour getvmstats()

int main()
{
  struct vmstats s;
  printf("TEST GETVMSTATS\n");
  if(getvmstats(&s) < 0){
    printf("Erreur : getvmstats a echoué\n");
    exit(1);
  }

  printf("Pages allouees : %d\n", s.pages_allocated);
  printf("Pages libres    : %d\n", s.pages_free);
  printf("Defauts de page : %d\n", s.page_faults);
  printf("Heap size       : %d\n", s.heap_size);
  printf("Metr. perso     : %d\n", s.mymetric);

  printf("Début du test mémoire\n");

  for(int i = 0; i < 10; i++){
    char *p = sbrk(PAGE);
    if(p == (char*)-1){
      printf("Erreur sbrk\n");
      exit(1);
    }

    // Forcer l'utilisation réelle de la page
    //p[0] = 1;
    //p[PAGE-1] = 1;

    getvmstats(&s);

    printf("Étape %d\n", i+1);
    printf("Pages allouées : %d\n", s.pages_allocated);
    printf("Pages libres   : %d\n", s.pages_free);
    printf("Defauts de page : %d\n", s.page_faults);
    printf("Heap size      : %d\n", s.heap_size);
    printf("Mymetric       : %d\n", s.mymetric);
    printf("---------------------\n");
  }

    printf("Fin du test\n");
    exit(0);
}

