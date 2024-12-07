#include "passserver.h"
#include <crypt.h>  // For crypt()
#include <fstream>
#include <sstream>
#include <iostream>

PassServer::PassServer(size_t size) : hashTable(size) {}

PassServer::~PassServer() {}

// Load the contents of a file into the hash table
bool PassServer::load(const char* filename) {
    return hashTable.load(filename);
}

// Add a new user with plaintext password
bool PassServer::addUser(std::pair<std::string, std::string>& kv) {
    kv.second = encrypt(kv.second);  // Encrypt the password
    return hashTable.insert(kv);
}

// Move version of addUser
bool PassServer::addUser(std::pair<std::string, std::string>&& kv) {
    kv.second = encrypt(kv.second);  // Encrypt the password
    return hashTable.insert(std::move(kv));
}

// Remove a user
bool PassServer::removeUser(const std::string& k) {
    return hashTable.remove(k);
}

// Change the password for an existing user
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

// Check if a user exists
bool PassServer::find(const std::string& user) const {
    return hashTable.contains(user);
}

// Dump the hash table's structure and contents
void PassServer::dump() const {
    hashTable.dump();
}

// Get the size of the hash table
size_t PassServer::size() const {
    return hashTable.size();
}

// Save the hash table contents to a file
bool PassServer::write_to_file(const char* filename) const {
    return hashTable.write_to_file(filename);
}

// Encrypt a plaintext password using MD5-based crypt() with a predefined salt
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
