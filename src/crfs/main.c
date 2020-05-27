#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cr_API.h"


// Variables Globales //
  //char *path_disk = "/discos/";
//

int main(int argc, char *argv[]){
  char* diskname = argv[1];
  cr_mount(diskname);
  //cr_bitmap(1, true); //unsigned disk, bool hex (0 = binario, 1 = hexadecimal)
  //printf("%d",cr_exists(1,"Baroque.mp3"));
  cr_ls(1);
}
