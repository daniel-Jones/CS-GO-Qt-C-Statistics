#include "graphical_stats.h"
#include "ui_graphical_stats.h"

graphical_stats::graphical_stats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphical_stats)
{
    ui->setupUi(this);

    connect(this, SIGNAL(window_loaded()), this, SLOT(window_open()), Qt::ConnectionType(Qt::QueuedConnection | Qt::UniqueConnection));
}

graphical_stats::~graphical_stats()
{
    delete ui;
}

void graphical_stats::weapon_use_graph()
{
    QPieSeries *series = new QPieSeries();
    for (int x = 0; x < 5; x ++)
    {
        series->append(QString::number(x), 1000);
        QPieSlice *slice = series->slices().at(x);
        slice->setExploded();
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::darkGreen, 2));
        slice->setBrush(Qt::green);
    }


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple chart");
    chart->legend()->hide();
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addItem(chart);
    scene->addText("test");
    ui->graphicsView->setScene(scene);
}

void graphical_stats::window_open()
{
    /*
     * our graphicals stats are ready to be done
     * setup our first graph
    */
    weapon_use_graph();
}

void graphical_stats::showEvent(QShowEvent *ev)
{
    emit window_loaded();
}
