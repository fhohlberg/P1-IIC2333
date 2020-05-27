#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cr_API.h"
#include <math.h>

// Variables Globales //
  char *path_disk = "/discos/";
//


// funciones //
  //Particion* particion_init(char *filename, int n, int inicio, int final);
  void cr_mount(char *diskname);
//

Bloque* bloque_init(int i, int tipo_bloque, unsigned char *bytes_malloc, Bloque **bloques, int particion){
  bloques[i] = malloc(sizeof(Bloque));
  bloques[i]->array_bytes = malloc(sizeof(unsigned char)* (int)pow(2,13));
  bloques[i]->array_bits= malloc(sizeof(int)* (int)pow(2,13)*8);
  bloques[i]->particion = particion;
  int inicio_bits = 0;

  for (int j = 0; j < (int)pow(2,13); j ++){
    bloques[i]->array_bytes[j] = bytes_malloc[j];
    int binary[8];
    for(int n = 0; n < 8; n++)
      binary[7-n] = (bloques[i]->array_bytes[j] >> n) & 1;
    for (int k = inicio_bits; k < 8+inicio_bits; k++){
      bloques[i]->array_bits[k] = binary[k-inicio_bits];
    }
    inicio_bits += 8;
  }

  for(int n = 0; n < (int)pow(2,13); n++)
    printf("%d", bloques[i]->array_bits[n]);
  printf("\n");
}

/*
Particion* particion_init(int n, int inicio, int final, unsigned char* bytes, Particion **particiones){
  particiones[n] = malloc(sizeof(Particion));
  particiones[n]->inicio = inicio;
  particiones[n]->final = final;
  int tipo_bloque = 5;

  Bloque **bloques = malloc(sizeof(Bloque*)*((int)pow(2,16))); // son 4 particiones
  int final_bloque = (int)pow(2,13);
  for(int i = 0; i<(2); i++){
      if (i == 0){
        tipo_bloque = 1; // DIRECTORIO
      }if (i == 1){
        tipo_bloque = 2; // BITMAP
      }
      bloque_init(i, tipo_bloque, bytes, final_bloque - (int)pow(2,13) , final_bloque, bloques);
      final_bloque += (int)pow(2,13);
    }
  }*/

Disco* disco_init(char *filename){
  unsigned char bytes[(int)pow(2,13)];
  Bloque **bloques = malloc(sizeof(Bloque*)*((int)pow(2,18))); // son 4 particiones
  FILE *archivo = fopen(filename, "rb");
  int tipo_bloque = 5;
  int final_bloque = (int)pow(2,13);
  int inicio_bloque = final_bloque - (int)pow(2,13);
  unsigned char *bytes_malloc = malloc(sizeof(unsigned char)*(int)pow(2,13));
  int particion = 0;

  for(int i = 0; i<(int)pow(2,1); i++){ // int)pow(2,18)
      fread(bytes,sizeof(bytes),1,archivo);
      for(int j = 0; j < (int)pow(2,13); j++){
        bytes_malloc[j] = bytes[j];
      }
      //printf("i es %d con %u \n", i, bytes[0]);
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
      if(i < 65536){
        particion = 1;
      }else if (i < 131072){
        particion = 2;
      }else if (i<196608){
        particion= 3;
      }else{
        particion = 4;
      }
      bloque_init(i, tipo_bloque, bytes_malloc, bloques, particion);
      final_bloque += (int)pow(2,13);
      inicio_bloque = final_bloque - (int)pow(2,13)*(i);
    }

  fclose(archivo);
}


void cr_mount(char *diskname){
  char buff[64];
  sprintf(buff, "discos/%s", diskname);
  path_disk = buff;

  // particion 1
  disco_init(path_disk);
  //free(disco);
}
