#include <iostream>
#include "MailManager.h"

using namespace std;

int main()
{
    MailManager mailManager;
    int choice;

    while (true)
    {
        cout << "\n=== MAIL MANAGEMENT SYSTEM ===\n";
        cout << "1. Show all mail\n";
        cout << "2. Add new mail\n";
        cout << "3. Find mail by ID\n";
        cout << "4. Change mail status\n";
        cout << "5. Get total mail weight\n";
        cout << "0. Exit\n";
        cout << "Select action: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1)
        {
            cout << "\n--- Mail List ---\n";
            mailManager.showAllMail();
        }
        else if (choice == 2)
        {
            int id, weight;
            string recipientAddress;
            char status;

            cout << "Enter mail ID: "; cin >> id;
            cout << "Enter recipient address (no_spaces): "; cin >> recipientAddress;
            cout << "Enter weight: "; cin >> weight;
            cout << "Enter status (D/P/R): "; cin >> status;

            // Convert char to uppercase
            status = toupper(status);

            mailManager.addNewMail(id, recipientAddress, weight, status);
        }
        else if (choice == 3)
        {
            int id;
            cout << "Enter mail ID to search: "; cin >> id;
            mailManager.getMailById(id);
        }
        else if (choice == 4)
        {
            int id;
            char status;
            cout << "Enter mail ID: "; cin >> id;
            cout << "Enter new status (D/P/R): "; cin >> status;
            mailManager.changeMailStatus(id, toupper(status));
        }
        else if (choice == 5)
        {
            cout << "Total weight: " << mailManager.getAllMailWeight() << " kg\n";
        }
        else if (choice == 0)
        {
            cout << "Saving data and exiting...\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}