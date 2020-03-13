# SoalShiftSISOP20_modul2_B04

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
