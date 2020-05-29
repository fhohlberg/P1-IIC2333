#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cr_API.h"
#include <math.h>
#include <stdbool.h>

// Variables Globales //
  char path_disk[255];
  Disco* disco;


Bloque* bloque_init(int i, int tipo_bloque, unsigned char *bytes_malloc){

  Bloque* bloque = malloc(sizeof(Bloque));
  bloque -> array_bytes = malloc(sizeof(unsigned char)* (int)pow(2,13));
  bloque -> array_bits= malloc(sizeof(int)* (int)pow(2,13)*8);
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
  unsigned char *bytes_malloc = malloc(sizeof(unsigned char)*(int)pow(2,13));
  int particion = 0;

  int i = 0;

  printf("Cargando disco...\n");
  while(fread(bytes,sizeof(bytes),1,archivo)){
    /*
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
    if (i == 196609){
      tipo_bloque = 2; // BITMAP
    }*/

    if (i == 0 || i == 1){
      //printf("Leyendo el %d bloque.\n", i);
      particion = 1;
      for(int j = 0; j < (int)pow(2,13); j++){
        bytes_malloc[j] = bytes[j];
      }
      disco -> array_bloques[i] = bloque_init(i, tipo_bloque, bytes_malloc);
    }else if (i == 65536 || i == 65537){
      //printf("Leyendo el %d bloque.\n", i);
      particion = 2;
      for(int j = 0; j < (int)pow(2,13); j++){
        bytes_malloc[j] = bytes[j];
      }
      disco -> array_bloques[i] = bloque_init(i, tipo_bloque, bytes_malloc);
    }
    else if (i == 131072 || i == 131073){
      //printf("Leyendo el %d bloque.\n", i);
      particion= 3;
      for(int j = 0; j < (int)pow(2,13); j++){
        bytes_malloc[j] = bytes[j];
      }
      disco -> array_bloques[i] = bloque_init(i, tipo_bloque, bytes_malloc);
    }else if (i == 196608 || i == 196609){
      //printf("Leyendo el %d bloque.\n", i);
      particion = 4;
      for(int j = 0; j < (int)pow(2,13); j++){
        bytes_malloc[j] = bytes[j];
      }
      disco -> array_bloques[i] = bloque_init(i, tipo_bloque, bytes_malloc);
    }

    /*if (i == bloque){
      for(int j = 0; j < (int)pow(2,13); j++){
        bytes_malloc[j] = bytes[j];
      }
      disco -> array_bloques[i] = bloque_init(i, tipo_bloque, bytes_malloc, particion);
    }*/

    i++;
  }

  fclose(archivo);
  return disco;
}

void cargar_bloque(Disco* disco, int bloque){

  unsigned char bytes[(int)pow(2,13)];
  FILE *archivo = fopen(path_disk, "rb");
  unsigned char *bytes_malloc = malloc(sizeof(unsigned char)*(int)pow(2,13));
  int tipo_bloque = 5;

  int i = 0;
  while(fread(bytes,sizeof(bytes),1,archivo)){

    if (i == bloque){
      for(int j = 0; j < (int)pow(2,13); j++){
        bytes_malloc[j] = bytes[j];
      }
      disco -> array_bloques[i] = bloque_init(i, tipo_bloque, bytes_malloc);
    }

    i++;
  }

  fclose(archivo);
  free(bytes_malloc);
}




void cr_mount(char *diskname){
  char buff[255];
  sprintf(buff, "discos/%s", diskname);
  strcpy(path_disk, buff);
  disco = disco_init(path_disk);
}

void cr_bitmap(unsigned disk, bool hex){
  if(hex == false){
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
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
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
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
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
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
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
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
    }
  }
  //HEXADECIMAL
  else{
    int libres = 0;
    int ocupadas = 0;
    if(disk == 1 || disk == 0){
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13)); j++){
        fprintf(stderr, "%04X", disco -> array_bloques[1]-> array_bytes[j]);
      }
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        if(disco -> array_bloques[1]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
    }
    if(disk == 2 || disk == 0){
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13)); j++){
        fprintf(stderr, "%04X", disco -> array_bloques[65537]-> array_bytes[j]);
      }
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        if(disco -> array_bloques[65537]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
    }
    if(disk == 3 || disk == 0){
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13)); j++){
        fprintf(stderr, "%04X", disco -> array_bloques[131073]-> array_bytes[j]);
      }
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        if(disco -> array_bloques[131073]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
    }
    if(disk == 4 || disk == 0){
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13)); j++){
        fprintf(stderr, "%04X", disco -> array_bloques[196609]-> array_bytes[j]);
      }
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        if(disco -> array_bloques[196609]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
    }
  }
}

int cr_exists(unsigned disk, char* filename){
  //Disco* disco = disco_init(path_disk, disk);
  if(disk == 1){
    char file_disco[29];
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      int distinta = 0;
      for(int j = inicio; j < final;j++){
        file_disco[j-inicio] = (char) disco -> array_bloques[0] -> array_bytes[j];
      }
      if(strcmp(file_disco, filename) == 0){
        //printf("1\n");
        return 1;
      }
      inicio += 32;
      final += 32;
    }
    //printf("0\n");
    return 0;
  }
  if(disk == 2){
    char file_disco[29];
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      int distinta = 0;
      for(int j = inicio; j < final;j++){
        file_disco[j-inicio] = (char) disco -> array_bloques[65536] -> array_bytes[j];
      }
      if(strcmp(file_disco, filename) == 0){
        //printf("1\n");
        return 1;
      }
      inicio += 32;
      final += 32;
    }
    //printf("0\n");
    return 0;
  }
  if(disk == 3){
    char file_disco[29];
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      int distinta = 0;
      for(int j = inicio; j < final;j++){
        file_disco[j-inicio] = (char) disco -> array_bloques[131072] -> array_bytes[j];
      }
      if(strcmp(file_disco, filename) == 0){
        //printf("1\n");
        return 1;
      }
      inicio += 32;
      final += 32;
    }
    //printf("0\n");
    return 0;
  }
  if(disk == 4){
    char file_disco[29];
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      int distinta = 0;
      for(int j = inicio; j < final;j++){
        file_disco[j-inicio] = (char) disco -> array_bloques[196608] -> array_bytes[j];
      }
      if(strcmp(file_disco, filename) == 0){
        //printf("1\n");
        return 1;
      }
      inicio += 32;
      final += 32;
    }
    //printf("0\n");
    return 0;
  }
}

void cr_ls(unsigned disk){
  //Disco* disco = disco_init(path_disk, disk);
  if(disk == 1){
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      for(int j = inicio; j < final;j++){
        fprintf(stderr, "%c", disco -> array_bloques[0] -> array_bytes[j]);
      }
      inicio += 32;
      final += 32;
      if (inicio < 256 * 32){
        if(disco -> array_bloques[0] -> array_bytes[inicio] != 0)
          fprintf(stderr,"\n");
      }
    }
    fprintf(stderr,"\n");
  }

  if(disk == 2){
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      for(int j = inicio; j < final;j++){
        fprintf(stderr, "%c", disco -> array_bloques[65536] -> array_bytes[j]);
      }
      inicio += 32;
      final += 32;
      if (inicio < 256 * 32){
        if(disco -> array_bloques[65536] -> array_bytes[inicio] != 0)
          fprintf(stderr,"\n");
      }
    }
    fprintf(stderr,"\n");
  }
  if(disk == 3){
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      for(int j = inicio; j < final;j++){
        fprintf(stderr, "%c", disco -> array_bloques[131072] -> array_bytes[j]);
      }
      inicio += 32;
      final += 32;
      if (inicio < 256 * 32){
        if(disco -> array_bloques[131072] -> array_bytes[inicio] != 0)
          fprintf(stderr,"\n");
      }
    }
    fprintf(stderr,"\n");
  }
  if(disk == 4){
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      for(int j = inicio; j < final;j++){
        fprintf(stderr, "%c", disco -> array_bloques[196608] -> array_bytes[j]);
      }
      inicio += 32;
      final += 32;
      if (inicio < 256 * 32){
        if(disco -> array_bloques[196608] -> array_bytes[inicio] != 0)
          fprintf(stderr,"\n");
      }
    }
    fprintf(stderr,"\n");
  }
}
