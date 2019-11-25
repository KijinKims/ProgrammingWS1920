# Task1
## Q1
The member of `struct` is public by default. On the other hand,  the member of `class` is private by default.

## Q2
- To make clean and simple interface
- To make it easy to keep a validity of value (=maintaining invariant)
- To streamline debugging
- To change representation with ease

## Q3
`const` means the value cannot be changed . `static` indicates that the value will shared by all objects which are instantiated from one class. Once `static` value is changed, it affects all objects.

## Q4
- To prevent developer's confusion
- To keep data from unprivileged modification during the access of external user

## Q5
Compiler copies the statements of the function to the place where the function is called. Thereby unnecessary overhead by function call can be removed. When the size of the function is small, function call overhead is bigger than actual function runtime. For this case, `inline` is useful.

## Q6
Destructor is a special member function and called when the lifetime of an object ends. In general, it is used to free the used resources by the object.

## Q7
When a class is expected to be inherited by another class and the semantic of member function would be changed, `virtual` makes the functions able to be redefined.

## Q8
`friend` declares **non-member** function can access private or protected members of class. `virtual`, however, is always declared for **member** function, which would be redefined by inherited class. There's the conflict between semantics and compiler also makes error.

## Q9
When a function does not have any semantic for current class, but it does for child class, pure virtual function shows explicitly its relation and prevent the class from instantiating as well.

## Q10
Multiple inheritance makes the dependency of classes complex, so it can makes confusion for developers. It also cause ambiguity because the origin of elements are obscure in child class.

## Q11
Interface provides the blueprint of class, which means it only includes the abstractions of member functions, not implementations. So it cannot be instantiated but inherited only. Implementations are conducted in concrete class which inherits interface.
