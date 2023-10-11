#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"

int funcion_comparador(void *e1, void *e2)
{
	if ((int *)e1 < (int *)e2) {
		return -1;
	} else if ((int *)e1 > (int *)e2) {
		return 1;
	}
	return 0;
}

void pruebas_crear()
{
	abb_comparador comparador = (abb_comparador)funcion_comparador;
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(arbol != NULL, "se creo correctamente un arbol");
	pa2m_afirmar(arbol->tamanio == 0,
		     "la cantidad de elementos del arbol es cero");
	pa2m_afirmar(abb_vacio(arbol), "el arbol esta vacio");
	pa2m_afirmar(arbol->nodo_raiz == NULL, "la raiz del arbol es nula");

	free(arbol);
}

void pruebas_insertar_buscar()
{
	abb_comparador comparador = (abb_comparador)funcion_comparador;
	abb_t *arbol = abb_crear(comparador);

	int *elemento1 = (int *)10;
	pa2m_afirmar(abb_insertar(NULL, (void *)elemento1) == NULL,
		     "insertar en arbol nulo devuelve NULL");
	arbol = abb_insertar(arbol, (void *)elemento1);
	pa2m_afirmar(arbol->nodo_raiz->elemento == (void *)elemento1,
		     "se agrego el elemento correcto en la raiz");
	pa2m_afirmar(arbol->nodo_raiz->derecha == NULL &&
			     arbol->nodo_raiz->izquierda == NULL,
		     "los nodos derecha e izquierda de la raiz apuntan a null");
	pa2m_afirmar(abb_tamanio(arbol) == 1, "la cantidad de nodos es 1");
	pa2m_afirmar(!abb_vacio(arbol), "el arbol no esta vacio");

	int *elemento2 = (int *)5;
	arbol = abb_insertar(arbol, (void *)elemento2);
	pa2m_afirmar(abb_tamanio(arbol) == 2, "la cantidad de nodos es 2");
	pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento == (void *)elemento2,
		     "se agrego el elemento en el hijo izquierdo de la raiz");
	pa2m_afirmar(
		arbol->nodo_raiz->derecha == NULL &&
			arbol->nodo_raiz->izquierda != NULL,
		"la raiz ahora tiene un hijo izquierdo y no tiene hijo derecho");

	int *elemento3 = (int *)15;
	abb_insertar(arbol, (void *)elemento3);
	pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == (void *)elemento3,
		     "se agrego el elemento en el hijo derecha de la raiz");
	pa2m_afirmar(arbol->nodo_raiz->derecha != NULL &&
			     arbol->nodo_raiz->izquierda != NULL,
		     "la raiz ahora tiene dos hijos");
	pa2m_afirmar(abb_tamanio(arbol) == 3, "la cantidad de nodos es 3");

	int *elemento4 = (int *)13;
	abb_insertar(arbol, (void *)elemento4);
	int *elemento5 = (int *)14;
	abb_insertar(arbol, (void *)elemento5);
	pa2m_afirmar(
		arbol->nodo_raiz->derecha->izquierda->elemento ==
			(void *)elemento4,
		"se agrego correctamente un elemento en el tercer nivel de la raiz");
	pa2m_afirmar(
		arbol->nodo_raiz->derecha->izquierda->derecha->elemento ==
			(void *)elemento5,
		"se agrego correctamente un elemento en el cuarto nivel de la raiz");
	pa2m_afirmar(abb_tamanio(arbol) == 5, "la cantidad de nodos es 5");

	void *elemento_buscado = abb_buscar(NULL, (void *)elemento1);
	pa2m_afirmar(elemento_buscado == NULL,
		     "buscar en arbol nulo devuelve NULL");
	elemento_buscado = abb_buscar(arbol, (void *)elemento1);
	pa2m_afirmar(elemento_buscado == (void *)elemento1,
		     "se busca un elemento y lo encuentra");
	elemento_buscado = abb_buscar(arbol, (void *)elemento2);
	pa2m_afirmar(elemento_buscado == (void *)elemento2,
		     "se busca un elemento y lo encuentra");
	elemento_buscado = abb_buscar(arbol, (void *)elemento3);
	pa2m_afirmar(elemento_buscado == (void *)elemento3,
		     "se busca un elemento y lo encuentra");
	elemento_buscado = abb_buscar(arbol, (void *)elemento4);
	pa2m_afirmar(elemento_buscado == (void *)elemento4,
		     "se busca un elemento y lo encuentra");
	elemento_buscado = abb_buscar(arbol, (void *)elemento5);
	pa2m_afirmar(elemento_buscado == (void *)elemento5,
		     "se busca un elemento y lo encuentra");
	elemento_buscado = abb_buscar(arbol, NULL);
	pa2m_afirmar(elemento_buscado == NULL,
		     "buscar un elemento nulo devuelve NULL");

	abb_destruir(arbol);
}

void pruebas_quitar()
{
	abb_comparador comparador = (abb_comparador)funcion_comparador;
	abb_t *arbol = abb_crear(comparador);

	int *elemento = (int *)44;
	void *elemento_eliminado = abb_quitar(NULL, (void *)elemento);
	pa2m_afirmar(elemento_eliminado == NULL,
		     "quitar elemento de un abb nulo devuelve NULL");
	elemento_eliminado = abb_quitar(arbol, (void *)elemento);
	pa2m_afirmar(elemento_eliminado == NULL,
		     "quitar elemento de un abb vacio devuelve NULL");

	elemento_eliminado = (void *)elemento;
	arbol = abb_insertar(arbol, NULL);
	elemento_eliminado = abb_quitar(arbol, NULL);
	pa2m_afirmar(elemento_eliminado == NULL,
		     "se puede buscar y eliminar un elemento NULL");

	int *veinte = (int *)20;
	abb_insertar(arbol, (void *)veinte);
	int *quince = (int *)15;
	abb_insertar(arbol, (void *)quince);
	int *diez = (int *)10;
	abb_insertar(arbol, (void *)diez);
	int *trece = (int *)13;
	abb_insertar(arbol, (void *)trece);
	int *diecisiete = (int *)17;
	abb_insertar(arbol, (void *)diecisiete);
	int *veinticinco = (int *)25;
	abb_insertar(arbol, (void *)veinticinco);
	int *treinta = (int *)30;
	abb_insertar(arbol, (void *)treinta);

	elemento_eliminado = abb_quitar(arbol, (void *)quince);
	pa2m_afirmar(
		elemento_eliminado == (void *)quince &&
			arbol->nodo_raiz->izquierda->elemento == (void *)trece,
		"se elimina correctamente un elemento con dos hijos y es reemplazado por su predecesor inorden");
	elemento_eliminado = abb_quitar(arbol, (void *)diecisiete);
	pa2m_afirmar(elemento_eliminado == (void *)diecisiete,
		     "se elimina correctamente una hoja");
	elemento_eliminado = abb_quitar(arbol, (void *)veinticinco);
	pa2m_afirmar(elemento_eliminado == (void *)veinticinco,
		     "se elimina correctamente un elemento con un hijo");
	elemento_eliminado = abb_quitar(arbol, (void *)veinte);
	pa2m_afirmar(elemento_eliminado == (void *)veinte &&
			     arbol->nodo_raiz->elemento == (void *)trece,
		     "se elimina y reemplaza correctamente la raiz");
	elemento_eliminado = abb_quitar(arbol, (void *)trece);
	pa2m_afirmar(elemento_eliminado == (void *)trece &&
			     arbol->nodo_raiz->elemento == (void *)diez,
		     "se elimina y reemplaza correctamente la raiz");
	elemento_eliminado = abb_quitar(arbol, (void *)diez);
	pa2m_afirmar(elemento_eliminado == (void *)diez &&
			     arbol->nodo_raiz->elemento == (void *)treinta,
		     "se elimina correctamente la raiz");
	elemento_eliminado = abb_quitar(arbol, (void *)treinta);
	pa2m_afirmar(elemento_eliminado == (void *)treinta && abb_vacio(arbol),
		     "se elimina el ultimo elemento y el arbol quedo vacio");

	abb_insertar(arbol, (void *)veinte);
	pa2m_afirmar(
		arbol->nodo_raiz->elemento == (void *)veinte,
		"se puede volver a insertar elementos luego de vaciar el arbol");
	abb_insertar(arbol, (void *)quince);
	abb_insertar(arbol, (void *)diez);
	abb_insertar(arbol, (void *)trece);
	abb_insertar(arbol, (void *)diecisiete);
	abb_insertar(arbol, (void *)veinticinco);
	abb_insertar(arbol, (void *)treinta);

	pa2m_nuevo_grupo(
		"\n======================== QUITAR ELEMENTOS DESDE LA RAIZ ========================");

	elemento_eliminado = abb_quitar(arbol, (void *)veinte);
	pa2m_afirmar(
		elemento_eliminado == (void *)veinte &&
			arbol->nodo_raiz->elemento == (void *)diecisiete,
		"se elimina la raiz y es reemplazada por su predecesor inorden");
	elemento_eliminado = abb_quitar(arbol, (void *)diecisiete);
	pa2m_afirmar(
		elemento_eliminado == (void *)diecisiete &&
			arbol->nodo_raiz->elemento == (void *)quince,
		"se elimina la raiz y es reemplazada por su predecesor inorden");
	elemento_eliminado = abb_quitar(arbol, (void *)quince);
	pa2m_afirmar(
		elemento_eliminado == (void *)quince &&
			arbol->nodo_raiz->elemento == (void *)trece,
		"se elimina la raiz y es reemplazada por su predecesor inorden");
	elemento_eliminado = abb_quitar(arbol, (void *)trece);
	pa2m_afirmar(
		elemento_eliminado == (void *)trece &&
			arbol->nodo_raiz->elemento == (void *)diez,
		"se elimina la raiz y es reemplazada por su predecesor inorden");
	elemento_eliminado = abb_quitar(arbol, (void *)diez);
	pa2m_afirmar(
		elemento_eliminado == (void *)diez &&
			arbol->nodo_raiz->elemento == (void *)veinticinco,
		"se elimina la raiz y es reemplazada por su predecesor inorden");
	elemento_eliminado = abb_quitar(arbol, (void *)veinticinco);
	pa2m_afirmar(
		elemento_eliminado == (void *)veinticinco &&
			arbol->nodo_raiz->elemento == (void *)treinta,
		"se elimina la raiz y es reemplazada por su predecesor inorden");
	elemento_eliminado = abb_quitar(arbol, (void *)treinta);
	pa2m_afirmar(
		elemento_eliminado == (void *)treinta &&
			arbol->nodo_raiz == NULL && abb_vacio(arbol),
		"se elimina el ultimo elemento, la raiz queda nula y el arbol esta vacio");

	abb_destruir(arbol);
}

void pruebas_recorrer_abb()
{
	abb_comparador comparador = (abb_comparador)funcion_comparador;
	abb_t *arbol = abb_crear(comparador);

	void *array[50];
	size_t tamanio_array = 10;

	pa2m_afirmar(abb_recorrer(NULL, INORDEN, array, tamanio_array) == 0,
		     "al intentar recorrer un arbol nulo se devuelve 0");
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, array, tamanio_array) == 0,
		     "al intentar recorrer un arbol vacio se devuelve 0");

	int *veinte = (int *)20;
	abb_insertar(arbol, (void *)veinte);
	int *quince = (int *)15;
	abb_insertar(arbol, (void *)quince);
	int *diez = (int *)10;
	abb_insertar(arbol, (void *)diez);
	int *trece = (int *)13;
	abb_insertar(arbol, (void *)trece);
	int *diecisiete = (int *)17;
	abb_insertar(arbol, (void *)diecisiete);
	int *veinticinco = (int *)25;
	abb_insertar(arbol, (void *)veinticinco);
	int *treinta = (int *)30;
	abb_insertar(arbol, (void *)treinta);

	pa2m_afirmar(
		abb_recorrer(arbol, 3, array, tamanio_array) == 0,
		"al intentar recorrer un arbol con un recorrido invalido se devuelve 0");
	pa2m_afirmar(
		abb_recorrer(arbol, INORDEN, array, tamanio_array) == 7,
		"al recorrer INORDEN, se almacenan todos los elementos en el array");
	pa2m_afirmar(
		array[0] == (void *)diez && array[1] == (void *)trece &&
			array[2] == (void *)quince &&
			array[3] == (void *)diecisiete &&
			array[4] == (void *)veinte &&
			array[5] == (void *)veinticinco &&
			array[6] == (void *)treinta,
		"los elementos se almacenaron en el orden correcto en el array");
	pa2m_afirmar(
		abb_recorrer(arbol, PREORDEN, array, tamanio_array) == 7,
		"al recorrer PREORDEN, se almacenan todos los elementos en el array");
	pa2m_afirmar(
		array[0] == (void *)veinte && array[1] == (void *)quince &&
			array[2] == (void *)diez && array[3] == (void *)trece &&
			array[4] == (void *)diecisiete &&
			array[5] == (void *)veinticinco &&
			array[6] == (void *)treinta,
		"los elementos se almacenaron en el orden correcto en el array");
	pa2m_afirmar(
		abb_recorrer(arbol, POSTORDEN, array, tamanio_array) == 7,
		"al recorrer POSTORDEN, se almacenan todos los elementos en el array");
	pa2m_afirmar(
		array[0] == (void *)trece && array[1] == (void *)diez &&
			array[2] == (void *)diecisiete &&
			array[3] == (void *)quince &&
			array[4] == (void *)treinta &&
			array[5] == (void *)veinticinco &&
			array[6] == (void *)veinte,
		"los elementos se almacenaron en el orden correcto en el array");

	tamanio_array = 0;
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, array, tamanio_array) == 0,
		     "si el tamaño del array es 0, se devuelve 0");

	tamanio_array = 2;
	pa2m_afirmar(
		abb_recorrer(arbol, INORDEN, array, tamanio_array) == 2,
		"al recorrer INORDEN con un array de tamaño 2, se almacenan 2 elementos en el array");
	pa2m_afirmar(
		array[0] == (void *)diez && array[1] == (void *)trece,
		"los elementos se almacenaron en el orden correcto en el array");
	pa2m_afirmar(
		abb_recorrer(arbol, PREORDEN, array, tamanio_array) == 2,
		"al recorrer PREORDEN con un array de tamaño 2, se almacenan 2 elementos en el array");
	pa2m_afirmar(
		array[0] == (void *)veinte && array[1] == (void *)quince,
		"los elementos se almacenaron en el orden correcto en el array");
	pa2m_afirmar(
		abb_recorrer(arbol, POSTORDEN, array, tamanio_array) == 2,
		"al recorrer POSTORDEN con un array de tamaño 2, se almacenan 2 elementos en el array");
	pa2m_afirmar(
		array[0] == (void *)trece && array[1] == (void *)diez,
		"los elementos se almacenaron en el orden correcto en el array");

	abb_destruir(arbol);
}

bool funcion_con_cada(void *v1, void *v2)
{
	return v1 != v2;
}

void pruebas_con_cada_elemento()
{
	abb_comparador comparador = (abb_comparador)funcion_comparador;
	abb_t *arbol = abb_crear(comparador);

	int *veinte = (int *)20;
	abb_insertar(arbol, (void *)veinte);
	int *quince = (int *)15;
	abb_insertar(arbol, (void *)quince);
	int *diez = (int *)10;
	abb_insertar(arbol, (void *)diez);
	int *trece = (int *)13;
	abb_insertar(arbol, (void *)trece);
	int *diecisiete = (int *)17;
	abb_insertar(arbol, (void *)diecisiete);
	int *veinticinco = (int *)25;
	abb_insertar(arbol, (void *)veinticinco);
	int *treinta = (int *)30;
	abb_insertar(arbol, (void *)treinta);

	bool (*funcion)(void *, void *) = funcion_con_cada;

	void *aux = (void *)treinta;
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, INORDEN, funcion, aux) == 7,
		"iterar el elemento INORDEN devuelve la cantidad correcta de veces que se aplico la funcion");
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, PREORDEN, funcion, aux) == 7,
		"iterar el elemento PREORDEN devuelve la cantidad correcta de veces que se aplico la funcion");
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, POSTORDEN, funcion, aux) == 5,
		"iterar el elemento POSTORDEN devuelve la cantidad correcta de veces que se aplico la funcion");
	aux = (void *)diecisiete;
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, INORDEN, funcion, aux) == 4,
		"iterar el elemento INORDEN devuelve la cantidad correcta de veces que se aplico la funcion");
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, PREORDEN, funcion, aux) == 5,
		"iterar el elemento PREORDEN devuelve la cantidad correcta de veces que se aplico la funcion");
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, POSTORDEN, funcion, aux) == 3,
		"iterar el elemento POSTORDEN devuelve la cantidad correcta de veces que se aplico la funcion");

	pa2m_afirmar(abb_con_cada_elemento(NULL, POSTORDEN, funcion, aux) == 0,
		     "iterar en arbol nulo devuelve 0");
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, NULL, aux) == 0,
		     "iterar con funcion nula devuelve 0");
	pa2m_afirmar(abb_con_cada_elemento(arbol, 5, funcion, aux) == 0,
		     "iterar el arbol con recorrido invalido devuelve 0");
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, POSTORDEN, funcion,
				      (void *)(int *)50) == abb_tamanio(arbol),
		"iterar el arbol sin que corte la funcion devuelve la cantidad de nodos del arbol");

	abb_t *arbol_vacio = abb_crear(comparador);
	pa2m_afirmar(abb_con_cada_elemento(arbol_vacio, POSTORDEN, funcion,
					   aux) == 0,
		     "iterar en arbol vacio devuelve 0");

	abb_destruir(arbol);
	abb_destruir(arbol_vacio);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== CREAR ABB ========================");
	pruebas_crear();
	pa2m_nuevo_grupo(
		"\n======================== INSERTAR y BUSCAR ELEMENTOS ========================");
	pruebas_insertar_buscar();
	pa2m_nuevo_grupo(
		"\n======================== QUITAR ELEMENTOS ========================");
	pruebas_quitar();
	pa2m_nuevo_grupo(
		"\n======================== RECORRER ABB ========================");
	pruebas_recorrer_abb();
	pa2m_nuevo_grupo(
		"\n======================== ITERADOR INTERNO ========================");
	pruebas_con_cada_elemento();

	return pa2m_mostrar_reporte();
}
