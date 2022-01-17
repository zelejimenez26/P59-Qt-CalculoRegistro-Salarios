#include "salarios.h"
#include "ui_salarios.h"

Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
    m_controlador=new Controlador(); //Intanciar objeto
}

Salarios::~Salarios()
{
    delete ui;
}


void Salarios::on_cmdCalcular_clicked()
{
    //Obtener datos de la GUI
    QString nombre=ui->inNombre->text(); //texto del widget
    int horas=ui->inHoras->value(); //value(), devuleve solo el valor
    tipoJornada jornada;
    if(ui->inMatutino->isChecked()){
        jornada=tipoJornada::Matutina;
    }else if(ui->inVespertina->isChecked()){
        jornada=tipoJornada::Vespertina;
    }else{
        jornada=tipoJornada::Vespertina;
    }
    //Agregar obrero al controlador
    m_controlador->agregarObrero(nombre, horas, jornada);
    //Calcular
    if(m_controlador->calcularSalario()){
        ui->outResultado->appendPlainText(m_controlador->obrero()->toString());
    }


}

