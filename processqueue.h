#ifndef PROCESSQUEUE_H
#define PROCESSQUEUE_H
#include "process.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

class ProcessQueue
{
public:
    ProcessQueue();
    int addProcess(Process s);
    int removeProcess();
    Process& getProcess(int index);
    void loadFromFile(const std::string& filename);
    void FCFSsort();
    int getNumberOfProcesses() const;
    const std::vector<Process>& getQueue() const;
    void clear();

private:
    std::vector<Process> queue;
    std::vector<Process> Finished;
    int numberOfProcesses;
    int ProcessesFinished;
    int start;
    int end;
};

#endif // PROCESSQUEUE_H
