#include "passserver.h"
#include <iostream>
#include <string>
#include <utility>

void Menu();

int main() {
    size_t tableSize;
    std::cout << "Enter the initial hash table size: ";
    std::cin >> tableSize;

    PassServer ps(tableSize); // Initialize the PassServer object

    char choice;
    std::string username, password, newpassword;
    std::string filename;

    do {
        Menu();
        std::cin >> choice;
        choice = tolower(choice); // Normalize input to lowercase
        std::cin.ignore();        // Clear the input buffer

        switch (choice) {
            case 'l': // Load from file
                std::cout << "Enter password file name to load: ";
                std::cin >> filename;
                if (ps.load(filename.c_str())) {
                    std::cout << "Passwords loaded successfully.\n";
                } else {
                    std::cout << "Error: Unable to load file.\n";
                }
                break;

            case 'a': // Add user
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (ps.addUser({username, password})) {
                    std::cout << "User added successfully.\n";
                } else {
                    std::cout << "Error: User already exists.\n";
                }
                break;

            case 'r': // Remove user
                std::cout << "Enter username to remove: ";
                std::cin >> username;
                if (ps.removeUser(username)) {
                    std::cout << "User removed successfully.\n";
                } else {
                    std::cout << "Error: User not found.\n";
                }
                break;

            case 'c': // Change user password
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter current password: ";
                std::cin >> password;
                std::cout << "Enter new password: ";
                std::cin >> newpassword;
                if (ps.changePassword({username, password}, newpassword)) {
                    std::cout << "Password changed successfully.\n";
                } else {
                    std::cout << "Error: Unable to change password. Ensure the user exists and the current password is correct.\n";
                }
                break;

            case 'f': // Find user
                std::cout << "Enter username to find: ";
                std::cin >> username;
                if (ps.find(username)) {
                    std::cout << "User found.\n";
                } else {
                    std::cout << "User not found.\n";
                }
                break;

            case 'd': // Dump hash table
                ps.dump();
                break;

            case 's': // Hash table size
                std::cout << "HashTable size: " << ps.size() << "\n";
                break;

            case 'w': // Write to file
                std::cout << "Enter password file name to write to: ";
                std::cin >> filename;
                if (ps.write_to_file(filename.c_str())) {
                    std::cout << "Passwords written successfully.\n";
                } else {
                    std::cout << "Error: Unable to write to file.\n";
                }
                break;

            case 'x': // Exit program
                std::cout << "Exiting program...\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != 'x');

    return 0;
}

void Menu() {
    std::cout << "\n\n";
    std::cout << "l - Load From File" << std::endl;
    std::cout << "a - Add User" << std::endl;
    std::cout << "r - Remove User" << std::endl;
    std::cout << "c - Change User Password" << std::endl;
    std::cout << "f - Find User" << std::endl;
    std::cout << "d - Dump HashTable" << std::endl;
    std::cout << "s - HashTable Size" << std::endl;
    std::cout << "w - Write to Password File" << std::endl;
    std::cout << "x - Exit program" << std::endl;
    std::cout << "\nEnter choice : ";
}

