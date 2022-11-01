#include "mainwindow.h"

//Va a gestire tutti gli eventi che avvengono sull'applicazione
#include <QApplication>

int main(int argc, char *argv[])
{
    //Questo crea l'application object
    QApplication a(argc, argv);
    //Creiamo l'oggetto finestra
    MainWindow w;
    //Questo fa vedere la finestra precedentemente creata
    w.show();

    //Questo mette l'applicazione in un loop per fare gestire i vari eventi dell'applicazione
    return a.exec();
}
