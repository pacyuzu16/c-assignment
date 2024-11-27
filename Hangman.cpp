#include <iostream>
#include <vector> // dynamic array that can change size as needed. 
#include <string>
#include <cstdlib> // random number generation 
#include <ctime> // for working with time and date,
#include <cctype> // for manipulation of characters
#include <unordered_set> // For storing unique items in an unordered collection, making lookups faster.

using namespace std;

// Function declarations
void displayInstructions();
string selectRandomWord(const vector<string>& wordList);  // Function to select a random word
void displayState(const string& word, const string& guessedWord, const unordered_set<char>& incorrectGuesses, int guessesLeft);  // Display current game state
bool isWordGuessed(const string& word, const string& guessedWord);  // Check if the word is fully guessed
char getValidatedGuess(const unordered_set<char>& guessedLetters);  // Get a valid letter guess from the user
void playHangman();  // Main function to handle game flow

int main() {
    displayInstructions();
    char playAgain;
    do {
        playHangman();  // Call the game function to start a game
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        playAgain = tolower(playAgain);  // Convert input to lowercase
    } while (playAgain == 'y');  // Continue playing if the user enters 'y'
    return 0;
}

// Function to select a random word from the list
string selectRandomWord(const vector<string>& wordList) {
    srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator with current time
    int randomIndex = rand() % wordList.size();  // Select a random index within the word list
    return wordList[randomIndex];  // Return the word at the random index
}

// Function to display the current game state
void displayState(const string& word, const string& guessedWord, const unordered_set<char>& incorrectGuesses, int guessesLeft) {
    cout << "\nWord: ";
    for (char c : guessedWord) {  // Display the guessed word with spaces between letters
        cout << c << " ";
    }
    cout << "\nIncorrect Guesses: ";
    for (char c : incorrectGuesses) {  // Display the incorrect guesses so far
        cout << c << " ";
    }
    cout << "\nGuesses Left: " << guessesLeft << "\n";  // Show how many guesses are left
}

// Function to check if the word has been guessed
bool isWordGuessed(const string& word, const string& guessedWord) {
    return word == guessedWord;  // Return true if the word and guessed word are identical
}

// Function to get a validated guess from the user
char getValidatedGuess(const unordered_set<char>& guessedLetters) {
    char guess;
    while (true) {
        cout << "Guess a letter: ";
        cin >> guess;
        guess = tolower(guess);  // Convert the guess to lowercase

        // Check if the input is a valid letter
        if (!isalpha(guess)) {
            cout << "Invalid input. Please enter a single letter.\n";
            continue;  // Ask for a new guess if the input is invalid
        }

        // Check if the letter has already been guessed
        if (guessedLetters.find(guess) != guessedLetters.end()) {
            cout << "You've already guessed that letter. Try again.\n";
            continue;  // Ask for a new guess if the letter was already guessed
        }

        return guess;  // Return the valid letter guess
    }
}

// Function to play the Hangman game
void playHangman() {
    // Predefined list of words for the game
    vector<string> wordList = {"teacher", "programming", "hangman", "difficulty", "keyboard", "developer", "algorithm"};
    string word = selectRandomWord(wordList);  // Select a random word from the list
    string guessedWord(word.size(), '_');  // Initialize the guessed word as all underscores
    unordered_set<char> incorrectGuesses;  // Set to keep track of incorrect guesses
    unordered_set<char> guessedLetters;  // Set to keep track of all guessed letters (correct or incorrect)

    int maxGuesses = 6;  // Maximum number of incorrect guesses allowed
    int guessesLeft = maxGuesses;  // Initialize the number of guesses left

    while (guessesLeft > 0) {
        displayState(word, guessedWord, incorrectGuesses, guessesLeft);  // Display the current game state

        // Get a valid guess from the user
        char guess = getValidatedGuess(guessedLetters);
        guessedLetters.insert(guess);  // Add the guessed letter to the set of guessed letters

        // Check if the guessed letter is in the word
        bool correct = false;
        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == guess) {
                guessedWord[i] = guess;  // Reveal the guessed letter in the guessed word
                correct = true;  // Mark that the guess was correct
            }
        }

        if (correct) {
            cout << "Good guess!\n";
            if (isWordGuessed(word, guessedWord)) {  // Check if the word has been fully guessed
                displayState(word, guessedWord, incorrectGuesses, guessesLeft);  // Display the final state
                cout << "Congratulations! You guessed the word \"" << word << "\" correctly!\n";
                return;  // End the game after guessing the word correctly
            }
        } else {
            cout << "Incorrect guess.\n";
            incorrectGuesses.insert(guess);  // Add the incorrect guess to the set of incorrect guesses
            --guessesLeft;  // Decrease the number of guesses left
        }
    }

    cout << "Sorry, you've run out of guesses. The correct word was \"" << word << "\".\n";  // Display the correct word if the player loses
}
void displayInstructions() {
    cout << "Welcome to Hangman!" << endl;
    cout << "How to play:" << endl;
    cout << "- Guess the word one letter at a time." << endl;
    cout << "- Correct guesses reveal the letter in the word." << endl;
    cout << "- Wrong guesses cost you a life." << endl;
    cout << "- You have a limited number of lives, so choose wisely!" << endl;
    cout << "- The game ends when you guess the word or lose all your lives." << endl<<endl;
    cout << "Good luck!" << endl;
}