#ifndef GRAPHICAL_STATS_H
#define GRAPHICAL_STATS_H
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts>
#include <QDebug>

namespace Ui {
class graphical_stats;
}

class graphical_stats : public QWidget
{
    Q_OBJECT
protected:
      void showEvent(QShowEvent *ev);
signals:
      void window_loaded();
public:
    explicit graphical_stats(QWidget *parent = 0);
    ~graphical_stats();

private:
    Ui::graphical_stats *ui;
    void weapon_use_graph();

private slots:
    void window_open();
};

#endif // GRAPHICAL_STATS_H
