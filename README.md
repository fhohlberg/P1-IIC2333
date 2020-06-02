# P1-IIC2333
Proyecto 1 Sistemas Operativos - Grupo DFLL

### Integrantes:
1. Francisca Hohlberg - Número de alumno: 16638964
2. Lucrecia Fernandez - Número de alumno: 1663828J
3. Lucas Alamos - Número de alumno: 16622359
4. Daniel Lyon - Número de alumno: 13638963

#### Principales decisiones de diseño

Diseñamos el proyecto utilizando una estructura de disco (variable global), de bloques y de crFILE.
Comenzamos cargando el struct disco con los bloque de directorio y bitmap
para cada partición dentro del array de bloques de esta estructura (file -> array_bloques).
A medida que se necesitara leer o escribir en un archivo se cargan sólo los bloques necesarios
(de índice y de datos correspondientes) para poder manejar la estructura crFILE.
Al hacer cr_open de un archivo, si se abre en formato "r" se verifica que exista, de no ser así
se maneja el error y si existe se instancia la estructura crFILE correspondiente. Acá se
guarda en atributos de esta el tamaño y el número del bloque índice, entre otros. Funcionaría de manera análoga para abrir en formato "w", sólo que se verifica primero
que no se quiera escribir un archivo que ya exista en la partición entregada y que esta
última sea válida. Al cargar esta estructura de crFILE se puede usar a lo largo
de la API y se logra simplificar el manejo del sistema de archivos.

### Supuestos y Extras

**IMPORTANTE**

Los archivos binarios 'simdiskfilled.bin' y 'simdiskformat.bin' deben ir dentro de la carpeta discos en el directorio principal.

De la mano del diseño del proceso y para poder realizar un correcto funcionamiento de la API
en términos de manejo de memoria creamos una función adicional cr_dismount(diskname) que se
encarga de liberar los bloques de directorio y bitmap de cada partición instanciados en cr_mount y de liberar la estructura de disco para así tener 0 leaks en la API.

Cabe mencionar que nuestro programa esta pensado desde el supuesto que siempre que se
abra un archivo (cr_open) se cerrará antes de terminar el programa (cr_close) si se han
hecho cambios para así tener actualizado el disco (archivo binario).

Siempre que se hace unload, los archivos se descargan en la carpeta file_disco. Si se desea cambiar, se debe especificar en el código. Las descargas de particiones se realizan en la carpeta file_disco/n_partición, para cada partición respectiva.
