#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>

class ExpressionEvaluator {
public:
    static double evaluate(const std::string& expression) {
        std::string postfix = infixToPostfix(expression);
        if (postfix == "ILLEGAL") return std::nan("");
        return evaluatePostfix(postfix);
    }

private:
    static int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    static bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    static std::string infixToPostfix(const std::string& infix) {
        std::stack<char> operators;
        std::string postfix;
        bool lastWasOp = true;
        bool lastWasDigit = false;

        for (size_t i = 0; i < infix.size(); ++i) {
            char c = infix[i];

            // 忽略空格
            if (isspace(c)) continue;

            if (isdigit(c) || c == '.') {
                postfix += c;
                lastWasOp = false;
                lastWasDigit = true;
            } else if (c == 'e' || c == 'E') {
                if (lastWasDigit) {
                    postfix += c;
                    lastWasOp = true; 
                    lastWasDigit = false;
                } else {
                    return "ILLEGAL";
                }
            } else if (c == '+' || c == '-') {
                if (lastWasOp) {
                    postfix += ' ';
                    postfix += c;
                } else {
                    postfix += ' ';
                    while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                        postfix += operators.top();
                        postfix += ' ';
                        operators.pop();
                    }
                    operators.push(c);
                }
                lastWasOp = true;
                lastWasDigit = false;
            } else if (c == '(') {
                operators.push(c);
                lastWasOp = true;
                lastWasDigit = false;
            } else if (c == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    postfix += ' ';
                    postfix += operators.top();
                    operators.pop();
                }
                if (operators.empty()) return "ILLEGAL";
                operators.pop();
                lastWasOp = false;
            } else if (isOperator(c)) {
                postfix += ' ';
                while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                    postfix += operators.top();
                    postfix += ' ';
                    operators.pop();
                }
                operators.push(c);
                lastWasOp = true;
                lastWasDigit = false;
            } else {
                return "ILLEGAL";
            }
        }

        while (!operators.empty()) {
            if (operators.top() == '(') return "ILLEGAL";
            postfix += ' ';
            postfix += operators.top();
            operators.pop();
        }

        return postfix;
    }


    static double evaluatePostfix(const std::string& postfix) {
        std::stack<double> values;
        std::string number;

        for (char c : postfix) {
            if (isdigit(c) || c == '.' || c == 'e' || c == 'E') {
                number += c;
            } else if (c == ' ' && !number.empty()) {
                values.push(std::stod(number));
                number.clear();
            } else if (isOperator(c)) {
                if (values.size() < 2) return std::nan("");
                double right = values.top(); values.pop();
                double left = values.top(); values.pop();

                switch (c) {
                    case '+': values.push(left + right); break;
                    case '-': values.push(left - right); break;
                    case '*': values.push(left * right); break;
                    case '/':
                        if (right == 0) return std::nan("");
                        values.push(left / right);
                        break;
                }
            }
        }

        return values.top();
    }
};

#endif
