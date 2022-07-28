/*  

------------------------------------------------------LIBRARY KIOSK--------------------------------------------------------------------------

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

*/  

#include<ctime> //////////for time funtionality for calculating fine
#include<unistd.h>  /////////for sleep function
#include<iostream>
#include<string.h>
#include<fstream>
#include<ios>    //used to get stream size
#include<limits> //used to get numeric limits   //// for solving cin buffer issue
#include<conio.h>   //// for getch() function (for password entering)
#include<math.h>
#include<sys/stat.h>    /////for opening directories
#include"bookManagement.h"  ///custom header file with book class

const int studBookLimit = 3;    /////// number of books the student can issue at one time
const int teachBookLimit = 5;   /////// number of books the teacher can issue at one time 
int adminFlag = 0;        /////// admin flag

using namespace std;

class student   {

    int rollNum;
    char *name;
    string password;
    int Branch,year;

    public:
    
    student()   {
        name = new char[20];
    }

    void studentBegin();
    void setRollNum(int RollNum);
    int getRollNum();
    void setName(char Name[20]);
    string getName();
    int Login();
    int Register();
    void credentials();
    void yearAndBranchFinder();
    void bookManagement(string* rnum, int bookLimit);

};

class teacher : public student {
    
    int teachID;
    char *name;
    string password;
    
    public:

    teacher()   {
        name = new char[20];
    }

    void teacherBegin();
    void getname();
    string getid();
    void idcheck();
    int Login();
    int Register();

};

class admin : public teacher {
    
    char* name;
    int adminID;
    string password;
    

    public:

    admin() {
        name = new char[20];
        mkdir("C:/Library Kiosk/adminData/123456");
        ofstream ofs("C:/Library Kiosk/adminData/123456/123456.txt");
        ofs << "123456" << endl << "123456";
        ofs.close();
    }

    void adminConsole();
    int Login();
    int Register();

};

void student :: studentBegin()  {
    
    system("cls");

    int flag=1;

            int loginOption;
            while(flag != 0) {   ///////taking student login and input
            cin.ignore();
            cout << "\n\t\t\t\t\t\tSelect one option:\n\t\t\t\t\t\t1. Login\n\t\t\t\t\t\t2. Register\n\t\t\t\t\t\tYour choice: ";
            cin >> loginOption;
            try {
                if (loginOption == 1 || loginOption == 2)   {
                    if (loginOption == 1)   {
                        flag = 0;
                        Login();

                    }
                    else    {
                        flag = 0;
                        Register();

                    }
                }

                else{
                    throw(loginOption);
                }
            }
            catch(int a) {
                cout << "\n\t\t\t\t\t\t::Choose only from options given above::\n";
                //loginOption = 1;
            }
        }

}

int student :: Login() {
        int flag=1;
        char c;
        while(flag != 0)    {
            cout << "\n\t\t\t\t\t\tEnter your 5 digit roll number: ";
            cin >> rollNum;
            if (rollNum <= 99999 && rollNum >= 10000)   {                       /////// roll num check
                yearAndBranchFinder();                                          ///checking the year, confirms the vaidity of the roll num
                if (Branch >0 && Branch <5) {
                flag = 0;
                cout << "\n\t\t\t\t\t\tEnter your password: ";
            while(c != '\r') //////////Loop until 'Enter' is pressed
            {
            c = getch();
            if(c == 0)
            {
            switch(getch())
               {
               default:
                  break;            
               };
            }
            else if(c == '\b')   /////If the 'Backspace' key is pressed
            {
            if(password.size() != 0)  //////If the password string contains data, erase last character
               {
               cout << "\b \b";
               password.erase(password.size() - 1, 1);
               }
            continue;
            }
            else if(c <= '9' && c >= '0' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')  //If user enters 1-9, a-z, or A-Z, add it to the password and display an asterisk
            {
            password += c;
            cout << "*";
            }
            else
            continue;
            }
            string rollnum;
            string pass;
            string rnum = to_string(rollNum);

            string directory;
            directory = "C:/Library Kiosk/studentData/" + rnum;

            ifstream readFile(directory + "/" + rnum + ".txt");   ////////////  opening the file ///// reading from the student database ///opening athe file in the studnet folder

            if (readFile.is_open()) {           ////// checking ro see if the file is openend
            getline(readFile, rollnum);
            getline(readFile, pass);

            if (rnum == rollnum && pass == password) {      
                cout << "\n\t\t\t\t\t\tSuccessful Login";
                sleep(1);
                system("cls");
                cout << "\n\t\t\t\t\t\t\tLOADING";      ///////showing loading on screen
                for(int i = 0; i < 3 ; i++) {
                    cout << ".";
                    sleep(1);
                }
                system("cls");
                bookManagement(&rnum, studBookLimit);       ////// now we open book management
            }
            else    { 
                cout << "\t\t\t\t\t\t::Wrong password::";
            }
            }
            else {
                cout << "\n\t\t\t\t\t\t::Invalid Username Entered::\n\t\t\t\t\t\tPlease register first with your username"; /////// case if no file is found for the roll num
            }
            readFile.close();
            
            break;
            }
            else    {
                cout << "\n\t\t\t\t\t\t::Invalid roll number entered::";
            }
            }
            else {
                cout << "\n\t\t\t\t\t\t::You entered the wrong roll number::\n\t\t\t\t\t\tTry again :(";    
            }   
        }   
    return 0;
}

int student :: Register()   {
    int flag=1; 
    char c;
        while(flag != 0)    {
            cout << "\n\t\t\t\t\t\tEnter your 5 digit roll number: ";
            cin >> rollNum;
            if (rollNum <= 99999 && rollNum >= 10000)   {                   ////////////Roll no check
                flag = 0;
                //cin.ignore();
                cout << "\n\t\t\t\t\t\tEnter your password: ";
            while(c != '\r') //////////Loop until 'Enter' is pressed
            {
            c = getch();
            if(c == 0)
            {
            switch(getch())
               {
               default:
                  break;            
               };
            }
            else if(c == '\b')   /////If the 'Backspace' key is pressed
            {
            if(password.size() != 0)  //////If the password string contains data, erase last character
               {
               cout << "\b \b";
               password.erase(password.size() - 1, 1);
               }
            continue;
            }
            else if(c <= '9' && c >= '0' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')  //If user enters 1-9, a-z, or A-Z, add it to the password and display an asterisk
            {
            password += c;
            cout << c;
            }
            else
            continue;
            }

                string RollNum;
                RollNum = to_string(rollNum);
                //cout << "\n" << RollNum;
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
                
                yearAndBranchFinder();  ////////// year and brach are calculated
                credentials();      ///////pass and username is created now we take the other credentials
                string directory;
                directory = "C:/Library Kiosk/studentData/" + RollNum;
                mkdir(directory.c_str());               ///////making a folder with roll number as name

                ofstream ofs(directory + "/" + RollNum + ".txt");
                ofs << rollNum << endl;
                ofs << password << endl;
                ofs.close();
                
                cout << "\n\n\t\t\t\t\t::Your ID has been created in the Library DataBase::";
                cout << "\n\t\t\t\t\tYou may login again using your RollNum and Password";
                //break;
            }   
            else {
                cout << "\n\t\t\t\t\t\t::You entered the wrong roll number::\n\t\t\t\t\t\tTry again :(";    
            }   
        }       
    sleep(5);
    return 0;   
}   

void student :: credentials()   {
    
    cout << "\n\t\t\t\t\t\tEnter your name: ";
    cin.getline(name,20);
    cout << "\n\t\t\t\t\t\tName: \t" << name ;
    cin.clear();
    cout << "\n\t\t\t\t\t\tYear: \t20" << year;

    switch(Branch)  {
        case 3: 
            cout << "\n\t\t\t\t\t\tBranch: CSE";
            break;
        case 1:
            cout << "\n\t\t\t\t\t\tBranch: CIVIL";
            break;
        case 2:
            cout << "\n\t\t\t\t\t\tBranch: ECE";
            break;
        case 4:
            cout << "\n\t\t\t\t\t\tBranch: MECH";
            break;
        default:
            cout << "\n\t\t\t\t\t\t::Invalid Roll-Num entered::";
            break;

    }
    //setName(Name);
    //cout << endl << getName();

}

void student :: yearAndBranchFinder()   {
    
    year = (rollNum/1000);
    Branch = rollNum;
    for (int i = 5; i >= 3; i--)    {
        int power;
        power = pow(10,i);
        Branch = (Branch%power);
    }
    Branch = Branch/100;
}

void student :: bookManagement(string *rnum, int bookLimit)    {

    int choice, i=0;
    book B;

    while(1)    {
        cout<<"\n\n\t\t\t\t\t\t\tMENU"
		<<"\n\t\t\t\t\t\t1. Issue New Book"
		<<"\n\t\t\t\t\t\t2. Return Book"
		<<"\n\t\t\t\t\t\t3. Search For Book"
		<<"\n\t\t\t\t\t\t4. Exit"
		<<"\n\t\t\t\t\t\tEnter your Choice: ";
		cin>>choice;

        switch (choice)
        {
        case 1: {
            
            B.newbookIssue(*rnum, bookLimit);
            break;
        }
        
        case 2: {
            adminFlag = 1;
            B.bookreturn(*rnum, bookLimit, adminFlag);
            break;
        }
        case 3: {
            
            string stock;
            cin.clear();
            cout << "\n\t\t\t\t\t\tEnter the stock number of the book(Example: A3): ";
            cin >> stock;
            B.bookData(stock);
            break;
        }
        case 4: {
            exit(0);
        }
        default:
            break;
        }

    }

}

void admin :: adminConsole()    {

    system("cls");

    book *B;
	int i=0,r,t,choice;
	char titlebuy[20],authorbuy[20];
	while(1)	{
		cout<<"\n\n\t\t\t\t\t\t\tMENU"
		<<"\n\t\t\t\t\t\t1. Entry of New Book"
		<<"\n\t\t\t\t\t\t2. Add a new Admin"
		<<"\n\t\t\t\t\t\t3. Search For Book"
		<<"\n\t\t\t\t\t\t4. Edit Details Of Book"
        <<"\n\t\t\t\t\t\t5. Approve late book return"
		<<"\n\t\t\t\t\t\t6. Exit"
		<<"\n\t\t\t\t\t\tEnter your Choice: ";
		cin>>choice;
		
		switch(choice)	{
			case 1:	
                B = new book;
				B->feeddata();
				i++;	
                break;
				
			case 2: 
                cin.ignore();
				Register();
				break;
			case 3: {
                
                string stock;
                
                cin.ignore();
                cout << "\t\t\t\t\t\tEnter the stock value for the book: ";
                cin >> stock;

				B->bookData(stock);

				break;
            }
			case 4: 
                
                B->editdata();
				break;

			case 5: {

                student stud;
                string RollNum;
                int i = 0;
                while(1)    {

                    cout << "\t\t\t\t\t\tBook return for: "
                    << "\n\t\t\t\t\t\t1. Student"
                    << "\n\t\t\t\t\t\t2. Teacher"
                    << "\n\t\t\t\t\t\tYour choice: ";
                    cin >> i;
                    switch(i)   {
                    case 1: {
                        cin.ignore();
                        cout << "\t\t\t\t\t\tEnter the roll Num of the student: ";
                        cin >> RollNum;
                        B->bookreturn(RollNum, studBookLimit, adminFlag);
                        break;
                    }
                    case 2: {
                        cin.ignore();
                        cout << "\t\t\t\t\t\tEnter the teacher's ID: ";
                        cin >> RollNum;
                        B->bookreturn(RollNum, teachBookLimit, adminFlag);
                        break;
                    }
                    default:
                        cout << "\n\n\t\t\t\t\t\t::Invalid Choice Entered::";
                        break;
                    }
                }
            }
			case 6:
                exit(0);
            default: 
                cout<<"\n\t\t\t\t\t\tInvalid Choice Entered";
                system("cls");
			
		}
	}

}

void student :: setName(char Name[20]) {
    strcpy(name, Name);
}
string student :: getName ()    {
    return name;
}
void student :: setRollNum(int RollNum) {
    rollNum = RollNum;
}
int student :: getRollNum() {
    return rollNum;
}

void teacher :: getname()   {
    cout << "Enter your name below:";
    cin >> name;
}

string teacher :: getid() {
    string TeachID;
    TeachID = to_string(teachID);
    return TeachID;
}

void teacher :: idcheck()   {
    
}

void teacher :: teacherBegin()  {
    
    int flag=1;

            int loginOption;
            while(flag != 0) {   ///////taking student login and input
            cin.ignore();
            cout << "\n\t\t\t\t\t\t\tSelect one option:\n\t\t\t\t\t\t1. Login\n\t\t\t\t\t\t2. Register\n";
            cin >> loginOption;
            try {
                if (loginOption == 1 || loginOption == 2)   {
                    if (loginOption == 1)   {
                        flag = 0;
                        Login();
                    }
                    else    {
                        flag = 0;
                        Register();
                    }
                }

                else{
                    throw(loginOption);
                }
            }
            catch(int a) {
                cout << "\n\t\t\t\t\t\t::Choose only from options given above::\n";
                //loginOption = 1;
            }
        }
}

int teacher :: Register()  {
        
        int flag=1; 
        char c;
        while(flag != 0)    {
            cout << "\n\t\t\t\t\t\tEnter your 5 digit Teacher's ID: ";
            cin >> teachID;
            if (teachID <= 99999 && teachID >= 10000)   {                   ////////////Roll no check
                flag = 0;
                //cin.ignore();
                cout << "\n\t\t\t\t\t\tEnter your password: ";
            while(c != '\r') //////////Loop until 'Enter' is pressed
            {
            c = getch();
            if(c == 0)
            {
            switch(getch())
               {
               default:
                  break;            
               };
            }
            else if(c == '\b')   /////If the 'Backspace' key is pressed
            {
            if(password.size() != 0)  //////If the password string contains data, erase last character
               {
               cout << "\b \b";
               password.erase(password.size() - 1, 1);
               }
            continue;
            }
            else if(c <= '9' && c >= '0' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')  //If user enters 1-9, a-z, or A-Z, add it to the password and display an asterisk
            {
            password += c;
            cout << c;
            }
            else
            continue;
            }
                cin.ignore();

                cout << "\n\t\t\t\t\t\tEnter your name: ";
                cin >> name;

                string TeachID;
                TeachID = to_string(teachID);
                //cout << "\n" << RollNum;
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
                
                string directory;
                directory = "C:/Library Kiosk/teacherData/" + TeachID;
                mkdir(directory.c_str());               ///////making a folder with roll number as name

                ofstream ofs(directory + "/" + TeachID + ".txt");
                ofs << teachID << endl;
                ofs << password;
                ofs.close();
                
                cout << "\n\n\t\t\t\t\t::Your ID has been created in the Library DataBase::";
                cout << "\n\t\t\t\t\tYou may login again using your Teacher's ID and Password";
                //break;
            }   
            else {
                cout << "\n\t\t\t\t\t::You entered the wrong Teacher's ID::\nTry again :(";    
            }   
        }     
        sleep(2);  
    return 0;
}

int teacher :: Login()  {
    
    int flag=1;
        char c;
        while(flag != 0)    {
            cout << "\n\t\t\t\t\t\tEnter your 5 digit teacher's ID: ";
            cin >> teachID;
            if (teachID <= 99999 && teachID >= 10000)   {                       /////// roll num check
                flag = 0;
                cout << "\n\t\t\t\t\t\tEnter your password: ";
                while(c != '\r') //////////Loop until 'Enter' is pressed
                {
                c = getch();
                if(c == 0)
                {
                switch(getch())
                {
                default:
                    break;            
                };
                }
                else if(c == '\b')   /////If the 'Backspace' key is pressed
                {
                if(password.size() != 0)  //////If the password string contains data, erase last character
                {
                cout << "\b \b";
                password.erase(password.size() - 1, 1);
                }
                continue;
                }
                else if(c <= '9' && c >= '0' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')  //If user enters 1-9, a-z, or A-Z, add it to the password and display an asterisk
                {
                password += c;
                cout << "*";
                }
                else
                continue;
                }
            string TeachID;
            string pass;
            string rnum = to_string(teachID);

            string directory;
            directory = "C:/Library Kiosk/teacherData/" + rnum;

            ifstream readFile(directory + "/" + rnum + ".txt");   ////////////  opening the file ///// reading from the student database ///opening athe file in the studnet folder

            if (readFile.is_open()) {           ////// checking ro see if the file is openend
            getline(readFile, TeachID);
            getline(readFile, pass);

            if (rnum == TeachID && pass == password) {      
                cout << "\n\t\t\t\t\t\tSuccessful Login";
                sleep(1);
                system("cls");
                cout << "\n\n\t\t\t\t\t\t\tLOADING";      ///////showing loading on screen
                for(int i = 0; i < 3 ; i++) {
                    cout << ".";
                    sleep(1);
                }
                system("cls");
                bookManagement(&rnum, teachBookLimit);       ////// now we open book management
            }
            else    { 
                cout << "\t\t\t\t\t\t\t::Wrong password::";
            }
            }
            else {
                cout << "\n\t\t\t\t\t::Invalid Username Entered::\n\t\t\t\t\tPlease register first with your username"; /////// case if no file is found for the roll num
            }
            readFile.close();
            
            break;

            }
            else {
                cout << "\n\t\t\t\t\t\t::You entered the wrong Teacher's ID::\n\t\t\t\t\t\tTry again :(";    
            }   
        }   
    return 0;
}


int admin :: Login()    {
        
        cout << "\n\t\t\t\t\t::Login with your Admin ID and password::\n";
        int flag=1;
        char c;
        while(flag != 0)    {
            cout << "\n\t\t\t\t\t\tEnter your 6 digit admin ID: ";
            cin >> adminID;
            if (adminID <= 999999 && adminID >= 100000)   {                       /////// roll num check
                flag = 0;
                cout << "\n\t\t\t\t\t\tEnter your password: ";
            while(c != '\r') //////////Loop until 'Enter' is pressed
            {
            c = getch();
            if(c == 0)
            {
            switch(getch())
               {
               default:
                  break;            
               };
            }
            else if(c == '\b')   /////If the 'Backspace' key is pressed
            {
            if(password.size() != 0)  //////If the password string contains data, erase last character
               {
               cout << "\b \b";
               password.erase(password.size() - 1, 1);
               }
            continue;
            }
            else if(c <= '9' && c >= '0' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')  //If user enters 1-9, a-z, or A-Z, add it to the password and display an asterisk
            {
            password += c;
            cout << "*";
            }
            else
            continue;
            }

            string rollnum;
            string pass;
            string rnum = to_string(adminID);

            string directory;
            
            directory = "C:/Library Kiosk/adminData/" + rnum;

            ifstream readFile(directory + "/" + rnum + ".txt");   ////////////  opening the file ///// reading from the admin database ///opening athe file in the studnet folder

            if (readFile.is_open()) {           ////// checking ro see if the file is openend
            getline(readFile, rollnum);
            getline(readFile, pass);
            cout << rollnum << endl << pass;
            if (rnum == rollnum && pass == password) {      
                cout << "\n\t\t\t\t\t\tSuccessful Login";
                sleep(1);
                system("cls");
                cout << "\n\n\t\t\t\t\t\tLOADING";      ///////showing loading on screen
                for(int i = 0; i < 3 ; i++) {
                    cout << ".";
                    sleep(1);
                }
                system("cls");
                adminConsole();       ////// now we open admin console
            }
            else    { 
                cout << "\t\t\t\t\t\t::Wrong password::";
            }
            }
            else {
                cout << "\n\t\t\t\t\t::Invalid Username Entered::\n\t\t\t\t\tPlease register first with your username"; /////// case if no file is found for the roll num
            }
            readFile.close();
            
            break;
            }
            else {
                cout << "\n\t\t\t\t\t\t::You entered the wrong Admin ID::\n\t\t\t\t\t\tTry again :(";    
            }   
        }   
    return 0;
}

int admin :: Register()    {
    
    int flag=1; 
    char c;
        while(flag != 0)    {
            cout << "\n\t\t\t\t\t\tEnter your 6 digit Admin ID: ";
            cin >> adminID;
            if (adminID <= 999999 && adminID >= 100000)   {                   ////////////Roll no check
                flag = 0;
                //cin.ignore();
                cout << "\n\t\t\t\t\t\tEnter your password: ";
            while(c != '\r') //////////Loop until 'Enter' is pressed
            {
            c = getch();
            if(c == 0)
            {
            switch(getch())
               {
               default:
                  break;            
               };
            }
            else if(c == '\b')   /////If the 'Backspace' key is pressed
            {
            if(password.size() != 0)  //////If the password string contains data, erase last character
               {
               cout << "\b \b";
               password.erase(password.size() - 1, 1);
               }
            continue;
            }
            else if(c <= '9' && c >= '0' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')  //If user enters 1-9, a-z, or A-Z, add it to the password and display an asterisk
            {
            password += c;
            cout << c;
            }
            else
            continue;
            }
                cin.ignore();

                cout << "\n\t\t\t\t\t\tEnter your name: ";
                cin >> name;

                string AdminID;
                AdminID = to_string(adminID);
                //cout << "\n" << RollNum;
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
                
                string directory;
                directory = "C:/Library Kiosk/adminData/" + AdminID;
                mkdir(directory.c_str());               ///////making a folder with roll number as name

                ofstream ofs(directory + "/" + AdminID + ".txt");
                ofs << adminID << endl;
                ofs << password;
                ofs.close();
                
                cout << "\n\n\t\t\t\t\t::Your ID has been created in the Library DataBase::";
                cout << "\n\t\t\t\t\tYou may login again using your Admin's ID and Password";
                //break;
            }   
            else {
                cout << "\n\t\t\t\t\t\t::You entered the wrong Admin ID::\n\t\t\t\t\t\tTry again :(";    
                sleep(2);
                system("cls");
            }   
        }      
    sleep(2);
    return 0;

}

int main()  {

    int i;
    
    //////////making our directory in C drive so data is secure and this program can run on all computers

    string directory;           ///////defining the directory where all data will be stored
    directory = "C:/Library Kiosk";
    mkdir(directory.c_str());   ///////making our main folder
    directory = "C:/Library Kiosk/studentData";
    mkdir(directory.c_str());   ///////,making our student folder
    directory =  "C:/Library Kiosk/teacherData";
    mkdir(directory.c_str());   ///////making our teacher folder
    directory =  "C:/Library Kiosk/adminData";
    mkdir(directory.c_str());   ///////making our admin folder
    directory =  "C:/Library Kiosk/bookdata";
    mkdir(directory.c_str());   ///////making our books folder


    while(1)    {
    system("cls");
    cout << "\n\n\n\n\n\t\t\t\t\t ::WELCOME TO THE LIBRARY KIOSK::";
    cout << "\n\n\t\t\t\t\t\t\tMENU \n\t\t\t\t\t\t1.Student, \n\t\t\t\t\t\t2.Teacher or \n\t\t\t\t\t\t3.Admin\n\t\t\t\t\t\t4.Exit\n\t\t\t\t\t\tYour choice: ";
    cin >> i;

    switch (i)  {

        case 1:     //////for student
        {
            student stud1;
            stud1.studentBegin();
            break;  //////////case break
        }
        case 2: ////////for teacher
        {
            teacher tech1;
            tech1.teacherBegin();
            break;
        }
        case 3: ////////for admin
        {
            admin adm;
            adm.Login();
            break;
        }
        case 4: exit(0);
        default:
        cout << "\n::Invalid choice entered::";
        break;

    }
    }

    return 0;

}