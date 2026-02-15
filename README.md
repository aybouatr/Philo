# 🍝 Philosophers - Dining Philosophers Problem

A multithreaded solution to the classic **Dining Philosophers Problem** implemented in C using POSIX threads and mutexes. This project explores concurrent programming, synchronization, and deadlock prevention.

---

## 📋 Table of Contents

- [About](#about)
- [The Problem](#the-problem)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Implementation Details](#implementation-details)
- [Author](#author)

---

## 🎯 About

The **Dining Philosophers Problem** is a classic synchronization problem in computer science that illustrates the challenges of resource allocation and deadlock avoidance in concurrent systems. This project implements a solution using POSIX threads (`pthread`) and mutexes.

---

## 🧩 The Problem

Several philosophers sit at a round table doing one of three things:
- **Eating** 🍝
- **Thinking** 💭
- **Sleeping** 😴

Rules:
- Philosophers alternate between eating, thinking, and sleeping
- There are as many forks as philosophers
- A philosopher needs **two forks** (left and right) to eat
- When done eating, they put down both forks and start sleeping
- After sleeping, they start thinking
- The simulation stops when a philosopher dies of starvation

---

## ✨ Features

- ✅ Multithreaded simulation with POSIX threads
- ✅ Mutex-based synchronization for fork access
- ✅ Thread-safe state monitoring
- ✅ Death detection system
- ✅ Configurable parameters (number of philosophers, timing)
- ✅ Optional meal count limit
- ✅ Race condition prevention
- ✅ Support for up to 250 philosophers

---

## 🚀 Installation

### Prerequisites

- GCC compiler
- POSIX-compliant system (Linux, macOS)
- Make

### Build

```bash
git clone https://github.com/aybouatr/Philo.git
cd Philo
make
```

This will compile the project and create the `philo` executable.

---

## 💻 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

| Parameter | Description | Required |
|-----------|-------------|----------|
| `number_of_philosophers` | Number of philosophers and forks | Yes |
| `time_to_die` | Time (ms) before a philosopher dies without eating | Yes |
| `time_to_eat` | Time (ms) it takes to eat | Yes |
| `time_to_sleep` | Time (ms) spent sleeping | Yes |
| `number_of_times_each_philosopher_must_eat` | Simulation stops when all philosophers eat this many times | No |

### Examples

```bash
# Basic simulation: 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep
./philo 5 800 200 200

# With meal limit: Stops after each philosopher eats 7 times
./philo 5 800 200 200 7

# Stress test: 200 philosophers with tight timing
./philo 200 410 200 200
```

### Expected Output

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
...
```

Format: `[timestamp_in_ms] [philosopher_id] [action]`

---

## 📁 Project Structure

```
Philo/
├── philo.h              # Header file with structures and function prototypes
├── main.c               # Entry point and argument validation
├── ft_parsing.c         # Input validation and parsing
├── ft_init.c            # Initialization of data structures
├── ft_threads.c         # Thread management and philosopher routine
├── ft_threads_utils.c   # Thread utility functions (eating, sleeping)
├── ft_utils.c           # Helper functions (time, printing)
└── Makefile             # Build configuration
```

---

## 🔧 Implementation Details

### Key Data Structures

#### `t_philo` - Philosopher Structure
```c
typedef struct s_philo {
    int             time_eat;
    pthread_t       threads;
    int             time_to_sleep;
    short           eating;
    short           id;
    int             nbr_eating;
    int             time_to_die;
    int             nbr_of_eat;
    int             num_philo;
    int             last_meal;
    int             start_time;
    int             *some_one_dead;
    pthread_mutex_t *lock_print;
    pthread_mutex_t *lock_dead;
    pthread_mutex_t *lock_meal;
    pthread_mutex_t *lock_fork_r;
    pthread_mutex_t *lock_fork_l;
} t_philo;
```

#### `t_meta_data` - Simulation Metadata
```c
typedef struct s_meta_data {
    int             time_to_eat;
    int             time_to_sleep;
    int             time_to_die;
    int             nbr_of_eat;
    int             some_one_dead;
    int             num_philo;
    int             nbr_eating;
    pthread_mutex_t lock_print;
    pthread_mutex_t lock_dead;
    pthread_mutex_t lock_meal;
    t_philo         *philo_s;
} t_meta_data;
```

### Synchronization Strategy

- **Fork Mutexes**: Each fork is protected by a mutex
- **Death Monitor**: Separate monitoring thread checks for philosopher deaths
- **Print Mutex**: Ensures thread-safe output
- **Meal Mutex**: Protects shared eating state
- **Deadlock Prevention**: Philosophers pick up forks in a specific order

### Core Functions

| Function | Purpose |
|----------|---------|
| `manage_threads()` | Creates and manages philosopher threads |
| `minotoring_all_threads()` | Monitors for deaths and meal completion |
| `eat()` | Handles eating logic with fork acquisition |
| `sleeping()` | Manages sleeping state |
| `printf_message()` | Thread-safe message printing |
| `get_current_time()` | Returns current timestamp in milliseconds |

---

## 🧪 Testing

### Test Cases

```bash
# Should not die
./philo 4 410 200 200

# Should not die
./philo 5 800 200 200

# No one should die
./philo 5 600 150 150

# A philosopher should die
./philo 4 310 200 100

# Should stop when all eat 5 times
./philo 4 410 200 200 5
```

---

## 🐛 Common Issues

- **Philosophers dying immediately**: `time_to_die` is too short
- **Deadlock**: Check fork acquisition order
- **Data races**: Ensure all shared data access is mutex-protected
- **Memory leaks**: Verify all mutexes are destroyed

---

## 🧹 Cleaning Up

```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Rebuild from scratch
```

---

## 📚 Resources

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [Mutex Locks](https://www.gnu.org/software/libc/manual/html_node/POSIX-Threads.html)

---

## 👤 Author

**aybouatr**
- GitHub: [@aybouatr](https://github.com/aybouatr)
- 42 School Project

---

## 📄 License

This project is part of the 42 School curriculum.

---

## 🎓 Learning Outcomes

- Understanding concurrent programming concepts
- Working with POSIX threads (`pthread`)
- Implementing mutex-based synchronization
- Handling race conditions and deadlocks
- Time management in multithreaded environments
- Resource allocation strategies

---

**⭐ If you found this helpful, consider giving it a star!**
