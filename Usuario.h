#ifndef USUARIO_H
#define USUARIO_H

#include "ListaRegistros.h"

using namespace std;

typedef struct {
	string nombre;			// - El nombre o identificador del usuario(string).Debe ser único en el gestor, es decir, en la lista de usuarios del gestor.
	string contraseña;		// - La contraseña del usuario(string).
	tListaRegCorreo	listaRegRecibidos;	// - La lista de registros de mensajes recibidos que será de tipo tListaRegistros y que nos permite implementar la bandeja de entrada del usuario.
	tListaRegCorreo	listRegEnviados;	// - La lista de registros de mensajes enviados que será de tipo tListaRegistros y que nos permite implementar la bandeja de salida del usuario.
} tUsuario;

bool cargar(tUsuario& usuario, ifstream& archivo); // Dado un flujo de archivo(ya abierto), se carga un usuario de fichero.
void guardar(const tUsuario& usuario, ofstream& archivo); // Dado un flujo de archivo(ya abierto), se guarda un usuario en fichero.
void inicializar(tUsuario& usuario, string id, string contrasenia); // Recibe un identificador de usuario y una contraseña y los asigna al usuario.
bool validarContrasenia(const tUsuario &usuario, string contrasenia); // Recibe una contraseña y un usuario y devuelve si la contraseña es correcta o no.

#endif