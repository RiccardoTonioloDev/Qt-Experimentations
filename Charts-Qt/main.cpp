//Inizializzazione dell'applicazione
#include <QApplication>
//Questo serve per utilizzare la finestra principale (toolbar, menubar, widget figli, ecc.)
#include <QtWidgets/QMainWindow>
//Per mostrare tutti i vari grafici
#include <QtCharts/QChartView>
//Per disegnare barre per rappresentare dati
#include <QtCharts/QBarSeries>
//Per rappresentare un set di barre
#include <QtCharts/QBarSet>
//Per fare vedere le legende nel grafico
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
//Un tipo di grafico
#include <QtCharts/QHorizontalStackedBarSeries>
//Per fare grafici con linee
#include <QtCharts/QLineSeries>
//Per cambiare i nomi degli assi
#include <QtCharts/QCategoryAxis>
//Per creare grafici a torta
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Qui stiamo creando un set per ogni giocatore
    //Il valore di inizializzazione del giocatore sarà indicato nella leggenda per riconoscerlo
    QBarSet *set0 = new QBarSet("Altuve");
    QBarSet *set1 = new QBarSet("Martinez");
    QBarSet *set2 = new QBarSet("Segura");
    QBarSet *set3 = new QBarSet("Simmons");
    QBarSet *set4 = new QBarSet("Trout");

    //In questo modo si posizionano dati all'interno di un set
    *set0<<283<<341<<313<<338<<346<<345;
    *set1<<250<<315<<282<<307<<303<<303;
    *set2<<294<<246<<257<<319<<300<<325;
    *set3<<248<<244<<264<<281<<278<<313;
    *set4<<323<<287<<299<<315<<306<<313;

    //Qui usavo delle barre verticali
    //QBarSeries* series = new QBarSeries();
    //Qui uso delle barre orizontali
    QHorizontalStackedBarSeries* series = new QHorizontalStackedBarSeries();

    //Metto in append alla serie da analizzare nel grafico, tutti i vari set
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    //Creiamo un nuovo grafico
    QChart *chart = new QChart();
    //Gli aggiungiamo le serie
    chart->addSeries(series);
    //Settiamo il titolo
    chart->setTitle("Batting Avg by Year");
    //NoAnimation, GridAxisAnimations, SeriesAnimations (Sono le varie opzioni per le animazioni
    chart->setAnimationOptions(QChart::AllAnimations);
    //Andiamo a creare una lista di categorie, che verranno utilizzate per l'asse delle annate
    QStringList categories;
    categories << "2013"<<"2014"<<"2015"<<"2016"<<"2017"<<"2018";
    //Creo un nuovo asse da usare per il grafico
    QBarCategoryAxis * axis = new QBarCategoryAxis();
    //Inserisco al suo interno le categorie precedentemente create
    axis->append(categories);
    //Creo degli assi di default per andare a creare un asse anche per le X
    chart->createDefaultAxes();
    //Sovrascrivo l'asse delle X con il mio.
    //Lo uso anche se deprecato, perchè non esistono soluzioni migliori/funzionanti al momento.
    chart->setAxisY(axis,series);

    //Imposto la leggenda come visibile e la ripongo in basso
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    //Uso chartView perchè è la classe che gestisce il display del grafico
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //Imposto la palette colori generale del grafico (I colori delle barre saranno automatici)
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404040));
    qApp->setPalette(pal);


    //In questa porzione posiziono, manualmente tramite codice, il grafico all'interno della finestra
    QMainWindow window;
    window.setCentralWidget(chartView);
    //Faccio il size della finestra
    window.resize(420,300);
    //E poi la mostro
    window.show();

    //Questo come già visto in precedenza serve per mettere in un loop infinito l'applicazione, per farla reagire
    //agli eventi.
    return a.exec();
}
