# PROCESSES-AND-SIGNALS

## Overview

This program demonstrates the creation and management of child processes in a Unix/Linux environment using the `fork()`, `wait()`, and `signal()` system calls. It creates a predefined number of child processes, manages their execution, and handles their termination appropriately. The program is designed to be compiled in two versions: one without signal handling and one with signal handling, directed by the `WITH_SIGNALS` preprocessor symbol.

## Features

- **Process Creation:** Creates a specified number of child processes using `fork()`.
- **Delayed Execution:** Introduces a one-second delay between consecutive `fork()` calls.
- **Process Monitoring:** Monitors and waits for all child processes to terminate.
- **Signal Handling (Optional):** Incorporates signal handling to demonstrate graceful interruption and process termination.

## Compilation

The program can be compiled in two modes: with and without signal handling support. Use the following commands to compile the program accordingly:

- **Without Signal Handling:**

  ```
  gcc -o child_process_manager child_process_manager.c
  ```

- **With Signal Handling:**

  ```
  gcc -DWITH_SIGNALS -o child_process_manager child_process_manager.c
  ```

## Running the Program

After compilation, you can run the program by executing:

```
./child_process_manager
```

## Program Behavior

- **Without Signal Handling:** The program will create child processes, each printing its PID and its parent's PID, then sleep for 10 seconds before indicating its execution completion.
- **With Signal Handling:** In addition to the basic behavior, the program will handle signals differently. It will ignore most signals but restore the default handler for `SIGCHLD`. A custom handler for `SIGINT` (keyboard interrupt) will set a flag to notify the occurrence of an interrupt, affecting the creation of subsequent child processes.

## Additional Notes

- The program utilizes standard Unix/Linux system calls such as `fork()`, `wait()`, `signal()`, and `kill()` to manage processes.
- It is designed to demonstrate basic process management and signal handling in a C program under a Unix/Linux environment.
- Ensure to check manual pages for system calls used (`man 2 fork`, `man 2 wait`, etc.) for a deeper understanding of their behavior.

