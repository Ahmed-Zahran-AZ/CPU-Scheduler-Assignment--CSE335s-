#ifndef PROCESS_H
#define PROCESS_H
#include<cstdlib>


class Process
{
public:
    Process();
    Process(int burst_time);
    Process(int arrival_time ,int burst_time);
    Process(int arrival_time,int burst_time,int Priority);
    int getNumber() const;
    int getBurstTime() const;
    void setBurstTime(int BurstTime);
    int getArrivalTime() const;
    void setArrivalTime(int ArrivalTime);
    int getRemainingBurstTime() const;
    void setRemainingBurstTime(int Remaining);
    int getPriority() const;
    void setPriority(int Priority);
    int getWaitingTime() const;
    void setWaitingTime(int time);
    int getTurnAroundTime() const;
    void setTurnAroundTime(int time);
    int getOriginalBurstTime() const;


private:
    int number;
    int arrival_time;
    int burst_time;
    int original_burst_time;
    int waitingTime;
    int TurnAroundTime;
    int RemainingBurstTime;
    int Priority;
};

#endif // PROCESS_H
