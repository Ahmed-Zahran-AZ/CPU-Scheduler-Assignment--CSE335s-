#include "processqueue.h"


ProcessQueue::ProcessQueue() {
    numberOfProcesses=0;
    ProcessesFinished=0;
    start=0;
    end=0;
}

int ProcessQueue::addProcess(Process s) {
    queue.push_back(s);
    numberOfProcesses++;
    end++;
    return 0;
}

int ProcessQueue::removeProcess() {
    if (queue.empty())
        return -1;
    queue.erase(queue.begin());
    numberOfProcesses--;
    start++;
    return 0;
}

Process& ProcessQueue::getProcess(int index) {
    return queue[index];
}

int ProcessQueue::getNumberOfProcesses() const {
    return numberOfProcesses;
}

const std::vector<Process>& ProcessQueue::getQueue() const {
    return queue;
}

void ProcessQueue::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string burstStr, arrivalStr, priorityStr;

        std::getline(ss, burstStr, ':');
        std::getline(ss, arrivalStr, ':');
        std::getline(ss, priorityStr, ':');

        int burst = burstStr.empty() ? 0 : std::stoi(burstStr);
        int arrival = arrivalStr.empty() ? 0 : std::stoi(arrivalStr);
        int priority = priorityStr.empty() ? 0 : std::stoi(priorityStr);

        if (burstStr.empty() && arrivalStr.empty() && priorityStr.empty()){
            addProcess(Process());
        }
        // Create Process object based on available values
        else if (!burstStr.empty() && !arrivalStr.empty() && !priorityStr.empty()) {
            addProcess(Process(arrival, burst, priority));
        } else if (!burstStr.empty() && !arrivalStr.empty()) {
            addProcess(Process(arrival, burst));
        } else if (!burstStr.empty()) {
            addProcess(Process(burst));
        } else {
            addProcess(Process());
        }
    }
}

void ProcessQueue::FCFSsort() {
    std::sort(queue.begin(), queue.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });
}

void ProcessQueue::clear() {
    queue.clear();
    Finished.clear();
    numberOfProcesses = 0;
    ProcessesFinished = 0;
    start = 0;
    end = 0;
}


