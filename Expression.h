

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include "Stack.h"

using namespace std;

bool isOpeningBracket(char c)
{
    return c == '(' || c == '[' || c == '{';
}

bool isClosingBracket(char c)
{
    return c == ')' || c == ']' || c == '}';
}

bool isMatchingBracket(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

// PART 1: CHECK BALANCED BRACKETS

bool checkBrackets(const string& expression, string& error)
{
    Stack<char> bracketStack;

    for (char c : expression)
    {
        if (isOpeningBracket(c))
        {
            bracketStack.push(c);
        }
        else if (isClosingBracket(c))
        {
            char topBracket;

            if (!bracketStack.pop(topBracket))
            {
                error = "Unmatched closing bracket.";
                return false;
            }

            if (!isMatchingBracket(topBracket, c))
            {
                error = "Mismatched brackets.";
                return false;
            }
        }
    }

    if (!bracketStack.isEmpty())
    {
        error = "Unclosed opening bracket.";
        return false;
    }

    error = "Brackets are balanced.";
    return true;
}

// PART 2: CONVERT INFIX TO POSTFIX

bool convertToPostfix(
    const string& expression,
    vector<string>& postfix,
    string& error)
{
    postfix.clear();

    Stack<char> operatorStack;

    bool expectOperand = true;
    bool foundToken = false;

    for (size_t i = 0; i < expression.length();)
    {
        char c = expression[i];

        if (isspace(static_cast<unsigned char>(c)))
        {
            i++;
            continue;
        }

        foundToken = true;

        // Read multi-digit integers
        if (isdigit(static_cast<unsigned char>(c)))
        {
            if (!expectOperand)
            {
                error = "Missing operator between numbers.";
                return false;
            }

            string number;

            while (i < expression.length() &&
                   isdigit(static_cast<unsigned char>(expression[i])))
            {
                number += expression[i];
                i++;
            }

            postfix.push_back(number);
            expectOperand = false;
            continue;
        }

        // Opening bracket
        if (isOpeningBracket(c))
        {
            if (!expectOperand)
            {
                error = "Implicit multiplication is not allowed.";
                return false;
            }

            operatorStack.push('(');
            expectOperand = true;
            i++;
            continue;
        }

        // Closing bracket
        if (isClosingBracket(c))
        {
            if (expectOperand)
            {
                error = "Empty group or missing operand.";
                return false;
            }

            char op;

            while (operatorStack.pop(op))
            {
                if (op == '(')
                    break;

                postfix.push_back(string(1, op));
            }

            expectOperand = false;
            i++;
            continue;
        }

        // Arithmetic operator
        if (isOperator(c))
        {
            if (expectOperand)
            {
                error = "Invalid operator sequence or unsupported unary sign.";
                return false;
            }

            char topOperator;

            while (operatorStack.peek(topOperator) &&
                   topOperator != '(' &&
                   precedence(topOperator) >= precedence(c))
            {
                operatorStack.pop(topOperator);
                postfix.push_back(string(1, topOperator));
            }

            operatorStack.push(c);

            expectOperand = true;
            i++;
            continue;
        }

        error = "Unsupported character in expression.";
        return false;
    }

    if (!foundToken)
    {
        error = "Empty expression is not allowed.";
        return false;
    }

    if (expectOperand)
    {
        error = "Expression ends with a missing operand.";
        return false;
    }

    char remainingOperator;

    while (operatorStack.pop(remainingOperator))
    {
        if (remainingOperator == '(')
        {
            error = "Unclosed opening bracket.";
            return false;
        }

        postfix.push_back(string(1, remainingOperator));
    }

    error = "Conversion successful.";
    return true;
}

// PART 3: EVALUATE POSTFIX

bool evaluatePostfix(
    const vector<string>& postfix,
    double& result,
    string& error)
{
    Stack<double> valueStack;

    for (const string& token : postfix)
    {
        // Check if token is a number
        if (!token.empty() &&
            isdigit(static_cast<unsigned char>(token[0])))
        {
            try
            {
                size_t position = 0;

                double number = stod(token, &position);

                if (position != token.length() || !isfinite(number))
                {
                    error = "Invalid or non-finite number.";
                    return false;
                }

                valueStack.push(number);
            }
            catch (...)
            {
                error = "Number conversion error.";
                return false;
            }
        }
        else if (token.length() == 1 && isOperator(token[0]))
        {
            double rightOperand;
            double leftOperand;

            if (!valueStack.pop(rightOperand) ||
                !valueStack.pop(leftOperand))
            {
                error = "Not enough operands for the operator.";
                return false;
            }

            double answer = 0;
            char op = token[0];

            switch (op)
            {
                case '+':
                    answer = leftOperand + rightOperand;
                    break;

                case '-':
                    answer = leftOperand - rightOperand;
                    break;

                case '*':
                    answer = leftOperand * rightOperand;
                    break;

                case '/':
                    if (rightOperand == 0)
                    {
                        error = "Division by zero is not allowed.";
                        return false;
                    }

                    answer = leftOperand / rightOperand;
                    break;
            }

            if (!isfinite(answer))
            {
                error = "Result is not finite.";
                return false;
            }

            valueStack.push(answer);
        }
        else
        {
            error = "Invalid postfix token.";
            return false;
        }
    }

    if (valueStack.size() != 1)
    {
        error = "Invalid postfix expression.";
        return false;
    }

    valueStack.pop(result);

    error = "Evaluation successful.";
    return true;
}

// DISPLAY POSTFIX EXPRESSION

string postfixToString(const vector<string>& postfix)
{
    stringstream output;

    for (size_t i = 0; i < postfix.size(); i++)
    {
        if (i > 0)
            output << " ";

        output << postfix[i];
    }

    return output.str();
}

#endif
