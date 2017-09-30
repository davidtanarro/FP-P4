#ifndef LISTA_USUARIOS_H
#define LISTA_USUARIOS_H

#include "usuario.h"

using namespace std;

const int DIM_USU = 50;
typedef tUsuario tArrayUsuarios[DIM_USU];
typedef struct {
	tArrayUsuarios listaUsuarios;
	int cont;
} tListaUsuarios;

void inicializar(tListaUsuarios &usuarios); // Inicializa la lista.
bool cargar(tListaUsuarios& usuarios, string dominio); // Implementa la carga de la lista de usuarios desde el fichero de usuarios de nombre <NombreDominio>_usuarios.txt .
void guardar(const tListaUsuarios& usuarios, string dominio); // Implementa el guardado de la lista de usuarios en el fichero de usuarios de nombre <NombreDominio>_usuarios.txt .
bool aniadir(tListaUsuarios& usuarios, const tUsuario& usuario); // Añade un usuario en la posición de la lista que le corresponde, si hay sitio para ello.Además devuelve un booleano indicando si la operación tuvo éxito o no.
bool buscarUsuario(const tListaUsuarios& usuarios, string id, int& posicion); // Dado un identificador de usuario y la lista, devuelve, si dicho identificador existe en la lista, su posición y el valor true, y si no existe en la lista, la posición que le correspondería y el valor false.

#endif