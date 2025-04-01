#include "process.h"
int Process_number=0;
int Process_arrival=0;



Process::Process(){
    number = Process_number;
    Process_number++;
    arrival_time=Process_arrival;
    burst_time=(rand() % 10) + 1;
    original_burst_time = burst_time;
    RemainingBurstTime=burst_time;
    Priority=(rand() % 10) + 1;
    waitingTime=0;
    TurnAroundTime=0;
}

Process::Process(int burst_time){
    number = Process_number;
    Process_number++;
    arrival_time=Process_arrival;
    this->burst_time=burst_time;
    original_burst_time = burst_time;
    RemainingBurstTime=burst_time;
    Priority=(rand() % 10) + 1;
    waitingTime=0;
    TurnAroundTime=0;
}

Process::Process(int arrival_time,int burst_time){
    number = Process_number;
    Process_number++;
    this->arrival_time=arrival_time;
    this->burst_time=burst_time;
    original_burst_time = burst_time;
    RemainingBurstTime=burst_time;
    Priority=(rand() % 10) + 1;
    waitingTime=0;
    TurnAroundTime=0;
}

Process::Process(int arrival_time,int burst_time,int Priority){
    number = Process_number;
    Process_number++;
    this->arrival_time=arrival_time;
    this->burst_time=burst_time;
    original_burst_time = burst_time;
    RemainingBurstTime=burst_time;
    this->Priority=Priority;
    waitingTime=0;
    TurnAroundTime=0;
}

int Process::getNumber() const {
    return this->number;
}

int Process::getBurstTime() const {
    return this->burst_time;
}

void Process::setBurstTime(int BurstTime){
    this->burst_time=BurstTime;
}

int Process::getArrivalTime() const {
    return this->arrival_time;
}

void Process::setArrivalTime(int ArrivalTime){
     this->arrival_time= ArrivalTime;
}

int Process::getRemainingBurstTime() const {
    return this->RemainingBurstTime;
}

void Process::setRemainingBurstTime(int Remaining){
    this->RemainingBurstTime=Remaining;
}

int Process::getPriority() const {
    return this->Priority;
}

void Process::setPriority(int Priority){
    this->Priority=Priority;
}

int Process::getWaitingTime() const {
    return this->waitingTime;
}

void Process::setWaitingTime(int time) {
    this->waitingTime = time;
}

int Process::getTurnAroundTime() const {
    return this->TurnAroundTime;
}

void Process::setTurnAroundTime(int time) {
    this->TurnAroundTime = time;
}

int Process::getOriginalBurstTime() const {
    return this->original_burst_time;
}
