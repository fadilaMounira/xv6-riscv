/*#include "kernel/types.h"
#include "user/user.h"

void spawn(int tickets)
{
  int pid = fork();
  if(pid == 0){
    settickets(tickets);
    exec("cpuburn", (char*[]){"cpuburn", 0});
    exit(1);
  }
}

int
main(void)
{
  spawn(10);
  spawn(50);
  spawn(200);
  wait(0);
  wait(0);
  wait(0);
  exit(0);
}
#include "kernel/types.h"
#include "user/user.h"



void spawn_and_set(int tickets) {
    int pid = fork();
    if(pid < 0){
        printf("fork failed\n");
        exit(1);
    }
    if(pid == 0){
        if(tickets > MAX_TICKETS) tickets = MAX_TICKETS;
        settickets(tickets);
        printf("child %d: tickets=%d\n", getpid(), tickets);

        char *args[] = {"cpuburn", 0};
        exec("cpuburn", args);

        printf("exec cpuburn failed\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    printf("Starting lottery test with max tickets %d\n", MAX_TICKETS);

    spawn_and_set(10);
    spawn_and_set(15);
    spawn_and_set(20);  // plafond

    // attendre que les enfants terminent
    for(int i=0; i<3; i++)
        wait(0);

    printf("Parent finished, all children done\n");
    exit(0);
}*/



#include "kernel/types.h"
#include "user/user.h"

void
run(int tickets)
{
  settickets(tickets);

  char *argv[] = { "cpuburn", 0 };
  exec("cpuburn", argv);

  // exec ne retourne que s'il y a une erreur
  printf("exec cpuburn failed\n");
  exit(1);
}


int
main(void)
{
  int pids[3];
  int tickets[3] = {10, 5, 40};

  printf("Lottery scheduler test\n");

  for(int i = 0; i < 3; i++){
    pids[i] = fork();
    if(pids[i] == 0){
      run(tickets[i]);
    }
  }

  // le parent attend les enfants
  for(int i = 0; i < 3; i++){
    wait(0);
  }

  printf("Test finished\n");
  exit(0);
}
