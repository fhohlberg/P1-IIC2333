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

  /* LA PRIMERA VEZ 
  crFILE * file = cr_open(4, "texto_nuevo.txt", 'r');
  void* buffer = malloc(sizeof(unsigned char)*115);
  buffer = "¡Hola! Somos el grupo DFLL del proyecto de Sistemas Operativos. ¡Hemos creado un sistema de archivos inreíble!";
  cr_write(file, buffer, 115);
  cr_close(file);*/


  //LA SEGUNDA VEZ
  crFILE * file = cr_open(4, "texto_nuevo.txt", 'r');
  void* buffer = malloc(sizeof(unsigned char)*115);
  cr_read(file, buffer, 115);
  cr_close(file);

}
