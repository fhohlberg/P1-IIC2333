#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cr_API.h"

// Variables Globales //
  //char *path_disk = "/discos/";
//

int main(int argc, char *argv[]){
  char* diskname = argv[1];
  cr_mount(diskname);
}
