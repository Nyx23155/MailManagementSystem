#pragma once
#include <string>
#include <iostream>

class Mail
{
public:
    Mail() {}
    ~Mail() {}

    // Constructor for easy initialization
    Mail(int id, std::string addr, int w, char s)
        : id(id), recipientAddress(addr), weight(w), status(s)
    {
    }

    // Getters
    int getId() const { return id; }
    std::string getRecipientAddress() const { return recipientAddress; }
    int getWeight() const { return weight; }
    char getStatus() const { return status; }

    // Setters
    void setId(int value) { id = value; }
    void setRecipientAddress(const std::string& value) { recipientAddress = value; }
    void setWeight(int value) { weight = value; }
    void setStatus(char value) { status = value; }

private:
    int id;
    std::string recipientAddress;
    int weight;
    char status; // D - Delivered, P - Pending, R - Returned
};