#include "listaClase.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "clase.h"
#include "laboratorio.h"
#include "curso.h"
using namespace std;
listaClase::listaClase()
{
    //ctor
    inicio=0;
    fin=0;

}

listaClase::~listaClase()
{
    //dtor
    cout<<"Detructor de lista"<<endl;

    Curso * temp = inicio;
    while(inicio != 0){
        inicio = temp->getSiguiente();
        delete temp;
        temp = inicio;
    }

}

void listaClase::insertarAlInicio(Curso * nuevo)
{
    if(inicio == 0){
        inicio = nuevo;
        fin = nuevo;
   }
   else{
        nuevo->setSiguiente(inicio);
        inicio->setAnterior(nuevo);
        inicio = nuevo;
   }
}

void listaClase::insertar(int codigo, const char * nombre, int matriculados, const char* hora, int aula, const char * catedratico, int dias)
{
    Curso * nuevo= new Clase(codigo,nombre,matriculados,hora,aula,catedratico,dias);
    if(inicio == 0){
        inicio = nuevo;
        fin = nuevo;
   }
   else{
        fin->setSiguiente(nuevo);
        nuevo->setAnterior(fin);
        fin = nuevo;
   }
}

void listaClase::insertarAlFinal(Curso * nuevo)
{
    if(inicio == 0){
        inicio = nuevo;
        fin = nuevo;
   }
   else{
        //delete fin;
        fin->setSiguiente(nuevo);
        nuevo->setAnterior(fin);
        fin = nuevo;
   }
}

void listaClase::agregar(Curso* nuevo)
{
    if(inicio == 0){
        inicio = nuevo;
        fin = nuevo;
   }
   else{
        fin->setSiguiente(nuevo);
        nuevo->setAnterior(fin);
        fin = nuevo;
   }
}

void listaClase::mostrarLista()
{
    Curso * temp = inicio;
    while(temp !=0){
        temp->imprimir();
        temp = temp->getSiguiente();
    }
}

bool listaClase::buscarCurso(int codigo)
{
    Curso * temp = inicio;
    while(temp !=0){
        if(codigo == temp->getCodigo())
            return true;

        temp = temp->getSiguiente();
    }
    return false;
}

void listaClase::guardarArchivoAleatorio()
{
    ofstream archivoSalida ("prueba.txt",ios::out|ios::binary);
    Curso *temp1=inicio;
   while(temp1 !=0){
        Clase *temp2 = new Clase(temp1->getCodigo(),temp1->getNombre(),temp1->getMatriculados(),temp1->getHora(),((Clase*)temp1)->getAula(),((Clase*)temp1)->getCatedratico(),((Clase*)temp1)->getDias());
        archivoSalida.write(reinterpret_cast <const char *> (temp2),sizeof(Clase));
        temp1=temp1->getSiguiente();
        delete temp2;
   }
   archivoSalida.close();
}

void listaClase::leerArchivoAleatorio()
{
    ifstream archivoEntrada ("prueba.txt",ios::in | ios::binary);
    if(!archivoEntrada)
    {
        cout<<"El archivo no existe."<<endl;
        return;
    }

    Clase curso;

    archivoEntrada.read(reinterpret_cast<char *> (&curso), sizeof(Clase));

    while(archivoEntrada && !archivoEntrada.eof())
    {
        //curso->imprimir();
        this->insertar(curso.getCodigo(),curso.getNombre(),curso.getMatriculados(),curso.getHora(),curso.getAula(),curso.getCatedratico(),curso.getDias());
        archivoEntrada.read(reinterpret_cast<char *> (&curso), sizeof(Clase));

    }
    archivoEntrada.close();

}


