Philo
Project Overview
Philo is a project from the 42 cursus that focuses on understanding and practicing fundamental programming concepts, mainly related to process management, concurrency, and synchronization. The project aims to simulate and manage multiple threads or processes working simultaneously while avoiding common problems like race conditions and deadlocks.

Concept
The core idea behind Philo is inspired by the classic Dining Philosophers problem, a common exercise in concurrency and synchronization. It involves multiple philosophers sitting around a table who alternately think and eat, but need two forks (shared resources) to eat. The challenge is to manage resource access without causing deadlocks or starvation.

Philo helps you understand:

How to create and manage multiple threads/processes.

Use of mutexes and semaphores to synchronize access to shared resources.

Avoid common concurrency problems like deadlocks and race conditions.

Proper timing and state management in concurrent programs.

Usage
After cloning the repo and building the project, run the executable with the appropriate arguments to simulate the philosophers’ behavior.

Example:

bash
Copy
Edit
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
Mandatory Sections
Compilation instructions

How to run the program with correct arguments

Explanation of expected behavior and output format
