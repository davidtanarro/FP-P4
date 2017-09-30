#include "ListaRegistros.h"

using namespace std;

// Inicializa la lista.
void inicializar(tListaRegCorreo &listaReg) {
	listaReg.cont = 0;
}

// Dado un flujo de archivo de entrada(ya abierto), lee los datos que corresponden a una lista de registros y la devuelve.
void cargar(tListaRegCorreo &listaReg, ifstream& archivo) {
	archivo >> listaReg.cont;
	for (int i = 0; i < listaReg.cont && listaReg.cont <= DIM_REG; i++)
		archivo >> listaReg.listaRegistros[i].id >> listaReg.listaRegistros[i].leido;
}

// Dado un flujo de archivo de salida(ya abierto), guarda los datos de la lista de registro.
void guardar(const tListaRegCorreo &listaReg, ofstream& archivo) {
	archivo << listaReg.cont << endl;
	for (int i = 0; i < listaReg.cont; i++)
		archivo << listaReg.listaRegistros[i].id << "		" << listaReg.listaRegistros[i].leido << endl;
}

// Dado un registro lo inserta al final de la lista.Si la lista está llena devuelve false, en otro caso devuelve true.
// Este subprograma se ejecutará cuando un usuario envíe un correo ya que se insertará el registro correspondiente en la lista de registros que representa su bandeja de salida,
// y también en las listas de registros que representan las bandejas de entrada de cada uno de los destinatarios del correo.
bool insertar(tListaRegCorreo &listaReg, tRegCorreo registro) {
	bool ok = true;

	if (listaReg.cont >= DIM_REG)
		ok = false;
	else {
		listaReg.listaRegistros[listaReg.cont].id = registro.id;
		listaReg.listaRegistros[listaReg.cont].leido = registro.leido;
		listaReg.cont++;
	}

	return ok;
}

// Dado un identificador de correo, busca el registro correspondiente y si lo encuentra lo elimina de la lista(¡sin dejar huecos!).
// Si no lo encuentra, devuelve false, en otro caso devuelve true.
// Este subprograma representa la acción de un usuario del borrado de un determinado correo de una de sus bandejas.
// OJO : esta operación sólo supone que el registro es borrado de la lista de registros, pero el correo seguirá existiendo en la lista de correos.
bool borrar(tListaRegCorreo &listaReg, string id) {
	bool ok = true;
	int pos;

	pos = buscar(listaReg, id);
	if (pos == -1)
		ok = false;
	else {
		for (int i = pos; i < listaReg.cont-1; i++)
			listaReg.listaRegistros[i] = listaReg.listaRegistros[i + 1];
		listaReg.cont--;
	}

	return ok;
}

// Dado un identificador de correo, busca el correspondiente registro y pone el indicador de leído a true.
// La operación devuelve un booleano indicando si se encontró o no el registro.
bool correoLeido(tListaRegCorreo &listaReg, string id) {
	bool ok = true;
	int pos;

	pos = buscar(listaReg, id);
	if (pos == -1)
		ok = false;
	else
		listaReg.listaRegistros[pos].leido = true;

	return ok;
}

// Dado un identificador de correo y la lista, devuelve, si dicho identificador existe en la lista, su posición, y si no existe devuelve - 1.
int buscar(const tListaRegCorreo &listaReg, string id) {
	int pos = 0;
	bool encontrado = false;

	while (!encontrado && pos < listaReg.cont)
		if (listaReg.listaRegistros[pos].id == id)
			encontrado = true;
		else
			pos++;
	if (!encontrado)
		pos = -1;

	return pos;
}
