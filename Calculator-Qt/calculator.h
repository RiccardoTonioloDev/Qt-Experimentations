#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
//Qui si usa il namespace della UI creata precedentemente. (appunto perchè abbiamo cambiato i nomi)
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    //Questa è la classe per generare tutti i widget qt, usata per l'handling dei segnali, ecc.
    Q_OBJECT

public:
    //Qui diciamo che questo widget non ha un genitore
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
private slots:
    //Definiamo altre funzioni che useremo in Calculator
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();

    void ClearButtonPressed();

    void MemAddButtonPressed();
    void MemClearButtonPressed();
    void MemGetButtonPressed();
};
#endif // CALCULATOR_H
