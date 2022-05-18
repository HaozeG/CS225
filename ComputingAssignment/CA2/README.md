> View this file after installing a _Markdown_ extension.

# Introduction

This project is a system that includes **registration, queuing and reporting**.

The core data structure is a Fibonacci heap to arrange patients based on different priorities. Data of patients are stored as a single-linked list.

![basic structure](./img/structure.png)

# Instruction

## To compile

There is a _Makefile_ you can use:

- `make` to compile the program
- `make clean` to clean executable files produced

## To use

If you have the executable file _test_, you can run it.

The interface you will see looks like this:

![interface](./img/interface.png)

Here, you can type in number to choose the operation.

### Basic

Type in `0` to quit.
Type in `7` to go to next day.

### Registration

1. Put registration data of patients in a file under the same directory as the program. You need to follow the input format as shown.

![input format](./img/input_format.png)

_Note: Here **risk status = 2** is interpreted that this people will have the same priority as other people with risk status 0/1 after 30 days, if the system needs to judge priority based on risk status._

2. In the interface, type in `1` and follow the instructions shown. You can designate which local registry(1/2) these data will go to.
3. To collect data to central registry, type in `2`. This system automatically collects all data from all local registries.
   _One person only has one data. If this person update his/her information, data before will be updated(overwritten)_

### queuing

Queuing is performed when they are added to central registry(when you type in `2`).
_Note: two week penalty is **added to the timestamp** when judging priority, which means it could be ignored if the priority can be judged by more important criteria like profession._

#### Present priority letter

Type in `3`, follow the instruction to type in ID and a deadline.

_Note: if it is now **less than 48 hours before the deadline**, our system will begin arranging appointments for people with priority letter._

#### Withdraw while queuing

Type in `4`, follow the instruction to type in ID.

#### appointment

Type in `5`, this system will make appointments for queuing people. Appointment information is displayed in terminal.
_Note: To set the daily capacity of each hospital, you can change the underlined parameters in main.cpp as shown._
![daily capacity](./img/capacity.png)

### reporting

1. Reports will be produced to _report_ folder.
2. `Open_file()` is used to produce a weekly report, while `Month()` is used to produce a monthly report. All other functions in _Report.h_ won't be used in main function.
3. Our Report system uses data from a single-linked list containing information of all registered people.
4. By using `sort()`, we can order the reporting order based on some keywords as you wish.

#### Manual

Type in `6`, follow the instruction to produce report.
_Note: don't do this on the first day!_

#### Automatic

Based on date, this system will automatically make weekly or monthly report.
