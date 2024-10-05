#include <curses.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int createFolder(char *folderPath, char *folderToAdd) {
  printf("\ncreando %s%s...\n", folderPath, folderToAdd);
  char *newfolderPath = malloc(strlen(folderPath) + strlen(folderToAdd) + 1);
  strcpy(newfolderPath, folderPath);
  strcat(newfolderPath, folderToAdd);
  int check = mkdir(newfolderPath, 0755);
  if (check == -1) {
    printf("\ncartella di merda non creata, succhiamelo\n");
    perror("mkdir");
    return -1;
  } else {
    printf("\n\t%s creata...\n", folderToAdd);
    return 0;
  }
}

int main(int argc, char *argv[]) {
  int currentArg;
  int createSuccess;
  char *folderPath = NULL;
  while ((currentArg = getopt(argc, argv, "f:")) != -1) {
    switch (currentArg) {
    case 'f':
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
    default:
      printf("devi mettere gli argomenti merda\n");

      break;
    }
  }
  return 0;
}
