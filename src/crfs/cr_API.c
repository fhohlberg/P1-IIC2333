#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cr_API.h"
#include <math.h>
#include <stdbool.h>

// Variables Globales //
  char path_disk[255];
  Disco* disco;

int* byte_to_bits(unsigned char byte){
  int* binary = malloc(sizeof(int)*8);
  for(int n = 0; n < 8; n++){
    binary[7-n] = (byte >> n) & 1;
    //printf("bit %d: %d\n", 7-n, binary[7-n]);
  }

  return binary;
}

int bits_to_int(int* bits, int n){
  int multiplier = 1;
  int bin = 0;
  for (int i = n-1; i >= 0; --i)
  {
    bin += (multiplier * bits[i]);
    multiplier *= 2;
  }
  return bin;
}

unsigned char* int_to_bytes(int n, int cantidad_bytes){
  unsigned char bytes[cantidad_bytes];
  //printf("Numero a convertir: %d\n", n);
  int inicio = (cantidad_bytes * 8) - 8;
  int contador = 0;
  for(int i = inicio; i >= 0; --i){
    bytes[contador] = (n >> inicio) & 0xFF;
    //printf("byte %d: %u\n", contador, bytes[contador]);
    inicio -= 8;
    contador++;
  }
  return bytes;
}

int* int_to_bits(int n, int cantidad_bytes){
  unsigned char bytes[cantidad_bytes];
  //printf("Numero a convertir: %d\n", n);
  int inicio = (cantidad_bytes * 8) - 8;
  int contador = 0;
  for(int i = inicio; i >= 0; --i){
    bytes[contador] = (n >> inicio) & 0xFF;
    //printf("byte %d: %u\n", contador, bytes[contador]);
    inicio -= 8;
    contador++;
  }

  int* bits = malloc(sizeof(int)*cantidad_bytes*8);
  int* bits_aux;
  int cont2 = 0;
  for(int i = 0; i < cantidad_bytes; i++){
    bits_aux = byte_to_bits(bytes[i]);
    for(int j = 0; j < 8; j++){
      bits[cont2] = bits_aux[j];
      cont2 ++;
    }
  }
  return bits;
}

void print_file(crFILE* file){
  fprintf(stderr, "-----------------------------------------------------------\n");
  fprintf(stderr, "Nombre archivo: %s  Tamaño archivo: %d Bytes\n", file -> nombre, file -> tamano);
  fprintf(stderr, "Cantidad de Hardlinks: %d\n", file -> hardlinks);
  fprintf(stderr, "-----------------------------------------------------------\n");
  //for (int i = 0; i < file -> tamano; i++)
    //fprintf(stderr, "%c", file -> data[i]);
}

Bloque* bloque_init(int i, int tipo_bloque, unsigned char *bytes_malloc){

  Bloque* bloque = malloc(sizeof(Bloque));
  bloque -> array_bytes = malloc(sizeof(unsigned char)* (int)pow(2,13));
  bloque -> array_bits= malloc(sizeof(int)* (int)pow(2,13)*8);
  int inicio_bits = 0;

  for (int j = 0; j < (int)pow(2,13); j ++){
    bloque -> array_bytes[j] = bytes_malloc[j];
    int* binary = byte_to_bits(bloque ->array_bytes[j]);
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
      fprintf(stderr, "BLOQUE %d CARGADO!\n", i);
      break;
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

crFILE* cr_open(unsigned disk, char* filename, char mode){
  if(mode == 'r'){
    if(cr_exists(disk, filename) == 1){
      unsigned char bytes_entrada[4];
      int* bits_entrada = malloc(sizeof(int)*24);
      if(disk == 1){
        char file_disco[29];
        int inicio_puntero = 0;
        int final_puntero = 3;
        int inicio = 3;
        int final = 32;
        for(int i = 0; i < 256; i++){
          for(int j = inicio; j < final;j++){
            file_disco[j-inicio] = (char) disco -> array_bloques[0] -> array_bytes[j];
          }
          if(strcmp(file_disco, filename) == 0){
            inicio_puntero = inicio - 3;
            final_puntero = final - 29;
            break;
          }
          inicio += 32;
          final += 32;
        }

        int* bits_aux;
        for(int j = inicio_puntero; j < final_puntero;j++){
          bytes_entrada[j - inicio_puntero] = (char) disco -> array_bloques[0] -> array_bytes[j];
          //fprintf(stderr, "\nbyte: %u bits: ", bytes_entrada[j-inicio_puntero]);
          bits_aux = byte_to_bits(bytes_entrada[j - inicio_puntero]);
          for(int k = 0; k < 8; k++) {
            bits_entrada[8*(j - inicio_puntero) + k] = bits_aux[k];
            //fprintf(stderr, "%d", bits_entrada[8*(j - inicio_puntero) + k]);
          }  
        }
      }
      else if(disk == 2){
        char file_disco[29];
        int inicio_puntero = 0;
        int final_puntero = 3;
        int inicio = 3;
        int final = 32;
        for(int i = 0; i < 256; i++){
          for(int j = inicio; j < final;j++){
            file_disco[j-inicio] = (char) disco -> array_bloques[65536] -> array_bytes[j];
          }
          if(strcmp(file_disco, filename) == 0){
            inicio_puntero = inicio - 3;
            final_puntero = final - 29;
            break;
          }
          inicio += 32;
          final += 32;
        }

        int* bits_aux;
        for(int j = inicio_puntero; j < final_puntero;j++){
          bytes_entrada[j - inicio_puntero] = (char) disco -> array_bloques[65536] -> array_bytes[j];
          //fprintf(stderr, "\nbyte: %u bits: ", bytes_entrada[j-inicio_puntero]);
          bits_aux = byte_to_bits(bytes_entrada[j - inicio_puntero]);
          for(int k = 0; k < 8; k++) {
            bits_entrada[8*(j - inicio_puntero) + k] = bits_aux[k];
            //fprintf(stderr, "%d", bits_entrada[8*(j - inicio_puntero) + k]);
          }  
        }
      }
      else if(disk == 3){
        char file_disco[29];
        int inicio_puntero = 0;
        int final_puntero = 3;
        int inicio = 3;
        int final = 32;
        for(int i = 0; i < 256; i++){
          for(int j = inicio; j < final;j++){
            file_disco[j-inicio] = (char) disco -> array_bloques[131072] -> array_bytes[j];
          }
          if(strcmp(file_disco, filename) == 0){
            inicio_puntero = inicio - 3;
            final_puntero = final - 29;
            break;
          }
          inicio += 32;
          final += 32;
        }

        int* bits_aux;
        for(int j = inicio_puntero; j < final_puntero;j++){
          bytes_entrada[j - inicio_puntero] = (char) disco -> array_bloques[131072] -> array_bytes[j];
          //fprintf(stderr, "\nbyte: %u bits: ", bytes_entrada[j-inicio_puntero]);
          bits_aux = byte_to_bits(bytes_entrada[j - inicio_puntero]);
          for(int k = 0; k < 8; k++) {
            bits_entrada[8*(j - inicio_puntero) + k] = bits_aux[k];
            //fprintf(stderr, "%d", bits_entrada[8*(j - inicio_puntero) + k]);
          }  
        }
      }
      else if(disk == 4){
        char file_disco[29];
        int inicio_puntero = 0;
        int final_puntero = 3;
        int inicio = 3;
        int final = 32;
        for(int i = 0; i < 256; i++){
          for(int j = inicio; j < final;j++){
            file_disco[j-inicio] = (char) disco -> array_bloques[196608] -> array_bytes[j];
          }
          if(strcmp(file_disco, filename) == 0){
            inicio_puntero = inicio - 3;
            final_puntero = final - 29;
            break;
          }
          inicio += 32;
          final += 32;
        }

        int* bits_aux;
        for(int j = inicio_puntero; j < final_puntero;j++){
          bytes_entrada[j - inicio_puntero] = (char) disco -> array_bloques[196608] -> array_bytes[j];
          //fprintf(stderr, "\nbyte: %u bits: ", bytes_entrada[j-inicio_puntero]);
          bits_aux = byte_to_bits(bytes_entrada[j - inicio_puntero]);
          for(int k = 0; k < 8; k++) {
            bits_entrada[8*(j - inicio_puntero) + k] = bits_aux[k];
            //fprintf(stderr, "%d", bits_entrada[8*(j - inicio_puntero) + k]);
          }  
        }
      }
      //fprintf(stderr, "\n");
      if (bits_entrada[0] == 1){
        crFILE* file = malloc(sizeof(crFILE));
        file -> pos_lect = 0;
        file -> nombre = filename;
        int bits_puntero[23];
        for(int i = 0; i < 23; i ++){
          bits_puntero[i] = bits_entrada[i + 1];
          //fprintf(stderr, "%d", bits_puntero[i]);
        }
        int bloque_indice = bits_to_int(bits_puntero, 23);
        //fprintf(stderr, "bloque indice: %d\n", bloque_indice);
        cargar_bloque(disco, bloque_indice);
        
        int referencias;
        int bits_ref[32];
        for(int i = 0; i < 32; i++){
          bits_ref[i] = disco -> array_bloques[bloque_indice] -> array_bits[i];
          //fprintf(stderr, "%u", disco -> array_bloques[bloque_indice] -> array_bits[i]);
        }
        referencias = bits_to_int(bits_ref, 32);
        file -> hardlinks = referencias;
        //fprintf(stderr, "\n");
        //fprintf(stderr, "%d\n", referencias);

        int tamano;
        int bits_tam[64];
        for(int i = 32; i < 96; i++){
          bits_tam[i - 32] = disco -> array_bloques[bloque_indice] -> array_bits[i];
          //fprintf(stderr, "%u", disco -> array_bloques[bloque_indice] -> array_bits[i]);
        }
        tamano = bits_to_int(bits_tam, 64);
        file -> tamano = tamano;
        //fprintf(stderr, "\nLeyendo %d Bytes del archivo: %s\n", file -> tamano, file -> nombre);
        //fprintf(stderr, "\n");
        //fprintf(stderr, "%d\n", tamano);
        if(file -> tamano != 0){
          file -> data = malloc(sizeof(unsigned char)* (file -> tamano));
          int bloque_dato;
          int contador = 0;
          int inicio = 12 * 8;//96
          for(int i = 0; i < 2044; i++){
            int bits_puntero_dato[32];
            for(int j = inicio; j < (inicio + 32); j++){ //((int) pow(2,13) * 8) - 32
                bits_puntero_dato[j - inicio] = disco -> array_bloques[bloque_indice] -> array_bits[j];
                //fprintf(stderr, "%d", disco -> array_bloques[bloque_indice] -> array_bits[j]);
            }
            bloque_dato = bits_to_int(bits_puntero_dato, 32);
            if (bloque_dato != 0){
              //fprintf(stderr, "bloque dato: %d\n", bloque_dato);
              cargar_bloque(disco, bloque_dato);
              for(int k = 0; k < (int) pow(2,13); k++){
                if(disco -> array_bloques[bloque_dato] -> array_bytes[k] != 0){
                  file -> data[contador] = disco -> array_bloques[bloque_dato] -> array_bytes[k];
                  //fprintf(stderr, "%c", disco -> array_bloques[bloque_dato] -> array_bytes[k]);
                  contador++;
                  //printf("contador: %d\n", contador);
                }
              }
            }
            inicio += 32;
          }

          int bits_puntero_indirecto[32];
          int bloque_indirecto;
          for(int j = ((int) pow(2,13)*8) - 32; j < (int) pow(2,13) * 8; j++){ 
              bits_puntero_indirecto[j - ((int) pow(2,13)*8 - 32)] = disco -> array_bloques[bloque_indice] -> array_bits[j];
              //fprintf(stderr, "%d", disco -> array_bloques[bloque_indice] -> array_bits[j]);
          }
          bloque_indirecto = bits_to_int(bits_puntero_indirecto, 32);
          if (bloque_indirecto != 0){
            //fprintf(stderr, "bloque dato: %d\n", bloque_dato);
            cargar_bloque(disco, bloque_indirecto);

            for(int i = 0; i < 2048; i++){
              int inicio1 = 0;
              int bits_puntero_dato1[32];
              int bloque_dato1;
              for(int j = inicio1; j < (inicio1 + 32); j++){ //((int) pow(2,13) * 8) - 32
                  bits_puntero_dato1[j - inicio1] = disco -> array_bloques[bloque_indirecto] -> array_bits[j];
                  //fprintf(stderr, "%d", disco -> array_bloques[bloque_indice] -> array_bits[j]);
              }
              bloque_dato1 = bits_to_int(bits_puntero_dato1, 32);
              for(int k = 0; k < (int) pow(2,13); k++){
                if(disco -> array_bloques[bloque_dato1] -> array_bytes[k] != 0){
                  file -> data[contador] = disco -> array_bloques[bloque_dato1] -> array_bytes[k];
                  //fprintf(stderr, "%c", disco -> array_bloques[bloque_dato] -> array_bytes[k]);
                  contador++;
                  //printf("contador: %d\n", contador);
                }
              }
              inicio1 += 32;
            } 
          }
        }
        
        print_file(file);
        return file;
      }
      else{
        fprintf(stderr, "El archivo %s ha sido eliminado.\n", filename);
      } 
    }
    else{
      fprintf(stderr, "El archivo %s no estiste.\n", filename);
    }
  }
  else if (mode == 'w'){
    if(cr_exists(disk, filename) == 0){
      int valida = 1;
      int pos_dir = 0;
      if(disk == 1)
        pos_dir = 0;
      else if(disk == 2)
        pos_dir = 65536;
      else if(disk == 3)
        pos_dir = 131072;
      else if(disk == 4)
        pos_dir = 196608;
      else{
        valida = 0;
        fprintf(stderr, "Partición %d no es válida.\n", disk);
      }
      if(valida){
        fprintf(stderr, "pos_dir : %d\n", pos_dir);
        char file_disco[32];
        int inicio = 0;
        int final = 32;
        for(int i = 0; i < 256; i++){
          int diferido = 0;
          for(int j = inicio; j < final;j++){
            file_disco[j-inicio] = (char) disco -> array_bloques[pos_dir] -> array_bytes[j];
            if(file_disco[j-inicio] != 0)
              diferido = 1;
          }
          if(diferido == 0){
            break;
          }
          inicio += 32;
          final += 32;
        }

        int* bits_bloque_indice;
        int bloque_indice_libre = -1;
        for( int j = 3; j < ((int) pow(2,13))*8; j++){
          if(disco -> array_bloques[pos_dir + 1]-> array_bits[j] == 0){
            bloque_indice_libre = j + ((((int) pow(2,13))*8)*(disk -1));
            disco -> array_bloques[pos_dir + 1]-> array_bits[j] = 1;
            break;
          }
        }
        if(bloque_indice_libre != -1){
          bits_bloque_indice = int_to_bits(bloque_indice_libre, 3);
          for(int i = 0; i < 24; i++){
            bits_bloque_indice[0] = 1;
          }
        }
        unsigned char bytes_nombre[29];
        for(int i = 0; i < 29; i++){
          bytes_nombre[i] = 0;
        }
        strcpy(bytes_nombre, filename);

        int bits_nombre[232];
        int* bits_nombre_aux;
        int cont = 0;
        for(int i = 0; i < 29; i++){
          bits_nombre_aux = byte_to_bits(bytes_nombre[i]);
          for(int j = 0; j < 8; j++){
            bits_nombre[cont] = bits_nombre_aux[j];
            cont++;
          }
        }
        int cont2 = 0;
        //printf("inicio: %d, final: %d\n", inicio, final);
        for(int i = inicio; i < final; i++){
          int bits_aux[8];
          for( int j = 0; j < 8; j++){
            if(i < inicio + 3){
              disco -> array_bloques[pos_dir] -> array_bits[cont2] =  bits_bloque_indice[cont2];
            }
            else{
              disco -> array_bloques[pos_dir] -> array_bits[cont2] =  bits_nombre[cont2 - 24];
            }
            bits_aux[j] = disco -> array_bloques[pos_dir] -> array_bits[cont2];
            cont2 ++;
          }
          unsigned char byte_aux = bits_to_int(bits_aux, 8);
          disco -> array_bloques[pos_dir] -> array_bytes[i] = byte_aux;
        }
        cr_open(disk, filename, 'r');
      }
    }
    else{
      fprintf(stderr, "El archivo %s ya existe, no se puede sobre escribir.\n", filename);
    }
    return 0;
  }
}

int cr_read(crFILE* file, void* buffer, int nbytes){
  int bytes_restantes = file -> tamano - file -> pos_lect;
  int inicio = file ->  pos_lect;
  if(nbytes > bytes_restantes){
    file -> pos_lect += bytes_restantes;

  }
  else{
    file -> pos_lect += nbytes;
    bytes_restantes = nbytes;
  }
  //fprintf(stderr, "\nLeyendo %d Bytes del archivo: %s\n", bytes_restantes, file -> nombre);
  for(int i = inicio; i < file -> pos_lect; i++){
    fprintf(stderr, "%u ", file -> data[i]);
  }

  return bytes_restantes;

}
  
