#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Questo serve per usare la finestra principale
#include <QMainWindow>


//Per gestire i file
#include <QFile>
//Per creare finestre di dialogo con l'utente
#include <QFileDialog>
//Per leggere e scrivere dal TextEdit
#include <QTextStream>
//Per creare box per messaggi
#include <QMessageBox>
//Per riuscire a stampare quanto scritto nella TextEdit
#include <QPrinter> //PROBLEMA: risolto aggiungendo quello che vedi nel CMake file
//Per creare una dialog per Stampare (suppongo?)
#include <QPrintDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //Costruttore dell'oggetto (Parent è a 0 se non possiede nessun sopra-componente
    MainWindow(QWidget *parent = nullptr);
    //Distruttore per liberare la memoria nel caso il componente venisse rimosso
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
};
#endif // MAINWINDOW_H
