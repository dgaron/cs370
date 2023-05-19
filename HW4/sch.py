# 0: PID
# 1: Arrival Time
# 2: Burst Time
# 3: Priority
# 4: Finish Time

import sys
from operator import itemgetter

def getWaitTime(p):
    return p[4] - p[1] - p[2]

def getAvgWaitTime(processList):
    avgWaitTime = 0
    for p in processList:
        avgWaitTime += getWaitTime(p)
    avgWaitTime /= float(len(processList))
    return avgWaitTime

def getTurnaroundTime(p):
    return p[4] - p[1]

def getAvgTurnaroundTime(processList):
    avgTurnaroundTime = 0
    for p in processList:
        avgTurnaroundTime += getTurnaroundTime(p)
    avgTurnaroundTime /= float(len(processList))
    return avgTurnaroundTime

def printWaitAndTurnaroundTimes(processList):
    print(" Process ID | Waiting Time | Turnaround Time")
    for p in processList:
        print("{0:^12}|{1:^14}|{2:^14}".format(p[0], getWaitTime(p), getTurnaroundTime(p)))
    print("")
    return

def populateReadyQueue(processList, readyQueue, completedProcesses, clock):
    # Add process to the ready queue as they arrive
    # Check to see if it's in the ready queue to prevent duplicates
    # Check to ensure that it has not yet completed
    for p in processList:
        if (p[1] <= clock and readyQueue.count(p) == 0 and
            completedProcesses.count(p[0]) == 0):
            readyQueue.append(p)
    return

def runProcesses(processList, method):
    # Clock
    clock = 0
    # Gantt chart output string    
    gantt = "Gantt Chart:\n"
    # Separator will indicate the clock time at the beginning and end of each process
    # Separator contains the newline character for formatting
    separator = ""
    # Number of processes remaining
    numProcesses = len(processList)
    # List of process ID numbers to track completed processes
    completedProcesses = []
    # Ready queue
    readyQueue = []
    # Boolean to track idle cycles
    idleStarted = False

    # Continue loop until all processes are completed
    while (numProcesses > 0):
        # Populate the ready queue
        populateReadyQueue(processList, readyQueue, completedProcesses, clock)
        # Sort the ready queue by priority if necessary
        if (method == "priority"):
            readyQueue.sort(key = itemgetter(3,0))
        # If the ready queue is empty, the CPU is idle
        if len(readyQueue) == 0:
            # This boolean ensures only one "idle" will print
            # in the Gantt chart
            if not idleStarted:
                gantt += separator
                gantt += "[{0:^6}]".format(clock)
                gantt += "--{0:^6}--".format("IDLE")
                # Set flag to indicate CPU is currently idling
                idleStarted = True
            # Increment clock to track idle cycles
            clock += 1
            separator = "[{0:^6}]\n".format(clock)
        else:
            # Set flag to indicate CPU is not idle
            idleStarted = False
            # Remove a process from the ready queue
            currentProcess = readyQueue.pop(0)
            currentIndex = processList.index(currentProcess)
            # Add to gantt string
            gantt += separator
            gantt += "[{0:^6}]".format(clock)
            gantt += "--{0:^6}--".format(currentProcess[0])
            # Increment the clock by the burst time
            clock += currentProcess[2]
            # Record that this process has completed and decrement numProcesses
            completedProcesses.append(currentProcess[0])
            numProcesses -= 1
            # Record the finish time of the process
            processList[currentIndex][4] = clock
            separator = "[{0:^6}]\n".format(clock)
            
    gantt += separator
    return gantt

def getEndTime(processList):
    max = 0
    for p in processList:
        if p[4] > max:
            max = p[4]
    return max

def fcfs(processList):

    print("-"*18 + "FCFS" + "-"*18)

    gantt = runProcesses(processList, "fcfs")

    endTime = getEndTime(processList)

    printWaitAndTurnaroundTimes(processList)
    print(gantt)
    print("Average Waiting Time: {0}".format(getAvgWaitTime(processList)))
    print("Average Turnaround Time: {0}".format(getAvgTurnaroundTime(processList)))
    print("Throughput: {0}".format(len(processList) / float(endTime)))
    return

def priority(processList):
    
    print("-"*20 + "PS" + "-"*20)

    gantt = runProcesses(processList, "priority")

    endTime = getEndTime(processList)

    printWaitAndTurnaroundTimes(processList)
    print(gantt)
    print("Average Waiting Time: {0}".format(getAvgWaitTime(processList)))
    print("Average Turnaround Time: {0}".format(getAvgTurnaroundTime(processList)))
    print("Throughput: {0}".format(len(processList) / float(endTime)))
    return

def roundRobin(processList, timeQuantum):
    print("-"*15 + "Round Robin" + "-"*15)

    # Clock
    clock = 0
    # Gantt chart output string    
    gantt = "Gantt Chart:\n"
    # Separator will indicate the clock time at the beginning and end of each process
    # Separator contains the newline character for formatting
    separator = ""
    # Number of processes remaining
    numProcesses = len(processList)
    # List of process ID numbers to track completed processes
    completedProcesses = []
    # Time remaining for each process
    timeRemaining = []
    for p in processList:
        timeRemaining.append(p[2])
    # Ready queue
    readyQueue = []
    # Boolean to track idle cycles
    idleStarted = False
    # Boolean to track context switches
    contextSwitch = True

    # Continue loop until all processes are completed
    while (numProcesses > 0):
        # Populate the ready queue
        populateReadyQueue(processList, readyQueue, completedProcesses, clock)
        # If the ready queue is empty, the CPU is idle
        if len(readyQueue) == 0:
            # This boolean ensures only one "idle" will print
            # in the Gantt chart
            if not idleStarted:
                gantt += separator
                gantt += "[{0:^6}]".format(clock)
                gantt += "--{0:^6}--".format("IDLE")
                # Set flag to indicate CPU is currently idling
                idleStarted = True
            # Increment clock to track idle cycles
            clock += 1
            separator = "[{0:^6}]\n".format(clock)
        else:
            # Set flag to indicate CPU is not idle
            idleStarted = False
            # Remove a process from the ready queue
            currentProcess = readyQueue.pop(0)
            currentIndex = processList.index(currentProcess)
            if contextSwitch:
                # Add to gantt string
                gantt += separator
                gantt += "[{0:^6}]".format(clock)
                gantt += "--{0:^6}--".format(currentProcess[0])
            # Increment the clock by the burst time or time quantum
            if timeRemaining[currentIndex] <= timeQuantum:
                contextSwitch = True
                clock += timeRemaining[currentIndex]
                timeRemaining[currentIndex] = 0
                # Record that this process has completed and decrement numProcesses
                completedProcesses.append(currentProcess[0])
                numProcesses -= 1
                # Record the finish time of the process
                processList[currentIndex][4] = clock
            else:
                timeRemaining[currentIndex] -= timeQuantum
                clock += timeQuantum
                # Populate the ready queue
                populateReadyQueue(processList, readyQueue, completedProcesses, clock)
                # Ensure that current process is at the back of the ready queue
                readyQueue.remove(currentProcess)
                readyQueue.append(currentProcess)
                if len(readyQueue) == 1:
                    contextSwitch = False
                else:
                    contextSwitch = True
            separator = "[{0:^6}]\n".format(clock)
            
    gantt += separator

    printWaitAndTurnaroundTimes(processList)
    print(gantt)
    print("Average Waiting Time: {0}".format(getAvgWaitTime(processList)))
    print("Average Turnaround Time: {0}".format(getAvgTurnaroundTime(processList)))
    print("Throughput: {0}".format(len(processList) / float(clock)))
    return

def main():
    if len(sys.argv) != 3:
        print("Usage: sch.py fileName timeQuantum")
        return

    try:
        inFile = open(sys.argv[1])
    except:
        print("{0}: unable to open file: {1}".format(sys.argv[0], sys.argv[1]))
        return

    try:
        timeQuantum = int(sys.argv[2])
    except:
        print("Time quantum must be an integer")
        print("Usage: sch.py fileName timeQuantum")
        return

    processList = []

    # Skip column headers
    next(inFile)
    for line in inFile:
        line += ",0"
        processList.append([int(s) for s in line.split(",")])

    inFile.close()

    # Sort list by PID
    processList.sort(key = itemgetter(0))

    # First come; first serve scheduling
    fcfs(processList)

    # Priority scheduling
    priority(processList)

    # Round Robin scheduling
    roundRobin(processList, timeQuantum)

if __name__ == "__main__":
    main()
