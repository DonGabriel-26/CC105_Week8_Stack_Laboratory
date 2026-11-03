
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Stack.h"
#include "Expression.h"

using namespace std;

void runStackDemo()
{
    Stack<int> myStack;
    int value;

    cout << "\n========== STACK DEMONSTRATION ==========\n";

    cout << "\n1. Pop on empty stack: ";

    if (myStack.pop(value))
        cout << value << endl;
    else
        cout << "False (Stack is empty)" << endl;

    cout << "\n2. Push 10 and 20\n";

    myStack.push(10);
    myStack.push(20);

    cout << "Stack size: " << myStack.size() << endl;

    if (myStack.peek(value))
        cout << "Peek: " << value << endl;

    cout << "\n3. Push 30\n";

    myStack.push(30);

    cout << "Stack size: " << myStack.size() << endl;

    cout << "\n4. Pop all items\n";

    while (myStack.pop(value))
    {
        cout << "Popped: " << value << endl;
    }

    cout << "\n5. Peek on empty stack: ";

    if (myStack.peek(value))
        cout << value << endl;
    else
        cout << "False (Stack is empty)" << endl;

    cout << "\nFinal stack size: " << myStack.size() << endl;

    cout << "\n=========================================\n";
}

void runBracketChecker()
{
    string expression;
    string error;

    cout << "\n========== BRACKET CHECKER ==========\n";

    cout << "Enter an expression: ";
    getline(cin, expression);

    if (checkBrackets(expression, error))
        cout << "Result: " << error << endl;
    else
        cout << "Error: " << error << endl;

    cout << "=====================================\n";
}

void runExpressionEvaluator()
{
    string expression;
    string bracketError;
    string error;

    vector<string> postfix;
    double result;

    cout << "\n========== EXPRESSION EVALUATOR ==========\n";

    cout << "Enter an expression: ";
    getline(cin, expression);

    cout << "\nInput: " << expression << endl;

    if (!checkBrackets(expression, bracketError))
    {
        cout << "Bracket Status: Invalid" << endl;
        cout << "Error: " << bracketError << endl;
        cout << "==========================================\n";
        return;
    }

    cout << "Bracket Status: Balanced" << endl;

    if (!convertToPostfix(expression, postfix, error))
    {
        cout << "Conversion Error: " << error << endl;
        cout << "==========================================\n";
        return;
    }

    cout << "Postfix Expression: "
         << postfixToString(postfix) << endl;

    if (!evaluatePostfix(postfix, result, error))
    {
        cout << "Evaluation Error: " << error << endl;
        cout << "==========================================\n";
        return;
    }

    cout << fixed << setprecision(6);
    cout << "Final Result: " << result << endl;

    cout << "==========================================\n";
}

int main()
{
    string choice;

    do
    {
        cout << "\n=========================================\n";
        cout << "       CC105 WEEK 8 STACK LABORATORY\n";
        cout << "=========================================\n";

        cout << "1. Check Brackets\n";
        cout << "2. Convert and Evaluate Expression\n";
        cout << "3. Run Stack Demonstration\n";
        cout << "0. Exit\n";

        cout << "=========================================\n";
        cout << "Enter your choice: ";

        getline(cin, choice);

        if (choice == "1")
        {
            runBracketChecker();
        }
        else if (choice == "2")
        {
            runExpressionEvaluator();
        }
        else if (choice == "3")
        {
            runStackDemo();
        }
        else if (choice == "0")
        {
            cout << "\nProgram ended. Thank you!\n";
        }
        else
        {
            cout << "\nInvalid choice. Please select 0, 1, 2, or 3.\n";
        }

    } while (choice != "0");

    return 0;
}
