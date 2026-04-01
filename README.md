# 🎓 Student Management System (C++ + MySQL)

## 📌 Description
This is a console-based Student Management System developed using C++ (Object-Oriented Programming) and MySQL Database.
The project allows users to manage student records with full CRUD operations and authentication system.

## 🚀 Features
- Add Student Record
- Search Student by ID
- Update Student Record
- Delete Student Record
- Show All Students
- Count Total Students
- Login & Signup System
- Forgot Password
- Strong Password Validation

## 🛠️ Technologies Used
- C++
- MySQL
- MySQL C API (mysql.h)

## ⚙️ How to Run

Step 1: Create Database in MySQL
CREATE DATABASE school;
USE school;

CREATE TABLE student(
id INT PRIMARY KEY,
name VARCHAR(50),
grade VARCHAR(10),
percentage FLOAT
);

CREATE TABLE admin(
username VARCHAR(50),
password VARCHAR(50)
);

Step 2: Compile Code
g++ yourfile.cpp -o project -I"C:\Program Files\MySQL\MySQL Server 8.0\include" -L"C:\Program Files\MySQL\MySQL Server 8.0\lib" -lmysql

Step 3: Run Program
./project

## 📚 Learning Outcome
- Learned C++ OOP concepts
- Learned MySQL database integration
- Built CRUD system
- Implemented login system

## 🚧 Future Improvements
- GUI version
- Password hashing
- Better UI

## 🙌 Author
Owais Khan

## ⭐ Give a Star
If you like this project, give it a star!
