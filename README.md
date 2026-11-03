# CC105 Week 8 Laboratory on Stacks

## Project Description

This project is a C++ console application that uses a Stack data structure to check balanced brackets, convert infix expressions into postfix expressions, and evaluate mathematical expressions.

## Name

Poblete, Don Gabriel T.
2.4BSIT

## Compiler Version

IDE: Code::Blocks

Compiler: GNU GCC

C++ Standard: C++17

Compiler Version: [gcc (Rev8, Built by MSYS2 project) 15.2.0]

## How to Build and Run

1. Open CC105_Week8_Stack_Laboratory.cbp in Code::Blocks.
2. Make sure the compiler is set to GNU GCC.
3. Build the project.
4. Run the program.
5. Use the menu to select the desired operation.

## Supported Syntax

- Addition (+)
- Subtraction (-)
- Multiplication (*)
- Division (/)
- Parentheses ()
- Square brackets []
- Curly brackets {}
- Nonnegative multi-digit integers
- Spaces between numbers and operators

## Limitations

- Decimal input numbers are not accepted.
- Negative numbers and unary signs are not supported.
- Exponents are not supported.
- Implicit multiplication is not allowed.
- Division by zero is rejected.

## Algorithm Explanation

The program uses a Stack that follows the Last In, First Out (LIFO) principle.

First, it checks if the brackets are properly matched. Next, it converts the infix expression into postfix form using an operator stack. Finally, it evaluates the postfix expression using a stack of double values.

The stack is implemented using a singly linked list. Each node stores a value and a pointer to the next node.

## Stack Operations

- push(): Adds an item to the top.
- pop(): Removes the top item.
- peek(): Checks the top item.
- isEmpty(): Checks if the stack is empty.
- size(): Returns the number of items.

## Memory Management

The program uses dynamic memory allocation with new when creating nodes. It uses delete when removing nodes. A destructor releases all remaining nodes when the stack is destroyed.

## Testing

The program was tested using valid expressions, invalid expressions, bracket errors, division by zero, and empty-stack operations.