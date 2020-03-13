#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>

void createIndomie();
void createSedaap();
void extract();

int main()
{
    createIndomie();
}

void createIndomie()
{
    pid_t indomie_creator;
    int status;

    indomie_creator = fork();

    if (indomie_creator < 0)
    {
        exit(EXIT_FAILURE);
    }

    // Create indomie folder
    if (indomie_creator == 0)
    {
        char *argv[] = {
            "mkdir",
            "/home/kenji/modul2/indomie"};

        execv("/bin/mkdir", argv);
    }

    while ((wait(&status)) > 0)
    {
        sleep(5);
        createSedaap();
    }
}

void createSedaap()
{
    pid_t sedaap_creator;
    int status;

    sedaap_creator = fork();

    if (sedaap_creator < 0)
    {
        exit(EXIT_FAILURE);
    }

    // Create sedaap folder
    if (sedaap_creator == 0)
    {
        char *argv[] = {
            "mkdir",
            "/home/kenji/modul2/sedaap"};

        execv("/bin/mkdir", argv);
    }

    while ((wait(&status)) > 0)
    {
        extract();
    }
}

void extract()
{
    pid_t jpg_extractor;
    int status;

    jpg_extractor = fork();

    if (jpg_extractor < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (jpg_extractor == 0)
    {
        char *argv[] = {
            "unzip", 
            "/home/kenji/modul2/jpg",
            "-d",
            "/home/kenji/modul2/"
            };
        execv("/usr/bin/unzip", argv);
    }

    // Categorize
    
}