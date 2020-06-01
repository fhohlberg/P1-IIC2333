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

  /* PARA PROBAR cr_close ABRIMOS ARCHIVO CERRADO EN MAIN ANTERIOR */
  fprintf(stderr,"\nAbrimos el archivo cerrado en el main anterior: texto_nuevo.txt de la partición 4 y lo leemos\n\n");
  crFILE* file2 = cr_open(4, "texto_nuevo.txt", 'r');
  void* buffer2 = malloc(sizeof(unsigned char)* file2 -> tamano);
  cr_read(file2, buffer2, file2 -> tamano);

  /* UNLOAD */
  fprintf(stderr,"\n\nFUNCIONES cr_unload y cr_load\n\n");

  fprintf(stderr,"Descargar archivo heapsort_hardlink.png de la partición 1:\n");
  cr_unload(1, "heapsort_hardlink.png", "file_disco/heapsort_hardlink.png");

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

  fprintf(stderr,"\n\nEscribimos (bibliografía) en el archivo InformeSocial.txt y hacemos UNLOAD\n");
  void* buffer1 = malloc(sizeof(unsigned char)* 175);
  buffer1 = "\n\nBibliografía: Municipalidad de Puente Alto. (2018). Misión y Visión. abril 10, 2020, de Municipalidad de Puente Alto Sitio web: https://www.mpuentealto.cl/?page_id=21027";
  cr_write(file, buffer1, 175);
  cr_unload(1, "InformeSocial.txt", "file_disco/InformeSocial.txt");

  fprintf(stderr,"\n\nLoad de archivo meme_computacion.jpg a la partición 1\n");
  cr_load(1, "meme_computacion.jpg"); 
  fprintf(stderr,"\n\nAbriendo archivo meme_computacion.jpg\n");
  crFILE* file_meme = cr_open(1, "meme_computacion.jpg", 'r');


  /* CERRAMOS TODOS LOS ARCHIVOS */
  cr_close(file2);
  cr_close(file);
  cr_close(file_meme);

}
