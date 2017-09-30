#ifndef GESTOR_H
#define GESTOR_H

#include "ListaUsuarios.h"
#include "ListaCorreos.h"

using namespace std;

typedef struct {
	string dominio; // -El dominio del gestor de correo(string).Se trata de un identificador como por ejemplo “fdimail.com”.Nos indica la lista de correos y de usuarios que debemos cargar.
	tListaCorreos listaCorrSistema; // - La lista de correos del sistema que será de tipo tListaCorreos y que guarda la única copia de los correos que existirá en la aplicación.
	tListaUsuarios listaUsuSistema; // - La lista de usuarios del sistema que será de tipo tListaUsuarios.
	int usuario_activo; // - Índice del usuario activo en el sistema(de tipo int).Nos indica la posición en la lista de usuarios que ocupa el usuario que se encuentra registrado en el sistema.Si no hay ningún usuario registrado(o el usuario ha cerrado sesión) valdrá - 1.
} tGestor;

void inicializar(tGestor& gestor, string dominio);
bool arrancar(tGestor& gestor, string dominio); // Inicializa el gestor e intenta arrancarlo cargando la información del dominio que se le pasa como parámetro.Para ello inicializará y cargará la lista de usuarios y de correos de dicho dominio.Si tiene éxito en todas las operaciones devuelve true y si alguna falla devuelve false.
void apagar(const tGestor &gestor); // Esta operación apaga el gestor y guarda para ello las listas de usuarios y de correos del dominio que se encontrase activo en ese momento.
bool crearCuenta(tGestor &gestor); // Lee los datos de usuario necesarios para crear una cuenta(id y contraseña) y si el id de usuario no existe y hay espacio en la lista de usuarios, crea la cuenta del usuario y registra al nuevo usuario como usuario activo en el gestor.Devuelve un booleano indicando si la operación tuvo éxito.
bool iniciarSesion(tGestor &gestor); // Lee los datos de usuario necesarios para validar la cuenta(id y contraseña) y si el usuario existe y la contraseña coincide, registra al usuario como usuario activo.Devuelve un booleano indicando si la operación tuvo éxito.
void leerCorreo(tGestor& gestor, tListaRegCorreo& listaReg); // Solicita el correo que el usuario quiere leer(será el número con el que el correo es mostrado por pantalla en la bandeja correspondiente), valida que existe y si es así, lo marca como correo leído.A continuación, busca el correo en la lista de correos y si lo encuentra lo muestra en la pantalla de lectura del correo(Fig. 3).
void enviarCorreo(tGestor& gestor, const tCorreo &correo); // Este subprograma implementa el envío del correo en nuestra aplicación.Para ello el correo recibido como parámetro es insertado en la lista de correo.Si ha habido éxito, entonces se inserta el registro correspondiente en la lista de registros enviados del emisor y se intenta insertar igualmente un registro de dicho correo en la lista de registros recibidos del destinatario del correo.Si el destinatario no existe o si su bandeja de entrada está llena, entonces se mostrará un mensaje de error.
void borrarCorreo(tGestor& gestor, tListaRegCorreo& listaReg); // Este subprograma implementa el borrado del correo de una bandeja de un determinado usuario(OJO : el correo no se borra de la lista de correos).Para ello, solicita el correo que el usuario quiere borrar(será el número con el que el correo es mostrado por pantalla en la bandeja correspondiente), valida que existe y si es así, procede a borrarlo.
void lecturaRapida(tGestor& gestor, tListaRegCorreo& listaReg); // Este subprograma implementa la lectura rápida de correos sin leer.El resultado es que muestra en una pantalla todos los correos sin leer ordenados por asunto(ignorando todos los “Re : ”) y por fecha.Al finalizar su ejecución los correos sin leer quedarán marcados como leídos.

#endif