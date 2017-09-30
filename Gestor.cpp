#include "Gestor.h"

using namespace std;

void inicializar(tGestor& gestor, string dominio) {
	gestor.dominio = dominio;
	inicializar(gestor.listaCorrSistema);
	inicializar(gestor.listaUsuSistema);
	gestor.usuario_activo = -1;
}

// Inicializa el gestor e intenta arrancarlo cargando la información del dominio que se le pasa como parámetro.
// Para ello inicializará y cargará la lista de usuarios y de correos de dicho dominio.
// Si tiene éxito en todas las operaciones devuelve true y si alguna falla devuelve false.
bool arrancar(tGestor& gestor, string dominio) {
	inicializar(gestor, dominio);
	return cargar(gestor.listaUsuSistema, dominio) && cargar(gestor.listaCorrSistema, dominio);
}

// Esta operación apaga el gestor y guarda para ello las listas de usuarios y de correos del dominio que se encontrase activo en ese momento.
void apagar(const tGestor &gestor) {
	guardar(gestor.listaUsuSistema, gestor.dominio);
	guardar(gestor.listaCorrSistema, gestor.dominio);
}

// Lee los datos de usuario necesarios para crear una cuenta(id y contraseña) y si el id de usuario no existe y hay espacio en la lista de usuarios,
// crea la cuenta del usuario y registra al nuevo usuario como usuario activo en el gestor.
// Devuelve un booleano indicando si la operación tuvo éxito.
bool crearCuenta(tGestor &gestor) {
	bool ok = false;
	int pos;
	string id, contrasenia;
	tUsuario aux;

	cout << "Bienvenido al correo de " << gestor.dominio << endl;
	cout << "Introduzca su identificador de correo: ";
	cin >> id;
	id += gestor.dominio;
	cout << "Introduzca su contrase" << char(164) << "a: ";
	cin >> contrasenia;
	inicializar(aux, id, contrasenia);
	if (!buscarUsuario(gestor.listaUsuSistema, id, pos))
		if (aniadir(gestor.listaUsuSistema, aux))
			ok = true;
		else
			cout << "Lista de usuarios del sistema llena\n";
	else
		cout << "El usuario introducido ya existe en " << gestor.dominio << endl;
	(ok) ? gestor.usuario_activo = pos : gestor.usuario_activo = -1;
	system("pause");

	return ok;
}

// Lee los datos de usuario necesarios para validar la cuenta(id y contraseña) y si el usuario existe y la contraseña coincide,
// registra al usuario como usuario activo. Devuelve un booleano indicando si la operación tuvo éxito.
bool iniciarSesion(tGestor &gestor) {
	bool ok = false;
	int pos;
	string id, contrasenia;
	
	cout << "Bienvenido al correo de " << gestor.dominio << endl;
	cout << "Introduzca su identificador del correo: ";
	cin >> id;
	id += gestor.dominio;
	cout << "Introduzca su contrase" << char(164) << "a: ";
	cin >> contrasenia;
	if (buscarUsuario(gestor.listaUsuSistema, id, pos) && validarContrasenia(gestor.listaUsuSistema.listaUsuarios[pos], contrasenia))
		ok = true;
	(ok) ? gestor.usuario_activo = pos : gestor.usuario_activo = -1;

	return ok;
}

// Solicita el correo que el usuario quiere leer(será el número con el que el correo es mostrado por pantalla en la bandeja correspondiente),
// valida que existe y si es así, lo marca como correo leído.
// A continuación, busca el correo en la lista de correos y si lo encuentra lo muestra en la pantalla de lectura del correo(Fig. 3).
void leerCorreo(tGestor& gestor, tListaRegCorreo& listaReg) {
	int n, pos, op;
	tCorreo correoContestado;

	cout << "Introduzca el numero de correo que quiere leer: ";
	cin >> n;
	if (0 < n && n <= listaReg.cont) {
		system("cls");
		correoLeido(listaReg, listaReg.listaRegistros[listaReg.cont - n].id);
		if (buscar(gestor.listaCorrSistema, listaReg.listaRegistros[listaReg.cont - n].id, pos)) {
			cout << aCadena(gestor.listaCorrSistema.listaCorreos[pos]);
			cout << "-------------------------------------------------------------------------------\n";
			cout << "Elija una opcion:\n";
			cout << "  1 - Contestar correo\n";
			cout << "  0 - Volver a la bandeja\n";
			cout << "-------------------------------------------------------------------------------\n";
			cout << "Introduzca una opcion: ";
			cin >> op;
			if (op == 1) {
				cout << "Introduce el cuerpo del correo (XXX para terminar):\n";
				correoContestacion(gestor.listaCorrSistema.listaCorreos[pos], correoContestado, gestor.listaUsuSistema.listaUsuarios[gestor.usuario_activo].nombre);
				enviarCorreo(gestor, correoContestado);
			}
			else
				cout << "Volviendo a la bandeja de correos...\n";
			system("pause");
		}
	}
	else
		cout << "El numero proporcionadono no es valido :s\n";
}

// Este subprograma implementa el envío del correo en nuestra aplicación.Para ello el correo recibido como parámetro es insertado en la lista de correo.
// Si ha habido éxito, entonces se inserta el registro correspondiente en la lista de registros enviados del emisor y se intenta insertar igualmente 
// un registro de dicho correo en la lista de registros recibidos del destinatario del correo.
// Si el destinatario no existe o si su bandeja de entrada está llena, entonces se mostrará un mensaje de error.
void enviarCorreo(tGestor& gestor, const tCorreo &correo) {
	int pos;
	tRegCorreo registro;

	if (insertar(gestor.listaCorrSistema, correo)) {
		registro.id = correo.id;
		registro.leido = true;
		if (insertar(gestor.listaUsuSistema.listaUsuarios[gestor.usuario_activo].listRegEnviados, registro))
			cout << "El correo enviado se ha guardado en tu lista de enviados\n";
		// pos va a cambiar de significado
		if (buscarUsuario(gestor.listaUsuSistema, correo.destinatario, pos)) {
			registro.leido = false;
			insertar(gestor.listaUsuSistema.listaUsuarios[pos].listaRegRecibidos, registro);
		}
		else
			cout << "El usuario " << correo.destinatario << " no existe\n";
	}
	else
		cout << "Error: Lista de correos llena\n";

}

// Este subprograma implementa el borrado del correo de una bandeja de un determinado usuario(OJO : el correo no se borra de la lista de correos).
// Para ello, solicita el correo que el usuario quiere borrar(será el número con el que el correo es mostrado por pantalla en la bandeja correspondiente),
// valida que existe y si es así, procede a borrarlo.
void borrarCorreo(tGestor& gestor, tListaRegCorreo& listaReg) {
	int n;

	cout << "Introduzca el numero del correo que quiere borrar: ";
	cin >> n;
	if (0 < n && n <= listaReg.cont) {
		for (int i = listaReg.cont - n; i < listaReg.cont; i++)
			listaReg.listaRegistros[i] = listaReg.listaRegistros[i + 1];
		listaReg.cont--;
	}
	else
		cout << "El correo no ha podido borrarse\n";
}

// Este subprograma implementa la lectura rápida de correos sin leer.El resultado es que muestra en una pantalla todos los correos sin leer ordenados
// por asunto(ignorando todos los "Re : ") y por fecha. Al finalizar su ejecución los correos sin leer quedarán marcados como leídos.
void lecturaRapida(tGestor& gestor, tListaRegCorreo& listaReg) {
	tListaCorreos correos;
	int pos;
	
	correos.cont = 0;
	for (int i = 0; i < listaReg.cont; i++) {
		if (!listaReg.listaRegistros[i].leido) {
			listaReg.listaRegistros[i].leido = true;
			if (buscar(gestor.listaCorrSistema, listaReg.listaRegistros[i].id, pos)) {
				correos.listaCorreos[correos.cont] = gestor.listaCorrSistema.listaCorreos[pos];
				correos.cont++;
			}
			else
				cout << "No se ha encontrado el id " << listaReg.listaRegistros[i].id << " en la lista de correos\n";
		}
	}
	if (correos.cont == 0)
		cout << "No hay correos sin leer en esta bandeja\n";
	else {
		ordenar_AF(correos);
		mostrarLista(correos);
	}	
}