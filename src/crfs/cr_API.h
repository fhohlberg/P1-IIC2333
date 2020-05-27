#pragma once
#include <stdint.h>
#include <math.h>


typedef struct bloque
{
  int tipo_bloque; // 1:DIRECTORIO  2:BITMAP  3:INDICE   4:DATOS  5:INDIRECTO
  unsigned char *array_bytes;
  int *array_bits;
  int particion; //1, 2, 3, 4
}Bloque;

typedef struct particion
{
  int inicio;
  int final;
  Bloque **array_bloques;
}Particion;

typedef struct disco
{
  Particion **array_particiones;
}Disco;


typedef struct crFILE
{
  char *nombre_archivo;
}crFILE;

void cr_mount(char *diskname);
Particion* particion_init(int n, int inicio, int final, unsigned char* bytes, Particion **particiones);
Disco* disco_init(char *filename);
Bloque* bloque_init(int i, int tipo_bloque, unsigned char *array_bytes, Bloque **bloques, int particion);
