/*#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  volatile int i = 0;
  while(i < 100000000){
    i++;
  }
  exit(0);
}*/



#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  uint64 start = uptime();
  volatile uint64 i = 0;

  while(uptime() - start < 3000){ // ~30 secondes
    i++;                          // calcul pur
  }

  exit(0);
}

