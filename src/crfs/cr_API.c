#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cr_API.h"
#include <math.h>
#include <stdbool.h>

// Variables Globales //
  char path_disk[255];
  //Disco* disco = malloc(sizeof(Disco));
//



Bloque* bloque_init(int i, int tipo_bloque, unsigned char *bytes_malloc, int particion){
  
  Bloque* bloque = malloc(sizeof(Bloque));
  bloque -> array_bytes = malloc(sizeof(unsigned char)* (int)pow(2,13));
  bloque -> array_bits= malloc(sizeof(int)* (int)pow(2,13)*8);
  bloque -> particion = particion;
  int inicio_bits = 0;

  for (int j = 0; j < (int)pow(2,13); j ++){
    bloque -> array_bytes[j] = bytes_malloc[j];
    int binary[8];
    for(int n = 0; n < 8; n++)
      binary[7-n] = (bloque ->array_bytes[j] >> n) & 1;
    for (int k = inicio_bits; k < 8+inicio_bits; k++){
      bloque -> array_bits[k] = binary[k-inicio_bits];
    }
    inicio_bits += 8;
  }

  /*for(int n = 0; n < (int)pow(2,13); n++)
    printf("%d", bloques[i]->array_bits[n]);
  printf("\n");*/
  return bloque;
}


Disco* disco_init(char *filename){

  Disco* disco = malloc(sizeof(disco));
  disco -> array_bloques = malloc(sizeof(Bloque*)*((int)pow(2,18))); 
   

  unsigned char bytes[(int)pow(2,13)];
  FILE *archivo = fopen(filename, "rb");
  int tipo_bloque = 5;
  int final_bloque = (int)pow(2,13);
  int inicio_bloque = final_bloque - (int)pow(2,13);
  unsigned char *bytes_malloc = malloc(sizeof(unsigned char)*(int)pow(2,13));
  int particion = 0;


  for(int i = 0; i<(int)pow(2,18); i++){ 
      fread(bytes,sizeof(bytes),1,archivo);
      for(int j = 0; j < (int)pow(2,13); j++){
        bytes_malloc[j] = bytes[j];
      }
      if (i == 0){
        tipo_bloque = 1; // DIRECTORIO
      }if (i == 1){
        tipo_bloque = 2; // BITMAP
      }if (i == 65536){
        tipo_bloque = 1; // DIRECTORIO
      }
      if (i == 65537){
        tipo_bloque = 2; // BITMAP
      }
      if (i == 131072){
        tipo_bloque = 1; // DIRECTORIO
      }
      if (i == 131073){
        tipo_bloque = 2; // BITMAP
      }
      if (i == 196608){
        tipo_bloque = 1; // DIRECTORIO
      }
      if (i == 196608){
        tipo_bloque = 2; // BITMAP
      }

      if(i < 65536){
        particion = 1;
      }else if (i < 131072){
        particion = 2;
      }else if (i<196608){
        particion= 3;
      }else{
        particion = 4;
      }
      disco -> array_bloques[i] = bloque_init(i, tipo_bloque, bytes_malloc, particion);
      final_bloque += (int)pow(2,13);
      inicio_bloque = final_bloque - (int)pow(2,13)*(i);
    }

  fclose(archivo);
  return disco;
}


void cr_mount(char *diskname){
  char buff[255];
  sprintf(buff, "discos/%s", diskname);
  strcpy(path_disk, buff);
  // particion 1
  //disco_init(path_disk);
  //free(disco);
}

void cr_bitmap(unsigned disk, bool hex){
  printf("%s\n", path_disk);
  Disco* disco = disco_init(path_disk);
  int libres = 0;
  int ocupadas = 0;
  if(disk == 1 || disk == 0){
    libres = 0;
    ocupadas = 0;
    for( int j = 0; j < ((int) pow(2,13))*8; j++){
      fprintf(stderr, "%d", disco -> array_bloques[1]-> array_bits[j]);
      if(disco -> array_bloques[1]-> array_bits[j] == 0)
        libres += 1;
      else
        ocupadas += 1; 
    }
    fprintf(stderr, "\n \n PARTICIÓN NÚMERO: %d\n", disk);
    fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupados);
  }
  if(disk == 2 || disk == 0){
    libres = 0;
    ocupadas = 0;
    for( int j = 0; j < ((int) pow(2,13))*8; j++){
      fprintf(stderr, "%d", disco -> array_bloques[65537]-> array_bits[j]);
      if(disco -> array_bloques[65537]-> array_bits[j] == 0)
        libres += 1;
      else
        ocupadas += 1; 
    }
    fprintf(stderr, "\n \n PARTICIÓN NÚMERO: %d\n", disk);
    fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupados);
  }
  if(disk == 3 || disk == 0){
    libres = 0;
    ocupadas = 0;
    for( int j = 0; j < ((int) pow(2,13))*8; j++){
      fprintf(stderr, "%d", disco -> array_bloques[131073]-> array_bits[j]);
      if(disco -> array_bloques[131073]-> array_bits[j] == 0)
        libres += 1;
      else
        ocupadas += 1; 
    }
    fprintf(stderr, "\n \n PARTICIÓN NÚMERO: %d\n", disk);
    fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupados);
  }
  if(disk == 4 || disk == 0){
    libres = 0;
    ocupadas = 0;
    for( int j = 0; j < ((int) pow(2,13))*8; j++){
      fprintf(stderr, "%d", disco -> array_bloques[196609]-> array_bits[j]);
      if(disco -> array_bloques[196609]-> array_bits[j] == 0)
        libres += 1;
      else
        ocupadas += 1; 
    }
    fprintf(stderr, "\n \n PARTICIÓN NÚMERO: %d\n", disk);
    fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupados);

  }
}
