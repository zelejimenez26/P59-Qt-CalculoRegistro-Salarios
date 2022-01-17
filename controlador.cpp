#include "controlador.h"

Controlador::Controlador(QObject *parent) : QObject(parent)
{
    this->m_obrero=nullptr;
}

bool Controlador::agregarObrero(QString nombre, int horas, tipoJornada jornada)
{
    this->m_obrero=new Obrero(nombre, horas, jornada);
    return true;
}

bool Controlador::calcularSalario()
{
    //Validar que el obrero no sea nulo
    if(this->m_obrero==nullptr){
        return false;
    }

    //Determinar el valor hora
    double valorHora=0;
    switch (m_obrero->jornada()) {
    case tipoJornada::Vespertina:
        valorHora=VESPERTINO;
        break;
    case tipoJornada::Matutina:
        valorHora=MATUTINO;
        break;
    case tipoJornada::Nocturna:
        valorHora=NOCTURNO;
        break;
    default:
        return false;
    }

    //Calculo de horas extra
    int horas= m_obrero->horas();
    int horasExtra=0;
    if(m_obrero->horas()>40){
        horasExtra=m_obrero->horas() - 40;
        horas = 40;
    }

    //Calculo salario bruto
    double salarioBruto=horas*valorHora+horasExtra*(HORA_EXTRA*valorHora/100);
    //Calculo descuento
    double descuento=salarioBruto*IESS/100;
    //Calculo salario neto
    double salarioNeto=salarioBruto-descuento;

    //Establecer valores l objeto
    m_obrero->setSalarioBruto(salarioBruto);
    m_obrero->setDescuento(descuento);
    m_obrero->setSalarioNeto(salarioNeto);

    return true;

}

Obrero *Controlador::obrero() const
{
    return m_obrero;
}
