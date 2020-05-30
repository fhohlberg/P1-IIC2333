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
  cr_ls(4);
  //printf("%d\n", cr_exists(1, "Baroque.mp3"));*/
  
  //crFILE * file = cr_open(1, "guides.txt", 'r');

  void* buffer = malloc(18);
  buffer = "HOLA LUCRE Y FRAN";
  //unsigned char buff;
  //buff = (unsigned char*)buffer;
  //printf("BUFFERR: %s\n", buffer);

  //cr_read(file,0,23708);
  crFILE * file = cr_open(2, "text.txt", 'r');
  //cr_read(file,0, 23800);
  cr_write(file, buffer, 18);
  //printf("\nENTREMEDIO\n");
  cr_read(file,0, 23800);



  //crFILE * file = cr_open(2, "yes.mp3", 'r');
  //cr_read(file, 0, 24484977);
  //crFILE * file = cr_open(1, "guides.txt", 'r');
  //cr_read(file, 0, 1000);
  //crFILE * file2 = cr_open(2, "text.txt", 'r');
  //cr_read(file2, 0, 1000);

  //cr_open(3, "hola.txt", 'w');
  //cr_open(4, "hola.txt", 'w');


  /*printf("Estoy en disco 2\n");
  cr_ls(2);
  printf("Estoy en disco 3\n");
  cr_ls(3);
  printf("Estoy en disco 4\n");
  cr_ls(4);*/
}
