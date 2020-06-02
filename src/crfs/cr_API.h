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
  unsigned long long int tamano; //tamano en Bytes
  int hardlinks;//cantidad de hardlinks
  int pos_lect; //posicion de lectura del archivo
  int pos_esc;
  int bloque_indice; //
  int disk;
}crFILE;


////////////////////////
//FUNCIONES ENUNCIADO//
///////////////////////


void cr_mount(char *diskname);
void cr_bitmap(unsigned disk, bool hex);
int cr_exists(unsigned disk, char* filename);
void cr_ls(unsigned disk);
crFILE* cr_open(unsigned disk, char* filename, char mode);
int cr_read(crFILE* file_desc, void* buffer, int nbytes);
int cr_write(crFILE* file, void* buffer, int nbytes);
int cr_unload(unsigned disk, char* orig, char* dest);
int cr_load(unsigned disk, char* orig);
int cr_hardlink(unsigned disk, char* orig, char* dest);
int cr_softlink(unsigned disk_orig, unsigned disk_dest, char* orig, char* dest);
void cr_rm(unsigned disk, char* filename);
int cr_close(crFILE* file_desc);

////////////////////////
//FUNCIONES EXTRAS AUX//
////////////////////////

Disco* disco_init(char *filename);
Bloque* bloque_init(int i, int tipo_bloque, unsigned char *array_bytes);
void cargar_bloque(Disco* disco, int bloque);
int* byte_to_bits(unsigned char byte);
unsigned long long int bits_to_int(int* bits, int n);
unsigned char* int_to_bytes(int n, int cantidad_bytes);
int* int_to_bits(int n, int cantidad_bytes);
void print_file(crFILE* file);
int cr_read_unload(crFILE* file, char* dest, int nbytes);
unsigned long long binario_largo(unsigned long long n, int* array_bits);
void respaldar_a_bin(int numero_bloque);
void respaldar_a_bin_bits(int numero_bloque);
void cr_dismount(char *diskname);


