# 📦 Mail Management System (C++)

A console-based simulation of a postal service management system developed in C++. This project demonstrates Object-Oriented Programming (OOP), file handling, and data validation.

## 📝 Description
The Mail Management System allows users to process mail items, track their status, and manage a database of shipments. It includes robust input validation and an automatic logging system to track all operations.

## ✨ Features
* **Mail Processing**: Add new mail with unique IDs, recipient addresses, and weight.
* **Status Tracking**: Update delivery status (Pending, Delivered, Returned).
* **Search System**: Find mail details quickly by ID.
* **Analytics**: Calculate the total weight of all mail in the system.
* **Data Persistence**: All data is automatically saved to `saves/mail_data.txt`.
* **Logging**: Comprehensive logs of every action (success or error) are stored in the `logs/` directory.

## 🛠️ Technical Details
* **Language**: C++
* **Paradigm**: OOP (Classes, Encapsulation)
* **Storage**: Custom text-based database.
* **Safety**: Input validation (prevents negative weights, duplicate IDs, invalid statuses).

## 🚀 How to Run
1.  Clone the repository.
2.  Open the project in **Visual Studio**.
3.  Build and Run (Ctrl + F5).
4.  The application will automatically create `logs/` and `saves/` directories upon first launch.

## 📂 Project Structure
* `main.cpp` - Entry point and user interface menu.
* `MailManager` - Controller class that handles logic and file I/O.
* `Mail` - Data class representing a single mail item.

---
*Created for educational purposes.*
