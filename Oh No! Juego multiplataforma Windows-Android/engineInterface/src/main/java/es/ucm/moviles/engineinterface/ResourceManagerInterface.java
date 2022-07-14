package es.ucm.moviles.engineinterface;
/*

Interfaz para la gestion de recursos.

Su funcionalidad es añadir, buscar y quitar.
Sus atributos serian un diccionario de tipo T y un metodo protegido para la carga de recursos
 */
public interface ResourceManagerInterface<T> {


    /**
     * Devuelve una instancia de recurso con el nombre solicitado
     * @return T o null si no es encontrado.
     */
    T getResource(String name, int size, int style);   //los parametros extra son para fuentes

    T getResource(String name);
    /**
     * Elimina el recurso con el nombre solicitado
     */
    void removeResource(String name);



    /**
     * @return Devuelve true en caso de exito, false en caso contrario.
     */
    void addResource(T res, String identifier);

}
