#pylist.h

The pylist.h is a library to input and manipulate the 1D integer and float arrays.
To use this file in your program first copy it to your current working directory.
Then simply put 

    #include"pylist.h"
    
in your C program.

While most of the functions are easy to use and you can understand the function use by
looking into the library file, the functions that read the array, for example intarrayin(),
require you to explicitly declare a variable of appropriate data type in your main program.

For example, the below program

int array1[6];

intarrayin(6,array1);

will fire an error.

The correct way of doing this is,

int x;

int array1;

intarrayin(x,6,array1)

#pymat.h

The pymat.h is a library to input and manipulate the 2D integer and float arrays.
To use this file in your program first copy it to your current working directory.
Then simply put 

    #include"pymat.h"

in your C program.

Again ,most of the functions are easy to use and work fine.
But like pylist.h, the array reading functions require an explicit variable of
specified data type to work. 

#climate

climate stands for Command Line Interfaced MATrix Environment
climate is a runtime environment for performing basic I/O and operations on
1D integer arrays.
To run climate on windows,

    1. Download climate.exe

    2. Simply click on it 
        or
       Open powershell in the folder containing the .exe and type .\climate.exe

To run climate on ubuntu,

    1. Download the climate.
    
    2. Open a terminal in the folder containing the climate.
    
    3. type ./climate

It is built purely by using the pylist.h file.
Climate demonstrates the simplicity of using the pylist.h and the need to simplify C syntax. 
