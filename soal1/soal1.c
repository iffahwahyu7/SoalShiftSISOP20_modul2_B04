#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int cekhuruf(char* input){
	int i=0;
	for(i; i < strlen(input); i++){
    	if(isalpha(input[i])) return 1;
	}
  return 0;
}

int main(int argc, char *argv[]){
	pid_t pid, sid;        // Variabel untuk menyimpan PID

	pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
	if (pid < 0) {
    	exit(EXIT_FAILURE);
	}

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  	if (pid > 0) {
    	exit(EXIT_SUCCESS);
  	}

  	umask(0);

  	sid = setsid();
  	if (sid < 0) {
    	exit(EXIT_FAILURE);
  	}

  	if ((chdir("/")) < 0) {
    	exit(EXIT_FAILURE);
  	}

  	close(STDIN_FILENO);
  	close(STDOUT_FILENO);
  	close(STDERR_FILENO);
	
	while (1) {

	if(argc!=5){
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	
    time_t t = time(NULL);
    struct tm *tmp = gmtime(&t);
	int s = t % 60;
	int m = (t / 60) % 60;
    int h = (t / 3600) % 24;

	int sec, min, hour;

	if(strcmp(argv[1],"*") == 0) sec = s;
	else if(cekhuruf(argv[1])){
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	else sec = atoi(argv[1]);

	if(strcmp(argv[2],"*") == 0) min = m;
	else if(cekhuruf(argv[2])){
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	else min = atoi(argv[2]);

	if(strcmp(argv[3],"*") == 0) hour = h;
	else if(cekhuruf(argv[3])){
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	else hour = atoi(argv[3]);

	if(hour<0 || hour>23 || min<0 ||min>59 || sec<0 || sec>59){
		printf("Error\n");
		exit(EXIT_FAILURE);
	}

	char script[100];
	strcpy(script,argv[4]);
	int length = strlen(script);
	if(length<4 || script[100-(100-length)-3]!='.' || script[100-(100-length)-2]!='s' || script[100-(100-length)-1]!= 'h'){
		printf("Error\n");
		exit(EXIT_FAILURE);
	}

	if (s == sec && m == min && h == hour){
		pid_t pid1 =  fork();
		if(pid1 == 0) {
			char *arg[] = {"bash", argv[4] , NULL};
			execv("/bin/bash", arg);
		}
	}

	sleep(1);
    }
}
