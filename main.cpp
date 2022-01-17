#include "salarios.h"
#include "obrero.h"
#include "controlador.h"


#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Salarios w;
    w.show();

    //Obrero *objObrero1=new Obrero ("Juan", 47, tipoJornada::Vespertina); //1. Primero crear un objeto  2. Llenar el contructor

    /*
    qDebug()<<objObrero1->nombre()<<objObrero1->horas();
    switch (objObrero1->jornada()) {
    case tipoJornada::Matutina:
        qDebug()<<"Matutino";
        break;
    case tipoJornada::Vespertina:
        qDebug()<<"Vespertina";
        break;
    case tipoJornada::Nocturna:
        qDebug()<<"Nocturna";
        break;
    }
    */

    Controlador *obj=new Controlador();
    obj->agregarObrero("Juan", 40, tipoJornada::Matutina);
    if(obj->calcularSalario()){
        qDebug()<<obj->obrero()->toString();
    }else{
        qDebug()<<"No se pudo realizar el calculo de salarios";
    }
    return a.exec();
}
