#include <iostream>
#include "expression_evaluator.h"

int main() {
    std::string expression;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, expression);

    double result = ExpressionEvaluator::evaluate(expression);
    if (std::isnan(result)) {
        std::cout << "ILLEGAL\n";
    } else {
        std::cout << "Result: " << result << std::endl;
    }

    return 0;
}
