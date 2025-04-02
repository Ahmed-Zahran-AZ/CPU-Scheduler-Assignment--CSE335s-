/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *inputGroup;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *CbuSchedulers;
    QLabel *label_2;
    QLineEdit *BurstTIme;
    QLabel *label_3;
    QLineEdit *Arrival;
    QLabel *PriorityLabel;
    QLineEdit *Priority;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_6;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *currentProcessesGroup;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *CurrentProcesses;
    QGroupBox *executionGroup;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *inExcution;
    QGroupBox *finishedGroup;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *FinishedProcesses;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *ganttGroup;
    QVBoxLayout *verticalLayout_7;
    QGraphicsView *GanttChart;
    QLabel *AverageTimes;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 800);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #f0f0f0;\n"
"}\n"
"QLabel {\n"
"    color: #2c3e50;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #bdc3c7;\n"
"}\n"
"QTableWidget {\n"
"    background-color: white;\n"
"    border: 1px solid #bdc3c7;\n"
"    border-radius: 4px;\n"
"}\n"
"QTableWidget::item {\n"
"    padding: 4px;\n"
"}\n"
"QTableWidget::item:selected {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #34495e;\n"
"    color: white;\n"
"    padding: 6px;\n"
"    border: none;\n"
"}\n"
"QLineEdit {\n"
"    padding: 6px;\n"
"    border: 1px solid #bdc3c7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"}\n"
"QComboBox {\n"
"    padding: 6px;"
                        "\n"
"    border: 1px solid #bdc3c7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"}\n"
"QGroupBox {\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 6px;\n"
"    margin-top: 1em;\n"
"    padding-top: 10px;\n"
"    font-weight: bold;\n"
"    color: #2c3e50;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        inputGroup = new QGroupBox(centralwidget);
        inputGroup->setObjectName(QString::fromUtf8("inputGroup"));
        verticalLayout = new QVBoxLayout(inputGroup);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(inputGroup);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        CbuSchedulers = new QComboBox(inputGroup);
        CbuSchedulers->addItem(QString());
        CbuSchedulers->addItem(QString());
        CbuSchedulers->addItem(QString());
        CbuSchedulers->addItem(QString());
        CbuSchedulers->addItem(QString());
        CbuSchedulers->addItem(QString());
        CbuSchedulers->setObjectName(QString::fromUtf8("CbuSchedulers"));

        verticalLayout->addWidget(CbuSchedulers);

        label_2 = new QLabel(inputGroup);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        BurstTIme = new QLineEdit(inputGroup);
        BurstTIme->setObjectName(QString::fromUtf8("BurstTIme"));

        verticalLayout->addWidget(BurstTIme);

        label_3 = new QLabel(inputGroup);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        Arrival = new QLineEdit(inputGroup);
        Arrival->setObjectName(QString::fromUtf8("Arrival"));

        verticalLayout->addWidget(Arrival);

        PriorityLabel = new QLabel(inputGroup);
        PriorityLabel->setObjectName(QString::fromUtf8("PriorityLabel"));

        verticalLayout->addWidget(PriorityLabel);

        Priority = new QLineEdit(inputGroup);
        Priority->setObjectName(QString::fromUtf8("Priority"));

        verticalLayout->addWidget(Priority);

        pushButton = new QPushButton(inputGroup);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(inputGroup);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(inputGroup);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        pushButton_6 = new QPushButton(inputGroup);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        verticalLayout->addWidget(pushButton_6);

        pushButton_4 = new QPushButton(inputGroup);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(inputGroup);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(inputGroup);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        currentProcessesGroup = new QGroupBox(centralwidget);
        currentProcessesGroup->setObjectName(QString::fromUtf8("currentProcessesGroup"));
        verticalLayout_3 = new QVBoxLayout(currentProcessesGroup);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        CurrentProcesses = new QTableWidget(currentProcessesGroup);
        if (CurrentProcesses->columnCount() < 3)
            CurrentProcesses->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        CurrentProcesses->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        CurrentProcesses->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        CurrentProcesses->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        CurrentProcesses->setObjectName(QString::fromUtf8("CurrentProcesses"));

        verticalLayout_3->addWidget(CurrentProcesses);


        verticalLayout_2->addWidget(currentProcessesGroup);

        executionGroup = new QGroupBox(centralwidget);
        executionGroup->setObjectName(QString::fromUtf8("executionGroup"));
        verticalLayout_4 = new QVBoxLayout(executionGroup);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        inExcution = new QTableWidget(executionGroup);
        if (inExcution->columnCount() < 3)
            inExcution->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        inExcution->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        inExcution->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        inExcution->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        inExcution->setObjectName(QString::fromUtf8("inExcution"));

        verticalLayout_4->addWidget(inExcution);


        verticalLayout_2->addWidget(executionGroup);

        finishedGroup = new QGroupBox(centralwidget);
        finishedGroup->setObjectName(QString::fromUtf8("finishedGroup"));
        verticalLayout_5 = new QVBoxLayout(finishedGroup);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        FinishedProcesses = new QTableWidget(finishedGroup);
        if (FinishedProcesses->columnCount() < 4)
            FinishedProcesses->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        FinishedProcesses->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        FinishedProcesses->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        FinishedProcesses->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        FinishedProcesses->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        FinishedProcesses->setObjectName(QString::fromUtf8("FinishedProcesses"));

        verticalLayout_5->addWidget(FinishedProcesses);


        verticalLayout_2->addWidget(finishedGroup);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        ganttGroup = new QGroupBox(centralwidget);
        ganttGroup->setObjectName(QString::fromUtf8("ganttGroup"));
        verticalLayout_7 = new QVBoxLayout(ganttGroup);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        GanttChart = new QGraphicsView(ganttGroup);
        GanttChart->setObjectName(QString::fromUtf8("GanttChart"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(GanttChart->sizePolicy().hasHeightForWidth());
        GanttChart->setSizePolicy(sizePolicy);

        verticalLayout_7->addWidget(GanttChart);

        AverageTimes = new QLabel(ganttGroup);
        AverageTimes->setObjectName(QString::fromUtf8("AverageTimes"));
        AverageTimes->setStyleSheet(QString::fromUtf8("font-size: 12pt;\n"
"padding: 10px;\n"
"background-color: #ecf0f1;\n"
"border-radius: 4px;"));
        AverageTimes->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(AverageTimes);


        verticalLayout_6->addWidget(ganttGroup);


        horizontalLayout->addLayout(verticalLayout_6);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CPU Scheduler Simulator", nullptr));
        inputGroup->setTitle(QCoreApplication::translate("MainWindow", "Process Input", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Scheduler Type:", nullptr));
        CbuSchedulers->setItemText(0, QCoreApplication::translate("MainWindow", "Priority Non-Preemptive", nullptr));
        CbuSchedulers->setItemText(1, QCoreApplication::translate("MainWindow", "Priority Preemptive", nullptr));
        CbuSchedulers->setItemText(2, QCoreApplication::translate("MainWindow", "SJF Non-Preemptive", nullptr));
        CbuSchedulers->setItemText(3, QCoreApplication::translate("MainWindow", "SJF Preemptive", nullptr));
        CbuSchedulers->setItemText(4, QCoreApplication::translate("MainWindow", "FCFS", nullptr));
        CbuSchedulers->setItemText(5, QCoreApplication::translate("MainWindow", "Round Robin", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "Burst Time:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Arrival Time:", nullptr));
        PriorityLabel->setText(QCoreApplication::translate("MainWindow", "Priority:", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Add Process", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Add Random Process", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Run Scheduler", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Run Scheduler (No Live Scheduling)", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Abort", nullptr));
        currentProcessesGroup->setTitle(QCoreApplication::translate("MainWindow", "Current Processes", nullptr));
        QTableWidgetItem *___qtablewidgetitem = CurrentProcesses->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Burst Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = CurrentProcesses->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Arrival Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = CurrentProcesses->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Priority", nullptr));
        executionGroup->setTitle(QCoreApplication::translate("MainWindow", "In Execution", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = inExcution->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Remaining Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = inExcution->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Turnaround Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = inExcution->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Priority", nullptr));
        finishedGroup->setTitle(QCoreApplication::translate("MainWindow", "Finished Processes", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = FinishedProcesses->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Waiting Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = FinishedProcesses->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Turnaround Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = FinishedProcesses->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Burst Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = FinishedProcesses->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Arrival Time", nullptr));
        ganttGroup->setTitle(QCoreApplication::translate("MainWindow", "Gantt Chart", nullptr));
        AverageTimes->setText(QCoreApplication::translate("MainWindow", "Average Waiting Time: 0\n"
"Average Turnaround Time: 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
