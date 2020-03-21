# SoalShiftSISOP20_modul2_B04

#### Iffah Wahyu Roshifa (05111840000018) 
#### Kenji Hikmatullah (05111840000074) 

## Soal 1

- Cek input huruf
```
int cekhuruf(char* input){
	int i=0;
	for(i; i < strlen(input); i++){
    	if(isalpha(input[i])) return 1;
	}
  return 0;
}
```

- Pada main
`int main(int argc, char *argv[])`
argc untuk menyimpan jumlah parameter yang akan dimasukkan, sedangkan argv untuk menyimpan argumen yang dimasukkan dalam bentuk char.

- Lakukan daemon
```
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
```

- Argumen harus 5
```
if(argc!=5){
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
```

- Mengambil current time
```
time_t t = time(NULL);
    struct tm *tmp = gmtime(&t);
	int s = t % 60;
	int m = (t / 60) % 60;
    int h = (t / 3600) % 24;
```
Variabel h adalah hasil ekstrak current hour, variabel m current minute, dan variabel s current second.

- Tetapkan nilai tiap waktu 
```
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
```
Jika input bukan `*`  , maka nilai hour adalah dari `argv[1]` yang diubah menjadi nilai integer, nilai min dari `argv[2]` , dan sec dari `argv[3]` . jika input `*` , maka nilai hour, min, atau sec adalah sama dengan current time, yaitu nilai `h`, `m`, atau `s`. Juga cek apakah input berupa huruf. Jika ya, maka langsung mengeluarkan output Error dan program berakhir. 

- Cek apakah memenuhi range
```
    if(hour<0 || hour>23 || min<0 ||min>59 || sec<0 || sec>59){
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
```
Jika input untuk jam bukan antara 0 - 23, menit bukan 0 - 59, dan detik bukan 0 - 59, maka `exit(EXIT_FAILURE);`

- Cek path file
```	
    char script[100];
	strcpy(script,argv[4]);
	int length = strlen(script);
	if(length<4 || script[100-(100-length)-3]!='.' || script[100-(100-length)-2]!='s' || script[100-(100-length)-1]!= 'h'){
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
```
argv[4] adalah input untuk path file .sh. Isinya kemudian di-copy ke array script. Jika panjang array kurang dari 4, dan tiga nilai paling belakang bukan `.sh` maka `exit(EXIT_FAILURE);`

- Jalankan bash script
```
    if (s == sec && m == min && h == hour){
		pid_t pid1 =  fork();
		if(pid1 == 0) {
			char *arg[] = {"bash", argv[4] , NULL};
			execv("/bin/bash", arg);
		}
	}
```
Jika nilai `h` (current hour) sama dengan input jam (hour), nilai `m` (current minute) sama dengan input menit (min), dan nilai `s` (current second) sama dengan input detik (sec) maka program akan menjalankan path file `.sh` yang diinputkan.

- Sleep
`sleep(1);`  sleep tiap 1 detik.


## Soal 2

2.1 Buat  daemon

Lakukan Fork
```
  pid_t main_process;

  main_process = fork();

  if (main_process < 0)
  {
    exit(EXIT_FAILURE);
  }

  if (main_process > 0)
  {
    exit(EXIT_SUCCESS);
```

Konfigurasi daemon
```
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
```

Lakukan tugas
```
while (1)
  {
    createFolder();
    sleep(30);
    continue;
  }
```

2.2 Buat Folder

Dapatkan waktu saat ini
```
    time_t timer;
    char buffer[26];
    struct tm *tm_info;
    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%Y-%m-%d_%H:%M:%S", tm_info);
```

Lakukan Fork untuk buat foler
```
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
```

Lakukan Fork untuk Unduh Gambar
```
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
```

Lakukan Fork buat Melakukan Zip
```
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
```

2.2.5 Hapus Folder setelah Zip Dibuat
```
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
```

## Soal 3
#### Buat Folder Indomie

Melakukan fork
```
pid_t indomie_creator;
int status;

indomie_creator = fork();

if (indomie_creator < 0)
    {
        exit(EXIT_FAILURE);
    }
```  
<br>

Panggil perintah mkdir melalui execv

```
if (indomie_creator == 0)
    {
        char *argv[] = {
            "mkdir",
            "/home/kenji/modul2/indomie"};

        execv("/bin/mkdir", argv);
    }
```

Ketika sudah selesai, 5 detik kemudian buat folder sedaap

```
while ((wait(&status)) > 0)  
    {  
      sleep(5);  
      createSedaap();      
    }  
```

#### Buat folder sedaap
Melakukan fork
```
pid_t sedaap_creator;
    int status;

    sedaap_creator = fork();

    if (sedaap_creator < 0)
    {
        exit(EXIT_FAILURE);
    }
```

Memanggil perintah mkdir melalui execv
```
if (sedaap_creator == 0)
    {
        char *argv[] = {
            "mkdir",
            "/home/kenji/modul2/sedaap"};

        execv("/bin/mkdir", argv);
    }
 ```
 
 Ketika sudah selesai, melakukan ekstraksi jpg
 ```
 while ((wait(&status)) > 0)
    {
        extract();
    }
 ```
 
 #### Ekstraksi JPG
 
 Melakukan fork
 ```
 pid_t jpg_extractor;
    int status;

    jpg_extractor = fork();

    if (jpg_extractor < 0)
    {
        exit(EXIT_FAILURE);
    }
 ```
 
 Memanggil perintah zip melalui execv
 ```
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
 ```
 
 Jika sudah selesai, kelompokkan
 ```
 while((wait(&status)) > 0) {
        categorize();
    }
 ```
