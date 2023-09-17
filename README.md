# Philosophers

Welcome to the Philosophers project, a part of the 42 School curriculum. In this project, you will implement a solution to the Dining Philosophers problem using threads and synchronization techniques.

## Problem Description

The Dining Philosophers problem is a classic synchronization and concurrency problem. It consists of a number of philosophers who sit at a round table with bowls of spaghetti. The philosophers alternate between thinking and eating, but they must use forks to eat. There are a limited number of forks on the table, and each philosopher needs two forks to eat.

Your task is to implement a program that ensures the philosophers can eat safely without leading to deadlocks or resource conflicts.

## Project Structure

The project consists of the following files:

- `philo.c`: The main program that sets up the philosophers, forks, and threads.
- `philo.h`: Header file containing function prototypes and data structures.
- `utils.c`: Utility functions for time measurement and error handling.
- `Makefile`: A Makefile for compiling the project.

## Compilation

To compile the project, you can use the provided Makefile.
```shell
make
```

## Usage

To run the program, use the following command-line arguments:
```shell
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

```

- `number_of_philosophers`: The number of philosophers sitting at the table.
- `time_to_die`: The time in milliseconds after which a philosopher will die if they have not eaten.
- `time_to_eat`: The time in milliseconds it takes for a philosopher to eat.
- `time_to_sleep`: The time in milliseconds it takes for a philosopher to sleep.
- `[number_of_times_each_philosopher_must_eat]` (optional): The number of times each philosopher must eat before the program terminates. If not provided, the program will run until a philosopher dies.

## Example

Here's an example of how to run the program with 5 philosophers.
```shell
./philo 5 800 200 200

```
