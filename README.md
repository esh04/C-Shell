# C-Shell

- To run the shell
    - `make`
    - `./a.out`

- To exit the shell
    - `Ctrl+D`
    -  `exit`

- Assumptions
    - `discover` does not print the hidden files and directories. To include hidden files and directories too follow instructions mentioned in `discover.c`
    - While giving multiple file inputs to `ls`, the directories/files are not sorted alphabetically but their results are.
    - The autocomplete template provided was not compatible with the previously written code so I have attached both `main.c` and `main2.c`
    -  `main2.py` works with all other functions, `main.c` works with autocomplete.
    - Move the required main file to src to run the code.

- Makefile contains the code required to compile the file
-  `main.c` contains the main code while all the other `*.c` files contain the corresponding functions while `*.h` contains the headers.
- all global variables are declared in `headers.h`