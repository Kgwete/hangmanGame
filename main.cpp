#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

class HangmanGame 
{
public:
    HangmanGame();
    void play();

private:
    std::string getRandomWord();
    void displayWord();
    bool isGameWon();
    bool isGameOver();
    void processGuess(char guess);

    std::string secretWord;
    std::string guessedWord;
    int maxIncorrectAttempts;
    int remainingAttempts;
    int incorrectAttempts;
    std::vector<char> incorrectGuesses;
};

HangmanGame::HangmanGame() : maxIncorrectAttempts(2), remainingAttempts(6), incorrectAttempts(0) 
{
    secretWord = getRandomWord();
    guessedWord = std::string(secretWord.length(), '_');
}

std::string HangmanGame::getRandomWord() 
{
   
    std::vector<std::string> words = {"hangman", "programming", "cplusplus", "challenge", "developer"};
    
    std::srand(std::time(0));
    return words[std::rand() % words.size()];
}

void HangmanGame::displayWord() 
{
    for (char letter : guessedWord) {
        std::cout << letter << ' ';
    }
    std::cout << std::endl;
}

bool HangmanGame::isGameWon() 
{
    return guessedWord == secretWord;
}

bool HangmanGame::isGameOver() 
{
    return remainingAttempts <= 0 || isGameWon();
}

void HangmanGame::processGuess(char guess) 
{
    bool correctGuess = false;

    for (size_t i = 0; i < secretWord.length(); ++i) {
        if (secretWord[i] == guess) {
            guessedWord[i] = guess;
            correctGuess = true;
        }
    }

    if (!correctGuess) {
        incorrectGuesses.push_back(guess);
        ++incorrectAttempts;

        std::cout << "Incorrect guess! Attempts remaining: " << remainingAttempts << "\n";
        std::cout << "Incorrect guesses: ";
        for (char letter : incorrectGuesses) {
            std::cout << letter << ' ';
        }
        std::cout << "\n\n";

        if (incorrectAttempts >= maxIncorrectAttempts) {
            --remainingAttempts;
            std::cout << "Maximum incorrect attempts reached. Game over! The word was: " << secretWord << "\n";
        } else {
            std::cout << "Try again!\n\n";
        }
    }
}

void HangmanGame::play()
{
    std::cout << "Welcome to Hangman!\n";
    
    while (!isGameOver()) {
        std::cout << "Attempts remaining: " << remainingAttempts << "\nIncorrect guesses: ";
        for (char letter : incorrectGuesses) {
            std::cout << letter << ' ';
        }
        std::cout << "\n\n";
        
        displayWord();

        char guess;
        std::cout << "Enter your guess: ";
        std::cin >> guess;

        processGuess(guess);
        std::cout << "\n------------------------\n";
    }

    if (isGameWon()) {
        std::cout << "Congratulations! You guessed the word: " << secretWord << "\n";
    } else {
        std::cout << "Game over! The word was: " << secretWord << "\n";
    }
}

int main() 
{
    HangmanGame hangman;
    hangman.play();

    return 0;
}
