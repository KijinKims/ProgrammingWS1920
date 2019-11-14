# Task2
## task2a.cpp

The index value **i** becomes very big value when it goes  below zero. And it makes infinite loop. Placehorder type specifier **auto** detects variable type automatically.  **size** method of **vector** class returns unsigned int variable. Hence variable **i** is declared as unsigned int. If unsigned value becomes below zero, it goes maximum positive value. So it makes infinite loop for this code. Simply replacing **auto**  in line 12 into **int** can fix the problem.

## task2b.cpp

The program makes Segmentation fault error. It means the program access unassigned memory. Function returns the value as a reference variable, and it means it doesn't copy value to newly assigned memory but make an alias to original memory location of variable. The variable, however, get lost its memory after the function is returned. So, it  cannot be accessed any more afterwards. It can be fixed just leaving out &(ampersand) in line 4, which makes function return copying return value to new memory location.
