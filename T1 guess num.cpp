#include <iostream>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time()

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate a random number between 1 and 100
    int secretNumber = std::rand() % 100 + 1;
    int guess = 0;
    int attempts = 0;

    std::cout << "Welcome to the Number Guessing Game!\n";
    std::cout << "I have selected a number between 1 and 100.\n";
    std::cout << "Can you guess it?\n";

    // Main guessing loop
    do {
        std::cout << "Enter your guess: ";
        std::cin >> guess;
        attempts++;

        if (guess > secretNumber) {
            std::cout << "Try smaller than " << guess << ".\n";
        } else if (guess < secretNumber) {
            std::cout << "Try bigger than " << guess << ".\n";
        } else {
            std::cout << "Congratulations! You guessed the number in " << attempts << " attempts.\n";
        }
    } while (guess != secretNumber);

    return 0;
}
