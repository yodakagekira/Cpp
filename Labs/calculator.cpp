#include <iostream>

// Typedef for function pointer
using funcPtr = int(*)(int, int);

int getInteger()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;
    return x;
}

char getOperation()
{
    char op{};

    do
    {
        std::cout << "Enter an operation ('+', '-', '*', '/'): ";
        std::cin >> op;
    } while (op != '+' && op != '-' && op != '*' && op != '/');

    return op;
}

int add(int x, int y) {
    return x + y;
}
int multiply(int x, int y) {
    return x * y;
}
int subtract(int x, int y) {
    return x - y;
}
int divide(int x, int y) {
    return x / y;
}

funcPtr getArithmeticFunction(char op)
{
    switch (op)
    {
    case '+': return &add;
    case '-': return &subtract;
    case '*': return &multiply;
    case '/': return &divide;
    }

    return nullptr; // Fallback in case of an invalid operation
}
int main()
{
    int x{ getInteger() };
    char op{ getOperation() };
    int y{ getInteger() };
    
    funcPtr fcn{getArithmeticFunction(op)};
    std::cout << "x " <<  op << "y = " << fcn(x,y); 
    
    return 0;
}
