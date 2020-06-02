#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cr_API.h"
#include <math.h>
#include <stdbool.h>

// Variables Globales //
  char path_disk[255];
  Disco* disco;
  int* bloques_cargados;
  int pos_bloques_cargados = 0;
  int cnt = 0;
  int cnt2 = 0;
  int load = 0;
  int load2 = 0;


////////////////////////
// FUNCIONES ENUNIADO //
////////////////////////

void cr_mount(char *diskname){
  bloques_cargados = malloc(sizeof(int) * (int) pow(2,18));
  char buff[255];
  sprintf(buff, "discos/%s", diskname);
  strcpy(path_disk, buff);
  disco = disco_init(path_disk);
}

void cr_bitmap(unsigned disk, bool hex){
  if(disk == 0){
    cr_bitmap(1, hex);
    cr_bitmap(2, hex);
    cr_bitmap(3, hex);
    cr_bitmap(4, hex);
    return;
  }

  if(hex == true && disk > 0 && disk < 5){
    fprintf(stderr, "\n\n----------------------------------------\n");
    fprintf(stderr, "BITMAP HEXADECIMAL PARTICIÓN NÚMERO: %d", disk);
    fprintf(stderr, "\n----------------------------------------\n\n");
  }
  else if (hex == false && disk > 0 && disk < 5){
    fprintf(stderr, "\n\n----------------------------------------\n");
    fprintf(stderr, "BITMAP BINARIO PARTICIÓN NÚMERO: %d", disk);
    fprintf(stderr, "\n----------------------------------------\n\n");
  }
  
  if(hex == false){
    int libres = 0;
    int ocupadas = 0;
    if(disk == 1){
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        fprintf(stderr, "%d", disco -> array_bloques[1]-> array_bits[j]);
        if(disco -> array_bloques[1]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
    }
    else if(disk == 2){
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        fprintf(stderr, "%d", disco -> array_bloques[65537]-> array_bits[j]);
        if(disco -> array_bloques[65537]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
    }
    else if(disk == 3){
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        fprintf(stderr, "%d", disco -> array_bloques[131073]-> array_bits[j]);
        if(disco -> array_bloques[131073]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
    }
    else if(disk == 4){
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        fprintf(stderr, "%d", disco -> array_bloques[196609]-> array_bits[j]);
        if(disco -> array_bloques[196609]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
    }
    else{
      fprintf(stderr, "\nNo existe la partición indicada.\n");
    }
    if(disk > 0 && disk < 5)
      fprintf(stderr, "\n\nRESUMEN BITMAP BINARIO PARTICIÓN %d:\n\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n\n\n", disk,libres, ocupadas);

  }
  //HEXADECIMAL
  else{
    int libres = 0;
    int ocupadas = 0;
    if(disk == 1){
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13)); j++){
        fprintf(stderr, "%04X ", disco -> array_bloques[1]-> array_bytes[j]);
      }
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        if(disco -> array_bloques[1]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
    }
    else if(disk == 2){
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13)); j++){
        fprintf(stderr, "%04X ", disco -> array_bloques[65537]-> array_bytes[j]);
      }
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        if(disco -> array_bloques[65537]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
    }
    else if(disk == 3){
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13)); j++){
        fprintf(stderr, "%04X ", disco -> array_bloques[131073]-> array_bytes[j]);
      }
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        if(disco -> array_bloques[131073]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
    }
    else if(disk == 4){
      libres = 0;
      ocupadas = 0;
      for( int j = 0; j < ((int) pow(2,13)); j++){
        fprintf(stderr, "%04X ", disco -> array_bloques[196609]-> array_bytes[j]);
      }
      for( int j = 0; j < ((int) pow(2,13))*8; j++){
        if(disco -> array_bloques[196609]-> array_bits[j] == 0)
          libres += 1;
        else
          ocupadas += 1;
      }
    }
    else{
      fprintf(stderr, "\nNo existe la partición indicada.\n");
    }

    fprintf(stderr, "\n\nRESUMEN BITMAP HEXADECIMAL PARTICIÓN %d:\n\nCANTIDAD BLOQUES LIBRES: %d\nCANTIDAD BLOQUES OCUPADOS: %d\n\n\n", disk,libres, ocupadas);
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

  if(disk > 0 && disk < 5){
    fprintf(stderr,"---------------------------------------\n");
    fprintf(stderr,"Archivos directorio de la partición: %d\n", disk);
    fprintf(stderr,"---------------------------------------\n");
  }

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

  else if(disk == 2){
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
  else if(disk == 3){
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
  else if(disk == 4){
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
  else{
    fprintf(stderr,"\nNo existe la partición ingresada.\n\n");
  }
}

crFILE* cr_open(unsigned disk, char* filename, char mode){
  int* bits_entrada = malloc(sizeof(int)*24);
  if(mode == 'r'){
    if(cr_exists(disk, filename) == 1){
      unsigned char bytes_entrada[4];
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
          free(bits_aux);
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
          free(bits_aux);
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
          free(bits_aux);
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
          free(bits_aux);
        }
      }
    //  fprintf(stderr, "bits validacion %d\n",bits_entrada[0]);
      if (bits_entrada[0] == 1){
        crFILE* file = malloc(sizeof(crFILE));
        file -> pos_lect = 0;
        file -> nombre = filename;
        file -> disk = disk;
        int bits_puntero[23];
        for(int i = 0; i < 23; i ++){
          bits_puntero[i] = bits_entrada[i + 1];
          //fprintf(stderr, "%d", bits_psuntero[i]);
        }
        int bloque_indice = bits_to_int(bits_puntero, 23);

        unsigned char aux_particion = filename[0];
        char aux_filename[255];
        //SOY UN SOFTLINK
        if (bloque_indice == 0){
          //fprintf(stderr, "str len: %d\n", strlen(filename) -2);
          strncpy(aux_filename, filename + 2, 255);
          char aux2_filename[255];
          strcpy(aux2_filename, aux_filename);
          //fprintf(stderr, "FILE NAME: %s\n", aux2_filename);

          if (aux_particion == '1'){
            //crFILE *file = cr_open(1, aux2_filename,mode);
            free(file);
            free(bits_entrada);
            return cr_open(1, aux2_filename,mode);;
          }
          else if (aux_particion == '2'){
            //crFILE *file = cr_open(2, aux2_filename,mode);
            free(file);
            free(bits_entrada);
            return cr_open(2, aux2_filename,mode);
          }
          else if (aux_particion == '3'){
            //crFILE *file = cr_open(3, aux2_filename,mode);
            free(file);
            free(bits_entrada);
            return cr_open(3, aux2_filename,mode);
          }
          else if (aux_particion == '4'){
            //crFILE *file = cr_open(4, aux2_filename,mode);
            free(file);
            free(bits_entrada);
            return cr_open(4, aux2_filename,mode);
          }
        }

        int cargado = 0;
        for(int a = 0; a < pos_bloques_cargados; a++){
          if(bloques_cargados[a] == bloque_indice){
            //fprintf(stderr, "ENTREEEE\n");
            cargado = 1;
          }
        }
        if(cargado == 0){
          cargar_bloque(disco, bloque_indice);
          for(int i = 0; i < 32; i++){
            if( i == 31)
              disco -> array_bloques[bloque_indice] -> array_bits[i] = 1;
            else
              disco -> array_bloques[bloque_indice] -> array_bits[i] = 0;
          }
          for(int i = 0; i < 4; i++){
            if( i == 4)
              disco -> array_bloques[bloque_indice] -> array_bits[i] = 1;
            else
              disco -> array_bloques[bloque_indice] -> array_bits[i] = 0;
          }
        }
        //fprintf(stderr, "bloque indice: %d\n", bloque_indice);
        

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

        unsigned long long int tamano;
        int bits_tam[64];
        //fprintf(stderr, "Tamaño: ");
        for(int i = 32; i < 96; i++){
          bits_tam[i - 32] = disco -> array_bloques[bloque_indice] -> array_bits[i];
          //fprintf(stderr, "%u", disco -> array_bloques[bloque_indice] -> array_bits[i]);
        }
        //fprintf(stderr, "\n");
        tamano = bits_to_int(bits_tam, 64);
        file -> tamano = tamano;
        file -> bloque_indice = bloque_indice;
        file -> pos_esc = file -> tamano;
        //fprintf(stderr, "\nLeyendo %d Bytes del archivo: %s\n", file -> tamano, file -> nombre);
        //fprintf(stderr, "\n");
        //fprintf(stderr, "%d\n", tamano);
        if(load == 0)
          print_file(file);
        free(bits_entrada);
        return file;
      }
      else{
        fprintf(stderr, "El archivo %s ha sido eliminado.\n", filename);
        free(bits_entrada);
        return 0;
      }
    }
    else{
      fprintf(stderr, "El archivo %s no existe.\n", filename);
      free(bits_entrada);
      return 0;
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
        //fprintf(stderr, "pos_dir : %d\n", pos_dir);
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

        if(inicio != 32 * 256){
          int* bits_bloque_indice;
          int bloque_indice_libre = -1;
          for( int j = 2; j < ((int) pow(2,13))*8; j++){
            if(disco -> array_bloques[pos_dir + 1]-> array_bits[j] == 0){
              bloque_indice_libre = j + ((((int) pow(2,13))*8)*(disk -1));
              disco -> array_bloques[pos_dir + 1]-> array_bits[j] = 1;
              break;
            }
          }
          if(bloque_indice_libre != -1){
            //printf("\nBloque indice asignado: %d\n", bloque_indice_libre);
            bits_bloque_indice = int_to_bits(bloque_indice_libre, 3);
            //for(int i = 0; i < 24; i++){
              //fprintf(stderr, "%d", bits_bloque_indice[i]);
            //}
            //printf("\n");
            bits_bloque_indice[0] = 1;
          }
          else{
            fprintf(stderr, "\nNo quedan bloques índices libres.\n");
            free(bits_entrada);
            return 0;
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
            free(bits_nombre_aux);
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
          free(bits_entrada);
          free(bits_bloque_indice);
          return cr_open(disk, filename, 'r');
        }
        else{
          fprintf(stderr, "No hay espacio en directorio para crear el archivo.\n");
          free(bits_entrada);
          return 0;
        }
      }
    }
    else{
      fprintf(stderr, "El archivo %s ya existe, no se puede sobre escribir.\n", filename);
      free(bits_entrada);
      return 0;
    }
  }
  free(bits_entrada);
  return 0;
}

int cr_read(crFILE* file, void* buffer, int nbytes){
  if(file == 0){
    return 0;
  }
  unsigned long long int bytes_restantes = file -> tamano - file -> pos_lect;
  int inicio_lectura = file ->  pos_lect;
  int bloque_actual = (int) (inicio_lectura / (int) pow(2,13));
  int byte_actual = inicio_lectura - (bloque_actual*(int) pow(2,13));


  if(nbytes > bytes_restantes){
    file -> pos_lect += bytes_restantes;
  }
  else{
    file -> pos_lect += nbytes;
    bytes_restantes = nbytes;
  }

  buffer = malloc(sizeof(unsigned char) * bytes_restantes);
  unsigned char * buff;
  buff = (unsigned char*)buffer;
  int contador = 0;
  if(file -> tamano != 0){

    int bloque_dato;
    int inicio = 12 * 8;//96
    int parar = 0;

    for(int i = 0; i < 2044; i++){
      if (i >= bloque_actual && parar == 0){
        int bits_puntero_dato[32];
        for(int j = inicio; j < (inicio + 32); j++){ //((int) pow(2,13) * 8) - 32
            bits_puntero_dato[j - inicio] = disco -> array_bloques[file -> bloque_indice] -> array_bits[j];
            //fprintf(stderr, "%d", disco -> array_bloques[bloque_indice] -> array_bits[j]);
        }
        bloque_dato = bits_to_int(bits_puntero_dato, 32);
        if (bloque_dato != 0){
          //fprintf(stderr, "bloque dato: %d\n", bloque_dato);
          //fprintf(stderr, pos)
          int cargado = 0;
          for(int a = 0; a < pos_bloques_cargados; a++){
            //fprintf(stderr, "\nSoy bloque cargado: %d = bloque dato: %d\n", bloques_cargados[a] , bloque_dato);
            if(bloques_cargados[a] == bloque_dato){
              //printf("\nENTRE\n");
              cargado = 1;
            }
          }
          if(cargado == 0){
            cargar_bloque(disco, bloque_dato);
          }
          //fprintf(stderr, "\nLeyendo en el bloque de datos %d\n", bloque_dato);
          for(int k = 0; k < (int) pow(2,13); k++){
            if(disco -> array_bloques[bloque_dato] -> array_bytes[k] != 0 && k >= byte_actual){
              //fprintf(stderr, "BYTE ACTUAL: %d =< %d\n", byte_actual, k);
              buff[contador] = disco -> array_bloques[bloque_dato] -> array_bytes[k];
              //fprintf(stderr, "%c", buff[contador]);
              //file -> data[contador] = disco -> array_bloques[bloque_dato] -> array_bytes[k];
              //fprintf(stderr, "%c", disco -> array_bloques[bloque_dato] -> array_bytes[k]);
              //fprintf(stderr, "Contador: %d\n", contador);
              contador++;
              if(contador == bytes_restantes){
                parar = 1;
                break;
              }
              //printf("contador: %d\n", contador);
            }
          }
        }
        inicio += 32;
      }
    }

    if(bloque_actual >= 2044 && parar == 0){
      int parar2 = 0;
      int bits_puntero_indirecto[32];
      int bloque_indirecto;
      for(int j = ((int) pow(2,13)*8) - 32; j < (int) pow(2,13) * 8; j++){
          bits_puntero_indirecto[j - ((int) pow(2,13)*8 - 32)] = disco -> array_bloques[file -> bloque_indice] -> array_bits[j];
          //fprintf(stderr, "%d", disco -> array_bloques[bloque_indice] -> array_bits[j]);
      }
      bloque_indirecto = bits_to_int(bits_puntero_indirecto, 32);
      if (bloque_indirecto != 0){
        //fprintf(stderr, "bloque dato: %d\n", bloque_dato);
        int cargado = 0;
        for(int a = 0; a < pos_bloques_cargados; a++){
          if(bloques_cargados[a] == bloque_indirecto)
            cargado = 1;
        }
        if(cargado == 0)
          cargar_bloque(disco, bloque_indirecto);
        int inicio1 = 0;
        for(int i = 0; i < 2048; i++){
          if (i >= (bloque_actual - 2044) && parar2 == 0){
            int bits_puntero_dato1[32];
            int bloque_dato1;
            for(int j = inicio1; j < (inicio1 + 32); j++){ //((int) pow(2,13) * 8) - 32
                bits_puntero_dato1[j - inicio1] = disco -> array_bloques[bloque_indirecto] -> array_bits[j];
                //fprintf(stderr, "%d", disco -> array_bloques[bloque_indice] -> array_bits[j]);
            }
            bloque_dato1 = bits_to_int(bits_puntero_dato1, 32);
            for(int k = 0; k < (int) pow(2,13); k++){
              if(disco -> array_bloques[bloque_dato1] -> array_bytes[k] != 0 && k >= byte_actual){
                buff[contador] = disco -> array_bloques[bloque_dato1] -> array_bytes[k];
                //file -> data[contador] = disco -> array_bloques[bloque_dato1] -> array_bytes[k];
                //fprintf(stderr, "%c", disco -> array_bloques[bloque_dato] -> array_bytes[k]);
                contador++;
                if( contador > bytes_restantes){
                  parar2 = 1;
                  break;
                }
                //printf("contador: %d\n", contador);
              }
            }
          }
          inicio1 += 32;
        }
      }
    }
  }

  if(load2 == 0){
    for(int i = 0; i < contador; i++){
        fprintf(stderr, "%c", buff[i]);
      }
  }
  free(buffer);
  return contador;
}

int cr_write(crFILE* file, void* buffer, int nbytes){
  if(file == 0){
    return 0;
  }
  int pos_dir = 0;
  //printf("NOMBRE ARCHIVO: %s\n", file -> nombre);
  if(file -> disk == 1)
    pos_dir = 0;
  else if(file -> disk == 2)
    pos_dir = 65536;
  else if(file -> disk == 3)
    pos_dir = 131072;
  else
    pos_dir = 196608;

  int bloque_actual = (int) (file -> pos_esc / (int) pow(2,13));
  int byte_actual = file -> pos_esc - (bloque_actual*(int) pow(2,13)); // entre 0 y 2^13

  int bloques_necesarios = (int) (nbytes / (int) pow(2,13)) + 1;

  int byte_restantes = (int) pow(2,13) - byte_actual;

  unsigned char* buff;
  buff = (unsigned char*)buffer;

  int bloque_dato;
  int contador = 0;
  int inicio = 12 * 8;//96
  int parar = 0;
  int contador_bloques = 0;
  for(int i = 0; i < 2044; i++){
    if (i >= bloque_actual && parar == 0){
      int bits_puntero_dato[32];
      for(int j = inicio; j < (inicio + 32); j++){ //((int) pow(2,13) * 8) - 32
        bits_puntero_dato[j - inicio] = disco -> array_bloques[file -> bloque_indice] -> array_bits[j];
        //fprintf(stderr, "%d", disco -> array_bloques[file -> bloque_indice] -> array_bits[j]);
      }

      bloque_dato = bits_to_int(bits_puntero_dato, 32);
      //printf("bloque dato: %d", bloque_dato);
      if(bloque_dato == 0){
        //printf("No tengo bloque de datos asignado..\n");
        //revisar que hayan bloques libres en el bitmap
        int puntero_datos[32];
        int bloque_datos_libre = 0;
        for( int j = 2; j < ((int) pow(2,13))*8; j++){
          if(disco -> array_bloques[pos_dir + 1]-> array_bits[j] == 0){
            bloque_datos_libre = j + ((((int) pow(2,13))*8)*(file -> disk -1));
            disco -> array_bloques[pos_dir + 1]-> array_bits[j] = 1;
            break;
          }
        }
        if(bloque_datos_libre != 0){
          int cargado = 0;
          for(int a = 0; a < pos_bloques_cargados; a++){
            if(bloques_cargados[a] == bloque_datos_libre)
              cargado = 1;
          }
          if(cargado == 0){
            //printf("Cargando bloque: %d\n", file -> bloque_indice);
            cargar_bloque(disco, bloque_datos_libre);
          }
          //fprintf(stderr, "\nbloque datos libre: %d\n", bloque_datos_libre);
          cnt = 0;
          int m = funcion_aux(bloque_datos_libre);
          cnt2 = 0;
          int puntero_datos_aux[cnt];
          binario_largo(bloque_datos_libre, puntero_datos_aux);
          //puntero_datos = int_to_bits(bloque_datos_libre, 4);
          int bits_32_puntero[32];

          int cnt3 = 0;
          for(int n = 0; n < 32; n++){
            if(n < 32 - cnt2){
              puntero_datos[n] = 0;
              //printf("0");
            }
            else{
              puntero_datos[n] = puntero_datos_aux[cnt3];
              //printf("%d", bits_tamano[cnt3]);
              cnt3++;
            }
          }

          //printf("Puntero datos: ");
          for(int j = inicio; j < (inicio + 32); j++){ //((int) pow(2,13) * 8) - 32
            disco -> array_bloques[file -> bloque_indice] -> array_bits[j] = puntero_datos[j - inicio];
            //printf("%d", puntero_datos[j - inicio]);
          }
          //printf("\n");
        }
        bloque_dato = bloque_datos_libre;
        
      }
      if (bloque_dato != 0){
        //fprintf(stderr, "bloque dato: %d\n", bloque_dato);
        int cargado = 0;
        for(int a = 0; a < pos_bloques_cargados; a++){
          if(bloques_cargados[a] == bloque_dato)
            cargado = 1;
        }
        if(cargado == 0)
          cargar_bloque(disco, bloque_dato);
        //fprintf(stderr, "\nEscribiendo en bloque de datos: %d\n", bloque_dato);
        for(int k = 0; k < (int) pow(2,13); k++){
          if(k == byte_actual){
            disco -> array_bloques[bloque_dato] -> array_bytes[k] = buff[contador];
            contador++;
            byte_actual++;
            if(contador == nbytes){
              parar = 1;
              break;
            }
            //printf("contador: %d\n", contador);
          }
        }
      }
      else{
        fprintf(stderr, "\nNo queda memoria.\n");
        parar = 1;
        break;
      }
    }
    inicio += 32;
  }


  if(bloque_actual >= 2044 && parar == 0){
    int parar2 = 0;
    int bits_puntero_indirecto[32];
    int bloque_indirecto;
    for(int j = ((int) pow(2,13)*8) - 32; j < (int) pow(2,13) * 8; j++){
        bits_puntero_indirecto[j - ((int) pow(2,13)*8 - 32)] = disco -> array_bloques[file -> bloque_indice] -> array_bits[j];
        //fprintf(stderr, "%d", disco -> array_bloques[bloque_indice] -> array_bits[j]);
    }
    bloque_indirecto = bits_to_int(bits_puntero_indirecto, 32);
    int inicio1 = 0;
    if(bloque_indirecto == 0){
      //revisar que hayan bloques libres en el bitmap
      int puntero_datos2[32];
      int bloque_datos_libre2 = 0;
      for( int j = 2; j < ((int) pow(2,13))*8; j++){
        if(disco -> array_bloques[pos_dir + 1]-> array_bits[j] == 0){
          bloque_datos_libre2 = j + ((((int) pow(2,13))*8)*(file -> disk -1));
          disco -> array_bloques[pos_dir + 1]-> array_bits[j] = 1;
          break;
        }
      }
      if(bloque_datos_libre2 != 0){
        int cargado = 0;
        for(int a = 0; a < pos_bloques_cargados; a++){
          if(bloques_cargados[a] == bloque_datos_libre2)
            cargado = 1;
        }
        if(cargado == 0)
          cargar_bloque(disco, bloque_datos_libre2);

        cnt = 0;
        int m = funcion_aux(bloque_datos_libre2);
        cnt2 = 0;
        int puntero_datos2_aux[cnt];
        binario_largo(bloque_datos_libre2, puntero_datos2_aux);
        //puntero_datos = int_to_bits(bloque_datos_libre, 4);


        int cnt10 = 0;
        for(int n = 0; n < 32; n++){
          if(n < 32 - cnt2){
            puntero_datos2[n] = 0;
            //printf("0");
          }
          else{
            puntero_datos2[n] = puntero_datos2_aux[cnt10];
            //printf("%d", bits_tamano[cnt3]);
            cnt10++;
          }
        }

        //puntero_datos2 = int_to_bits(bloque_datos_libre2, 4);
        for(int j = 0; j < 32; j++){ //((int) pow(2,13) * 8) - 32
          disco -> array_bloques[file -> bloque_indice] -> array_bits[8188 + j] = puntero_datos2[j];
        }
        //free(puntero_datos2);
      }
      bloque_indirecto = bloque_datos_libre2;
    }
    if (bloque_indirecto != 0){
      inicio1 = 0;
      int cargado = 0;
      for(int a = 0; a < pos_bloques_cargados; a++){
        if(bloques_cargados[a] == bloque_indirecto)
          cargado = 1;
      }
      if(cargado == 0)
        cargar_bloque(disco, bloque_indirecto);

      for(int i = 0; i < 2048; i++){
        if (i >= (bloque_actual - 2044) && parar2 == 0){
          int bits_puntero_dato1[32];
          int bloque_dato1;
          for(int j = inicio1; j < (inicio1 + 32); j++){ //((int) pow(2,13) * 8) - 32
              bits_puntero_dato1[j - inicio1] = disco -> array_bloques[bloque_indirecto] -> array_bits[j];
              //fprintf(stderr, "%d", disco -> array_bloques[bloque_indice] -> array_bits[j]);
          }
          bloque_dato1 = bits_to_int(bits_puntero_dato1, 32);
          if(bloque_dato1 == 0){
            //revisar que hayan bloques libres en el bitmap
            int puntero_datos1[32];
            int bloque_datos_libre1 = 0;
            for( int j = 2; j < ((int) pow(2,13))*8; j++){
              if(disco -> array_bloques[pos_dir + 1]-> array_bits[j] == 0){
                bloque_datos_libre1 = j + ((((int) pow(2,13))*8)*(file -> disk -1));
                disco -> array_bloques[pos_dir + 1]-> array_bits[j] = 1;
                break;
              }
            }
            if(bloque_datos_libre1 != 0){
              int cargado = 0;
              for(int a = 0; a < pos_bloques_cargados; a++){
                if(bloques_cargados[a] == bloque_datos_libre1)
                  cargado = 1;
              }
              if(cargado == 0)
                cargar_bloque(disco, bloque_datos_libre1);

              cnt = 0;
              int m = funcion_aux(bloque_datos_libre1);
              cnt2 = 0;
              int puntero_datos1_aux[cnt];
              binario_largo(bloque_datos_libre1, puntero_datos1_aux);
              //puntero_datos = int_to_bits(bloque_datos_libre, 4);


              int cnt12 = 0;
              for(int n = 0; n < 32; n++){
                if(n < 32 - cnt2){
                  puntero_datos1[n] = 0;
                  //printf("0");
                }
                else{
                  puntero_datos1[n] = puntero_datos1_aux[cnt12];
                  //printf("%d", bits_tamano[cnt3]);
                  cnt12++;
                }
              }

              //puntero_datos1 = int_to_bits(bloque_datos_libre1, 4);
              for(int j = inicio1; j < (inicio1 + 32); j++){ //((int) pow(2,13) * 8) - 32
                disco -> array_bloques[bloque_indirecto] -> array_bits[j] = puntero_datos1[j - inicio1];
              }
              //free(puntero_datos1);
            }
            bloque_dato1 = bloque_datos_libre1;
            
          }
          if (bloque_dato1 != 0){
            //fprintf(stderr, "bloque dato: %d\n", bloque_dato);
            int cargado = 0;
            for(int a = 0; a < pos_bloques_cargados; a++){
              if(bloques_cargados[a] == bloque_dato1)
                cargado = 1;
            }
            if(cargado == 0)
              cargar_bloque(disco, bloque_dato1);
            fprintf(stderr, "\nEscribiendo en bloque de datos: %d\n", bloque_dato1);
            for(int k = 0; k < (int) pow(2,13); k++){
              if(k == byte_actual){
                disco -> array_bloques[bloque_dato1] -> array_bytes[k] = buff[contador];
                contador++;
                byte_actual++;
                if(contador == nbytes){
                  parar2 = 1;
                  break;
                }
              }
            }
          }
          else{
            fprintf(stderr, "\nNo queda memoria.\n");
            parar2 = 1;
            break;
          }
        }
        inicio1 += 32;
      }
    }
  }
  file -> pos_esc += contador;
  file -> tamano += contador;

  //fprintf(stderr,"TAMANO FILE: %d\n" ,file ->tamano);
  cnt = 0;
  int m = funcion_aux(file ->tamano);
  cnt2 = 0;
  int bits_tamano[cnt];
  binario_largo(file -> tamano, bits_tamano);

  int bits_64_tamano[64];

  int cnt3 = 0;
  for(int n = 0; n < 64; n++){
    if(n < 64 - cnt2){
      bits_64_tamano[n] = 0;
      //printf("0");
    }
    else{
      bits_64_tamano[n] = bits_tamano[cnt3];
      //printf("%d", bits_tamano[cnt3]);
      cnt3++;
    }
  }
  for(int n = 32; n < 96; n++)
    disco -> array_bloques[file -> bloque_indice] -> array_bits[n] = bits_64_tamano[n - 32];

  int bits2_aux[8];
  int conta = 32;
  for(int n = 32; n < 96; n++){
    //printf("\nBITS: ");
    for(int j = 0; j < 8; j++){
      bits2_aux[j] = disco -> array_bloques[file -> bloque_indice] -> array_bits[conta];
      //printf("%d", bits2_aux[j]);
      conta++;
    }
    //printf("\n");
    unsigned char byte_tam = (unsigned char)bits_to_int(bits2_aux, 8);
    disco -> array_bloques[file -> bloque_indice] -> array_bytes[n/8] = byte_tam;
    //printf("%u ", disco -> array_bloques[file -> bloque_indice] -> array_bytes[n/8]);
    n+=8;
  }
  //printf("\n");
  //free(buffer);
  return contador;
}


int cr_unload(unsigned disk, char* orig, char* dest){
  int pos_dir = -1;
  char buff[255];
  if(disk == 1)
    pos_dir = 0;
  else if(disk == 2)
    pos_dir = 65536;
  else if(disk == 3)
    pos_dir = 131072;
  else
    pos_dir = 196608;

  if(pos_dir == -1 && (disk != 0)){
    fprintf(stderr,"\nNo existe la partición %d.\n",  disk);
    return 0;
  }

  else if(disk ==  0){
    for(int i = 1 ; i < 5; i++){
      sprintf(buff, "%s/%d", dest, i);
      cr_unload(i, "particion", buff);
    }
  }

  else if(strcmp(orig, "particion") == 0 && (pos_dir != -1)&& (disk != 0)){
    char file_disco[29];
    int inicio = 3;
    int final = 32;
    for(int i = 0; i < 256; i++){
      int distinta = 0;
      for(int j = inicio; j < final;j++){
        file_disco[j-inicio] = (char) disco -> array_bloques[pos_dir] -> array_bytes[j];
        if ((int)file_disco[j-inicio] != 0)
           distinta = 1;
      }
      if (distinta == 1){
        sprintf(buff, "%s/%s", dest, file_disco);
        //fprintf(stderr,"\nBUFF %s\n",  buff);
        crFILE* up_file = cr_open(disk, file_disco, 'r');
        cr_read_unload(up_file, buff, up_file -> tamano);
        free(up_file);
      }
      inicio += 32;
      final += 32;
    }
  }
    //leer el disco completo
  else if(cr_exists(disk, orig)){
    //printf("ENTRE A UNLOAD\n");
    crFILE* up_file = cr_open(disk, orig, 'r');
    cr_read_unload(up_file, dest, up_file -> tamano);
    free(up_file);
  }
  else{
    fprintf(stderr,"\nNo existe el archivo %s en la partición %d.\n", orig, disk);
  }
}

int cr_load(unsigned disk, char* orig){
  //supuesto: orig no esta dentro de una carpeta
  FILE *archivo = fopen(orig,"rb");
  if(archivo !=NULL){
    //fprintf(stderr,"\nSe encontro el archivo\n");
    unsigned char bytes[(int)pow(2,4)]; //(int)pow(2,13)
    unsigned char* bytes_malloc = malloc(sizeof(unsigned char)*(int)pow(2,4));

    //printf("Cargando archivo en disco...\n");
    int bytes_restantes;
    load = 1;
    crFILE *file_nuevo = cr_open(disk, orig, 'w');
    void* buffer;
    load = 0;
    if(file_nuevo == 0){
      fclose(archivo);
      free(bytes_malloc);
      free(file_nuevo);
      return 0;
    }

    while(fread(bytes,sizeof(bytes),1,archivo)){
      buffer = bytes;
      //  for(int j = 0; j < (int)pow(2,13); j++){
      //    bytes_malloc[j] = bytes[j];
      //  }
      bytes_restantes = cr_write(file_nuevo,buffer,(int)pow(2,4));

      //if (bytes_restantes == -1){//No queda mas memoria
        //return -1;
      //}
    }
    //fclose(archivo);
    free(bytes_malloc);
    //free(buffer);
    free(file_nuevo);
  }
  else{
    fprintf(stderr,"\nNo se ha encontrado el archivo en su computador\n");
    return 0;
  }
  fclose(archivo);
  return 1;
}

int cr_hardlink(unsigned disk, char* orig, char* dest){
  if (cr_exists(disk, orig) == 1){
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
      fprintf(stderr, "Partición %d no es válida.\n", disk);
      return 0;
    }
    load = 1;
    crFILE *file_orig = cr_open(disk, orig, 'r');
    load = 0;
    if(file_orig == 0){
      free(file_orig);
      return 0;
    }
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

    if(inicio != 32 * 256){
      unsigned char bytes_nombre[29];
      for(int i = 0; i < 29; i++){
        bytes_nombre[i] = 0;
      }
      strcpy(bytes_nombre, dest);

      int bits_nombre[232];
      int* bits_nombre_aux;
      int cont = 0;
      for(int i = 0; i < 29; i++){
        bits_nombre_aux = byte_to_bits(bytes_nombre[i]);
        for(int j = 0; j < 8; j++){
          bits_nombre[cont] = bits_nombre_aux[j];
          cont++;
        }
        free(bits_nombre_aux);
      }
      int cont2 = 0;
      int *bits_indice = int_to_bits(file_orig -> bloque_indice, 3);
      bits_indice[0] = 1;
      int contad2 = 0;
      //printf("inicio: %d, final: %d\n", inicio, final);
      for(int i = inicio; i < final; i++){
        int bits_aux[8];
        for( int j = 0; j < 8; j++){
          if(i < inicio + 3){
            disco -> array_bloques[pos_dir] -> array_bits[cont2] = bits_indice[contad2];
            contad2 += 1;
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
      file_orig -> hardlinks += 1;
      //int *bits_hardlink = int_to_bits(file_orig ->hardlinks, 4);
      int bits_hardlink[32];
      cnt = 0;
      int m = funcion_aux(file_orig ->hardlinks);
      cnt2 = 0;
      int bits_hardling_aux[cnt];
      binario_largo(file_orig ->hardlinks, bits_hardling_aux);
      //puntero_datos = int_to_bits(bloque_datos_libre, 4);


      int cnt10 = 0;
      for(int n = 0; n < 32; n++){
        if(n < 32 - cnt2){
          bits_hardlink[n] = 0;
          //printf("0");
        }
        else{
          bits_hardlink[n] = bits_hardling_aux[cnt10];
          //printf("%d", bits_tamano[cnt3]);
          cnt10++;
        }
      }

      for (int i = 0 ; i <32 ; i ++){
        disco -> array_bloques[file_orig -> bloque_indice] -> array_bits[i] = bits_hardlink[i];
      }

      for(int i = 0; i < 4; i ++){
        int bits_aux[8];
        for(int j = 0; j < 8; j ++){
          //fprintf(stderr, "%d", bits_hardlink[i*8 + j] );
          bits_aux[j] = bits_hardlink[i*8 + j];
        }
        unsigned long long int byte_hardlink = bits_to_int(bits_aux, 8);
        disco -> array_bloques[file_orig -> bloque_indice] -> array_bytes[i] = byte_hardlink;
        //fprintf(stderr, "\nBYTES HARDLINK %u\n", byte_hardlink );
      }
      free(bits_indice);
      //free(bits_hardlink);
      free(file_orig);
    }
    else{
      fprintf(stderr, "No queda espacio en directorio para agregar el hardlink en la particion %d\n", disk);
      free(file_orig);
      return 0;
    }
  }
  else{
    fprintf(stderr, "No se ha encontrado el archivo %s en la particion %d\n",orig, disk);
    return 0;
  }
}

int cr_softlink(unsigned disk_orig, unsigned disk_dest, char* orig, char* dest){
  if (cr_exists(disk_orig, orig) == 1){
    int pos_dir_orig = 0;
    if(disk_orig == 1)
      pos_dir_orig = 0;
    else if(disk_orig == 2)
      pos_dir_orig = 65536;
    else if(disk_orig == 3)
      pos_dir_orig = 131072;
    else if(disk_orig == 4)
      pos_dir_orig = 196608;
    else{
      fprintf(stderr, "Partición de origen %d no es válida.\n", disk_orig);
      return 0;
    }

    int pos_dir_dest = 0;
    if(disk_dest == 1)
      pos_dir_dest = 0;
    else if(disk_dest == 2)
      pos_dir_dest = 65536;
    else if(disk_dest == 3)
      pos_dir_dest = 131072;
    else if(disk_dest == 4)
      pos_dir_dest = 196608;
    else{
      fprintf(stderr, "Partición de destino %d no es válida.\n", disk_dest);
      return 0;
    }

    int inicio = 0;
    int final = 32;
    char file_disco[29];

    for(int i = 0; i < 256; i++){
      int diferido = 0;
      for(int j = inicio; j < final;j++){
        file_disco[j-inicio] = (char) disco -> array_bloques[pos_dir_dest] -> array_bytes[j];
        if(file_disco[j-inicio] != 0)
          diferido = 1;
      }
      if(diferido == 0){
        break;
      }
      inicio += 32;
      final += 32;
    }

    if(inicio != 32 * 256){
      unsigned char bytes_nombre[29];
      for(int i = 0; i < 29; i++){
        bytes_nombre[i] = 0;
      }
      char nombre_soft[255];
      sprintf(nombre_soft, "%d/%s",disk_orig, orig);
      strcpy(bytes_nombre, nombre_soft);
      fprintf(stderr, "NOMBRE SOFTLINK: %s\n", nombre_soft);
      int bits_nombre[232];
      int* bits_nombre_aux;
      int cont = 0;
      for(int i = 0; i < 29; i++){
        bits_nombre_aux = byte_to_bits(bytes_nombre[i]);
        for(int j = 0; j < 8; j++){
          bits_nombre[cont] = bits_nombre_aux[j];
          cont++;
        }
        free(bits_nombre_aux );
      }
      int cont2 = 0;
      int *bits_indice = int_to_bits(0, 3);
      bits_indice[0] = 1;
      int contad2 = 0;
      //printf("inicio: %d, final: %d\n", inicio, final);
      for(int i = inicio; i < final; i++){
        int bits_aux[8];
        for( int j = 0; j < 8; j++){
          if(i < inicio + 3){
            //fprintf(stderr, "%d", bits_indice[contad2] );
            disco -> array_bloques[pos_dir_dest] -> array_bits[cont2] = bits_indice[contad2];
            contad2 += 1;
          }
          else{
            disco -> array_bloques[pos_dir_dest] -> array_bits[cont2] =  bits_nombre[cont2 - 24];
          }
          bits_aux[j] = disco -> array_bloques[pos_dir_dest] -> array_bits[cont2];
          cont2 ++;
        }
        unsigned char byte_aux = bits_to_int(bits_aux, 8);
        disco -> array_bloques[pos_dir_dest] -> array_bytes[i] = byte_aux;
        //printf("\n");
      }
      free(bits_indice);
    }
    else{
      fprintf(stderr, "No hay espacio en directorio para crear un softlink en la particion %d.\n", disk_dest);
      return 0;
    } 
  }
  else{
    fprintf(stderr, "No se ha encontrado el archivo de origen %s en la particion %d.\n",  orig, disk_orig);
    return 0;
  }
  return 1;
}

void cr_rm(unsigned disk, char* filename){
  if (cr_exists(disk, filename) == 1){
    load = 1;
    crFILE* archivo = cr_open(disk, filename, 'r');
    load = 0;
    if(archivo == 0){
      free(archivo);
      return;
    }
    int bloque_directorio = (disk-1)*65536;
    archivo -> hardlinks --;

    //int *bits_hardlink = int_to_bits(archivo ->hardlinks, 4);
    int bits_hardlink[32];
    cnt = 0;
    int m = funcion_aux(archivo ->hardlinks);
    cnt2 = 0;
    int bits_hardling_aux[cnt];
    binario_largo(archivo ->hardlinks, bits_hardling_aux);
    //puntero_datos = int_to_bits(bloque_datos_libre, 4);


    int cnt10 = 0;
    for(int n = 0; n < 32; n++){
      if(n < 32 - cnt2){
        bits_hardlink[n] = 0;
        //printf("0");
      }
      else{
        bits_hardlink[n] = bits_hardling_aux[cnt10];
        //printf("%d", bits_tamano[cnt3]);
        cnt10++;
      }
    }

    for (int i = 0 ; i <32 ; i ++){
      disco -> array_bloques[archivo -> bloque_indice] -> array_bits[i] = bits_hardlink[i];
    }

    for(int i = 0; i < 4; i ++){
      int bits_aux[8];
      for(int j = 0; j < 8; j ++){
        //fprintf(stderr, "%d", bits_hardlink[i*8 + j] );
        bits_aux[j] = bits_hardlink[i*8 + j];
      }
      unsigned long long int byte_hardlink = bits_to_int(bits_aux, 8);
      disco -> array_bloques[archivo -> bloque_indice] -> array_bytes[i] = byte_hardlink;
      //fprintf(stderr, "\nBYTES HARDLINK %u\n", byte_hardlink );
    }
    
    int inicio = 3;
    int final = 32;
    char nombre_archivo_auxiliar[29];
    for (int i = 0; i < 256; i++){ //256 secuencias de 32 bytes
      //fprintf(stderr, "\nBITS VALIDACION: ");
      for (int j = inicio; j < final; j++){ // Por cada byte de la secuencia
        nombre_archivo_auxiliar[j - inicio] = (char) disco -> array_bloques[bloque_directorio] -> array_bytes[j];
        //fprintf(stderr, "%c", nombre_archivo_auxiliar[j - inicio]);
      }
      //fprintf(stderr, " = %s\n", filename);
      if (strcmp(nombre_archivo_auxiliar, filename) == 0){
        disco -> array_bloques[bloque_directorio] -> array_bits[i*8*32] = 0; // Bit Validez = 0
        //fprintf(stderr, "\nBITS VALIDACION: ");
        //for(int h = 0; h < 8; h++)
          //fprintf(stderr, "%d", disco -> array_bloques[bloque_directorio] -> array_bits[i*8*32]);
        int byte_validacion = disco -> array_bloques[bloque_directorio] -> array_bytes[i*32];
        byte_validacion -= (int) pow(2,7);
        disco -> array_bloques[bloque_directorio] -> array_bytes[i*32] = byte_validacion;
        //fprintf(stderr, "\nBYTE VALIDACION: %u\n", disco -> array_bloques[bloque_directorio] -> array_bytes[i*32]);
      }
      inicio += 32;
      final += 32;
    }

    if (archivo -> hardlinks  <= 0) { 
      // Cambio de bitmap de bloque indice
      disco -> array_bloques[bloque_directorio + 1] -> array_bits[archivo -> bloque_indice] = 0; // aca esta el error valgrind
      //disco -> array_bloques[bloque_directorio + 1] -> array_bytes[(int) archivo -> bloque_indice/ 8] -= // esta parte hay que cachar bien lo de la parte enterta y modulo
      //disco -> array_bloques[bloque_directorio + 1] -> array_bytes[(int) pow(2, archivo -> bloque_indice % 8)]; //Duda

      // Cambio bitmap bloques de datos a partir de punteros directos
      for (int i = 12*8; i < (2044 * 4 + 12)*8; i = i + 32){
        int puntero_bits[32];
        for (int j= 0; j < 32; j++){
          puntero_bits[j] = disco -> array_bloques[archivo -> bloque_indice] -> array_bits[i + j];
        }
        int puntero = bits_to_int(puntero_bits, 32);
        if (puntero != 0){
        // Cambio bitmap
        disco -> array_bloques[bloque_directorio + 1] -> array_bits[puntero] = 0;
        //disco -> array_bloques[bloque_directorio + 1] -> array_bytes[(int) puntero/ 8] -=
        //disco -> array_bloques[bloque_directorio + 1] -> array_bytes[(int) pow(2, puntero % 8)]; //Duda
        }
      }

      // Cambio bitmap bloques de datos partir de punteros indirectos
      int puntero_indirecto_bits[32];
      for (int x = 0; x < 32; x++){
        puntero_indirecto_bits[x] = disco -> array_bloques[archivo -> bloque_indice]-> array_bits[65536-32 + x];
      }
      int puntero_indirecto = bits_to_int(puntero_indirecto_bits, 32);
      if (puntero_indirecto != 0){
        for (int y = 0; y < 2045 * 4 * 8; y += 32){
          int nuevo_bloque_bit[32];
          for (int t = 0; t < 32; t ++){
            nuevo_bloque_bit[t] = disco -> array_bloques[puntero_indirecto] -> array_bits[y + t];
          }
          int puntero_bloque_data_indirecto = bits_to_int(nuevo_bloque_bit, 32);
          if (puntero_bloque_data_indirecto != 0){
            //Cambio bitmap
            disco -> array_bloques[bloque_directorio + 1] -> array_bits[puntero_bloque_data_indirecto] = 0;
            //disco -> array_bloques[bloque_directorio + 1] -> array_bytes[(int) puntero_bloque_data_indirecto/ 8] -=
            //disco -> array_bloques[bloque_directorio + 1] -> array_bytes[(int) pow(2, puntero_bloque_data_indirecto % 8)]; //Duda

          }
        }
      }
    }
    else{
      fprintf(stderr, "Se ha eliminado una referencia al archivo %s. Le quedan %i referencias. \n", filename, archivo -> hardlinks);
    }
    //cr_close(archivo); // no creo que haya que hacer esto, osi?
    //free(bits_hardlink);
    free(archivo);
  }

  else {
    fprintf(stderr, "El archivo %s no existe. \n", filename);
  }
}


int cr_close(crFILE* file_desc){
  fprintf(stderr, "\nCerrando archivo %s, esto puede tardar..\n", file_desc -> nombre);

  int pos_dir_orig = 0;
  if(file_desc -> disk == 1)
    pos_dir_orig = 0;
  if(file_desc -> disk == 2)
    pos_dir_orig = 65536;
  if(file_desc -> disk == 3)
    pos_dir_orig = 131072;
  if(file_desc -> disk == 4)
    pos_dir_orig = 196608;

  void* buffer = malloc(sizeof(unsigned char)*file_desc ->tamano);
  load2 = 1;
  file_desc -> pos_lect = 0;
  cr_read(file_desc, buffer, file_desc -> tamano);
  load2 = 0;


  int bloque_dato;
  int inicio = 12 * 8;//96
  int parar = 0;

  for(int i = 0; i < 2044; i++){
    int bits_puntero_dato[32];
    for(int j = inicio; j < (inicio + 32); j++){ //((int) pow(2,13) * 8) - 32
        bits_puntero_dato[j - inicio] = disco -> array_bloques[file_desc -> bloque_indice] -> array_bits[j];
        //fprintf(stderr, "%d", disco -> array_bloques[bloque_indice] -> array_bits[j]);
    }
    bloque_dato = bits_to_int(bits_puntero_dato, 32);

    //fprintf(stderr, "bloque dato: %d\n", bloque_dato);
    //fprintf(stderr, pos)
    for(int a = 0; a < pos_bloques_cargados; a++){
      //fprintf(stderr, "\nSoy bloque cargado: %d = bloque dato: %d\n", bloques_cargados[a] , bloque_dato);
      if(bloques_cargados[a] == bloque_dato){
        respaldar_a_bin(bloques_cargados[a]);
      }
    }
    inicio += 32;
  }
  

  /*for(int a = 0; a < pos_bloques_cargados; a++){
    respaldar_a_bin(bloques_cargados[a]);
  }*/

  // Liberar bloque indice
  respaldar_a_bin_bits(file_desc -> bloque_indice);
  respaldar_a_bin_bits(pos_dir_orig);
  respaldar_a_bin_bits(pos_dir_orig + 1);
  free(buffer);
  //free(file_desc -> nombre);
  //free(file_desc);
  return 1;
}




//////////////////////
// FUNCIONES EXTRAS //
//////////////////////


void respaldar_a_bin(int numero_bloque){
  FILE *fp = fopen(path_disk, "rb+");
  int posicion = numero_bloque * (int) pow(2,13);
  for (int j = 0; j < (int) pow(2,13); j++){
    fseek(fp, posicion + j, SEEK_SET);
    fwrite(&(disco -> array_bloques[numero_bloque] -> array_bytes[j]), sizeof(unsigned char), 1 , fp);
  }
  fclose(fp);
}

void respaldar_a_bin_bits(int numero_bloque){
  FILE *fp = fopen(path_disk, "rb+");
  int posicion = numero_bloque * (int) pow(2,13);
  int contador = 0;
  for (int j = 0; j < (int) pow(2,13); j++){
    int bits_aux[8];
    for (int u= 0; u < 8; u++){
      bits_aux[u] = disco -> array_bloques[numero_bloque] -> array_bits[contador];
      contador++;
    }
    unsigned char byte = bits_to_int(bits_aux, 8);
    fseek(fp, posicion + j, SEEK_SET);
    fwrite(&(byte), sizeof(unsigned char), 1,  fp);
  }
  fclose(fp);
}

int funcion_aux(unsigned long long n){
  unsigned long long m = n ? funcion_aux(n / 2) : 0;
  cnt++;
  return m;
}

unsigned long long binario_largo(unsigned long long n, int* array_bits){
  unsigned long long m = n ? binario_largo(n / 2, array_bits) : 0;
  //printf("%d", (int)(n % 2));
  array_bits[cnt2] = (int)(n % 2);
  cnt2++;
  return m;
}


int* byte_to_bits(unsigned char byte){

  int* binary = malloc(sizeof(int)*8);
  for(int n = 0; n < 8; n++){
    binary[7-n] = (byte >> n) & 1;
    //printf("bit %d: %d\n", 7-n, binary[7-n]);
  }
  return binary;
}

unsigned long long int bits_to_int(int* bits, int n){
  int multiplier = 1;
  unsigned long long int bin = 0;
  for (int i = n-1; i >= 0; --i)
  {
    bin += (multiplier * bits[i]);
    multiplier *= 2;
  }
  //printf("MALDITO BIN: %lld\n", bin);
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
      //fprintf(stderr, "%d", bits[cont2]);
      cont2 ++;
    }
    free(bits_aux);
  }
  //fprintf(stderr, "\n");
  return bits;
}

void print_file(crFILE* file){
  fprintf(stderr, "-----------------------------------------------------------------\n");
  fprintf(stderr, "Nombre archivo: %s  Tamaño archivo: %llu Bytes\n", file -> nombre, file -> tamano);
  fprintf(stderr, "Cantidad de Hardlinks: %d\n", file -> hardlinks);
  fprintf(stderr, "-----------------------------------------------------------------\n");
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
    free(binary);
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
  free(bytes_malloc);
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
      //fprintf(stderr, "BLOQUE %d CARGADO!\n", i);
      break;
    }
    i++;
  }
  bloques_cargados[pos_bloques_cargados] = bloque;
  pos_bloques_cargados++;

  fclose(archivo);
  free(bytes_malloc);
}


int cr_read_unload(crFILE* file, char* dest, int nbytes){

  FILE *destino;
  destino = fopen(dest ,"wb+");

  unsigned long long int bytes_restantes = file -> tamano - file -> pos_lect;
  int inicio_lectura = file ->  pos_lect;
  int inicio_lectura_aux = file ->  pos_lect;
  file ->  pos_lect = 0;
  int bloque_actual = (int) (inicio_lectura / (int) pow(2,13));
  int byte_actual = inicio_lectura - (bloque_actual*(int) pow(2,13));


  if(file -> tamano != 0){
    //file -> data = malloc(sizeof(unsigned char)* (file -> tamano));

    int bloque_dato;
    int contador = 0;
    int inicio = 12 * 8;//96
    int parar = 0;

    for(int i = 0; i < 2044; i++){
      if (i >= bloque_actual && parar == 0){
        int bits_puntero_dato[32];
        for(int j = inicio; j < (inicio + 32); j++){ //((int) pow(2,13) * 8) - 32
            bits_puntero_dato[j - inicio] = disco -> array_bloques[file -> bloque_indice] -> array_bits[j];
            //fprintf(stderr, "%d", disco -> array_bloques[bloque_indice] -> array_bits[j]);
        }
        bloque_dato = bits_to_int(bits_puntero_dato, 32);
        if (bloque_dato != 0){
          //fprintf(stderr, "bloque dato: %d\n", bloque_dato);
          //fprintf(stderr, pos)
          int cargado = 0;
          for(int a = 0; a < pos_bloques_cargados; a++){
            if(bloques_cargados[a] == bloque_dato){
              cargado = 1;
            }
          }
          if(cargado == 0){
            cargar_bloque(disco, bloque_dato);
          }
          //fprintf(stderr, "\nLeyendo en el bloque de datos %d\n", bloque_dato);
          for(int k = 0; k < (int) pow(2,13); k++){
              //fprintf(stderr, "%u ",disco -> array_bloques[bloque_dato] -> array_bytes[k]);
              fwrite(&disco -> array_bloques[bloque_dato] -> array_bytes[k], sizeof(unsigned char), 1 , destino);
              //buff[contador] = disco -> array_bloques[bloque_dato] -> array_bytes[k];

              contador++;
              if(contador == file -> pos_lect){
                parar = 1;
                break;
              }
              //printf("contador: %d\n", contador);
          }
        }
        inicio += 32;
      }
    }

    if(bloque_actual >= 2044 && parar == 0){
      int parar2 = 0;
      int bits_puntero_indirecto[32];
      int bloque_indirecto;
      for(int j = ((int) pow(2,13)*8) - 32; j < (int) pow(2,13) * 8; j++){
          bits_puntero_indirecto[j - ((int) pow(2,13)*8 - 32)] = disco -> array_bloques[file -> bloque_indice] -> array_bits[j];
          //fprintf(stderr, "%d", disco -> array_bloques[bloque_indice] -> array_bits[j]);
      }
      bloque_indirecto = bits_to_int(bits_puntero_indirecto, 32);
      if (bloque_indirecto != 0){
        //fprintf(stderr, "bloque dato: %d\n", bloque_dato);
        int cargado = 0;
        for(int a = 0; a < pos_bloques_cargados; a++){
          if(bloques_cargados[a] == bloque_indirecto)
            cargado = 1;
        }
        if(cargado == 0)
          cargar_bloque(disco, bloque_indirecto);
        int inicio1 = 0;
        for(int i = 0; i < 2048; i++){
          if (i >= (bloque_actual - 2044) && parar2 == 0){
            int bits_puntero_dato1[32];
            int bloque_dato1;
            for(int j = inicio1; j < (inicio1 + 32); j++){ //((int) pow(2,13) * 8) - 32
                bits_puntero_dato1[j - inicio1] = disco -> array_bloques[bloque_indirecto] -> array_bits[j];
                //fprintf(stderr, "%d", disco -> array_bloques[bloque_indice] -> array_bits[j]);
            }
            bloque_dato1 = bits_to_int(bits_puntero_dato1, 32);
            for(int k = 0; k < (int) pow(2,13); k++){
                fwrite(&disco -> array_bloques[bloque_dato1] -> array_bytes[k], sizeof(unsigned char), 1 , destino);

                contador++;
                if( contador > file -> pos_lect){
                  parar2 = 1;
                  break;
                }

            }
          }
          inicio1 += 32;
        }
      }
    }
  }
  file -> pos_lect = inicio_lectura_aux;
  fclose(destino);
  return 1;
}

void cr_dismount(char *diskname){
  //fprintf(stderr, "DISMOUNT\n");
  for (int i = 0; i < pos_bloques_cargados; i ++){
    free(disco -> array_bloques[bloques_cargados[i]]->array_bits);
    free(disco -> array_bloques[bloques_cargados[i]]->array_bytes);
    free(disco -> array_bloques[bloques_cargados[i]]);
  }
  int pos_dir = 0;

  for (int i = 1; i < 5; i ++){
      if(i == 1)
        pos_dir = 0;
      else if(i == 2)
        pos_dir = 65536;
      else if(i == 3)
        pos_dir = 131072;
      else
        pos_dir = 196608;
      free(disco -> array_bloques[pos_dir] -> array_bits);
      free(disco -> array_bloques[pos_dir]->array_bytes);
      free(disco -> array_bloques[pos_dir]);
      free(disco -> array_bloques[pos_dir + 1] -> array_bits);
      free(disco -> array_bloques[pos_dir + 1]->array_bytes);
      free(disco -> array_bloques[pos_dir + 1]);

  }
  free(disco -> array_bloques);
  free(disco);
  free(bloques_cargados);
}