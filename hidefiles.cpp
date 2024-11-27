#include <iostream>
#include <fstream> // is essential for file operations (reading and writing) in C++.
#include <string>
#include <filesystem> // For filesystem operations such as checking file existence and renaming
using namespace std;
namespace fs = std::filesystem; // Alias for the filesystem namespace to simplify code

// Function to hide a file
void hideFile(const string& filePath) {
    // Check if the file exists
    if (!fs::exists(filePath)) { // fs::exists checks if the file path points to an existing file
        cerr << "Error: File does not exist.\n";
        return; // Exit the function if the file doesn't exist
    }

#ifdef _WIN32 // Preprocessor directive for Windows-specific code
    // Windows: Use the `attrib` command to set the file as hidden
    string command = "attrib +h \"" + filePath + "\""; // Construct the command with quotes around the file path
    if (system(command.c_str()) == 0) { // Execute the command and check if it succeeds
        cout << "File hidden successfully.\n";
    } else {
        cerr << "Error hiding the file.\n";
    }
#else // Linux/macOS-specific code
    // On Linux/macOS, a file is considered hidden if its name starts with a dot (.)
    string newFileName = "." + filePath; // Prepend a dot to the file name to hide it
    fs::rename(filePath, newFileName);  // Rename the file using the filesystem library
    cout << "File hidden successfully as " << newFileName << ".\n";
#endif
}

// Function to unhide a file
void unhideFile(const string& filePath) {
    // Check if the file exists
    if (!fs::exists(filePath)) { // Ensure the file exists before attempting to unhide it
        cerr << "Error: File does not exist.\n";
        return; // Exit the function if the file doesn't exist
    }

#ifdef _WIN32 // Preprocessor directive for Windows-specific code
    // Windows: Use the `attrib` command to remove the hidden attribute
    string command = "attrib -h \"" + filePath + "\""; // Construct the command to remove the hidden attribute
    if (system(command.c_str()) == 0) { // Execute the command and check if it succeeds
        cout << "File unhidden successfully.\n";
    } else {
        cerr << "Error unhiding the file.\n";
    }
#else // Linux/macOS-specific code
    // On Linux/macOS, remove the dot prefix to unhide the file
    if (filePath[0] == '.') { // Check if the file name starts with a dot
        string newFileName = filePath.substr(1); // Remove the first character (dot) from the file name
        fs::rename(filePath, newFileName); // Rename the file using the filesystem library
        cout << "File unhidden successfully as " << newFileName << ".\n";
    } else {
        cerr << "Error: File is not hidden.\n"; // File does not appear to be hidden (no dot prefix)
    }
#endif
}

int main() {
    try {
        // Display the menu to the user
        cout << "File Hide/Unhide Utility\n";
        cout << "1. Hide a file\n";   // Option to hide a file
        cout << "2. Unhide a file\n"; // Option to unhide a file
        cout << "Choose an option (1 or 2): ";
        int choice;
        cin >> choice; // Take user input for the choice

        // Prompt the user for the file path
        cout << "Enter the file path: ";
        string filePath;
        cin >> filePath; // Take user input for the file path

        // Perform the appropriate action based on the user's choice
        if (choice == 1) {
            hideFile(filePath); // Call hideFile to hide the specified file
        } else if (choice == 2) {
            unhideFile(filePath); // Call unhideFile to unhide the specified file
        } else {
            cerr << "Invalid choice.\n"; // Handle invalid user input
        }
    } catch (const exception& e) {
        // Catch and display any exceptions that occur during execution
        cerr << "Error: " << e.what() << "\n";
    }

    return 0; // Return 0 to indicate successful execution
}
