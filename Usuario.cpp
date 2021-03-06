#include "Usuario.h"

using namespace std;

const string CENTINELA = "XXX";

// Dado un flujo de archivo(ya abierto), se carga un usuario de fichero.
bool cargar(tUsuario& usuario, ifstream& archivo) {
	bool ok = true;

	archivo >> usuario.nombre;
	if (usuario.nombre == CENTINELA)
		ok = false;
	else {
		archivo >> usuario.contraseņa;
		cargar(usuario.listaRegRecibidos, archivo);
		cargar(usuario.listRegEnviados, archivo);
	}

	return ok;
}

// Dado un flujo de archivo(ya abierto), se guarda un usuario en fichero.
void guardar(const tUsuario& usuario, ofstream& archivo) {
	archivo << usuario.nombre << endl << usuario.contraseņa << endl;
	guardar(usuario.listaRegRecibidos, archivo);
	guardar(usuario.listRegEnviados, archivo);
}

// Recibe un identificador de usuario y una contraseņa y los asigna al usuario.
void inicializar(tUsuario& usuario, string id, string contrasenia) {
	usuario.nombre = id;
	usuario.contraseņa = contrasenia;
	inicializar(usuario.listaRegRecibidos);
	inicializar(usuario.listRegEnviados);
}

// Recibe una contraseņa y un usuario y devuelve si la contraseņa es correcta o no.
bool validarContrasenia(const tUsuario &usuario, string contrasenia) {
	return usuario.contraseņa == contrasenia;
}
