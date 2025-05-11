# Student Information Console App

This is a simple **Student Information System** developed in C that runs in the terminal. It allows basic operations like class management, student record handling, and password-protected access.

## 🚀 Features

- 🔐 Login system with basic password encryption(Caesar Cipher)
- 📜 List all class files
- 👨‍🏫 Read student data from a class
- ➕ Create a new class
- ❌ Delete an existing class
- 🔎 Search for a student by ID
- 🔑 Change the login password

## 📂 File Structure

Each class is stored as a `.txt` file named after the class.  
Each student record is stored in the following format:

## 🔒 Password System
The password is stored encrypted in a file named AccountInfo.txt.

A basic Caesar cipher is used for encryption, based on the sum of digits in the password.(Actually,You have to user number)

## Shortcomings
I tried to edit student data but it is complicate with c language and I couldn't.
Password system needed to be fixed.


## 📌 Notes
Use lowercase letters when entering passwords.

Ensure AccountInfo.txt exists before launching the program.
  
Only .txt files (excluding AccountInfo.txt) are treated as class files.
