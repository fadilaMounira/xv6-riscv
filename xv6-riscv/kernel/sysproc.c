#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "vm.h"
#include "vmstats.h"

#define MAX_TICKETS 100

void getvmstats(struct vmstats *stats);


uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  kexit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return kfork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return kwait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int t;
  int n;

  argint(0, &n);
  argint(1, &t);
  addr = myproc()->sz;

  if(t == SBRK_EAGER || n < 0) {
    if(growproc(n) < 0) {
      return -1;
    }
  } else {
    // Lazily allocate memory for this process: increase its memory
    // size but don't allocate memory. If the processes uses the
    // memory, vmfault() will allocate it.
    if(addr + n < addr || addr + n > TRAPFRAME)
      return -1;
    myproc()->sz += n;
  }
  myproc()->heap_sz = myproc()->sz;
  return addr;
}

uint64
sys_pause(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kkill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// sys_getvmstats : reçoit un pointeur user, remplit et copie vers user.
// Explication :
// Le programme utilisateur passe un pointeur vers une structure vide.
// Le noyau remplit une structure interne puis la copie vers l'utilisateur.

uint64
sys_getvmstats(void)
{
  uint64 user_addr;

  // Récupérer l'adresse utilisateur passée en argument
  argaddr(0, &user_addr);

  // Créer une structure interne (noyau)
  struct vmstats stats;
  getvmstats(&stats);

  // Copier vers l'espace utilisateur
  if(copyout(myproc()->pagetable, user_addr, (char *)&stats, sizeof(stats)) < 0)
    return -1;

  return 0;
}

uint64
sys_settickets(void)
{
  int n;

  argint(0, &n);

  if(n < 0)
    return -1;

  if(n < 1)
    n = 1;
  if(n > MAX_TICKETS)
    n = MAX_TICKETS;

  myproc()->tickets = n;
  return 0;
}

