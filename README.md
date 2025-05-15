# Library Management System

##  Overview of the System
This application has been developed as part of the **CS253** course assignments offered in the **2024-25-II Semester**. The entire application is implemented in **C++**, utilizing **Object-Oriented Programming (OOP)** principles. **Database management** is handled using **C++ file handling**, and all interactions with the application are conducted via the **terminal**.

##  Basic Structure of the Application
The system maintains 4 primary databases: **student.txt**,**faculty.txt**,**Librarian.txt** and **books.txt**.

###  `student.txt`
Each entry consists of a `Username`, `Password`,`User ID`, `Outstanding Fine Amount`. It also includes the `Number of Previously Borrowed Books` along with their `ISBN`. Then it has`ISBN  of currently Borrowed Books`
###  `Faculty.txt`
Each entry consists of a `Username`, `Password`,`User ID`, `Outstanding Fine Amount` which is zero throughout. It also includes the `Number of Previously Borrowed Books` along with their `ISBN`. Then it has`ISBN  of  currently Borrowed Books`
###  `Faculty.txt`
Each entry consists of a `Username`, `Password`,`User ID'

###  `books.txt`
This file stores details about books, including `Title`,`ISBN`, `Author`, `Publisher`, `Year of Publication`, `Status` (Available , Borrowed and reserved), `Last Borrowed Date`and `Current Borrower Username` (if borrowed).

This structured approach ensures efficient tracking of users and books within the **Library Management System**.

## Features and Functionalities
- **Students and Faculty** can search for a book, borrow a book, return a book. Students can also pay fines.
- **Librarians** can search for a book/user, add a book/user, delete a book/user, update book details, and update details of users.
- All users have unique usernames so usernames have been used as IDs for the users.
- All books have unique ISBNs and are stored with a single copy in the system, so ISBNs are used as IDs for the books.

## Usage

Compile the code using `g++ compiler`:

    `g++ main.cpp -o main`
Then run the code by using :
    
    `./main`
