#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <math.h>


typedef struct bloque
{
  int tipo_bloque; // 1:DIRECTORIO  2:BITMAP  3:INDICE   4:DATOS  5:INDIRECTO
  unsigned char *array_bytes;
  int *array_bits;
  int particion; //1, 2, 3, 4
}Bloque;



typedef struct disco
{
    Bloque **array_bloques;
}Disco;


typedef struct crFILE
{
  char *nombre_archivo;
}crFILE;

void cr_mount(char *diskname);
Disco* disco_init(char *filename);
Bloque* bloque_init(int i, int tipo_bloque, unsigned char *array_bytes, int particion);
void cr_bitmap(unsigned disk, bool hex);