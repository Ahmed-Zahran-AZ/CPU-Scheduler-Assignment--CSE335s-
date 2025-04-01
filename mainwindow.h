#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QLabel>
#include <QLineEdit>
#include <QVector>
#include <QPair>
#include <QQueue>
#include "process.h"
#include "processqueue.h"
#include "fcfs.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_CbuSchedulers_currentIndexChanged(int index);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void updateExecution();
    void exportGanttChart();

private:
    void updateProcessTables();
    void runScheduler();
    void runScheduler_instant();
    void addProcessToTable(const Process& p, QTableWidget* table, int row);
    void startExecution();
    void executeInstantly();
    void updateGanttChart();
    void updateAverageTimes();
    void drawGanttChart();
    void resetApplication();
    void abortExecution();
    void updateButtonStates();
    void updateReadyQueue();

    Ui::MainWindow *ui;
    ProcessQueue Queue;
    FCFS fcfs;
    QTimer *executionTimer;
    QLabel *timeQuantumLabel;
    QLineEdit *timeQuantumInput;
    int currentProcessIndex;
    int currentTime;
    bool isExecuting;
    bool isPreemptive;
    bool isPriority;
    bool isSJF;
    bool isRoundRobin;
    int timeQuantum;
    int quantumRemaining;
    QVector<QPair<int, int>> ganttChartData;
    
    // Graphics scene for Gantt chart
    QGraphicsScene *ganttScene;
    QVector<QGraphicsRectItem*> processBars;
    QVector<QGraphicsTextItem*> processLabels;
    QVector<QGraphicsTextItem*> timeLabels;
    QQueue<int> readyQueue;
};
#endif // MAINWINDOW_H
