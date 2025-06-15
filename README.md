Philo
Overview
Philo is a project developed as part of the 42 cursus. It aims to provide hands-on experience with fundamental programming concepts, particularly in process management, concurrency, and synchronization. The project implements the classic Dining Philosophers problem—a well-known exercise for understanding multithreading, resource sharing, and avoiding concurrency pitfalls such as deadlocks and race conditions.

Project Concept
The Dining Philosophers problem simulates a group of philosophers sitting at a table, alternating between thinking and eating. Each philosopher needs two forks to eat, but forks are shared between neighbors, leading to potential resource contention. The challenge lies in designing a system that allows all philosophers to eat without causing deadlocks or starvation.

This project focuses on:

Managing multiple threads or processes to represent philosophers.
Using mutexes and/or semaphores to synchronize access to shared resources (forks).
Preventing concurrency issues like deadlocks and race conditions.
Handling timing and state management in a concurrent environment.
Features
Accurate simulation of philosopher behaviors (thinking, eating, sleeping).
Configurable parameters for the number of philosophers and timing behaviors.
Robust synchronization mechanisms to prevent deadlocks and starvation.
Clean and informative output for monitoring simulation states.
Installation
Clone the repository:

bash
git clone https://github.com/aybouatr/Philo.git
cd Philo
Compile the project:

bash
make
Usage
Run the compiled executable with the following arguments:

bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
number_of_philosophers — Number of philosopher threads/processes.
time_to_die — Time (in ms) a philosopher can go without eating before dying.
time_to_eat — Time (in ms) it takes for a philosopher to eat.
time_to_sleep — Time (in ms) a philosopher spends sleeping.
number_of_times_each_philosopher_must_eat (optional) — If specified, simulation stops when each philosopher has eaten this many times.
Example
bash
./philo 5 800 200 200
This command launches a simulation with 5 philosophers.

Output
The program prints the actions of each philosopher to the standard output, including:

When a philosopher takes a fork
When a philosopher starts eating
When a philosopher starts sleeping
When a philosopher starts thinking
If a philosopher dies
This format helps track the simulation and verify correct synchronization.

Project Structure
philo.c — Main simulation logic
utils.c — Utility functions
Makefile — Build instructions
Compilation
To build the project, simply run:

bash
make
This will generate the philo executable.

To clean up build files:

bash
make clean
Contributing
Contributions are welcome! Feel free to open issues or submit pull requests for improvements or bug fixes.

License
This project is for educational purposes as part of the 42 cursus
