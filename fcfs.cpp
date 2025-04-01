#include "fcfs.h"

FCFS::FCFS() {
}

void FCFS::sort(ProcessQueue& queue) {
    queue.FCFSsort();
}

void FCFS::calculateTimes(ProcessQueue& queue) {
    // Calculate waiting time and turnaround time
    int currentTime = 0;
    for(int i = 0; i < queue.getNumberOfProcesses(); i++) {
        Process& p = queue.getProcess(i);
        
        if(p.getArrivalTime() > currentTime) {
            currentTime = p.getArrivalTime();
        }
        
        p.setWaitingTime(currentTime - p.getArrivalTime());
        
        currentTime += p.getBurstTime();
        
        p.setTurnAroundTime(currentTime - p.getArrivalTime());
    }
}
