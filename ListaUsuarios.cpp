#include "ListaUsuarios.h"

using namespace std;

const string CENTINELA = "XXX";

// Inicializa la lista.
void inicializar(tListaUsuarios &usuarios) {
	usuarios.cont = 0;
}

// Implementa la carga de la lista de usuarios desde el fichero de usuarios de nombre <NombreDominio>_usuarios.txt .
bool cargar(tListaUsuarios& usuarios, string dominio) {
	bool ok = true;
	ifstream archivo;

	archivo.open(dominio + "_usuarios.txt");
	if (!archivo.is_open())
		ok = false;
	else
		while (cargar(usuarios.listaUsuarios[usuarios.cont], archivo) && usuarios.cont < DIM_USU)
			usuarios.cont++;
	archivo.close();

	return ok;
}

// Implementa el guardado de la lista de usuarios en el fichero de usuarios de nombre <NombreDominio>_usuarios.txt .
void guardar(const tListaUsuarios& usuarios, string dominio) {
	ofstream archivo;

	archivo.open(dominio + "_usuarios.txt");
	for (int i = 0; i < usuarios.cont; i++)
		guardar(usuarios.listaUsuarios[i], archivo);
	archivo << CENTINELA;
	archivo.close();
}

// Añade un usuario en la posición de la lista que le corresponde, si hay sitio para ello.
// Además devuelve un booleano indicando si la operación tuvo éxito o no.
bool aniadir(tListaUsuarios& usuarios, const tUsuario& usuario) {
	bool ok = true, inter = true;
	int i = 0;
	tUsuario aux;

	if (usuarios.cont > DIM_USU-1)
		ok = false;
	else {
		usuarios.listaUsuarios[usuarios.cont] = usuario;
		usuarios.cont++;
		while (i < usuarios.cont-1 && inter) {
			inter = false;
			for (int j = usuarios.cont-1; j > i; j--) {
				if (usuarios.listaUsuarios[j - 1].nombre > usuarios.listaUsuarios[j].nombre) {
					aux = usuarios.listaUsuarios[j - 1];
					usuarios.listaUsuarios[j - 1] = usuarios.listaUsuarios[j];
					usuarios.listaUsuarios[j] = aux;
					inter = true;
				}
			}
			if (inter) i++;
		}
	}

	return ok;
}

// Dado un identificador de usuario y la lista, devuelve, si dicho identificador existe en la lista, su posición y el valor true,
// y si no existe en la lista, la posición que le correspondería y el valor false.
bool buscarUsuario(const tListaUsuarios& usuarios, string id, int& posicion) {
	int ini = 0, fin = usuarios.cont-1, mitad;
	bool encontrado = false;
	
	while (ini <= fin && !encontrado) {
		mitad = (ini + fin) / 2;
		if (id < usuarios.listaUsuarios[mitad].nombre)
			fin = mitad - 1;
		else if (usuarios.listaUsuarios[mitad].nombre < id)
			ini = mitad + 1;
		else
			encontrado = true;
	}
	if (encontrado) posicion = mitad;
	else posicion = ini;

	return encontrado;
}