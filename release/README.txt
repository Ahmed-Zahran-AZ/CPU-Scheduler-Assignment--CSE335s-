CPU Scheduler Application Guide
=============================

This application simulates various CPU scheduling algorithms with a graphical interface.

Supported Scheduling Algorithms:
1. Priority Non-Preemptive
2. Priority Preemptive
3. Shortest Job First (SJF) Non-Preemptive
4. Shortest Remaining JOB First (SRJF)
5. First Come First Serve (FCFS)
6. Round Robin

How to Use the Application
-------------------------

1. Adding Processes:
   a) Manual Entry:
      - Enter Burst Time (required)
      - Enter Arrival Time (optional)
      - Enter Priority (optional)
      - Click "Add Process" button

   b) Random Process:
      - Click "Add Random Process" button
      - A process will be generated with:
        * Random burst time (1-10)
        * Random arrival time (0-20)
        * Random priority (1-10)

   c) From Text File:
      - you can add processes in the text file called "processes.txt"
      - Format each line as: burst_time:arrival_time:priority
      - Example:
        4:0:1
        3:2:2
        5:4:1

2. Running the Scheduler:
   - Select the desired scheduling algorithm from the dropdown menu
   - For Round Robin, enter the time quantum value
   - Click "Run Scheduler" button  	
   - The simulation will start automatically
      - Run Scheduler (No Live Scheduling) will finsih all the processes immediately
   - note: Run Scheduler will automatically load the processes in the text "processes.txt"

3. During Execution:
   - Watch the Gantt chart for visual representation of process execution
   - Monitor current processes, executing process, and finished processes in the tables
   - View average waiting and turnaround times
   - You can add more processes while the scheduler is running
   - Use "Abort" button to stop the current execution

4. Resetting:
   - Click "Reset" button to clear all processes and start fresh
   - This will clear all tables and the Gantt chart

Important Notes:
---------------
1. The application supports adding processes in three ways:
   - Manual entry through the GUI
   - Random process generation
   - Loading from processes.txt file

2. Process.txt Format:
   - Each line represents one process
   - Format: burst_time:arrival_time:priority
   - Burst time is required
   - Arrival time defaults to 0 if not specified
   - Priority defaults to 0 if not specified

3. Round Robin Specifics:
   - Time quantum must be greater than 0
   - If invalid quantum is entered, it defaults to 1

4. Visual Feedback:
   - Current Processes table shows processes waiting to be executed
   - In Execution table shows the currently running process
   - Finished Processes table shows completed processes with their waiting and turnaround times
   - Gantt chart shows the execution timeline with different colors for each process

5. Column Visibility:
   - Priority column is hidden for FCFS , Round Robin and SJF
   - All columns are visible for other scheduling algorithms

Example processes.txt:
---------------------
4:0:1
3:2:2
5:4:1
2:6:3
4:8:2

This will create 5 processes with:
- Process 1: Burst=4, Arrival=0, Priority=1
- Process 2: Burst=3, Arrival=2, Priority=2
- Process 3: Burst=5, Arrival=4, Priority=1
- Process 4: Burst=2, Arrival=6, Priority=3
- Process 5: Burst=4, Arrival=8, Priority=2
