#include <iostream>
using namespace std;

int main() {
    char op;
    double num1, num2;
	
	cout << "Enter first numbers: ";
    cin >> num1;
    
    cout << "Enter the operator (+, -, *, /): ";
    cin >> op;

    cout << "Enter second numbers: ";
    cin >> num2;

    switch(op) {
        case '+':
            cout << num1 << " + " << num2 << " = " << (num1 + num2);
            break;
        case '-':
            cout << num1 << " - " << num2 << " = " << (num1 - num2);
            break;
        case '*':
            cout << num1 << " * " << num2 << " = " << (num1 * num2);
            break;
        case '/':
            if(num2 != 0)
                cout << num1 << " / " << num2 << " = " << (num1 / num2);
            else
                cout << "Error: Division by zero!";
            break;
        default:
            cout << "Invalid operator!";
    }

    return 0;
}
