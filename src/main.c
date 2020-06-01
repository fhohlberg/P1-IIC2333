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
  fprintf(stderr,"\n\nCreamos un hardlink en la partición 2 a yes.mp3, llamado yes_hardlink.mp3\n");
  cr_hardlink(2, "yes.mp3", "yes_hardlink.mp3");
  fprintf(stderr,"\nAbrimos yes.mp3 de la partición 2\n");
  crFILE * file4 = cr_open(2, "yes.mp3", 'r');
  fprintf(stderr,"\n\nElimino de la partición 2 el archivo yes.mp3\n");
  cr_rm(2, "yes.mp3");
  fprintf(stderr,"\n\nAbrimos el archivo yes_hardlink.mp3 de la partición 2\n");
  crFILE* file2 = cr_open(2, "yes_hardlink.mp3", 'r');

  /* CREAR UN SOFTLINK */
  fprintf(stderr,"\nCreo un softlink en la partición 3 al archivo guides.txt de la partición 1\n");
  cr_softlink(1, 3, "guides.txt", "1/guides.txt");
  fprintf(stderr,"\nAbrimos guides.txt de la partición 1\n");
  crFILE * file5 = cr_open(1, "guides.txt", 'r');
  fprintf(stderr,"\nAhora eliminamos el archivo guides.txt de la partición 1\n");
  cr_rm(1, "guides.txt");
  //TIRA ERROR YA QUE SE ELIMINA EL ARCHIVO AL QUE APUNTA EL SOFTLINK
  fprintf(stderr,"\n\nAbrimos el archivo 1/guides.txt de la partición 3\n");
  crFILE* file3 = cr_open(3, "1/guides.txt", 'r');



}
