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
        if (postfix == "ILLEGAL") return std::nan(""); // 使用NaN表示非法表达式
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
        bool lastWasOp = true; // 用于检测表达式开头或括号后是否为运算符
        bool lastWasDigit = false; // 用于处理数字和科学计数法

        for (size_t i = 0; i < infix.size(); ++i) {
            char c = infix[i];

            // 忽略空格
            if (isspace(c)) continue;

            if (isdigit(c) || c == '.') {
                postfix += c;
                lastWasOp = false;
                lastWasDigit = true;
            } else if (c == 'e' || c == 'E') {
                if (lastWasDigit) { // 确保e前是数字
                    postfix += c;
                    lastWasOp = true; // e后可以接负号
                    lastWasDigit = false;
                } else {
                    return "ILLEGAL";
                }
            } else if (c == '+' || c == '-') {
                if (lastWasOp) { // 支持表达式开头或括号后的负号
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
                lastWasOp = true; // 括号后可以是运算符（例如负号）
                lastWasDigit = false;
            } else if (c == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    postfix += ' ';
                    postfix += operators.top();
                    operators.pop();
                }
                if (operators.empty()) return "ILLEGAL"; // 括号不匹配
                operators.pop(); // 弹出 '('
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
                return "ILLEGAL"; // 非法字符
            }
        }

        while (!operators.empty()) {
            if (operators.top() == '(') return "ILLEGAL"; // 括号不匹配
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
                if (values.size() < 2) return std::nan(""); // 非法表达式
                double right = values.top(); values.pop();
                double left = values.top(); values.pop();

                switch (c) {
                    case '+': values.push(left + right); break;
                    case '-': values.push(left - right); break;
                    case '*': values.push(left * right); break;
                    case '/':
                        if (right == 0) return std::nan(""); // 除数为0
                        values.push(left / right);
                        break;
                }
            }
        }

        return values.top();
    }
};

#endif // EXPRESSION_EVALUATOR_H
