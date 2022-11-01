#include "mainwindow.h"
//Fai una build per risolvere il problema (sostanzialmente cerca il file mainwindow.cpp)
//compilato
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Stiamo dicendo sul 'this' (rappresenta l'intera applicazione), che il widget che vogliamo
    //usare come elemento centrale (che prende tutto lo spazio), è quello chiamato 'textEdit',
    // !IMPORTANTE: textEdit è il nome che gli abbiamo dato all'interno della UI (volendo si può
    //cambiare da li.
    this->setCentralWidget(ui->textEdit);
    setWindowTitle("New File");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
   //Ci stiamo riferendo al currentFile dichiarato nel .h
   currentFile.clear();
   //Il textEdit coorrente viene svuotato a una nuova stringa
    ui->textEdit->setText(QString());
   setWindowTitle("New File");
}


void MainWindow::on_actionOpen_triggered()
{
    //Apre una finestra di dialogo per scegliere il file
   QString filename = QFileDialog::getOpenFileName(this, "Open the file");
   //Crea un oggetto per la gestione del file
   QFile file(filename);
   //Si imposta il nome del file corrente al nome file selezionato
   currentFile = filename;
   //Se il file non si apre in lettura, o non si riesce a percepire del testo
   if(!file.open(QIODevice::ReadOnly | QFile::Text)){
       //MessageBox per errori
       QMessageBox::warning(this,"Warning", "Cannot open file: " + file.errorString());
       return;
   }
   //Si imposta il window title al nome scelto precedentemente
   setWindowTitle(filename);
   //Si apre uno stream di testo dal file
   QTextStream in(&file);
   //Si legge il testo all'interno del file selezionato
   QString text = in.readAll();
   //Si imposta il contenuto di textEdit al testo precedentemente letto
   ui->textEdit->setText(text);
   //Si chiude il file
   file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    //Finestra di dialogo per salvare
   QString fileName = QFileDialog::getSaveFileName(this, "Save as");
   //Crea un oggetto per la gestione del file
   QFile file(fileName);
   //Se il file non si apre in scrittura, o non si riesce a percepire del testo
   if(!file.open(QFile::WriteOnly | QFile::Text)){
       //MessageBox per errori
       QMessageBox::warning(this,"Warning", "Cannot save file: " + file.errorString());
       return;
   }
   //Seleziona come file corrente il fileName selezionato precedentemente
   currentFile = fileName;
   //Si imposta il window title al nome scelto precedentemente
   setWindowTitle(fileName);
   //Si apre uno stream di testo verso file
   QTextStream out(&file);
   //Si converte il testo di textEdit in plainText
   QString text = ui->textEdit->toPlainText();
   //Si printa all'interno del file (tramite l'oggetto per la sua gestione
   //precedentemente creato), il testo appena convertito
   out << text;
   //Si chiude il file
   file.close();
}


void MainWindow::on_actionPrint_triggered()
{
    //Crea un oggetto printer
   QPrinter printer;
   //Qui come stringa dovremmo inserire il nome della stampante (Se già ne avessimo uno)
   printer.setPrinterName("Printer Name");
   //Qui ci permette di scegliere una stampante nella nostra network
   QPrintDialog pDialog(&printer,this);
   //Eseguiamo questa finestra di dialogo, e vediamo se viene rifiutata, in tal caso si printa un errore
  if(pDialog.exec() == QDialog::Rejected){
      QMessageBox::warning(this,"Warning", "Cannot access printer");
      return;
  }
  //Usiamo un metodo proprietario di textEdit per printare, tramite l'oggetto di printing
  ui->textEdit->print(&printer);
}


void MainWindow::on_actionExit_triggered()
{
    //Semplicemente chiude l'applicazione
   QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    //Metodo proprietario che ti permette di copiare quello che viene selezionato
   ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    //Metodo proprietario che ti permette di incollare quanto precedentemente copiato
   ui->textEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{

    //Metodo proprietario che ti permette di tagliare quanto selezionato
   ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    //Metodo proprietario che ti permette di tornare indietro di una mossa
   ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    //Metodo proprietario che ti permette di andare avanti di una mossa
   ui->textEdit->redo();
}


void MainWindow::on_actionSave_triggered()
{
    if(currentFile == ""){
       //MessageBox per errori
       QMessageBox::warning(this,"Warning", "No file selected");
       return;
    }
   QFile file(currentFile);
   //Se il file non si apre in scrittura, o non si riesce a percepire del testo
   if(!file.open(QFile::WriteOnly | QFile::Text)){
       //MessageBox per errori
       QMessageBox::warning(this,"Warning", "Cannot save file: " + file.errorString());
       return;
   }
   //Si apre uno stream di testo verso file
   QTextStream out(&file);
   //Si converte il testo di textEdit in plainText
   QString text = ui->textEdit->toPlainText();
   //Si printa all'interno del file (tramite l'oggetto per la sua gestione
   //precedentemente creato), il testo appena convertito
   out << text;
   //Si chiude il file
   file.close();

}

