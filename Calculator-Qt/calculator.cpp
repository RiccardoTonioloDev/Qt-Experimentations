#include "calculator.h"
#include "ui_calculator.h"
//Va impostato per forza per utilizzare le RegEx
#include <QRegularExpression>

double calcVal = 0.0;
double memory = 0.0;
bool divTrigger = false;
bool multTrigger= false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    //Questo va a settare la vera e propria UI creata
    ui->setupUi(this);

    //SETUP + SLOTS dei widget di Calculator (non manuale come per notepad, ma automatizzato)
    //QString::number() ci permette di convertire i numeri in stringa
    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i = 0; i<10; ++i){
        //Qui creiamo i nomi dei vari tasti creati precedentemente
        QString butName = "Button" + QString::number(i);
        //Qui noi stiamo dicendo che cerchiamo un figlio (widget) di Calculator, che abbia butName, e specifichiamo
        //il tipo di quello che cerchiamo come puntatore (in questo caso, vogliamo un puntatore a QPushButton)
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        //Connettiamo i puntatori ai widget appena creati, e diciamo che quando si emette un SIGNAL del tipo released,
        //in this (ovvero nell'applicazione Calculator), dobbiamo attivare la funzione NumPressed (Definita precedentemente
        //nel file .h
        connect(numButtons[i],SIGNAL(released()), this, SLOT(NumPressed()));
    }

    //QUI facciamo il binding di tutti i vari slot, ai vari widget dell'interfaccia
        connect(ui->Add,SIGNAL(released()), this, SLOT(MathButtonPressed()));
        connect(ui->Subtract,SIGNAL(released()), this, SLOT(MathButtonPressed()));
        connect(ui->Multiply,SIGNAL(released()), this, SLOT(MathButtonPressed()));
        connect(ui->Devide,SIGNAL(released()), this, SLOT(MathButtonPressed()));

        connect(ui->Equals,SIGNAL(released()), this, SLOT(EqualButtonPressed()));
        connect(ui->ChangeSign,SIGNAL(released()), this, SLOT(ChangeNumberSign()));

        connect(ui->Clear,SIGNAL(released()), this, SLOT(ClearButtonPressed()));

        connect(ui->MemAdd,SIGNAL(released()), this, SLOT(MemAddButtonPressed()));
        connect(ui->MemClear,SIGNAL(released()), this, SLOT(MemClearButtonPressed()));
        connect(ui->MemGet,SIGNAL(released()), this, SLOT(MemGetButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    //Sender è una funzione che ci permette di ricevere il puntatore dell'oggetto che ha attivato lo slot
    QPushButton *button = (QPushButton *)sender();
    QString butval = button->text();
    QString displayVal = ui->Display->text();
    //Cambia il testo in un altro numero se prima c'era uno 0
    if((displayVal.toDouble()==0) ||(displayVal.toDouble()==0.0) ){
        ui->Display->setText(butval);
    }else{
        //Cambia il testo aggiungendo in coda, al numero sul display, la cifra presa dal bottone selezionato
        QString newVal = displayVal + butval;
        //Facciamo la conversione in double
        double dblNewVal = newVal.toDouble();
        //Così da poter trasformare in rappresentazione esponenziale (fornita in automatico da QString::number) nel caso in cui si superino le 16 cifre
        ui->Display->setText(QString::number(dblNewVal,'g',16));
    }
}

void Calculator::MathButtonPressed(){
    //Resettiamo tutti i simboli a false
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    //Salviamo in calcVal il numero precedente
    calcVal = displayVal.toDouble();
    //Richiediamo al sender il bottone che ha attivato lo slot
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    //In base a quello che è stato premuto andiamo ad attivare il boleano di operazione corrispondente
    if(QString::compare(butVal,"/",Qt::CaseInsensitive) == 0){
        divTrigger = true;
    }else if(QString::compare(butVal,"*",Qt::CaseInsensitive) == 0){
        multTrigger = true;
    }else if(QString::compare(butVal,"+",Qt::CaseInsensitive) == 0){
        addTrigger = true;
    }else{
        subTrigger = true;
    }
    //Rimettiamo a 0 il display per scrivere il numero successivo
    ui->Display->setText("0");
}

void Calculator::EqualButtonPressed(){
   double solution = 0.0;
   QString displayVal = ui->Display->text();
   //Prendiamo quanto scritto sul display, e lo convertiamo in double
   double dblDisplayVal = displayVal.toDouble();
   if(addTrigger || subTrigger || multTrigger || divTrigger){
       //In base alla operazione selezionata precedentemente, facciamo l'operazione di conseguenza, e la salviamo in solution
       if(addTrigger){
           solution = calcVal + dblDisplayVal;
       }
       else if(subTrigger){
           solution = calcVal - dblDisplayVal;
       }
       else if(multTrigger){
           solution = calcVal * dblDisplayVal;
       }
       else if(divTrigger){
           solution = calcVal / dblDisplayVal;
       }
   }
   //Impostiamo il valore del display a solution
   ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    //Usiamo i RegEx anche se volendo se ne potrebbe fare a meno
    QRegularExpression reg("[-]?[0-9.]*");
    if(reg.match(displayVal).hasMatch()){
        double dblDisplayVal = displayVal.toDouble();
        //Moltiplichiamo per -1 il risultato
        double dblDisplayValSign = -1 * dblDisplayVal;
        //Lo impostiamo nel display
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void Calculator::ClearButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    calcVal = 0.0;
    ui->Display->setText(QString::number(0));
}

void Calculator::MemAddButtonPressed(){
    QString displayVal = ui->Display->text();
    memory = displayVal.toDouble();
}

void Calculator::MemClearButtonPressed(){
    memory = 0.0;
}

void Calculator::MemGetButtonPressed(){
    ui->Display->setText(QString::number(memory));
}
