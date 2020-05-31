#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cr_API.h"



int main(int argc, char *argv[]){
  /* NOMBRE DEL ARCHIVO BIN*/
  char* diskname = argv[1];

  /** FUNCIONES UNLOAD y LOAD **/

  /* MONTAR EL DISCO */
  cr_mount(diskname);

  /* UNLOAD */
  fprintf(stderr,"\nFUNCIÓN cr_unload y cr_load\n\n");

  fprintf(stderr,"Descargar archivo guides.txt de la partición 1:\n");
  cr_unload(1, "guides.txt", "file_disco/guides.txt");

  fprintf(stderr,"Descargar archivo QPC.gif de la partición 1:\n");
  cr_unload(1, "QPC.gif", "file_disco/QPC.gif");

  fprintf(stderr,"Descargar archivo text.txt de la partición 2:\n");
  cr_unload(2, "text.txt", "file_disco/text.txt");

  /* LOAD */
  fprintf(stderr,"\n\nLoad de archivo InformeSocial.txt a la partición 1\n");
  cr_load(1, "InformeSocial.txt"); //el informe tiene 12217 caracteres (bytes)
  void* buffer = malloc(sizeof(unsigned char) * 500);

  fprintf(stderr,"\n\nAbriendo archivo InformeSocial.txt\n");
  crFILE* file = cr_open(1, "InformeSocial.txt", 'r');
  fprintf(stderr,"\n\nLeemos los primeros 1000 caracteres de InformeSocial.txt\n\n");
  cr_read(file, buffer, 500);
  cr_read(file, buffer, 500);

  fprintf(stderr,"\n\nEscribimos en el archivo InformeSocial.txt y hacemos UNLOAD\n");
  void* buffer1 = malloc(sizeof(unsigned char)* 175);
  buffer1 = "\n\nBibliografía: Municipalidad de Puente Alto. (2018). Misión y Visión. abril 10, 2020, de Municipalidad de Puente Alto Sitio web: https://www.mpuentealto.cl/?page_id=21027";
  cr_write(file, buffer1, 169);
  cr_unload(1, "InformeSocial.txt", "file_disco/InformeSocial.txt");

  fprintf(stderr,"\n\nLoad de archivo meme_computacion.txt a la partición 1\n");
  cr_load(1, "meme_computacion.jpg"); 
  fprintf(stderr,"\n\nAbriendo archivo meme_computacion.txt\n");
  crFILE* file_meme = cr_open(1, "meme_computacion.jpg", 'r');

}
