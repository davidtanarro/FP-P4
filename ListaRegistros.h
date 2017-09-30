#ifndef LISTA_REGISTROS_H
#define LISTA_REGISTROS_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

typedef struct {
	string id; // se compone de la concatenación del emisor y la fecha (p.e. pepe@fdimail.com_143456443). Este identificador coincide con el identificador del tCorreo.
	bool leido;
} tRegCorreo;

const int DIM_REG = 50;
typedef tRegCorreo tArrayRegistros[DIM_REG];
typedef  struct {
	tArrayRegistros listaRegistros;
	int cont;
} tListaRegCorreo;

void inicializar(tListaRegCorreo &listaReg); // Inicializa la lista.
void cargar(tListaRegCorreo &listaReg, ifstream& archivo); // Dado un flujo de archivo de entrada(ya abierto), lee los datos que corresponden a una lista de registros y la devuelve.
void guardar(const tListaRegCorreo &listaReg, ofstream& archivo); // Dado un flujo de archivo de salida(ya abierto), guarda los datos de la lista de registro.
bool insertar(tListaRegCorreo &listaReg, tRegCorreo registro); // Dado un registro lo inserta al final de la lista.Si la lista está llena devuelve false, en otro caso devuelve true.Este subprograma se ejecutará cuando un usuario envíe un correo ya que se insertará el registro correspondiente en la lista de registros que representa su bandeja de salida, y también en las listas de registros que representan las bandejas de entrada de cada uno de los destinatarios del correo.
bool borrar(tListaRegCorreo &listaReg, string id); // Dado un identificador de correo, busca el registro correspondiente y si lo encuentra lo elimina de la lista(¡sin dejar huecos!).Si no lo encuentra, devuelve false, en otro caso devuelve true.Este subprograma representa la acción de un usuario del borrado de un determinado correo de una de sus bandejas.OJO : esta operación sólo supone que el registro es borrado de la lista de registros, pero el correo seguirá existiendo en la lista de correos.
bool correoLeido(tListaRegCorreo &listaReg, string id); // Dado un identificador de correo, busca el correspondiente registro y pone el indicador de leído a true.La operación devuelve un booleano indicando si se encontró o no el registro.
int buscar(const tListaRegCorreo &listaReg, string id); // Dado un identificador de correo y la lista, devuelve, si dicho identificador existe en la lista, su posición, y si no existe devuelve - 1.

#endif