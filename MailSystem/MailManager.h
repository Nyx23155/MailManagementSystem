#pragma once
#include "Mail.h"
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

// Alias for filesystem namespace
namespace fs = std::filesystem;

class MailManager
{
public:
    MailManager();
    ~MailManager();

    // Core Functionality
    void addNewMail(int id, const std::string& recipientAddress, int weight, char status);
    void showAllMail() const;
    void getMailById(int id) const;
    void changeMailStatus(int id, char status);
    int getAllMailWeight() const;

    // File I/O
    void saveDataToFile(const std::string& filename) const;
    bool loadDataFromFile(const std::string& filename);

    // Logging & Utilities
    void logData(const std::string& message) const;
    std::string generateLogFilename();
    std::string getCurrentTimestamp();

private:
    std::vector<Mail> mailList;
    std::string logFile;
    bool ensureDirectories();
};