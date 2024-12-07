#include "passserver.h"
#include <crypt.h>  // For crypt()
#include <fstream>
#include <sstream>
#include <iostream>

//------------------------------------------------
// ========== Constructors & Destructors =========
//------------------------------------------------

// Constructor, create a hash table of the specified size. You just need to pass this size parameter to the constructor of the HashTable. 
// Therefore, the real hash table size could be different from the parameter size (because prime_below() will be called in the constructor 
// of the HashTable).
PassServer::PassServer(size_t size) : hashTable(size) {}

// Destructor. You need to decide what you should do based on your design of PassServer (how you develop the adaptor class based on the 
// adaptee HashTable). In essence, we do not want to have memory leak.
PassServer::~PassServer() {}

//------------------------------------------------
// =========== Public Member functions ===========
//------------------------------------------------

// Load a password file into the HashTable object. Each line contains a pair of username and encrypted password.
bool PassServer::load(const char* filename) {
    return hashTable.load(filename);    // Return true if file is loaded successfully, false otherwise
}

// Add a new username and password.  The password passed in is in plaintext, it should be encrypted before insertion. The pair should 
// not be added if the username already exists in the hash table.
bool PassServer::addUser(std::pair<std::string, std::string>& kv) {
    kv.second = encrypt(kv.second);  // Encrypt the password
    return hashTable.insert(kv);    // True if the user is added successfully, false otherwise (e.g., user already exists)
}

// Move version of addUser
bool PassServer::addUser(std::pair<std::string, std::string>&& kv) {
    kv.second = encrypt(kv.second);  // Encrypt the password
    return hashTable.insert(std::move(kv)); // True if the user is added successfully, false otherwise (e.g., user already exists)
}

// Delete an existing user with username k.
bool PassServer::removeUser(const std::string& k) {
    return hashTable.remove(k); // True if the user is removed successfully, false otherwise.
}

// Change an existing user's password. Note that both passwords passed in are in plaintext. They should be encrypted before you 
// interact with the hash table. If the user is not in the hash table, return false. If p.second does not match the current password, 
// return false. Also return false if the new password and the old password are the same (i.e., we cannot update the password).
bool PassServer::changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword) {
    if (newpassword == p.second) {
        return false;  // New password is the same as the current password
    }

    auto encryptedOldPassword = encrypt(p.second);
    auto encryptedNewPassword = encrypt(newpassword);

    // Verify that the username and old password match
    if (!hashTable.match({p.first, encryptedOldPassword})) {
        return false;
    }

    // Update the password
    return hashTable.insert({p.first, encryptedNewPassword});
}

// Check if a user exists (if user is in the hash table).
bool PassServer::find(const std::string& user) const {
    return hashTable.contains(user);
}

// Show the structure and contents of the HashTable object to the screen. Same format as the dump() function in the HashTable class template.
void PassServer::dump() const {
    hashTable.dump();
}

// Return the size of the HashTable (the number of username/password pairs in the table).
size_t PassServer::size() const {
    return hashTable.size();
}

// Save the username and password combination into a file. Same format as the write_to_file() function in the HashTable class template.
bool PassServer::write_to_file(const char* filename) const {
    return hashTable.write_to_file(filename);
}

//------------------------------------------------
// =========== Private Member functions ==========
//------------------------------------------------

// Encrypt the parameter str and return the encrypted string.
// Use the crypt() method to enctrypt the password, which should be MD5-based
std::string PassServer::encrypt(const std::string& str) {
    char salt[] = "$1$########";  // Predefined salt
    char* encrypted = crypt(str.c_str(), salt);
    if (encrypted == nullptr) {
        throw std::runtime_error("Encryption failed");
    }

    std::string encryptedStr(encrypted);

    // Extract the password substring after the third '$'
    size_t pos = encryptedStr.rfind('$');
    if (pos != std::string::npos) {
        return encryptedStr.substr(pos + 1);
    }

    return encryptedStr;  // Fallback if structure doesn't match (shouldn't happen)
}