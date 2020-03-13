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

void createDaemon();
void createFolder();
void downloadImages();

int main()
{
  createDaemon();
}

void createDiamon()
{
  pid_t main_process;

  main_process = fork();

  if (main_process < 0)
  {
    exit(EXIT_FAILURE);
  }

  if (main_process > 0)
  {
    exit(EXIT_SUCCESS);
  }

  umask(0);
  pid_t sid = setsid();

  if (sid < 0)
  {
    exit(EXIT_FAILURE);
  }

  // if ((chdir("/")) < 0)
  // {
  //   exit(EXIT_FAILURE);
  // }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  // Create a folder every 30s
  while (1)
  {
    createFolder();
    sleep(30);
    continue;
  }
}

void createFolder() {
  // Variable for timestamp
    time_t timer;
    char buffer[26];
    struct tm *tm_info;
    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%Y-%m-%d_%H:%M:%S", tm_info);

    pid_t folder_creator;
    int status;

    // Create folder creator
    folder_creator = fork();

    // Failed to create folder creator
    if (folder_creator < 0)
    {
      exit(EXIT_FAILURE);
    }

    // Create folder
    if (folder_creator == 0)
    {
      char *argv[] = {"mkdir", buffer, NULL};
      execv("/bin/mkdir", argv);
    }

    // Parent
    else
    {
      // Download 20 images to the created folder
      while ((wait(&status)) > 0)
        ;

      for (int i = 0; i < 20; i++)
      {
        pid_t image_downloader;
        int status;

        image_downloader = fork();
        umask(0);

        if (image_downloader < 0)
        {
          exit(EXIT_FAILURE);
        }

        // Download image
        if (image_downloader == 0)
        {
          char download_directory[500] = "/home/kenji/Shift2/";
          strcat(download_directory, buffer);

          time_t seconds;
          seconds = time(NULL);
          seconds = (seconds % 1000) + 100;
          char sec_string[100];
          sprintf(sec_string, "%ld", seconds);

          char downlod_url[200] = "https://picsum.photos/";

          strcat(downlod_url, sec_string);

          char *argv[] = {
              "wget",
              "-P",
              download_directory,
              downlod_url,
              NULL};

          execv("/usr/bin/wget", argv);
        }

        else
        {
          while ((wait(&status)) > 0)
            ;

          pid_t folder_zipper = fork();
          if (folder_zipper < 0)
          {
            exit(EXIT_FAILURE);
          }

          if (folder_zipper == 0)
          {
            char *argv[] = {
                "zip",
                buffer,
                buffer,
                NULL};

            execv("/usr/bin/zip", argv);
          }

          else
          {
            pid_t folder_remover = fork();
            int status;

            if (folder_remover < 0)
            {
              exit(EXIT_FAILURE);
            }

            if (folder_remover == 0)
            {
              char *argv[] = {
                  "rmdir",
                  buffer,
                  NULL};

              execv("/bin/rmdir", argv);
            }

            else
            {
              while ((wait(&status)) > 0)
                ;
              sleep(5);
              continue;
            }
          }
        }
      }
    }
}

void downloadImages() {
  
}
