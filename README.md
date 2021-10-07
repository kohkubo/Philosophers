# Philosophers in 42 project

Code for The Dining Philosophers Problem in 42 project.

In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

The problem was designed to illustrate the challenges of avoiding deadlock, a system state in which no progress is possible. 

![demo](gif/demo_philo.gif)

## philo

The simulation is implemented in multi-threading.
Mutexes were used to avoid multi-threaded deadlocks.

### Usage

```sh
> cd philo
> make
> ./philo
Usage: ./philo PN TD TE TS [EC]

        PN = number of philosophers
        TD = time to die
        TE = time to eat
        TS = time to sleep
        EC = number of times each philosopher must eat
```

## philo_bonus

The simulation is implemented in a multi-process.
Semaphores were used to avoid multi-process deadlocks.

### Usage

```sh
> cd philo_bonus
> make
> ./philo_bonus
Usage: ./philo_bonus PN TD TE TS [EC]

        PN = number of philosophers
        TD = time to die
        TE = time to eat
        TS = time to sleep
        EC = number of times each philosopher must eat
```
