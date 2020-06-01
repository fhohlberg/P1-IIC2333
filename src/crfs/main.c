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
  crFILE * file = cr_open(4, "texto_nuevo.txt", 'r');//cambiar a w
  fprintf(stderr,"\nEscribimos en el archivo creado texto_nuevo.txt\n");
  void* buffer;//= malloc(sizeof(unsigned char)*115);
  buffer = "¡Hola! Somos el grupo DFLL del proyecto de Sistemas Operativos. ¡Hemos creado un sistema de archivos inreíble!";
  cr_write(file, buffer, 115);
  fprintf(stderr,"\nLeemos el archivo texto_nuevo.txt\n");

  void* buffer3;
  cr_read(file, buffer3, 115);
  fprintf(stderr,"\nDescargamos el archivo creado texto_nuevo.txt\n");
  void* buffer2;// = malloc(sizeof(unsigned char)*31);
  buffer2 = "\n\nVamos a descargar el archivo.";
  cr_write(file, buffer2, 31);
  cr_unload(4, "texto_nuevo.txt", "file_disco/texto_nuevo.txt");

  /* CREAR UN HARDLINK */
  fprintf(stderr,"\n\nCreamos un hardlink en la partición 1 a heapsort.png, llamado heapsort_hardlink.png\n");
  cr_hardlink(1, "heapsort.png", "heapsort_hardlink.png");
  fprintf(stderr,"\nAbrimos heapsort.png de la partición 1\n");
  crFILE * file4 = cr_open(1, "heapsort.png", 'r');
  fprintf(stderr,"\n\nElimino de la partición 1 el archivo heapsort.png\n");
  cr_rm(1, "heapsort.png");
  fprintf(stderr,"\n\nAbrimos el archivo heapsort_hardlink.png de la partición 1\n");
  crFILE* file2 = cr_open(1, "heapsort_hardlink.png", 'r');

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

  /* CERRAMOS LOS ARCHIVOS ABIERTOS (ACTUALIZAR ARCHIVO .BIN) QUE NO HAN SIDO ELIMINADOS */ 
  cr_close(file);
  cr_close(file2);
  //cr_close(file3);
  //cr_close(file4);
  //cr_close(file5);

  free(file);
  free(file2);
  free(file3);
  free(file4);
  free(file5);

  //free(buffer);
  //free(buffer2);

  cr_dismount(diskname);

}
