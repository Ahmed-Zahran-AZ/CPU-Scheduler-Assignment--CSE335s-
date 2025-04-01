#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "process.h"
#include "processqueue.h"
#include <QFile>
#include <QTextStream>
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QPainter>
#include <QMessageBox>

ProcessQueue Queue;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentProcessIndex(-1)
    , currentTime(0)
    , isExecuting(false)
    , isPreemptive(false)
    , isPriority(false)
    , isSJF(false)
    , isRoundRobin(false)
    , timeQuantum(0)
    , quantumRemaining(0)
{
    ui->setupUi(this);
    
    // Create and set up TimeQuantum input and label
    timeQuantumLabel = new QLabel("Quantum:", this);
    timeQuantumLabel->setObjectName("TimeQuantumLabel");
    timeQuantumLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    timeQuantumLabel->setStyleSheet(ui->PriorityLabel->styleSheet());  // Match other labels
    timeQuantumLabel->setMinimumWidth(ui->PriorityLabel->width());
    
    timeQuantumInput = new QLineEdit(this);
    timeQuantumInput->setObjectName("TimeQuantum");
    timeQuantumInput->setPlaceholderText("Enter quantum");
    timeQuantumInput->setStyleSheet(ui->BurstTIme->styleSheet());  // Match other inputs
    timeQuantumInput->setMinimumWidth(ui->BurstTIme->width());
    
    // Create Export Gantt Chart button
    QPushButton* exportButton = new QPushButton("Export Gantt Chart", this);
    exportButton->setObjectName("exportButton");
    exportButton->setStyleSheet(ui->pushButton->styleSheet());  // Match other buttons
    connect(exportButton, &QPushButton::clicked, this, &MainWindow::exportGanttChart);

    QWidget* inputContainer = ui->BurstTIme->parentWidget();
    QVBoxLayout* mainLayout = qobject_cast<QVBoxLayout*>(inputContainer->layout());
    
    if (mainLayout) {
        QHBoxLayout* quantumLayout = new QHBoxLayout();
        quantumLayout->addWidget(timeQuantumLabel);
        quantumLayout->addWidget(timeQuantumInput);
        
        int insertIndex = 2;
        mainLayout->insertLayout(insertIndex, quantumLayout);
        
        // Add export button after other controls
        mainLayout->addWidget(exportButton);
    }
    
    // Initially hide the time quantum widgets
    timeQuantumLabel->hide();
    timeQuantumInput->hide();
    
    // Initialize timer
    executionTimer = new QTimer(this);
    executionTimer->setInterval(1000); // 1 second interval
    connect(executionTimer, &QTimer::timeout, this, &MainWindow::updateExecution);

    // Initialize graphics scene for Gantt chart
    ganttScene = new QGraphicsScene(this);
    ui->GanttChart->setScene(ganttScene);
    ui->GanttChart->setRenderHint(QPainter::Antialiasing);

    // Set up table headers for finished processes
    QStringList finishedHeaders;
    finishedHeaders << "Waiting Time" << "Turnaround Time" << "Burst Time" << "Arrival Time" << "Priority";
    ui->FinishedProcesses->setHorizontalHeaderLabels(finishedHeaders);

    updateButtonStates();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_CbuSchedulers_currentIndexChanged(int index)
{
    bool showPriority = (index == 0 || index == 1);  // Priority schedulers
    bool showQuantum = (index == 5);  // Round Robin

    if (ui->Priority && ui->PriorityLabel && timeQuantumInput && timeQuantumLabel) {
        ui->Priority->setVisible(showPriority);
        ui->PriorityLabel->setVisible(showPriority);
        timeQuantumInput->setVisible(showQuantum);
        timeQuantumLabel->setVisible(showQuantum);
    }

    // Update column visibility based on scheduler
    if (ui->CurrentProcesses && ui->inExcution && ui->FinishedProcesses) {
        switch(index) {
            case 4: // FCFS
            case 2:
            case 3:
            case 5: // Round Robin
                ui->CurrentProcesses->setColumnHidden(2, true);
                ui->inExcution->setColumnHidden(2, true);
                ui->FinishedProcesses->setColumnHidden(4, true);
                ui->FinishedProcesses->setColumnHidden(0, false); // Waiting Time
                ui->FinishedProcesses->setColumnHidden(1, false); // Turnaround Time
                ui->FinishedProcesses->setColumnHidden(2, false); // Burst Time
                ui->FinishedProcesses->setColumnHidden(3, false); // Arrival Time
                break;
            default:
                ui->CurrentProcesses->setColumnHidden(2, false);
                ui->inExcution->setColumnHidden(2, false);
                ui->FinishedProcesses->setColumnHidden(4, false); // Show priority column
                break;
        }
    }
}

void MainWindow::addProcessToTable(const Process& p, QTableWidget* table, int row) {
    table->setVerticalHeaderItem(row, new QTableWidgetItem("Process " + QString::number(row + 1)));
    table->setItem(row, 0, new QTableWidgetItem(QString::number(p.getBurstTime())));
    table->setItem(row, 1, new QTableWidgetItem(QString::number(p.getArrivalTime())));
    table->setItem(row, 2, new QTableWidgetItem(QString::number(p.getPriority())));
}

void MainWindow::updateProcessTables() {
    ui->CurrentProcesses->setRowCount(0);
    ui->FinishedProcesses->setRowCount(0);
    ui->inExcution->setRowCount(0);

    for(int i = 0; i < Queue.getNumberOfProcesses(); i++) {
        const Process& p = Queue.getProcess(i);
        // Only show processes that haven't finished
        if (p.getRemainingBurstTime() > 0) {
            int row = ui->CurrentProcesses->rowCount();
            ui->CurrentProcesses->insertRow(row);
            ui->CurrentProcesses->setVerticalHeaderItem(row, new QTableWidgetItem("Process " + QString::number(i + 1)));
            
            QTableWidgetItem* remainingItem = new QTableWidgetItem(QString::number(p.getRemainingBurstTime()));
            remainingItem->setFlags(remainingItem->flags() & ~Qt::ItemIsEditable);
            ui->CurrentProcesses->setItem(row, 0, remainingItem);
            
            QTableWidgetItem* arrivalItem = new QTableWidgetItem(QString::number(p.getArrivalTime()));
            arrivalItem->setFlags(arrivalItem->flags() & ~Qt::ItemIsEditable);
            ui->CurrentProcesses->setItem(row, 1, arrivalItem);
            
            QTableWidgetItem* priorityItem = new QTableWidgetItem(QString::number(p.getPriority()));
            priorityItem->setFlags(priorityItem->flags() & ~Qt::ItemIsEditable);
            ui->CurrentProcesses->setItem(row, 2, priorityItem);
        }
        else if (p.getTurnAroundTime() > 0) {
            int row = ui->FinishedProcesses->rowCount();
            ui->FinishedProcesses->insertRow(row);
            ui->FinishedProcesses->setVerticalHeaderItem(row, new QTableWidgetItem("Process " + QString::number(i + 1)));
            
            QTableWidgetItem* waitingItem = new QTableWidgetItem(QString::number(p.getWaitingTime()));
            waitingItem->setFlags(waitingItem->flags() & ~Qt::ItemIsEditable);
            ui->FinishedProcesses->setItem(row, 0, waitingItem);
            
            QTableWidgetItem* turnaroundItem = new QTableWidgetItem(QString::number(p.getTurnAroundTime()));
            turnaroundItem->setFlags(turnaroundItem->flags() & ~Qt::ItemIsEditable);
            ui->FinishedProcesses->setItem(row, 1, turnaroundItem);
            
            QTableWidgetItem* burstItem = new QTableWidgetItem(QString::number(p.getOriginalBurstTime()));
            burstItem->setFlags(burstItem->flags() & ~Qt::ItemIsEditable);
            ui->FinishedProcesses->setItem(row, 2, burstItem);
            
            QTableWidgetItem* arrivalItem = new QTableWidgetItem(QString::number(p.getArrivalTime()));
            arrivalItem->setFlags(arrivalItem->flags() & ~Qt::ItemIsEditable);
            ui->FinishedProcesses->setItem(row, 3, arrivalItem);
            
            QTableWidgetItem* priorityItem = new QTableWidgetItem(QString::number(p.getPriority()));
            priorityItem->setFlags(priorityItem->flags() & ~Qt::ItemIsEditable);
            ui->FinishedProcesses->setItem(row, 4, priorityItem);
        }
    }

    if (isExecuting && currentProcessIndex >= 0 && currentProcessIndex < Queue.getNumberOfProcesses()) {
        const Process& p = Queue.getProcess(currentProcessIndex);
        int row = ui->inExcution->rowCount();
        ui->inExcution->insertRow(row);
        ui->inExcution->setVerticalHeaderItem(row, new QTableWidgetItem("Process " + QString::number(currentProcessIndex + 1)));
        
        QTableWidgetItem* remainingItem = new QTableWidgetItem(QString::number(p.getRemainingBurstTime()));
        remainingItem->setFlags(remainingItem->flags() & ~Qt::ItemIsEditable);
        ui->inExcution->setItem(row, 0, remainingItem);
        
        QTableWidgetItem* turnaroundItem = new QTableWidgetItem(QString::number(p.getTurnAroundTime()));
        turnaroundItem->setFlags(turnaroundItem->flags() & ~Qt::ItemIsEditable);
        ui->inExcution->setItem(row, 1, turnaroundItem);
        
        QTableWidgetItem* priorityItem = new QTableWidgetItem(QString::number(p.getPriority()));
        priorityItem->setFlags(priorityItem->flags() & ~Qt::ItemIsEditable);
        ui->inExcution->setItem(row, 2, priorityItem);
    }
}

void MainWindow::updateGanttChart() {
    ganttScene->clear();
    processBars.clear();
    processLabels.clear();
    timeLabels.clear();

    int barHeight = 30;
    int spacing = 10;
    int startY = 20;
    int maxTime = currentTime;

    for (int t = 0; t <= maxTime; t++) {
        QGraphicsTextItem* timeLabel = ganttScene->addText(QString::number(t));
        timeLabel->setPos(t * 30, 0);
        timeLabels.append(timeLabel);
    }

    QMap<int, int> processPositions;
    int currentPosition = 0;

    for (int i = 0; i < ganttChartData.size(); i++) {
        int processIndex = ganttChartData[i].first;
        if (!processPositions.contains(processIndex)) {
            processPositions[processIndex] = currentPosition++;
        }
    }

    for (auto it = processPositions.begin(); it != processPositions.end(); ++it) {
        int processIndex = it.key();
        int yPos = startY + it.value() * (barHeight + spacing);

        QGraphicsTextItem* processLabel = ganttScene->addText("P" + QString::number(processIndex + 1));
        processLabel->setPos(-30, yPos + 5);
        processLabels.append(processLabel);

        QGraphicsRectItem* backgroundBar = new QGraphicsRectItem(0, yPos, maxTime * 30, barHeight);
        backgroundBar->setBrush(Qt::lightGray);
        backgroundBar->setPen(QPen(Qt::gray, 1, Qt::DashLine));
        ganttScene->addItem(backgroundBar);
    }

    for (int i = 0; i < ganttChartData.size(); i++) {
        int processIndex = ganttChartData[i].first;
        int startTime = ganttChartData[i].second;
        int endTime;

        if (i == ganttChartData.size() - 1) {
            if (processIndex == currentProcessIndex) {
                endTime = currentTime;
            } else {
                const Process& p = Queue.getProcess(processIndex);
                if (p.getRemainingBurstTime() <= 0) {
                    endTime = p.getArrivalTime() + p.getTurnAroundTime();
                } else {
                    endTime = currentTime;
                }
            }
        } else {
            endTime = ganttChartData[i + 1].second;
        }

        if (endTime > startTime) {
            int yPos = startY + processPositions[processIndex] * (barHeight + spacing);
            
            QGraphicsRectItem* executionBar = new QGraphicsRectItem(
                startTime * 30,
                yPos,
                (endTime - startTime) * 30,
                barHeight
            );

            // Set distinct color for each process
            QColor processColor = QColor::fromHsv((processIndex * 360) / Queue.getNumberOfProcesses(), 200, 200);
            executionBar->setBrush(processColor);
            executionBar->setPen(QPen(Qt::black));
            ganttScene->addItem(executionBar);

            // Add time labels
            QGraphicsTextItem* startLabel = ganttScene->addText(QString::number(startTime));
            startLabel->setPos(startTime * 30, yPos + barHeight);
            QGraphicsTextItem* endLabel = ganttScene->addText(QString::number(endTime));
            endLabel->setPos(endTime * 30, yPos + barHeight);
        }
    }

    QRectF boundingRect = ganttScene->itemsBoundingRect();
    ganttScene->setSceneRect(boundingRect.adjusted(-40, -10, 10, 10));
    ui->GanttChart->fitInView(ganttScene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::updateAverageTimes() {
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    int finishedProcesses = 0;

    for (int i = 0; i < Queue.getNumberOfProcesses(); i++) {
        const Process& p = Queue.getProcess(i);
        if (p.getTurnAroundTime() > 0) {
            totalWaitingTime += p.getWaitingTime();
            totalTurnaroundTime += p.getTurnAroundTime();
            finishedProcesses++;
        }
    }

    if (finishedProcesses > 0) {
        double avgWaitingTime = totalWaitingTime / finishedProcesses;
        double avgTurnaroundTime = totalTurnaroundTime / finishedProcesses;
        ui->AverageTimes->setText(QString("Average Waiting Time: %1\nAverage Turnaround Time: %2")
            .arg(avgWaitingTime, 0, 'f', 2)
            .arg(avgTurnaroundTime, 0, 'f', 2));
    }
}

void MainWindow::updateReadyQueue() {
    // Add newly arrived processes to ready queue
    for (int i = 0; i < Queue.getNumberOfProcesses(); i++) {
        Process& p = Queue.getProcess(i);
        if (p.getArrivalTime() <= currentTime && p.getRemainingBurstTime() > 0 && 
            !readyQueue.contains(i) && i != currentProcessIndex) {
            readyQueue.enqueue(i);
        }
    }
}

void MainWindow::updateExecution() {
    if (!isExecuting) {
        executionTimer->stop();
        updateButtonStates();
        return;
    }

    updateReadyQueue();

    // If we don't have a current process or need to check for preemption
    if (currentProcessIndex == -1 || 
        (isPreemptive && ((isPriority || isSJF) || (isRoundRobin && quantumRemaining <= 0)))) {
        
        int nextProcessIndex = -1;
        int highestPriority = currentProcessIndex >= 0 ? 
            Queue.getProcess(currentProcessIndex).getPriority() : INT_MAX;
        int shortestTime = currentProcessIndex >= 0 ? 
            Queue.getProcess(currentProcessIndex).getRemainingBurstTime() : INT_MAX;

        if (isRoundRobin) {
            // If current process's quantum expired and it's not finished
            if (currentProcessIndex >= 0 && quantumRemaining <= 0 && 
                Queue.getProcess(currentProcessIndex).getRemainingBurstTime() > 0) {
                
                readyQueue.enqueue(currentProcessIndex);
                
                ganttChartData.append(qMakePair(currentProcessIndex, currentTime));
                
                currentProcessIndex = -1;
            }
            
            // If no current process, get next from ready queue
            if (currentProcessIndex == -1 && !readyQueue.isEmpty()) {
                nextProcessIndex = readyQueue.dequeue();
                quantumRemaining = timeQuantum;
                currentProcessIndex = nextProcessIndex;
                ganttChartData.append(qMakePair(currentProcessIndex, currentTime));
            }
        } else {
            // Find next process or check for preemption for other scheduling algorithms
            for (int i = 0; i < Queue.getNumberOfProcesses(); i++) {
                Process& p = Queue.getProcess(i);
                if (p.getArrivalTime() <= currentTime && 
                    p.getRemainingBurstTime() > 0 && 
                    (currentProcessIndex == -1 || i != currentProcessIndex)) {
                    
                    if (isPriority) {
                        // For priority scheduling
                        if (p.getPriority() < highestPriority) {  // Lower number = higher priority
                            highestPriority = p.getPriority();
                            nextProcessIndex = i;
                        }
                    } else if (isSJF) {
                        // For SJF/SRTF scheduling
                        if (p.getRemainingBurstTime() < shortestTime) {
                            shortestTime = p.getRemainingBurstTime();
                            nextProcessIndex = i;
                        } else if (p.getRemainingBurstTime() == shortestTime && 
                                 p.getArrivalTime() < Queue.getProcess(nextProcessIndex != -1 ? nextProcessIndex : i).getArrivalTime()) {
                            // If burst times are equal, choose the one that arrived first
                            nextProcessIndex = i;
                        }
                    } else {
                        // For FCFS
                        if (nextProcessIndex == -1 || p.getArrivalTime() < Queue.getProcess(nextProcessIndex).getArrivalTime()) {
                            nextProcessIndex = i;
                        }
                    }
                }
            }
        }

        // Switch to next process if found (for non-RR algorithms)
        if (!isRoundRobin && nextProcessIndex != -1 && 
            (currentProcessIndex == -1 || 
             (isPreemptive && ((isPriority && 
              Queue.getProcess(nextProcessIndex).getPriority() < Queue.getProcess(currentProcessIndex).getPriority()) ||
              (isSJF && 
              Queue.getProcess(nextProcessIndex).getRemainingBurstTime() < Queue.getProcess(currentProcessIndex).getRemainingBurstTime()))))) {
            
            // If we're preempting a process
            if (currentProcessIndex != -1) {
                ganttChartData.append(qMakePair(currentProcessIndex, currentTime));
            }
            
            currentProcessIndex = nextProcessIndex;
            ganttChartData.append(qMakePair(currentProcessIndex, currentTime));
        }
    }

    // If we have a current process, execute it
    if (currentProcessIndex >= 0 && currentProcessIndex < Queue.getNumberOfProcesses()) {
        Process& currentProcess = Queue.getProcess(currentProcessIndex);
        
        // If this is the first time we're executing this process
        if (currentProcess.getRemainingBurstTime() == currentProcess.getOriginalBurstTime() && 
            (ganttChartData.isEmpty() || ganttChartData.last().first != currentProcessIndex)) {
            ganttChartData.append(qMakePair(currentProcessIndex, currentTime));
        }

        currentProcess.setRemainingBurstTime(currentProcess.getRemainingBurstTime() - 1);
        
        if (isRoundRobin) {
            quantumRemaining--;
        }

        // If process is finished
        if (currentProcess.getRemainingBurstTime() <= 0) {
            currentProcess.setTurnAroundTime(currentTime + 1 - currentProcess.getArrivalTime());
            currentProcess.setWaitingTime(currentProcess.getTurnAroundTime() - currentProcess.getOriginalBurstTime());
            
            ganttChartData.append(qMakePair(currentProcessIndex, currentTime + 1));
            
            currentProcessIndex = -1;
        }
    } else {
        bool allFinished = true;
        for (int i = 0; i < Queue.getNumberOfProcesses(); i++) {
            if (Queue.getProcess(i).getRemainingBurstTime() > 0) {
                allFinished = false;
                break;
            }
        }

        if (allFinished) {
            isExecuting = false;
            executionTimer->stop();
            updateProcessTables();
            updateGanttChart();
            updateAverageTimes();
            updateButtonStates();
            return;
        }
    }

    currentTime++;
    updateProcessTables();
    updateGanttChart();
}

void MainWindow::startExecution() {
    currentProcessIndex = -1;
    currentTime = 0;
    isExecuting = true;
    executionTimer->start(1000);
    updateButtonStates();
}

void MainWindow::runScheduler() {
    int schedulerIndex = ui->CbuSchedulers->currentIndex();
    
    // Load processes from file
    QFile file("processes.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(":");
            if (parts.size() >= 2) {
                int burstTime = parts[0].toInt();
                int arrivalTime = parts[1].toInt();
                int priority = (parts.size() > 2) ? parts[2].toInt() : 0;
                
                Process newProcess(arrivalTime, burstTime, priority);
                Queue.addProcess(newProcess);
            }
        }
        file.close();
        updateProcessTables();
    }
    
    switch(schedulerIndex) {
        case 0: // Priority Non-Preemptive
            isPreemptive = false;
            isPriority = true;
            isSJF = false;
            isRoundRobin = false;
            ganttChartData.clear();
            startExecution();
            break;
        case 1: // Priority Preemptive
            isPreemptive = true;
            isPriority = true;
            isSJF = false;
            isRoundRobin = false;
            ganttChartData.clear();
            startExecution();
            break;
        case 2: // SJF Non-Preemptive
            isPreemptive = false;
            isPriority = false;
            isSJF = true;
            isRoundRobin = false;
            ganttChartData.clear();
            startExecution();
            break;
        case 3: // SRTF (SJF Preemptive)
            isPreemptive = true;
            isPriority = false;
            isSJF = true;
            isRoundRobin = false;
            ganttChartData.clear();
            startExecution();
            break;
        case 4: // FCFS
            isPreemptive = false;
            isPriority = false;
            isSJF = false;
            isRoundRobin = false;
            fcfs.sort(Queue);
            ganttChartData.clear();
            startExecution();
            break;
        case 5: // Round Robin
            isPreemptive = true;
            isPriority = false;
            isSJF = false;
            isRoundRobin = true;
            timeQuantum = timeQuantumInput->text().toInt();
            if (timeQuantum <= 0) {
                timeQuantum = 1; // Default time quantum if invalid input
                timeQuantumInput->setText("1");
            }
            quantumRemaining = timeQuantum;
            ganttChartData.clear();
            startExecution();
            break;
        default:
            break;
    }
    
    updateProcessTables();
}

void MainWindow::runScheduler_instant() {
    int schedulerIndex = ui->CbuSchedulers->currentIndex();

    // Load processes from file
    QFile file("processes.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(":");
            if (parts.size() >= 2) {
                int burstTime = parts[0].toInt();
                int arrivalTime = parts[1].toInt();
                int priority = (parts.size() > 2) ? parts[2].toInt() : 0;

                Process newProcess(arrivalTime, burstTime, priority);
                Queue.addProcess(newProcess);
            }
        }
        file.close();
        updateProcessTables();
    }

    switch(schedulerIndex) {
    case 0: // Priority Non-Preemptive
        isPreemptive = false;
        isPriority = true;
        isSJF = false;
        isRoundRobin = false;
        ganttChartData.clear();
        executeInstantly();
        break;
    case 1: // Priority Preemptive
        isPreemptive = true;
        isPriority = true;
        isSJF = false;
        isRoundRobin = false;
        ganttChartData.clear();
        executeInstantly();
        break;
    case 2: // SJF Non-Preemptive
        isPreemptive = false;
        isPriority = false;
        isSJF = true;
        isRoundRobin = false;
        ganttChartData.clear();
        executeInstantly();
        break;
    case 3: // SRTF (SJF Preemptive)
        isPreemptive = true;
        isPriority = false;
        isSJF = true;
        isRoundRobin = false;
        ganttChartData.clear();
        executeInstantly();
        break;
    case 4: // FCFS
        isPreemptive = false;
        isPriority = false;
        isSJF = false;
        isRoundRobin = false;
        fcfs.sort(Queue);
        ganttChartData.clear();
        executeInstantly();
        break;
    case 5: // Round Robin
        isPreemptive = true;
        isPriority = false;
        isSJF = false;
        isRoundRobin = true;
        timeQuantum = timeQuantumInput->text().toInt();
        if (timeQuantum <= 0) {
            timeQuantum = 1; // Default time quantum if invalid input
            timeQuantumInput->setText("1");
        }
        quantumRemaining = timeQuantum;
        ganttChartData.clear();
        executeInstantly();
        break;
    default:
        break;
    }

    updateProcessTables();
}
/*
void MainWindow::executeInstantly() {
    currentProcessIndex = -1;
    currentTime = 0;
    isExecuting = true;
    executionTimer->start(0);
    updateButtonStates();
}*/

void MainWindow::executeInstantly() {
    // Stop any ongoing execution

    if (isExecuting) {
        executionTimer->stop();
    }

    // Reset state
    currentProcessIndex = -1;
    currentTime = 0;
    isExecuting = true;
    readyQueue.clear();
    ganttChartData.clear();

    // Reset process states while keeping their original data
    for (int i = 0; i < Queue.getNumberOfProcesses(); i++) {
        Process& p = Queue.getProcess(i);
        p.setRemainingBurstTime(p.getOriginalBurstTime());
        p.setTurnAroundTime(0);
        p.setWaitingTime(0);
    }

    // Get scheduler settings from UI
    int schedulerIndex = ui->CbuSchedulers->currentIndex();
    isPreemptive = (schedulerIndex == 1 || schedulerIndex == 3 || schedulerIndex == 5);
    isPriority = (schedulerIndex == 0 || schedulerIndex == 1);
    isSJF = (schedulerIndex == 2 || schedulerIndex == 3);
    isRoundRobin = (schedulerIndex == 5);

    if (isRoundRobin) {
        timeQuantum = timeQuantumInput->text().toInt();
        if (timeQuantum <= 0) {
            timeQuantum = 1;
            timeQuantumInput->setText("1");
        }
        quantumRemaining = timeQuantum;
    }

    // For FCFS, sort the processes
    if (schedulerIndex == 4) {
        fcfs.sort(Queue);
    }

    // Disable UI updates during instant execution
    bool oldUpdatesEnabled = ui->GanttChart->updatesEnabled();
    ui->GanttChart->setUpdatesEnabled(false);

    // Run the scheduler to completion
    while (true) {
        // Use the existing update logic
        updateExecution();

        // Check if all processes are finished
        bool allFinished = true;
        for (int i = 0; i < Queue.getNumberOfProcesses(); i++) {
            if (Queue.getProcess(i).getRemainingBurstTime() > 0) {
                allFinished = false;
                break;
            }
        }

        if (allFinished) {
            break;
        }

        // Prevent the timer from stopping our execution
        isExecuting = true;
    }

    // Restore UI updates
    ui->GanttChart->setUpdatesEnabled(oldUpdatesEnabled);

    // Final updates
    isExecuting = false;
    updateProcessTables();
    updateGanttChart();
    updateAverageTimes();
    updateButtonStates();
}

void MainWindow::on_pushButton_clicked()
{
    // Add process manually
    int burstTime = ui->BurstTIme->text().toInt();
    int arrivalTime = ui->Arrival->text().toInt();
    int priority = ui->Priority->text().toInt();
    
    Process newProcess;
    if (!ui->BurstTIme->text().isEmpty()) {
        if (!ui->Arrival->text().isEmpty()) {
            if (!ui->Priority->text().isEmpty()) {
                newProcess = Process(arrivalTime, burstTime, priority);
            } else {
                newProcess = Process(arrivalTime, burstTime);
            }
        } else {
            newProcess = Process(burstTime);
        }
    }
    
    Queue.addProcess(newProcess);
    updateProcessTables();
    
    // Clear input fields
    ui->BurstTIme->clear();
    ui->Arrival->clear();
    ui->Priority->clear();
}

void MainWindow::on_pushButton_2_clicked() // add random process
{
    int burstTime = rand() % 10 + 1;
    
    int arrivalTime = rand() % 21;  // 0 to 20
    
    int priority = rand() % 10 + 1;
    
    Process p(arrivalTime, burstTime, priority);
    Queue.addProcess(p);
    
    updateProcessTables();
}

void MainWindow::on_pushButton_3_clicked()
{
    runScheduler();
}
void MainWindow::on_pushButton_6_clicked()
{
    runScheduler_instant();
}

void MainWindow::updateButtonStates() {
    // Enable/disable buttons based on execution state
    ui->pushButton_3->setEnabled(!isExecuting);  // Run Scheduler button
    ui->pushButton_4->setEnabled(!isExecuting);  // Reset button
    ui->pushButton_5->setEnabled(isExecuting);   // Abort button
    ui->pushButton->setEnabled(true);            // Add Process button - always enabled
    ui->pushButton_2->setEnabled(true);          // Add Random Process button - always enabled
    ui->pushButton_6->setEnabled(true);  // Instant Execution button
    // Update Export button state
    QPushButton* exportButton = findChild<QPushButton*>("exportButton");
    if (exportButton) {
        exportButton->setEnabled(!ganttChartData.isEmpty());
    }
}

void MainWindow::resetApplication() {
    // Stop execution if running
    if (isExecuting) {
        abortExecution();
    }

    // Clear all data
    Queue.clear();
    currentProcessIndex = -1;
    currentTime = 0;
    ganttChartData.clear();
    readyQueue.clear();
    
    // Clear all tables and charts
    ui->CurrentProcesses->setRowCount(0);
    ui->FinishedProcesses->setRowCount(0);
    ui->inExcution->setRowCount(0);
    ganttScene->clear();
    ui->AverageTimes->setText("Average Waiting Time: 0\nAverage Turnaround Time: 0");
    
    // Update button states
    updateButtonStates();
}

void MainWindow::abortExecution() {
    if (isExecuting) {
        isExecuting = false;
        executionTimer->stop();
        
        // Reset process states
        for (int i = 0; i < Queue.getNumberOfProcesses(); i++) {
            Process& p = Queue.getProcess(i);
            if (p.getTurnAroundTime() == 0) {
                p.setRemainingBurstTime(p.getOriginalBurstTime());
                p.setTurnAroundTime(0);
                p.setWaitingTime(0);
            }
        }
        
        // Clear Gantt chart data and ready queue
        ganttChartData.clear();
        readyQueue.clear();
        
        // Update UI
        updateProcessTables();
        updateGanttChart();
        updateAverageTimes();
        updateButtonStates();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    resetApplication();
}

void MainWindow::on_pushButton_5_clicked()
{
    abortExecution();
}

void MainWindow::exportGanttChart() {
    if (ganttChartData.isEmpty()) {
        QMessageBox::warning(this, "Export Error", "No Gantt chart data to export!");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this,
        "Export Gantt Chart", "",
        "PNG Image (*.png);;JPEG Image (*.jpg);;All Files (*)");

    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".png", Qt::CaseInsensitive) && 
        !fileName.endsWith(".jpg", Qt::CaseInsensitive)) {
        fileName += ".png";
    }

    QPixmap pixmap(ganttScene->sceneRect().size().toSize());
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    ganttScene->render(&painter);

    if (pixmap.save(fileName)) {
        QMessageBox::information(this, "Success", 
            "Gantt chart exported successfully to:\n" + fileName);
    } else {
        QMessageBox::critical(this, "Error", 
            "Failed to export Gantt chart!");
    }
}

