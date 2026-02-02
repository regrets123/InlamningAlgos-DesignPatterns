# InlamningAlgos-DesignPatterns

Event logger written in C. Demonstrates ADTs (queue, log), design patterns (singleton, memory pool, strategy), and sorting algorithms (bubble, selection, insertion).

## Building

Requires CMake 4.0+ and a C11 compiler.

```bash
cmake -B build
cmake --build build
```

## Running

```bash
./build/InlamningAlgos_DesignPatterns
```

The program presents an interactive menu:

```
 This is an eventLogger, tick registers n amount of events.
 Menu:
1. Tick
2. Print
3. Sort
4. Find
5. Help
6. Quit
```

## Example session

Generate 10 events, print them, sort by sensor ID, then verify:

```
Enter your choice: 1
Input how many tics, must be higher than 1, will be capped at 200.
Enter your choice: 10

Enter your choice: 2
Queue size: 0
Event Log contains the following:
Event[time=1738534400, sensor=0, type=TEMP, value=421]
Event[time=1738534399, sensor=1, type=MOTION, value=87]
Event[time=1738534398, sensor=2, type=BUTTON, value=550]
Event[time=1738534397, sensor=3, type=TEMP, value=12]
Event[time=1738534396, sensor=4, type=MOTION, value=903]
Event[time=1738534395, sensor=5, type=BUTTON, value=244]
Event[time=1738534394, sensor=6, type=TEMP, value=671]
Event[time=1738534393, sensor=7, type=MOTION, value=338]
Event[time=1738534392, sensor=8, type=BUTTON, value=105]
Event[time=1738534391, sensor=9, type=TEMP, value=762]

Enter your choice: 3
Input what sorting option you want to use. 1: BubbleSort, 2: SelectionSort, 3:InsertionSort.
Enter your choice: 3
Input what comparator you want to use. 1:Timestamp, 2:SensorId, 3:Value, 4:Type.
Enter your choice: 2

Enter your choice: 5
Select what comparator to check if the log is sorted by:
Input what comparator you want to use. 1:Timestamp, 2:SensorId, 3:Value, 4:Type.
Enter your choice: 2
Log is sorted: YES

Enter your choice: 4
Enter sensor ID to search for: 5
Event[time=1738534395, sensor=5, type=BUTTON, value=244]
Found 1 event(s) with sensor ID 5.

Enter your choice: 6
```
