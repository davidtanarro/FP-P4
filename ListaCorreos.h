#ifndef LISTA_CORREOS_H
#define LISTA_CORREOS_H

#include "Correo.h"

using namespace std;

const int DIM_CORR = 50;
typedef tCorreo tArrayCorreos[DIM_CORR];
typedef struct {
	tArrayCorreos listaCorreos;
	int cont;
} tListaCorreos;

void inicializar(tListaCorreos &correos); // Inicializa la lista.
bool cargar(tListaCorreos &correos, string dominio); // Implementa la carga de la lista de correos desde el fichero de correos de nombre <NombreDominio>_correos.txt.
void guardar(const tListaCorreos &correos, string dominio); // Implementa el guardado de la lista de correos en el fichero de correos de nombre <NombreDominio>_ correos.txt.Guarda en fichero la lista de correos.El nombre del fichero será como en el subprograma anterior.
bool insertar(tListaCorreos &correos, const tCorreo &correo); // Dado un correo, si hay espacio en la lista, lo coloca en la posición de la lista que le corresponda de acuerdo con su identificador y devuelve true.Si no lo ha podido colocar devuelve false.
bool buscar(const tListaCorreos &correos, string id, int &pos); // Dado un identificador de correo y la lista, devuelve, si dicho identificador existe en la lista, su posición y el valor true, y si no existe en la lista, la posición que le correspondería y el valor false.
void ordenar_AF(tListaCorreos &correos); // Dada una lista de correos la devuelve ordenada por asunto y fecha.Como es una clave de ordenación doble, habrá que redefinir el operador de comparación en el módulo que corresponda.

bool operator<(tCorreo& c1, tCorreo& c2); // Devuelve true si c1 es menor alfabeticamente en asunto y en caso de tener el mismo asunto: lo ordena por fecha de mas antiguos a mas recientes, false en cualquier otro caso (se ignora todos los "Re: " de los asuntos)
void limpiarAsunto(string& asunto); // Elimina los "Re: " del un asunto si los hubiese
void mostrarLista(const tListaCorreos& listaCorreos);

#endif