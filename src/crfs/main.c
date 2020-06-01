#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cr_API.h"



int main(int argc, char *argv[]){
  /* NOMBRE DEL ARCHIVO BIN*/
  char* diskname = argv[1];
  /* FUNCIONES GENERALES */

  /* MONTAR EL DISCO */
  cr_mount(diskname);

  /* CREAR ARCHIVO NUEVO, ESCRIBIR DENTRO, LEER y DESCARGAR */
  //fprintf(stderr,"\nCreo un archivo nuevo texto_nuevo.txt, en modo 'write' en la partición 4\n");
  crFILE * file = cr_open(2, "text.txt", 'r');
  //fprintf(stderr,"\nEscribimos en el archivo creado texto_nuevo.txt\n");
  void* buffer = malloc(sizeof(unsigned char)*115);
  //buffer = "¡Hola! Somos el grupo DFLL del proyecto de Sistemas Operativos. ¡Hemos creado un sistema de archivos inreíble!";
  //cr_write(file, buffer, 115);
  //fprintf(stderr,"\nLeemos el archivo texto_nuevo.txt\n");
  cr_read(file, buffer, 115);
  free(buffer);
  free(file);


  cr_dismount(diskname);

}
