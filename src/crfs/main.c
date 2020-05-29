#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cr_API.h"


int main(int argc, char *argv[]){
  char* diskname = argv[1];
  cr_mount(diskname);
  //cr_bitmap(1, true); //unsigned disk, bool hex (true = binario, false = hexadecimal)
  //printf("%d",cr_exists(1,"Baroque.mp3"));
  //printf("Estoy en disco 1\n");
  /*printf("Directorio disco 1\n");
  cr_ls(1);
  printf("BITMAP  binario disco 1\n");
  cr_bitmap(1, false); //unsigned disk, bool hex (true = binario, false = hexadecimal)
  printf("BITMAP hexa disco 2\n");
  cr_bitmap(2, true);
  printf("Directorio disco 2\n");
  cr_ls(2);
  printf("Directorio disco 1\n");
  cr_ls(1);
  printf("Viendo si existe archivo text.txt en particion 3\n");
  printf("Existe: %d\n", cr_exists(3, "text.txt"));
  printf("Directorio disco 3\n");
  cr_ls(3);
  printf("Directorio disco 4\n");
  cr_ls(4);*/
  //printf("%d\n", cr_exists(1, "Baroque.mp3"));
  //cr_open(2, "hola.txt", 'w');
  //cr_open(3, "hola.txt", 'w');
  //cr_open(4, "hola.txt", 'w');
  cr_open(1, "guides.txt", 'r');
  //cr_open(3, "hola.txt", 'w');
  //cr_open(4, "hola.txt", 'w');


  /*printf("Estoy en disco 2\n");
  cr_ls(2);
  printf("Estoy en disco 3\n");
  cr_ls(3);
  printf("Estoy en disco 4\n");
  cr_ls(4);*/
}
