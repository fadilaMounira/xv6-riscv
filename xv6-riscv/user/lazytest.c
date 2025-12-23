#include "kernel/types.h"
#include "user/user.h"
#include "../kernel/vmstats.h"

int main(void)
{
  struct vmstats s;

  printf("=== Etat initial ===\n");
  getvmstats(&s);
  printf("Pages allouees : %d\n", s.pages_allocated);
  printf("Pages libres   : %d\n", s.pages_free);
  printf("Page faults    : %d\n", s.page_faults);
  printf("Heap size      : %d\n", s.heap_size);
  printf("Metr. perso    : %d\n", s.mymetric);

  char *p = sbrk(5 * 4096);   // réservation uniquement

  printf("\n=== Apres sbrk(5 pages) ===\n");
  getvmstats(&s);
  printf("Pages allouees : %d\n", s.pages_allocated);
  printf("Pages libres   : %d\n", s.pages_free);
  printf("Page faults    : %d\n", s.page_faults);
  printf("Heap size      : %d\n", s.heap_size);
  printf("Metr. perso    : %d\n", s.mymetric);

  // Accès à la DERNIERE page
  p[4 * 4096] = 42;

  printf("\n=== Apres acces derniere page ===\n");
  getvmstats(&s);
  printf("Pages allouees : %d\n", s.pages_allocated);
  printf("Pages libres   : %d\n", s.pages_free);
  printf("Page faults    : %d\n", s.page_faults);
  printf("Heap size      : %d\n", s.heap_size);
  printf("Metr. perso    : %d\n", s.mymetric);
  exit(0);
}
