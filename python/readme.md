# how to use python
## some short cut
1. start a terminal in terminal type python
    1. clear screen
    
    ```python
    import os
    os.system('cls')
    ```
    2. import dis to check the disassembled bytecode of a function
    ```python
    import dis
    ```
    3. check current folder
    ```python
    import os
    os.getcwd()
    ```

2. run a python file
    1. in terminal type python path_to_Your_Folder\test.py
       1. python enter the python terminal
        2. run the py file in python terminal
        ```cmd
        exec(open("test.py").read())
        ```
    2. python -i
        python -i test.py
3. show all disassembly code in a py file
    ```cmd    
    py -m dis .\test.py
    ```