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
  char *nombre;
  int tamano; //tamano en Bytes
  int hardlinks;//cantidad de hardlinks
  unsigned char* data; //contenido del file
  int pos_lect; //posicion de lectura del archivo
  int pos_esc;
  int bloque_indice; //
  int disk;
}crFILE;

void cr_mount(char *diskname);
Disco* disco_init(char *filename);
void cargar_bloque(Disco* disco, int bloque);
Bloque* bloque_init(int i, int tipo_bloque, unsigned char *array_bytes);
void cr_bitmap(unsigned disk, bool hex);
int cr_exists(unsigned disk, char* filename);
void cr_ls(unsigned disk);
crFILE* cr_open(unsigned disk, char* filename, char mode);
int cr_read(crFILE* file_desc, void* buffer, int nbytes);
void print_file(crFILE* file);
int cr_write(crFILE* file, void* buffer, int nbytes);
void cr_rm(unsigned disk, char* filename);
//int cr_unload(unsigned disk, char* orig, char* dest);
void respaldar(int numero_bloque);
void cr_close_bloque(int i);
int cr_close(crFILE* file_desc);
