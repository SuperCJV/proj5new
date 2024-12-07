#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"
#include <string>
#include <utility> // for std::pair

class PassServer {
public:
    PassServer(size_t size = 101);  // Constructor
    ~PassServer();  // Destructor
    bool load(const char* filename);    // Load a password file into the HashTable object
    bool addUser(std::pair<std::string, std::string>& kv);  // Add a new username and password
    bool addUser(std::pair<std::string, std::string>&& kv); // Move version of addUser
    bool removeUser(const std::string& k);  // Delete an existing user with username k
    bool changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword);  // Change an existing user's password
    bool find(const std::string& user) const;   // Check if a user exists
    void dump() const;  // Show the structure and contents of the HashTable object to the screen
    size_t size() const;    // Return the size of the HashTable
    bool write_to_file(const char* filename) const; // Save the username and password combination into a file

private:
    std::string encrypt(const std::string& str);    // Encrypt the parameter str and return the encrypted string

    // HashTable object to store username-password pairs (both as strings).
    cop4530::HashTable<std::string, std::string> hashTable;
};

#endif