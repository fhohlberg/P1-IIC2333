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

  /* UNLOAD POR POR PARTICION */
  fprintf(stderr,"\nDescargar partición 1:\n");
  cr_unload(1, "particion", "file_disco/1_only");

  fprintf(stderr,"\nDescargar disco completo:\n");
  cr_unload(0, "disco", "file_disco");
  
}
