// David Tanarro de las Heras 1ºF
// Javier Lanchas Hernández 1ºF
// Practica 4: Sin version opcional

#include <iostream>
#include <sstream>
#include <ctime>
#include <stdlib.h> // system("CLS") y system("pause")
#include "Gestor.h"

using namespace std;

const string DOMINIO = "@fdimail.com"; // @fdimail.com
const string CENTINELA = "XXX";

void gestionarGestor(tGestor& gestor);
int menu();
int submenu(const tGestor& gestor, const bool bandejaEntrada);
void mostrarCabeceras(const tGestor& gestor, const tListaRegCorreo& listaReg);

int main(){
	tGestor gestor;
	int op;

	if (!arrancar(gestor, DOMINIO)) {
		cout << "No se han encontrado archivos. El sistema empieza con listas vacias\n";
		inicializar(gestor, DOMINIO);
		system("pause");
		system("cls");
	}
	do {
		op = menu();
		if (op == 1) {
			if (iniciarSesion(gestor)) {
				system("cls");
				gestionarGestor(gestor);
			}
			else {
				cout << "\nNo se ha podido iniciar sesion el usuario/contraseña no son correctos\n";
				system("pause"); system("cls");
			}
		}
		else if (op == 2) {
			if (crearCuenta(gestor)) {
				cout << "\nLa cuenta ha sido creada correctamente. Va a iniciar por primera vez en " << gestor.dominio << "!\n";
				system("pause"); system("cls");
				gestionarGestor(gestor);
			}
			else {
				cout << "\nNo se ha podido crear la cuenta de usuario\n";
				system("pause"); system("cls");
			}
		}
	} while (op != 0);
	apagar(gestor);

	return 0;
}


void gestionarGestor(tGestor& gestor) {
	bool bandejaEntrada = true;
	int op = -1;
	tCorreo correo;

	while (op != 0) {
		// SUBMENU
		op = submenu(gestor, bandejaEntrada);
		switch (op) {
		case 1:
		{	// Leer correo
			(bandejaEntrada) ? leerCorreo(gestor, gestor.listaUsuSistema.listaUsuarios[gestor.usuario_activo].listaRegRecibidos) : leerCorreo(gestor, gestor.listaUsuSistema.listaUsuarios[gestor.usuario_activo].listRegEnviados);
		}
		break;
		case 2:
		{	// Enviar correo
			correoNuevo(correo, gestor.listaUsuSistema.listaUsuarios[gestor.usuario_activo].nombre);
			enviarCorreo(gestor, correo);
		}
		break;
		case 3:
		{	// Borrar correo
			(bandejaEntrada) ? borrarCorreo(gestor, gestor.listaUsuSistema.listaUsuarios[gestor.usuario_activo].listaRegRecibidos) : borrarCorreo(gestor, gestor.listaUsuSistema.listaUsuarios[gestor.usuario_activo].listRegEnviados);
		}
		break;
		case 4:
		{	// Cambiar de bandeja
			bandejaEntrada = !bandejaEntrada;
		}
		break;
		case 5:
		{	// Lectura de correos sin leer
			system("cls");
			(bandejaEntrada) ? lecturaRapida(gestor, gestor.listaUsuSistema.listaUsuarios[gestor.usuario_activo].listaRegRecibidos) : lecturaRapida(gestor, gestor.listaUsuSistema.listaUsuarios[gestor.usuario_activo].listRegEnviados);
		}
		break;
		case 0:
		{
			cout << "Cerrando la sesion...Hasta pronto!\n";
			system("pause");
		}
		break;
		default:{}
		}
		system("pause"); system("cls");
	}
}

int menu() {
	int op = -1;
	while (op < 0 || op > 2) {
		cout << "Elija la opcion deseada: \n";
		cout << "   1 - Acceder a mi cuenta de correo\n";
		cout << "   2 - Crear cuenta de correo\n\n";
		cout << "   0 - Salir\n";
		cin >> op;
		if (op == 0) {
			cout << "Hasta pronto!\n";
			system("pause");
		}
		else {
			system("cls");
			if (op < 0 || op > 2)
				cout << "ERROR: opcion incorrecta\n";
		}
	}

	return op;
}

int submenu(const tGestor& gestor, const bool bandejaEntrada) {
	int op = -1;
	string tipoBandeja;

	(bandejaEntrada) ? tipoBandeja = "entrada" : tipoBandeja = "salida";
	cout << "Correo de " << gestor.listaUsuSistema.listaUsuarios[gestor.usuario_activo].nombre << endl;
	cout << "------------------------------Bandeja de " << tipoBandeja << "-------------------------------\n";
	cout << "-------------------------------------------------------------------------------\n";
	cout << "L N    EMISOR              ASUNTO                                        FECHA \n";
	cout << "-------------------------------------------------------------------------------\n";
	(bandejaEntrada) ? mostrarCabeceras(gestor, gestor.listaUsuSistema.listaUsuarios[gestor.usuario_activo].listaRegRecibidos) : mostrarCabeceras(gestor, gestor.listaUsuSistema.listaUsuarios[gestor.usuario_activo].listRegEnviados);
	cout << "-------------------------------------------------------------------------------\n";
	cout << "Elija una opcion:\n";
	cout << "  1 - Leer correo\n";
	cout << "  2 - Enviar correo\n";
	cout << "  3 - Borrar correo\n";
	(!bandejaEntrada) ? tipoBandeja = "entrada" : tipoBandeja = "salida";
	cout << "  4 - Ver bandeja de " << tipoBandeja << endl;
	cout << "  5 - Lectura de correos sin leer\n";
	cout << "  0 - Cerrar sesion\n";
	cout << "-------------------------------------------------------------------------------\n";
	cout << "Introduzca una opcion: ";
	cin >> op;

	return op;
}

void mostrarCabeceras(const tGestor& gestor, const tListaRegCorreo& listaReg) {
	int n = 1, pos;

	for (int i = listaReg.cont - 1; i >= 0; i--)
		if (buscar(gestor.listaCorrSistema, listaReg.listaRegistros[i].id, pos)) {
			(listaReg.listaRegistros[i].leido) ? cout << "  " : cout << "* ";
			cout << n << "   " << obtenerCabecera(gestor.listaCorrSistema.listaCorreos[pos]) << endl;
			n++;
		}
}