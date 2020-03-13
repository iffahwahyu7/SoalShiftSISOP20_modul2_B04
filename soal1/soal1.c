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
char buff[2];
    time_t t = time(NULL);
    struct tm *tmp = gmtime(&t);

    int h = (t / 3600) % 24;
    int m = (t / 60) % 60;
    int s = t % 60;
//printf("%d %d %d\n",h,m,s);


int hour, min, sec;
char hi[2], mi[2], si[2];
strcpy(hi,argv[1]);
strcpy(mi,argv[2]);
strcpy(si,argv[3]);

if(hi!="*") hour = atoi(argv[1]);
if(mi!="*") min = atoi(argv[2]);
if(si!="*") sec = atoi(argv[3]);

if(hi=="*") hour = h;
if(mi=="*") min = m;
if(si=="*") sec = s;
//printf("%s %sa %s %s %s %s\n",hi,mi,si, argv[1], argv[2], argv[3]);
if(hour<0 || hour>23 || min<0 ||min>59 || sec<0 || sec>59){
printf("Error\n");
exit(EXIT_FAILURE);
}

char script[100];
strcpy(script,argv[4]);
int length = strlen(script);
if(length<4 && script[length-2]!='.' && script[length-1]!='s' && script[length]!= 'h'){
printf("Error\n");
exit(EXIT_FAILURE);
}


if (h == hour && m == min && s == sec){
char *arg[] = {"bash", argv[4] , NULL};
execv("/bin/bash", arg);
}
sleep(1);
    }
}
