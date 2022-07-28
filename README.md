# Library-Kiosk

What if there was a Kiosk setup in our library instead of a librarian? A simple machine with a dedicated software for our own college.
This project is made by keeping in mind all the necessary functions and the duties of a human librarian in the library. It has been made with  
the purpose of automating the tasks in library and making them more efficient, faster and leaving lesser possibilities for errors.

It has three main classes, Student, Teacher and the Admin, which represent the different entities that will be interacting with the program.
The three classes exhibit multilevel inheritance, with student being the base class, teacher class inherits from student class and admin class 
inherits from teacher class. 

Thus our admin can access all public/private attributes and methods of both student and teacher class and vice versa is not possible.
The program makes directories in C drive of the computer and stores all data in the form of files. Also this program works with a custom 
header file "bookManagement.h" which contains all the operations that we can perform on books and the database. 

::::::READ THESE BEFORE RUNNING THE PROGRAM::::::

**Before issuing the books, you need to enter books in the database by logging in as admin, or just copy the files provided in the books folder 
into the bookdata folder created in C:/Library Kiosk/bookdata folder . 

**The program creates a default admin the first time it runs, 
->Username-123456
->Password-123456, Login using these credentials to add more admins

For a detailed report of the project, visit the link:  
https://linktr.ee/libraryKiosk

Credits: 
Name:       Charan Kamal Singh
Roll No:    CO21314
Branch:     CSE

Submitted to - Sarabjit Sir
