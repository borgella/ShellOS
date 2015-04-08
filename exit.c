#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(int agrc, char*argv[]){
	
	kill(getppid(),SIGKILL);	
    return 0;
}
