#include <curses.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char *stringParser(char *folderPath, char *stuffToAdd) {
  char *newfolderPath = malloc(strlen(folderPath) + strlen(stuffToAdd) + 1);
  strcpy(newfolderPath, folderPath);
  strcat(newfolderPath, stuffToAdd);
  return newfolderPath;
}

int createFolder(char *folderPath, char *folderToAdd) {
  printf("\ncreando %s%s...\n", folderPath, folderToAdd);
  char *newfolderPath = stringParser(folderPath, folderToAdd);
  int check = mkdir(newfolderPath, 0755);
  free(newfolderPath);
  if (check == -1) {
    printf("\ncartella di merda non creata, succhiamelo\n");
    perror("mkdir");
    return -1;
  } else {
    printf("\n\t%s creata...\n", folderToAdd);
    return 0;
  }
}

int boilerplate(char *path) {
  char *filePath = stringParser(path, "/main.c");
  printf("\n%s\n", filePath);
  int fd = open(filePath, O_CREAT | O_RDWR, 0644);
  if (fd == -1) {
    printf("sto file di merda non si vuole creare, cazzacci tuoi");
    perror("open");
    return -1;
  }
  free(filePath);
  char *boilerplate = "#include <stdio.h>\n"
                      "\n"
                      "int main(int argc, char* argv[]) {\n"
                      "return 0;\n"
                      "}\n";
  int checkWrite = write(fd, boilerplate, strlen(boilerplate));
  if (checkWrite == -1) {
    perror("write");
    printf("non riesco a scrivere... cazzi tuoi");
    close(fd);
    return -1;
  }
  close(fd);
  printf("file creato, lavora figlio di puttana");
  return 0;
}
int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: proj -f filepath");
    return -1;
  }
  int currentArg;
  int createSuccess;
  char *folderPath = stringParser(argv[2], "/src");
  while ((currentArg = getopt(argc, argv, "f:b")) != -1) {
    switch (currentArg) {
    case 'f':
      printf("%s", optarg);
      createSuccess = createFolder(optarg, "");
      if (createSuccess == -1) {
        return 1;
      } else {
        printf("\nho creato la cartella %s\nCreo le sottocartelle...\n",
               optarg);
        createSuccess = createFolder(optarg, "/bin");
        if (createSuccess == -1) {
          return 1;
        }
        createSuccess = createFolder(optarg, "/src");
        if (createSuccess == -1) {
          return 1;
        }
        createSuccess = createFolder(optarg, "/include");
        if (createSuccess == -1) {
          return 1;
        }
        createSuccess = createFolder(optarg, "/obj");
        if (createSuccess == -1) {
          return 1;
        }
      }
      break;
    case '?':
      printf("Comando non riconosciuto %c\n", currentArg);
      break;
    case 'b':
      int isWritten = boilerplate(folderPath);
      if (isWritten == -1) {
        return -1;
      }
      break;
    default:
      printf("devi mettere gli argomenti merda\n");

      break;
    }
  }
  return 0;
}
