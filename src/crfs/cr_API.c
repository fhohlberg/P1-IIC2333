#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cr_API.h"
#include <math.h>
#include <stdbool.h>

// Variables Globales //
  char path_disk[255];
  Disco* disco1;
  Disco* disco2;
  Disco* disco3;
  Disco* disco4;
  int disco1_cargado = 0;
  int disco2_cargado = 0;
  int disco3_cargado = 0;
  int disco4_cargado = 0;


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


Disco* disco_init(char *filename, unsigned disk){

  Disco* disco = malloc(sizeof(disco));
  disco -> array_bloques = malloc(sizeof(Bloque*)*((int)pow(2,18)));

  unsigned char bytes[(int)pow(2,13)];
  FILE *archivo = fopen(filename, "rb");
  int tipo_bloque = 5;
  int final_bloque = (int)pow(2,13);
  int inicio_bloque = final_bloque - (int)pow(2,13);
  unsigned char *bytes_malloc = malloc(sizeof(unsigned char)*(int)pow(2,13));
  int particion = 0;

  int i = 0;

  printf("Leyendo el disco: %d ... queda 1 min 30 s\n", disk);

  while(fread(bytes,sizeof(bytes),1,archivo)){

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
    }

    if (disk == 1 && i < 65536){
      //printf("Leyendo el %d bloque.\n", i);
      particion = 1;
      for(int j = 0; j < (int)pow(2,13); j++){
        bytes_malloc[j] = bytes[j];
      }
      disco -> array_bloques[i] = bloque_init(i, tipo_bloque, bytes_malloc, particion);
    }else if (disk == 2 && i < 131072 && i >= 65536){
      //printf("Leyendo el %d bloque.\n", i);
      particion = 2;
      for(int j = 0; j < (int)pow(2,13); j++){
        bytes_malloc[j] = bytes[j];
      }
      disco -> array_bloques[i] = bloque_init(i, tipo_bloque, bytes_malloc, particion);
    }
    else if (disk == 3 && i < 196608 && i >= 131072){
      //printf("Leyendo el %d bloque.\n", i);
      particion= 3;
      for(int j = 0; j < (int)pow(2,13); j++){
        bytes_malloc[j] = bytes[j];
      }
      disco -> array_bloques[i] = bloque_init(i, tipo_bloque, bytes_malloc, particion);
    }else if (disk == 4 && i < 262144 && i >= 196608){
      //printf("Leyendo el %d bloque.\n", i);
      particion = 4;
      for(int j = 0; j < (int)pow(2,13); j++){
        bytes_malloc[j] = bytes[j];
      }
      disco -> array_bloques[i] = bloque_init(i, tipo_bloque, bytes_malloc, particion);
    }

    i++;
  }

  fclose(archivo);
  return disco;
}


void cr_mount(char *diskname){
  char buff[255];
  sprintf(buff, "discos/%s", diskname);
  strcpy(path_disk, buff);
  //disco1 = disco_init(path_disk, 1);
  //disco2 = disco_init(path_disk, 2);
  //disco3 = disco_init(path_disk, 3);
  //disco4 = disco_init(path_disk, 4);
}

void cr_bitmap(unsigned disk, bool hex){
  if(hex == false){
    int libres = 0;
    int ocupadas = 0;
    if(disk == 1 || disk == 0){
      if (disco1_cargado == 0){
        disco1 = disco_init(path_disk, 1);
        disco1_cargado = 1;
      }
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        fprintf(stderr, "%d", disco1 -> array_bloques[1]-> array_bits[j]);
        if(disco1 -> array_bloques[1]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
    }
    if(disk == 2 || disk == 0){
      if (disco2_cargado == 0){
        disco2 = disco_init(path_disk, 2);
        disco2_cargado = 1;
      }
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        fprintf(stderr, "%d", disco2 -> array_bloques[65537]-> array_bits[j]);
        if(disco2 -> array_bloques[65537]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
    }
    if(disk == 3 || disk == 0){
      if (disco3_cargado == 0){
        disco3 = disco_init(path_disk, 3);
        disco3_cargado = 1;
      }
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        fprintf(stderr, "%d", disco3 -> array_bloques[131073]-> array_bits[j]);
        if(disco3 -> array_bloques[131073]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
    }
    if(disk == 4 || disk == 0){
      if (disco4_cargado == 0){
        disco4 = disco_init(path_disk, 4);
        disco4_cargado = 1;
      }
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        fprintf(stderr, "%d", disco4 -> array_bloques[196609]-> array_bits[j]);
        if(disco4 -> array_bloques[196609]-> array_bits[j] == 0)
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
      if (disco1_cargado == 0){
        disco1 = disco_init(path_disk, 1);
        disco1_cargado = 1;
      }
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13)); j++){
        fprintf(stderr, "%04X", disco1 -> array_bloques[1]-> array_bytes[j]);
      }
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        if(disco1 -> array_bloques[1]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
    }
    if(disk == 2 || disk == 0){
      if (disco2_cargado == 0){
        disco2 = disco_init(path_disk, 2);
        disco2_cargado = 1;
      }
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13)); j++){
        fprintf(stderr, "%04X", disco2 -> array_bloques[65537]-> array_bytes[j]);
      }
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        if(disco2 -> array_bloques[65537]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
    }
    if(disk == 3 || disk == 0){
      if (disco3_cargado == 0){
        disco3 = disco_init(path_disk, 3);
        disco3_cargado = 1;
      }
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13)); j++){
        fprintf(stderr, "%04X", disco3 -> array_bloques[131073]-> array_bytes[j]);
      }
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        if(disco3 -> array_bloques[131073]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
      fprintf(stderr, "\n\nPARTICIÓN NÚMERO: %d\n", disk);
      fprintf(stderr, "\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n", libres, ocupadas);
    }
    if(disk == 4 || disk == 0){
      if (disco4_cargado == 0){
        disco4 = disco_init(path_disk, 4);
        disco4_cargado = 1;
      }
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13)); j++){
        fprintf(stderr, "%04X", disco4 -> array_bloques[196609]-> array_bytes[j]);
      }
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        if(disco4 -> array_bloques[196609]-> array_bits[j] == 0)
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
    if (disco1_cargado == 0){
      disco1 = disco_init(path_disk, 1);
      disco1_cargado = 1;
    }
    char file_disco[29];
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      int distinta = 0;
      for(int j = inicio; j < final;j++){
        file_disco[j-inicio] = (char) disco1 -> array_bloques[0] -> array_bytes[j];
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
    if (disco2_cargado == 0){
      disco2 = disco_init(path_disk, 2);
      disco2_cargado = 1;
    }
    char file_disco[29];
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      int distinta = 0;
      for(int j = inicio; j < final;j++){
        file_disco[j-inicio] = (char) disco2 -> array_bloques[65536] -> array_bytes[j];
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
    if (disco3_cargado == 0){
      disco3 = disco_init(path_disk, 3);
      disco3_cargado = 1;
    }
    char file_disco[29];
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      int distinta = 0;
      for(int j = inicio; j < final;j++){
        file_disco[j-inicio] = (char) disco3 -> array_bloques[131072] -> array_bytes[j];
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
    if (disco4_cargado == 0){
      disco4 = disco_init(path_disk, 4);
      disco4_cargado = 1;
    }
    char file_disco[29];
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      int distinta = 0;
      for(int j = inicio; j < final;j++){
        file_disco[j-inicio] = (char) disco4 -> array_bloques[196608] -> array_bytes[j];
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
    if (disco1_cargado == 0){
      disco1 = disco_init(path_disk, 1);
      disco1_cargado = 1;
    }
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      for(int j = inicio; j < final;j++){
        fprintf(stderr, "%c", disco1 -> array_bloques[0] -> array_bytes[j]);
      }
      inicio += 32;
      final += 32;
      if (inicio < 256 * 32){
        if(disco1 -> array_bloques[0] -> array_bytes[inicio] != 0)
          fprintf(stderr,"\n");
      }
    }
    fprintf(stderr,"\n");
  }

  if(disk == 2){
    if (disco2_cargado == 0){
      disco2 = disco_init(path_disk, 2);
      disco2_cargado = 1;
    }
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      for(int j = inicio; j < final;j++){
        fprintf(stderr, "%c", disco2 -> array_bloques[65536] -> array_bytes[j]);
      }
      inicio += 32;
      final += 32;
      if (inicio < 256 * 32){
        if(disco2 -> array_bloques[65536] -> array_bytes[inicio] != 0)
          fprintf(stderr,"\n");
      }
    }
    fprintf(stderr,"\n");
  }
  if(disk == 3){
    if (disco3_cargado == 0){
      disco3 = disco_init(path_disk, 3);
      disco3_cargado = 1;
    }
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      for(int j = inicio; j < final;j++){
        fprintf(stderr, "%c", disco3 -> array_bloques[131072] -> array_bytes[j]);
      }
      inicio += 32;
      final += 32;
      if (inicio < 256 * 32){
        if(disco3 -> array_bloques[131072] -> array_bytes[inicio] != 0)
          fprintf(stderr,"\n");
      }
    }
    fprintf(stderr,"\n");
  }
  if(disk == 4){
    if (disco4_cargado == 0){
      disco4 = disco_init(path_disk, 4);
      disco4_cargado = 1;
    }
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      for(int j = inicio; j < final;j++){
        fprintf(stderr, "%c", disco4 -> array_bloques[196608] -> array_bytes[j]);
      }
      inicio += 32;
      final += 32;
      if (inicio < 256 * 32){
        if(disco4 -> array_bloques[196608] -> array_bytes[inicio] != 0)
          fprintf(stderr,"\n");
      }
    }
    fprintf(stderr,"\n");
  }
}
