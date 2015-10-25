
typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

typedef struct abb_nodo {
    char* clave;
    void* dato;
    struct abb_nodo_t* izq;
    struct abb_nodo_t* der;
} abb_nodo_t;

typedef struct abb {
    abb_comparar_clave_t* comparar;
    abb_destruir_dato_t* destruir;
    abb_nodo_t raiz;
    size_t tam;
} abb_t;

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
    abb_t* arbol = malloc(sizeof(abb_t));
    if(!arbol) return NULL;

    arbol->comparar = cmp;
    arbol->destruir = destruir_dato;
    arbol->raiz = NULL;
    arbol->tam = 0;

    return arbol;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
    if(!arbol || !clave) return false;

    abb_nodo_t* nuevo_nodo = malloc(sizeof(abb_nodo_t));
    if(!nuevo_nodo) return false;

    copiar_clave(clave, nuevo_nodo->clave);
    nuevo_nodo->dato = dato;
    nuevo_nodo->der = NULL;
    nuevo_nodo->izq = NULL;

    return guardar_recursivo(arbol, nuevo_nodo, arbol->raiz);
}

bool guardar_recursivo(abb_t* arbol, abb_nodo_t* nodo, abb_nodo_t* raiz) {
    if(!raiz)
    {
        raiz = nodo;
        arbol->tam++;
        return true;
    }

    int comp = arbol->comparar(raiz->clave, nodo->clave);

    if(comp == 0)
    {
        arbol->destruir(raiz->dato);
        free(raiz);
        raiz = nodo;
        arbol->tam++;
        return true;
    }

    if(comp > 0)
    {
        if(!arbol->raiz->der)
        {
            arbol->tam++;
            raiz->der = nodo;
            return true;
        }
        else
            return guardar_recursivo(arbol, nuevo_nodo, raiz->der);
    }

    if(!raiz->izq)
    {
        arbol->tam++;
        raiz->izq = nodo;
        return true
    }

    return guardar_recursivo(arbol, nuevo_nodo, raiz->izq);
}

void *abb_borrar(abb_t *arbol, const char *clave);

void *abb_obtener(const abb_t *arbol, const char *clave) {
    if(!arbol || !clave) return NULL;
    return obtener_recursivo(arbol->raiz, clave);
}

void* obtener_recursivo(abb_t* arbol, abb_nodo_t* nodo, const char* clave) {
    if(!nodo) return NULL;
    int comp = arbol->comparar(raiz->clave, nodo->clave);
    if(comp == 0)
        return nodo->dato;
    if(comp > 0)
        return obtener_recursivo(nodo->der, clave);
    return obtener_recursivo(nodo->izq, clave);
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {
    if(!arbol || !clave) return false;
        return pertenece_recursivo(arbol->raiz, clave);
}

bool pertenece_recursivo(abb_t* arbol, abb_nodo_t* nodo, const char* clave) {
    if(!nodo) return false;
    int comp = arbol->comparar(raiz->clave, nodo->clave);
    if(comp == 0)
        return true
    if(comp > 0)
        return obtener_recursivo(nodo->der, clave);
    return obtener_recursivo(nodo->izq, clave);
}

size_t abb_cantidad(abb_t *arbol) {
    return arbol->tam;
}

void abb_destruir(abb_t *arbol) {
    // TODO:
}

/*
La función destruir_dato se recibe en el constructor, para usarla en abb_destruir y en abb_insertar en el caso de que tenga que reemplazar el dato de una clave ya existente.

Por otro lado deben implementar dos iteradores inorder.
El iterador interno funciona usando la función de callback "visitar" que recibe la clave, el valor y un puntero extra, y devuelve true si se debe seguir iterando, false en caso contrario:
*/

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/* Y un iterador externo: */

typedef struct abb_iter {
    pila_t* pila;
} abb_iter_t;

bool apilar_izquierdos(pila_t* pila, abb_nodo_t* nodo) {
    abb_nodo_t* temp = nodo;

    while(temp =! NULL)
    {
        pila_apilar(temp);
        temp = temp->izq;
    }

    return true;
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
    if(!arbol) return NULL;

    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if(!iter) return NULL;

    pila_t* pila = malloc(sizeof(pila_t));
    if(!pila)
    {
        free(iter);
        return NULL;
    }

    iter->pila = pila;
    apilar_izquierdos(pila, arbol->raiz);

    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
    if(!iter || pila_esta_vacia(iter->pila)) return false;

    abb_nodo_t* nodo = pila_ver_tope(iter->pila);
    if(nodo->der != NULL && nodo->der->izq != NULL)
        return apilar_izquierdos(iter->pila, nodo->der);

    nodo = pila_desapilar(iter->pila);
    pila_apilar();

    return true;
}


const char *abb_iter_in_ver_actual(const abb_iter_t *iter);
bool abb_iter_in_al_final(const abb_iter_t *iter);
void abb_iter_in_destruir(abb_iter_t* iter);







