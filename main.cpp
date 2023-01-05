/*
    This program serves as a simple
    arithmetic calculator on integer
    inputs. It supports basic integer
    arithmetic addition, subtraction,
    division, and multiplication only.
    Note that, by implementation, this
    calculator evaluates expressions
    from left-to-right.
*/

#include <iostream>
#include <vector>
#include "DivideByZeroException.h"
#include "UnexpectedTokenException.h"
#include "Token.h"
#include <stack>

int main()
{
    //Print a header to make the calculator look nicer!
    std::cout << "********CALCULATOR********\n";
    
    //Create a new string that will represent the expression we are parsing.
    std::string expressionToParse;
    //Create a vector to store the tokens in our expression.
    std::vector<Token*> tokenList; 

    //Simply more flair for the calculator output.
    std::cout << "Enter A Mathematical Expression" << std::endl;
    //Take input from the user to obtain a mathematical expression to parse.
    std::getline(std::cin, expressionToParse);

    /*
        We want to iterate over the characters in the
        expression string to determine which entered
        characters are tokens and which are whitespace.
        We will disregard whitespace. If any other
        unexpected characters are present we will
        throw an exception.
    */
    for(char t : expressionToParse)
    {
        switch(t)
        {
            case ' ': //We disregard whitespace.
                break;
            case '(':
                tokenList.push_back(new Token(Token::LPARENTHESIS));
                break;
            case ')':
                tokenList.push_back(new Token(Token::RPARENTHESIS));
                break;
            case '+':
                tokenList.push_back(new Token(Token::OPERATOR, t));
                break;
            case '-':
                tokenList.push_back(new Token(Token::OPERATOR, t));
                break;
            case '*':
                tokenList.push_back(new Token(Token::OPERATOR, t));
                break;
            case '/':
                tokenList.push_back(new Token(Token::OPERATOR, t));
                break;
            default: //Here we consider values and invalid tokens.
                try
                {
                    /*
                        We will throw an exception in the case that 
                        std::atof fails to convert the value and thus returns 0.0.
                    */
                    if(t != '0' && std::atof(&t) == 0.0) throw std::invalid_argument("Unexpected Token"); 
                    tokenList.push_back(new Token(Token::VALUE, std::atof(&t)));
                }
                catch(std::invalid_argument e)
                {
                    throw new UnexpectedTokenException();
                }
        }
    }

    //We create a stack to track operators in post-fix order.
    std::stack<Token*> operatorStack;
    //We create a new vector to contain the postfix notation of Tokens.
    std::vector<Token*> rpnTokenList;

    /*
        We will iterate over the tokens
        obtained from parsing our expression.
        We use an implementation of the
        Shunting-Yard Algorithm to achieve
        post-fix notation.
    */
    for(Token* token : tokenList)
    {
        switch(token->type())
        {
            //When our token is a value we simply put it at the back of the postfix list.
            case Token::VALUE:
                rpnTokenList.push_back(token);
                break;
            //When the token is ( we push it to the top of the operator stack.
            case Token::LPARENTHESIS:
                operatorStack.push(token);
                break;
            /*
                When our token is an operator, we must remove operations
                from the stack and place them in the post fix list with
                regard to the current operator token. In this implementation,
                we pop operators from the stack that are strictly greater in
                precedence than the current operator token.
            */
            case Token::OPERATOR:
                int precedence;
                if(token->operation() == '+' || token->operation() == '-') precedence = 1;
                else if(token->operation() == '*' || token->operation() == '/') precedence = 2;
                while(!operatorStack.empty() && operatorStack.top()->operatorPrecedence() > precedence)
                {
                    rpnTokenList.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token);
                break;
            //When we have ), we push operators to the post-fix list until ( is encountered.
            case Token::RPARENTHESIS:
                while(!operatorStack.empty() && operatorStack.top()->type() != Token::LPARENTHESIS)
                {
                    rpnTokenList.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                if(!operatorStack.empty()) operatorStack.pop();
                break;
            //Default should never execute.
            default:
                break;
        }
    }
    //We put any remaining operators at the end of our vector.
    while(!operatorStack.empty())
    {
        rpnTokenList.push_back(operatorStack.top());
        operatorStack.pop();
    }

    //Since we no longer need the original token vector, we erase its elements.
    tokenList.erase(tokenList.begin(), tokenList.end());

    //We create a new stack to track the calculations of our expression.
    std::stack<double> calculations;

    /*
        We want to iterate over the post-fix list we
        obtained and perform calculations.
    */
    for(Token* t : rpnTokenList)
    {
        switch(t->type())
        {
            /*
                When we encounter an operator, we
                want to pop the last two values on the
                calculation stack and perform the
                operation on them. Since a stack uses a
                Last-In-First-Out implementation the
                top of the stack is the second value in
                the calculation.
            */
            case Token::OPERATOR:
                double num2;
                num2 = calculations.top();
                calculations.pop();
                double num1;
                num1 = calculations.top();
                calculations.pop();
                double tempResult;
                //We must consider the operations that can be performed.
                switch(t->operation())
                {
                    case '+':
                        tempResult = num1 + num2;
                        calculations.push(tempResult);
                        break;
                    case '-':
                        tempResult = num1 - num2;
                        calculations.push(tempResult);
                        break;
                    case '*':
                        tempResult = num1 * num2;
                        calculations.push(tempResult);
                        break;
                    default:
                        if(num2 == 0) throw new DivideByZeroException();
                        tempResult = num1 / num2;
                        calculations.push(tempResult);
                }
                break;
            //When the token is value, simply push it to the stack.
            case Token::VALUE:
                calculations.push(t->value());
                break;
            //Default will never execute.
            default:
                break;
        }
    }

    /*
        We can now deallocate the items in the post-fix
        list from memory by erasing them from the vector.
    */
    rpnTokenList.erase(rpnTokenList.begin(), rpnTokenList.end());

    std::cout << "RESULT: " << calculations.top() << std::endl;
    calculations.pop(); //Remove the result to deallocate space.

    std::cout << "*************************\n"; //Conclude the menu.

    system("pause");
}