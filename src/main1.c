#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cr_API.h"



int main(int argc, char *argv[]){
  /* NOMBRE DEL ARCHIVO BIN*/
  char* diskname = argv[1];
  /** FUNCIONES GENERALES **/

  /* MONTAR EL DISCO */
  cr_mount(diskname);

  /* MOSTRAMOS EL BITMAP */
  fprintf(stderr,"\n\nFUNCIÓN cr_bitmap\n");
  cr_bitmap(1, true); //(true = hexadecimal, false = decimal)
  cr_bitmap(1, false);
  cr_bitmap(0, false);
  cr_bitmap("a", true);



  /* ARCHIVOS DE TODAS LAS PARTICIONES */
  fprintf(stderr,"\nFUNCIÓN cr_ls\n");
  cr_ls(1);
  cr_ls(2);
  cr_ls(3);
  cr_ls(4);
  cr_ls("a");

  /* FUNCION cr_exist*/
  fprintf(stderr,"\nFUNCIÓN cr_exists\n");
  //Archivos que si estan:
  fprintf(stderr, "\n¿Existe Baroque.mp3 en la partición 1? %d\n", cr_exists(1, "Baroque.mp3"));
  fprintf(stderr, "¿Existe yes.mp3 en la partición 2? %d\n", cr_exists(2, "yes.mp3"));
  fprintf(stderr, "¿Existe in.mkv en la partición 3? %d\n", cr_exists(3, "in.mkv"));
  fprintf(stderr, "¿Existe 1/Baroque.mp3 en la partición 4? %d\n", cr_exists(4, "1/Baroque.mp3"));
  
  // Archivos que no están
  fprintf(stderr, "¿Existe Baroque.mp en la partición 1? %d\n", cr_exists(1, "Baroque.mp"));
  fprintf(stderr, "¿Existe proyecto-iic2333.png en la partición 2? %d\n", cr_exists(2, "proyecto-iic2333.png"));
  fprintf(stderr, "¿Existe heapsort.png en la partición 7? %d\n\n", cr_exists(7, "heapsort.png"));

  cr_dismount(diskname);
}
