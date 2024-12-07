#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"
#include <string>
#include <utility> // for std::pair

class PassServer {
public:
    /**
     * @brief Constructor to initialize the PassServer with a specified hash table size.
     * @param size Initial size of the hash table (will be adjusted to the nearest prime).
     */
    PassServer(size_t size = 101);

    /**
     * @brief Destructor to clean up the PassServer.
     */
    ~PassServer();

    /**
     * @brief Load the contents of a password file into the hash table.
     * @param filename Name of the file containing username-password pairs.
     * @return True if the file is loaded successfully, false otherwise.
     */
    bool load(const char* filename);

    /**
     * @brief Add a new user to the hash table.
     * @param kv A pair of username (key) and plaintext password (value).
     * @return True if the user is added successfully, false otherwise (e.g., user already exists).
     */
    bool addUser(std::pair<std::string, std::string>& kv);

    /**
     * @brief Add a new user to the hash table (move version).
     * @param kv A pair of username (key) and plaintext password (value).
     * @return True if the user is added successfully, false otherwise (e.g., user already exists).
     */
    bool addUser(std::pair<std::string, std::string>&& kv);

    /**
     * @brief Remove an existing user from the hash table.
     * @param k Username (key) to remove.
     * @return True if the user is removed successfully, false otherwise.
     */
    bool removeUser(const std::string& k);

    /**
     * @brief Change the password for an existing user.
     * @param p A pair of username (key) and current plaintext password (value).
     * @param newpassword New plaintext password to set.
     * @return True if the password is changed successfully, false otherwise.
     */
    bool changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword);

    /**
     * @brief Check if a user exists in the hash table.
     * @param user Username (key) to check.
     * @return True if the user exists, false otherwise.
     */
    bool find(const std::string& user) const;

    /**
     * @brief Display the contents of the hash table to the screen.
     */
    void dump() const;

    /**
     * @brief Get the number of username-password pairs in the hash table.
     * @return The size of the hash table.
     */
    size_t size() const;

    /**
     * @brief Save the username-password pairs to a file.
     * @param filename Name of the file to save the contents to.
     * @return True if the contents are saved successfully, false otherwise.
     */
    bool write_to_file(const char* filename) const;

private:
    /**
     * @brief Encrypt a plaintext password using MD5-based crypt() with a predefined salt.
     * @param str Plaintext password to encrypt.
     * @return The encrypted password.
     */
    std::string encrypt(const std::string& str);

    // HashTable object to store username-password pairs (both as strings).
    cop4530::HashTable<std::string, std::string> hashTable;
};

#endif
