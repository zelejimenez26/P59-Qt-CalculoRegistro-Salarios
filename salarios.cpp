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
    calcular();
}

void Salarios::limpiar()
{
    //Limpiar controles - dejar valores por defecto
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutino->setChecked(true);
    //Dejar cursor siempre en el menu
    ui->inNombre->setFocus();
}

void Salarios::guardar()
{
    //Abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo=QFileDialog::getSaveFileName(this,
                                                       "Guardar archivo",
                                                       QDir::home().absolutePath(),
                                                       "Archivos de texto(*.txt)");


    //Crear un objeto QFile
    QFile archivo(nombreArchivo);
    //Abrirlo para escritura
    if(archivo.open(QFile::WriteOnly|QIODevice::Text)){
        //Crear un stream de texto
        QTextStream salida(&archivo);
        //Enviar los datos del resulatdo a la salida
        salida<<ui->outResultado->toPlainText();
        salida<<"****************\n";
        //salida<<"Totales\n";
        salida<<ui->outSalarioB->text()<<"\n";
        salida<<ui->outDescuento->text()<<"\n";
        salida<<ui->outSalarioN->text()<<"\n";
        //Mostrar por 5 segundos que todo esta bien
        ui->statusbar->showMessage("Datos alamcenados en " + nombreArchivo, 5000);
    }else{
        QMessageBox::warning(this,"Guardar datos", "No se puedo guardar el archivo");
    }
    //Cerrar archivo
    archivo.close();

}

void Salarios::abrir()
{
    //Abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo=QFileDialog::getOpenFileName(this,
                                                       "Abrir archivo",
                                                       QDir::home().absolutePath(),
                                                       "Archivos de texto(*.txt)");


    //Crear un objeto QFile
    QFile archivo(nombreArchivo);
    //Abrirlo para lectura
    if(archivo.open(QFile::ReadOnly)){
        //Crear un stream de texto
        QTextStream entrada(&archivo);

        /*
        //Leer
        QString datos=entrada.readAll();
        //Cargar el contenido al area de texto
        ui->outResultado->clear();
        ui->outResultado->setPlainText(datos);
        */

        //Leer linea por linea el contenido del archivo
        QString linea="", totalB="", totalD="", totalN="";

        while (!entrada.atEnd()){
            linea=linea+entrada.readLine()+"\n";
            if(linea.contains("********")){
                linea.remove("*");
                //return true;
                totalB=entrada.readLine();
                totalD=entrada.readLine();
                totalN=entrada.readLine();
            }
        }

        ui->outResultado->clear();
        ui->outResultado->setPlainText(linea);
        ui->outSalarioB->setText(totalB);
        ui->outDescuento->setText(totalD);
        ui->outSalarioN->setText(totalN);

        //Mostrar por 5 segundos que todo esta bien
        ui->statusbar->showMessage("Datos leidos desde " + nombreArchivo, 5000);
    }else{
        QMessageBox::warning(this,"Abrir datos", "No se puedo abrir el archivo");
    }

    //Cerrar archivo
    archivo.close();
}


void Salarios::on_actionCalcular_triggered()
{
    calcular();
}

void Salarios::calcular()
{
    //Obtener datos de la GUI
    QString nombre=ui->inNombre->text(); //texto del widget
    int horas=ui->inHoras->value(); //value(), devuelve solo el valor
    tipoJornada jornada;
    if(ui->inMatutino->isChecked()){
        jornada=tipoJornada::Matutina;
    }else if(ui->inVespertina->isChecked()){
        jornada=tipoJornada::Vespertina;
    }else{
        jornada=tipoJornada::Nocturna;
    }
    //Validar datos correctos - mostrar cuadro de dialogo
    if(nombre==""||horas==0){
        /*
        QMessageBox msgBox;
        msgBox.setText("El nombre o el numero de horas esta vacio"); //mostrar mensaje
        msgBox.setIcon(QMessageBox::Warning); //incluir icono
        msgBox.exec(); //ejecutar
        */

        //Otra forma
        QMessageBox::warning(this, "Advertencia", "El nombre o el numero esta vacio");
        return;
    }

    //Agregar obrero al controlador
    m_controlador->agregarObrero(nombre, horas, jornada);
    //Calcular
    if(m_controlador->calcularSalario()){
        //Muestra los resultados de los calculos de los obrero
        ui->outResultado->appendPlainText(m_controlador->obrero()->toString());
        //Mostrar totales
        ui->outSalarioB->setText("$ " + QString::number(m_controlador->m_totalSalarioB, 'f', 2));
        ui->outDescuento->setText("$ " + QString::number(m_controlador->m_totalDescuento, 'f', 2));
        ui->outSalarioN->setText("$ " + QString::number(m_controlador->m_totalSalarioN, 'f', 2));
        //Limpiar la interfaz
        limpiar();
        //Mostrar mensage por 5 segundos en la barra de estado
        ui->statusbar->showMessage("Calculos procesados para " + nombre, 5000);

    }else{
        QMessageBox::critical(
                    this,
                    "Error",
                    "Error al calcular el salario."
                    );
    }
}


void Salarios::on_actionGuardar_triggered()
{
    guardar();
}


void Salarios::on_actionNuevo_triggered()
{
    limpiar();

    ui->outResultado->clear();

    ui->outSalarioB->clear();
    ui->outDescuento->clear();
    ui->outSalarioN->clear();
}


void Salarios::on_actionAbrir_triggered()
{
    abrir();
}


void Salarios::on_actionAcerca_de_salarios_triggered()
{
    //Crear un objeto de la ventana que queremos invocar
    Acerca *dialogo = new Acerca(this);
    //Enviar parametro a la ventana de diaogo
    dialogo->setVersion(VERSION);
    //Mostrar la ventana (dialogo)
    dialogo->exec();
}

