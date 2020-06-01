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

  /* CREAR ARCHIVO NUEVO, ESCRIBIR DENTRO, LEER y DESCARGAR */
  fprintf(stderr,"\nCreo un archivo nuevo texto_nuevo.txt, en modo 'write' en la partición 4\n");
  crFILE * file = cr_open(4, "texto_nuevo.txt", 'w');
  fprintf(stderr,"\nEscribimos en el archivo creado texto_nuevo.txt\n");
  void* buffer = malloc(sizeof(unsigned char)*115);
  buffer = "¡Hola! Somos el grupo DFLL del proyecto de Sistemas Operativos. ¡Hemos creado un sistema de archivos inreíble!";
  cr_write(file, buffer, 115);
  fprintf(stderr,"\nLeemos el archivo texto_nuevo.txt\n");
  cr_read(file, buffer, 115);
  fprintf(stderr,"\nDescargamos el archivo creado texto_nuevo.txt\n");
  void* buffer2 = malloc(sizeof(unsigned char)*31);
  buffer2 = "\n\nVamos a descargar el archivo.";
  cr_write(file, buffer2, 31);
  cr_unload(4, "texto_nuevo.txt", "file_disco/texto_nuevo.txt");

  /* CREAR UN HARDLINK */
  fprintf(stderr,"\n\nCreo un hardlink en la partición 2 a yes.mp3\n");
  cr_hardlink(2, "yes.mp3", "yes_hardlink.mp3");
  //remover yes.mp3
  crFILE* file2 = cr_open(2, "yes_hardlink.mp3", 'r');

  /* CREAR UN SOFTLINK */
  fprintf(stderr,"\nCreo un softlink en la partición 3 al archivo guides.txt de la partición 1\n");
  cr_softlink(1, 3, "guides.txt", "1/guides.txt");
  //remover guides.txt
  //TIRA ERROR YA QUE SE ELIMINA EL ARCHIVO AL QUE APUNTA EL SOFTLINK
  crFILE* file3 = cr_open(3, "1/guides.txt", 'r');



}
