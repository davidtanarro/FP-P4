#include "Correo.h"

using namespace std;

const string CENTINELA = "XXX";
const string CENTINELA_MEN = "X";

// Recibe un identificador de emisor y devuelve un correo con todos sus datos rellenos según se ha explicado en la sección 1.3.
void correoNuevo(tCorreo &correo, string emisor) {
	bool vacio = true;
	char c;
	string linea;
	stringstream flujo1, flujo2, flujo3;

	correo.emisor = emisor;
	linea = " "; // Cualquier valor no valido
	while (linea != CENTINELA) {
		(vacio) ? cout << "Destinatarios (al menos uno, XXX para terminar): " : cout << "Destinatarios (XXX para terminar): ";
		cin >> linea;
		if (linea != CENTINELA) {
			correo.destinatario = linea;
			vacio = false;
		}
	}
	cout << "Introduce el asunto (una linea): ";
	cin.get(c);
	getline(cin, linea);
	flujo1 << linea;
	correo.asunto = flujo1.str();
	cout << "Introduce el cuerpo del correo (XXX para terminar):\n";
	linea = " "; // Cualquier valor no valido
	while (linea != CENTINELA) {
		getline(cin, linea);
		if (linea != CENTINELA)
			flujo2 << linea << endl;
	}
	flujo2 << endl;
	correo.cuerpo = flujo2.str();
	correo.fecha = time(0);
	flujo3 << emisor << "_" << correo.fecha;
	correo.id = flujo3.str();
}

// Recibe un identificador de emisor y el correo original que se va a contestar,
// y devuelve un correo con todos sus datos rellenos segun se ha explicado en la sección 1.3.
void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor) {
	string linea;
	stringstream flujo1, flujo2, flujo3;

	correo.emisor = emisor;
	correo.destinatario = correoOriginal.emisor;
	flujo1 << "Re: " << correoOriginal.asunto;
	correo.asunto = flujo1.str();
	while (linea != CENTINELA) {
		getline(cin, linea);
		if (linea != CENTINELA)
			flujo2 << linea << endl;
	}
	flujo2 << "\n------------------------------------------\n\n";
	flujo2 << "De: " << left << setw(20) << correoOriginal.emisor << right << setw(53) << mostrarFecha(correoOriginal.fecha) << "\n";
	flujo2 << "Para: " << correoOriginal.destinatario << "\n";
	flujo2 << "Asunto: " << correoOriginal.asunto << "\n\n";
	flujo2 << correoOriginal.cuerpo;
	correo.cuerpo = flujo2.str();
	correo.fecha = time(0);
	flujo3 << emisor << "_" << correo.fecha;
	correo.id = flujo3.str();
}

// Devuelve un string con el contenido completo del correo para poderlo mostrar por consola.
string aCadena(const tCorreo &correo) {
	string cuerpo;
	stringstream flujo;

	flujo << "De: " << correo.emisor << right << setw(60) << mostrarFecha(correo.fecha);
	flujo << "\nPara: " << correo.destinatario;
	flujo << "\nAsunto: " << correo.asunto << endl << endl;
	flujo << correo.cuerpo << endl;
	cuerpo = flujo.str();

	return cuerpo;
}

// Devuelve un string que contiene la información que se mostrará en la bandeja de entrada / salida : emisor, asunto y fecha sin hora.
string obtenerCabecera(const tCorreo &correo) {
	string cabecera;
	stringstream flujo;

	flujo << left << setw(20) << correo.emisor << setw(43) << correo.asunto << right << setw(10) << mostrarSoloDia(correo.fecha);
	cabecera = flujo.str();

	return cabecera;
}

// Para mostrar sólo el día de la fecha en formato Año / Mes / Dia(sin hora) :
string mostrarSoloDia(tFecha fecha) {
	stringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon << "/" << ltm.tm_mday;
	return resultado.str();
}

// Deberás definir además la siguiente función para mostrar la fecha en formato Año / Mes / Dia, Hora / Mins / Segs:
string mostrarFecha(tFecha fecha) {
	stringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon << "/" << ltm.tm_mday;
	resultado << " (" << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << ")";
	return resultado.str();
}

// Dado un flujo de archivo de entrada(ya abierto), lee los datos que corresponden a un correo y lo devuelve.
// Devuelve false sólo si el correo cargado no es válido.
bool cargar(tCorreo &correo, ifstream& archivo) {
	bool ok = true;
	string aux;
	stringstream linea;

	archivo >> correo.id;
	if (correo.id == CENTINELA)
		ok = false;
	else {
		archivo >> correo.fecha;
		archivo >> correo.emisor;
		archivo >> correo.destinatario;
		archivo.get();
		getline(archivo, correo.asunto);
		getline(archivo, aux);
		while (aux != CENTINELA_MEN) {
			linea << aux << endl;
			correo.cuerpo = linea.str();
			getline(archivo, aux);
		}
		if (archivo.fail())
			ok = false;
	}

	return ok;
}

// Dado un flujo de archivo de salida(ya abierto), escribe en el flujo los datos que corresponden a un correo.
void guardar(const tCorreo &correo, ofstream& archivo) {
	archivo << correo.id << endl;
	archivo << correo.fecha << endl;
	archivo << correo.emisor << endl;
	archivo << correo.destinatario << endl;
	archivo << correo.asunto << endl;
	archivo << correo.cuerpo;
	archivo << CENTINELA_MEN << endl;
}
