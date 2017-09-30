#include "ListaCorreos.h"

using namespace std;
const string CENTINELA = "XXX";

// Inicializa la lista.
void inicializar(tListaCorreos &correos) {
	correos.cont = 0;
}

// Implementa la carga de la lista de correos desde el fichero de correos de nombre <NombreDominio>_correos.txt.
bool cargar(tListaCorreos &correos, string dominio) {
	bool ok = true;
	ifstream archivo;
	string centinela;

	archivo.open(dominio + "_correos.txt");
	if (!archivo.is_open())
		ok = false;
	else {
		while (cargar(correos.listaCorreos[correos.cont], archivo) && correos.cont < DIM_CORR)
			correos.cont++;
		archivo >> centinela;
	}
	archivo.close();

	return ok;
}

// Implementa el guardado de la lista de correos en el fichero de correos de nombre <NombreDominio>_ correos.txt.
// Guarda en fichero la lista de correos. El nombre del fichero será como en el subprograma anterior.
void guardar(const tListaCorreos &correos, string dominio) {
	ofstream archivo;

	archivo.open(dominio + "_correos.txt");
	for (int i = 0; i < correos.cont; i++)
		guardar(correos.listaCorreos[i], archivo);
	archivo << CENTINELA;
	archivo.close();
}

// Dado un correo, si hay espacio en la lista, lo coloca en la posición de la lista que le corresponda de acuerdo con su identificador y devuelve true.
// Si no lo ha podido colocar devuelve false.
bool insertar(tListaCorreos &correos, const tCorreo &correo) {
	bool ok = true, inter = true;
	int i = 0;
	tCorreo tmp;

	if (correos.cont < DIM_CORR) {
		correos.listaCorreos[correos.cont] = correo;
		correos.cont++;
		// Desde el 1º hasta el penúltimo si hay intercambios...
		while ((i < correos.cont - 1) && inter) {
			inter = false;
			// Desde el último hasta el siguiente a i...
			for (int j = correos.cont - 1; j > i; j--) {
				if (correos.listaCorreos[j].id < correos.listaCorreos[j - 1].id) {
					tmp = correos.listaCorreos[j];
					correos.listaCorreos[j] = correos.listaCorreos[j - 1];
					correos.listaCorreos[j - 1] = tmp;
					inter = true;
				}
			}
			if (inter) {
				i++;
			}
		}
	}
	else
		ok = false;

	return ok;
}

// Dado un identificador de correo y la lista, devuelve, si dicho identificador existe en la lista, su posición y el valor true,
// y si no existe en la lista, la posición que le correspondería y el valor false.
bool buscar(const tListaCorreos &correos, string id, int &pos) {
	int ini = 0, fin = correos.cont - 1, mitad;
	bool encontrado = false;

	while (ini <= fin && !encontrado) {
		mitad = (ini + fin) / 2;
		if (id < correos.listaCorreos[mitad].id)
			fin = mitad - 1;
		else if (correos.listaCorreos[mitad].id < id)
			ini = mitad + 1;
		else
			encontrado = true;
	}
	if (encontrado) pos = mitad;
	else pos = ini;

	return encontrado;
}

// Dada una lista de correos la devuelve ordenada por asunto y fecha.
// Como es una clave de ordenación doble, habrá que redefinir el operador de comparación en el módulo que corresponda.
void ordenar_AF(tListaCorreos &correos) {
	bool inter = true;
	int i = 0;
	tCorreo tmp;

	while ((i < correos.cont - 1) && inter) {
		inter = false;
		// Desde el último hasta el siguiente a i...
		for (int j = correos.cont - 1; j > i; j--) {
			if (correos.listaCorreos[j] < correos.listaCorreos[j - 1]) {
				tmp = correos.listaCorreos[j];
				correos.listaCorreos[j] = correos.listaCorreos[j - 1];
				correos.listaCorreos[j - 1] = tmp;
				inter = true;
			}
		}
		if (inter) {
			i++;
		}
	}
}


// Devuelve true si c1 es menor alfabeticamente en asunto y en caso de tener el mismo asunto:
// lo ordena por fecha de mas antiguos a mas recientes, false en cualquier otro caso (se ignora todos los "Re: " de los asuntos)
bool operator<(tCorreo& c1, tCorreo& c2) {
	bool menor;

	limpiarAsunto(c1.asunto);
	limpiarAsunto(c2.asunto);

	if (c1.asunto < c2.asunto)
		menor = true;
	else if (c2.asunto < c1.asunto)
		menor = false;
	else if (c1.fecha > c2.fecha)
		menor = false;
	else
		menor = true;

	return menor;
}

// Elimina los "Re: " del un asunto si los hubiese
void limpiarAsunto(string& asunto) {
	string re = "Re: ", aux = re;

	while (aux == re) {
		aux = asunto.substr(0, 4);	// aux coge "Re: " si lo hubiese
		if (aux == re)
			asunto.erase(0, 4);		// borra "Re: " del asunto
	}
}

void mostrarLista(const tListaCorreos& listaCorreos) {
	for (int i = 0; i < listaCorreos.cont; i++) {
		cout << aCadena(listaCorreos.listaCorreos[i]);
		cout << "------------------------------------\n";
	}
}