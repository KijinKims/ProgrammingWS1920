# Task1
## Q1

- Integer(**int**)
- Character(**char**)
- Boolean(**bool**)
- Floating Point(**float**)
- Double Floating Point( **double**)
-  **void**

## Q2

Expression is made of sequence of operands and operators. It specifies which computation will be done. e.g. 4==5, a < b
Statement is a chunk of code performing some actions such as computation, declaration or conditional flow control. It includes if statement, return statement, expression statement and so on. e.g.  x = x + 1; , return y; if(true) x++;

## Q3

Compiler in some case convert data type to another type automatically. It is called "implicit" type conversion. When programmer, on the other hand, directs the type conversion explicitly, it is "explicit" type conversion.

## Q4

If developer doesn't deal with coner case of properly, it cause unexpected error. Also if he/she cooperate with another developer or his/her work is succeeded by others, implicit type conversion can be hard to be found by others.

## Q5

Junk data is placed on the values and cause unexpected result or errors. Especially, it can cost a lot of time to be debugged.

## Q6

If condition of conditional statements is single integer or character and many cases should be handled, switch-statment is preferred.

## Q7

Missing **break** or **default** can make unintended result and be hard to be found. For example,
switch(a){
    case(1): x + 1;
    case(2): x - 1;
}
the switch statement above looks concise and good (and don't cause compile/runtime error). However, for the case when a is 1, x becomes not x+1 but keeps x because operation under case with 2 will be done as well. In addition, missing **default** make it impossible to deal with cases other than 1 and 2.

## Q8

operator[] of string class, access to each character, doesn't operate on integer. operator*, multiplication, can be used for integers but not on string.

## Q9

Reference is making it possible to use existing variable as another name and access existing memory with aliased name. Pointer, however, is a variable which has its own memory location and store the memory address of another variable or object. For example, int a = 1; int& b = a; (reference) make it possible access a with the name of b. On the contrary, int* c = &a;  (pointer) points the memory address of a. 

## Q10

Array is data structure consisting of a series of data with same data type. And array can be accessed with pointer which points the starting point of the array. For instance,
int[5] intArray = {1, 2, 3, 4, 5}; int * ptr = intArray; 
data of array intArray can be accessed with ptr like this way, *ptr.

## Q11

When the function returns the value for another function, 
