#include "ListaLaboratorio.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "Laboratorio.h"
#include "laboratorio.h"
#include "curso.h"
using namespace std;
ListaLaboratorio::ListaLaboratorio()
{
    //ctor
    inicio=0;
    fin=0;

}

ListaLaboratorio::~ListaLaboratorio()
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

void ListaLaboratorio::insertarAlInicio(Curso * nuevo)
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

void ListaLaboratorio::insertar(int codigo, const char * nombre, int matriculados, const char* hora, int numLaboratorio, const char * instructor)
{
    Curso * nuevo= new Laboratorio(codigo,nombre,matriculados,hora,numLaboratorio,instructor);
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

void ListaLaboratorio::insertarAlFinal(Curso * nuevo)
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

void ListaLaboratorio::agregar(Curso* nuevo)
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

void ListaLaboratorio::mostrarLista()
{
    Curso * temp = inicio;
    while(temp !=0){
        temp->imprimir();
        temp = temp->getSiguiente();
    }
}

Curso* ListaLaboratorio::buscarCurso(int codigo)
{
    Curso * temp = inicio;
    while(temp !=0){
        if(codigo == temp->getCodigo())
            return temp;

        temp = temp->getSiguiente();
    }
    return 0;
}

void ListaLaboratorio::guardarArchivoAleatorio()
{
    ofstream archivoSalida ("prueba.txt",ios::out|ios::binary);
    Curso *temp1=inicio;
   while(temp1 !=0){
        Laboratorio *temp2 = new Laboratorio(temp1->getCodigo(),temp1->getNombre(),temp1->getMatriculados(),temp1->getHora(),((Laboratorio*)temp1)->getNumLaboratorio(),((Laboratorio*)temp1)->getInstructor());
        archivoSalida.write(reinterpret_cast <const char *> (temp2),sizeof(Laboratorio));
        temp1=temp1->getSiguiente();
        delete temp2;
   }
   archivoSalida.close();
}

void ListaLaboratorio::leerArchivoAleatorio()
{
    ifstream archivoEntrada ("prueba.txt",ios::in | ios::binary);
    if(!archivoEntrada)
    {
        cout<<"El archivo no existe."<<endl;
        return;
    }

    Laboratorio curso;

    archivoEntrada.read(reinterpret_cast<char *> (&curso), sizeof(Laboratorio));

    while(archivoEntrada && !archivoEntrada.eof())
    {
        //curso->imprimir();
        this->insertar(curso.getCodigo(),curso.getNombre(),curso.getMatriculados(),curso.getHora(),curso.getNumLaboratorio(),curso.getInstructor());
        archivoEntrada.read(reinterpret_cast<char *> (&curso), sizeof(Laboratorio));

    }
    archivoEntrada.close();

}


