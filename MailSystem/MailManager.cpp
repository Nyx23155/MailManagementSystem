#include "MailManager.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

MailManager::MailManager()
{
    ensureDirectories();
    logFile = generateLogFilename();

    logData("=== SYSTEM STARTED ===");

    if (loadDataFromFile("mail_data.txt")) {
        logData("Data loaded successfully.");
    }
    else {
        logData("No previous data found. Starting empty.");
    }
}

MailManager::~MailManager()
{
    saveDataToFile("mail_data.txt");
    logData("=== SYSTEM SHUTDOWN ===");
}

void MailManager::addNewMail(int id, const string& recipientAddress, int weight, char status)
{
    // 1. Validate ID (Must be positive)
    if (id <= 0) {
        cout << "Error: ID must be positive (>0).\n";
        logData("Failed to add mail: Invalid ID " + to_string(id));
        return;
    }

    // 2. Validate ID (Must be unique)
    for (const auto& mail : mailList)
    {
        if (mail.getId() == id)
        {
            cout << "Error: ID " << id << " is already taken.\n";
            logData("Failed to add mail: ID " + to_string(id) + " duplicate.");
            return;
        }
    }

    // 3. Validate Weight
    if (weight <= 0) {
        cout << "Error: Weight must be positive.\n";
        logData("Failed to add mail: Invalid weight " + to_string(weight));
        return;
    }

    // 4. Validate Status
    if (status != 'D' && status != 'P' && status != 'R') {
        cout << "Error: Invalid status. Use D, P, or R.\n";
        logData("Failed to add mail: Invalid status char.");
        return;
    }

    // Add Mail
    Mail newMail(id, recipientAddress, weight, status);
    mailList.push_back(newMail);

    cout << "New mail added successfully.\n";
    logData("Added Mail ID: " + to_string(id) + " to " + recipientAddress);

    saveDataToFile("mail_data.txt");
}

void MailManager::showAllMail() const
{
    if (mailList.empty()) {
        cout << "Mail list is empty.\n";
        return;
    }

    for (const auto& mail : mailList)
    {
        cout << "ID: " << mail.getId()
            << " | To: " << mail.getRecipientAddress()
            << " | Weight: " << mail.getWeight()
            << " | Status: " << mail.getStatus() << endl;
    }
}

void MailManager::getMailById(int id) const
{
    for (const auto& mail : mailList)
    {
        if (mail.getId() == id)
        {
            cout << "Found: ID: " << mail.getId()
                << ", Recipient: " << mail.getRecipientAddress()
                << ", Weight: " << mail.getWeight()
                << ", Status: " << mail.getStatus() << endl;
            return;
        }
    }
    cout << "Mail with ID " << id << " not found." << endl;
}

void MailManager::changeMailStatus(int id, char status)
{
    if (status != 'D' && status != 'P' && status != 'R') {
        cout << "Error: Invalid status. Use D, P, or R.\n";
        return;
    }

    for (auto& mail : mailList)
    {
        if (mail.getId() == id)
        {
            char oldStatus = mail.getStatus();
            mail.setStatus(status);
            cout << "Mail ID " << id << " status changed: " << oldStatus << " -> " << status << endl;
            logData("Status changed for ID " + to_string(id) + ": " + string(1, status));

            saveDataToFile("mail_data.txt");
            return;
        }
    }
    cout << "Mail with ID " << id << " not found." << endl;
}

int MailManager::getAllMailWeight() const
{
    int totalWeight = 0;
    for (const auto& mail : mailList)
    {
        totalWeight += mail.getWeight();
    }
    return totalWeight;
}

void MailManager::saveDataToFile(const string& filename) const
{
    string path = "saves/" + filename;
    ofstream outFile(path);

    if (!outFile) {
        logData("ERROR: Could not save data to " + path);
        return;
    }

    outFile << "MAILS" << endl;
    outFile << mailList.size() << endl;
    for (const auto& mail : mailList)
    {
        outFile << mail.getId() << " "
            << mail.getRecipientAddress() << " "
            << mail.getWeight() << " "
            << mail.getStatus() << endl;
    }
    outFile.close();
}

bool MailManager::loadDataFromFile(const string& filename)
{
    string path = "saves/" + filename;
    ifstream inFile(path);

    if (!inFile) return false;

    mailList.clear();
    string header;
    int count;

    inFile >> header;
    if (header != "MAILS") return false;

    inFile >> count;
    for (int i = 0; i < count; ++i)
    {
        int id, weight;
        string addr;
        char status;

        inFile >> id >> addr >> weight >> status;
        mailList.emplace_back(id, addr, weight, status);
    }
    return true;
}

void MailManager::logData(const string& message) const
{
    string path = "logs/" + logFile;
    ofstream file(path, ios::app);
    if (file.is_open()) {
        auto now = chrono::system_clock::now();
        time_t time = chrono::system_clock::to_time_t(now);
        struct tm tm;
        localtime_s(&tm, &time);

        file << "[" << put_time(&tm, "%H:%M:%S") << "] " << message << endl;
    }
}

string MailManager::generateLogFilename()
{
    return "mail-session-" + getCurrentTimestamp() + ".log";
}

string MailManager::getCurrentTimestamp()
{
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    struct tm tm;
    localtime_s(&tm, &time);
    stringstream ss;
    ss << put_time(&tm, "%Y-%m-%d__%H-%M-%S");
    return ss.str();
}

bool MailManager::ensureDirectories()
{
    try {
        if (!fs::exists("logs")) fs::create_directory("logs");
        if (!fs::exists("saves")) fs::create_directory("saves");
        return true;
    }
    catch (...) { return false; }
}