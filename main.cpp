/**
 * @file main.cpp
 * @version 1.0
 * @date 12/03/2023
 * @authors Claudio Arce Cascante 201058559, Andrés Madrigal Vega 2021572460 y Julia Harlander 2023397041
 * @brief Primer trabajo extra clase, curso  Algoritmos y Estructuras de Datos II
 */

#include<iostream>
#include<list>

using namespace std;

/**
 * @brief Clase collector
 * Esta clase será la encargada de recolectar y reciclar las diversas direcciones de memoria
 */
class Collector {
private:
    list<void *> addresses;

public:
    /**
     * @brief Método encargado de generar una lista vacía para almacenar las diversas direcciones de memoria
     */
    Collector() {
        this->addresses = {};
    }

    /**
     * @brief Método encargado de recolectar las direcciones de memoria
     * @param size
     * @return direccion liberada
     */
    void *getRecicledAddress(size_t size) {
        if (this->addresses.size() == 0) {
            return malloc(size);
        } else {
            void *freeAddress = this->addresses.back();
            addresses.pop_back();
            return freeAddress;
        }
    }

    /**
     * @brief Método encargado de obtener las direcciones de memoria
     * @param freedAdrress
     */
    void collectAdrress(void *freedAdrress) {
        this->addresses.push_front(freedAdrress);
    }

    /**
     * @brief Metodo encargado de realizar los prints correspondientes a la clase Collector
     */
    void print() {
        if (this->addresses.size() == 0) {
            cout << "No hay dirreciones para reciclar" << '\n';
        } else {
            cout << "Dirreciones Disponibles" << '\n';
            for (auto const &i: addresses) {
                cout << i << std::endl;
            }
        }
    }
};

Collector myCollector; ///< Se crea myCollector para poder hacer uso de la clase Collector

/**
 * @brief Clase Nodo
 * Esta clase se encarga de crear los diversos nodos a utilizar en la lista
 */
class Node {
private:
    int value;///< Se crea un valor entero para los nodos
    Node *next; ///< Se crea un puntero para pasar de nodo


public:
    /**
     * @brief Función Nodo
     * Encargada de manejar las funciones de los nodos
     */
    Node() {

    }

    /**
     * @brief Metodo Nodo
     * Encargado de asiganr el valor el nodo head y al siguiente
     * @param value
     * @param next
     */
    Node(int value, Node *next) {
        this->value = value;
        this->next = next;
    }

    /**
     * @brief Metodo getValue
     * Metodo encargado de obtener el valor de los nodos
     * @return valor del nodo
     */
    int getValue() {
        return this->value;
    }

    /**
     * @brief Metodo getNext
     * Encargado de obtener el valor del nodo consecuente
     * @return valor del siguiente nodo
     */
    Node *getNext() {
        return this->next;
    }

    /**
     * @brief Metodo para obtener las direcciones recicladas
     * Encargada de brindar las direcciones recicladas
     * @param size
     * @return
     */
    void *operator new(size_t size) {
        return myCollector.getRecicledAddress(size);
    }

    /**
     * @brief Metodo delete
     * Encargado de liberar espacios en la memoria
     * @param pointer
     */
    void operator delete(void *pointer) {
        myCollector.collectAdrress((void *) pointer);
    }

};

/**
 * @brief Clase List
 * Esta clase se encarga de crear y manejar las diversas funciones presentes en la lista
 */
class List {

private:
    int value;
    int next;

public:
    Node *head;///< Puntero al primer nodo de la lista.

    /**
     * @brief Constructor de la clase List.
     * @param h Puntero al primer nodo de la lista.
     */
    List(Node *h = nullptr) : head(h) {}

    /**
     * @brief Inserta un nuevo nodo al inicio de la lista.
     * @param val Valor que se almacenará en el nuevo nodo.
     */
    void insert(int val) {
        Node *new_node = new Node(val, head);
        head = new_node;
    };

    /**
     * @brief Elimina elementos de la lista
     */
    void deleteNode() {
        if (head != nullptr) {
            Node *temp = head;
            head = (Node *) head->getNext();
            delete temp;
        }
    }

    /**
     * @brief Printea el contenido de la lista
     */
    void print() {
        Node *node_ptr = head;
        cout << "Contenido de la lista: ";
        while (node_ptr != nullptr) {
            cout << node_ptr->getValue() << " ";
            node_ptr = (Node *) node_ptr->getNext();
        }
        cout << endl;
    }

    int getValue(){
        return this->value;
    }

    void setValue(int value){
        this->value = value;
    }

    int getNext(){
        return this->next;
    }

    void setNext(){
        this->next = value;
    }


};

/**
 * @brief Clase main
 * Clase principal para el funcionamiento y llamado de funciones del código
 * @return printea diversas lineas las cuales le brindan al usuario una idea rápida del funcionamiento del código
 */
int main() {

    /**
     * Establece myList para poder hacer uso de la clase List
     */
    List myList;

    /**
     * Se incertan 3 valores a la lista
     */
    myList.insert(1);
    myList.insert(2);
    myList.insert(3);

    myList.print();///< Printea la lista
    cout << '\n';
    myCollector.print();///< Printea el collector
    cout << '\n';
    printf("---------------------------------- \n");
    cout << '\n';

    myList.deleteNode();///< Eliminacion de nodo
    myList.print();
    cout << '\n';
    myCollector.print();///< Printea collector
    cout << '\n';
    printf("---------------------------------- \n");
    cout << '\n';

    /**
     * Repite los procesos anteriores
     */
    myList.deleteNode();
    myList.print();
    cout << '\n';
    myCollector.print();
    cout << '\n';
    printf("---------------------------------- \n");
    cout << '\n';

    myList.deleteNode();
    myList.print();
    cout << '\n';
    myCollector.print();
    cout << '\n';
    printf("---------------------------------- \n");
    cout << '\n';

    myList.insert(4);///< Inserta un nuevo valor a la lista
    myList.print();///< Pirntea la lista
    cout << '\n';
    cout << "Dirrecion Reciclada: \n";
    cout << myList.head << '\n';///< Printea la direccion reciclada
    cout << '\n';
    myCollector.print();///< Printea collector
    cout << '\n';
    printf("---------------------------------- \n");
    cout << '\n';

    /**
     * Repite proceso anterior
     */
    myList.insert(5);
    myList.print();
    cout << '\n';
    cout << "Dirrecion Reciclada: \n";
    cout << myList.head << '\n';
    cout << '\n';
    myCollector.print();
    cout << '\n';
    printf("---------------------------------- \n");
    cout << '\n';

    myList.insert(6);
    myList.print();
    cout << '\n';
    cout << "Dirrecion Reciclada: \n";
    cout << myList.head << '\n';
    cout << '\n';
    myCollector.print();
    cout << '\n';
    printf("---------------------------------- \n");
    cout << '\n';

    return 0;
}
