# CS4760 Project 2

This project simulates a system with a master process (oss) and worker processes, using shared memory and a simulated clock.

## Compilation

To compile this project, run 'make' in the terminal. This will generate the 'oss' and 'worker' executables.

## Running

To run the project, execute './oss' with the desired command-line options:

* '-h': Display help information
* '-n <num_processes>': Specify the number of worker processes to create (default: 5)
* '-s <num_simultaneous>': Specify the maximum number of simultaneous worker processes (default: 3)
* '-t <time_limit>': Specify the upper bound for the time a worker process can run (default: 10 seconds)
* '-i <interval>': Specify the internal in milliseconds for launching worker processes (default: 100 ms)

For example, to run with 10 worker processes, 5 simultaneous processes, a time limit of 20 seconds, and an interval of 50 ms, use the following command:

``` bash
./oss -n 10 -s 5 -t 20 -i 50

## Problems Encountered

Several issues were found, and below was their solutions:

1. **Missing Closing Braces**:
	- **Problem**: The code would not compile due to an "expected declaration or statement at end of input" error.
	- **Solution**: Ensure that all opening braces '{' have corresponding closing braces '}'. This was particularly important for the 'main' function and loops.

2. **Unused Variable Warning**:
	-**Problem**: Warnings were generated for variables that were declared but not used ('increment' and 'intervalInMsToLaunchChildren').
	--**Solution**: These warnings can be ignored.

3. **Redefintion of Variables**+
	-**Problem**: Errors occured due to the redefinition of variables (e.g., 'increment).
	-**Solution**: Ensure that each variable is defined only once within the same scope.

4. **Undeclared Identifiers**:
	-**Problem**: Errors related to undeclare identifiers (e.g., 'children_running').
	-**Solution**: Ensure that all variables are decalred before they are used.

5. **Signal Handling Issues**:
	-**Problem**: Issues with signal handling and shared memory management.
	-**Solution**: Properly manage shared memory and ensure that signal handlers are set up correctly to handle termination signals.

6. **Output Timing**:
	-**Problem**: Ensuring that worker processes correctly calculate their terminatime times and terminate as expected.
	-**Solution**: The worker processes were tested to confirm they output their status and terminate correctly.


