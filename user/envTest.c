#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"
#include "kernel/memlayout.h"
#include "kernel/riscv.h"

void env(int size, int interval, char* env_name) {
    int result = 1;
    int loop_size = 1000000;
    int n_forks = 1;
    int originPid = getpid();
    printf("%d", originPid);
    for (int i = 0; i < n_forks; i++) {
        fork();
    }
    int pid = getpid();
    for (int i = 0; i < loop_size; i++) {
        if (i % (loop_size/100) == 0) {
        	if (pid == originPid) {
        		printf("%s %d/%d completed.\n", env_name, i, loop_size);
        	}
        }
       if ((i % interval == 0)) {
            result = result * size;
            //sleep(1);
        }
    }
    if (pid == originPid)
    {
        wait(0);
    }
    else
    {
        exit(0);
    }
    printf("\n");

}

void env_large() {
    env(100000000, 100000, "env_large");
}

void env_freq() {
    env(10, 10, "env_freq");
}

int
main(int argc, char *argv[])
{
    env_large();
    //env_freq();
    print_stats();
    exit(0);
}