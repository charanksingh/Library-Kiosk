#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>
#include<ctime>
#include<unistd.h>
#include<iomanip>

using namespace std;

time_t now = time(NULL);				/////// taking seconds

tm *cur_time = localtime(&now);			/////// making a local time object

class book	{		/////////our main book class for the functions we perform on our books

private:
	
	string *author,*title,*publisher;
	float price;
	string stock;
	string booksIssued;

public:	

	book()	{
		author = new string;
		title = new string;
		publisher = new string;
	}
	
	void feeddata();
	void editdata();
	void bookData(string Stock);
	void newbookIssue(string id, int i);
	void bookreturn(string id, int I, int adminFlag);
	int calculateFine(int numOfDays);
	void removeEntry(int linecount, string id, int i);
	void returnTomenu();
	void databaseEntry(string id, int i);

};

void book::feeddata()	{
	system("cls");
	cin.ignore();
	cout<<"\n\n\t\t\t\t\t\tEnter Author Name: ";      
	getline(cin,*author);
	cout<<"\t\t\t\t\t\tEnter Title Name: ";       
	getline(cin,*title);
	cout << "\t\t\t\t\t\tEnter Publisher Name: ";   
	getline(cin,*publisher);
	cout << "\t\t\t\t\t\tEnter Price: ";            
	cin >> price;
	cout << "\t\t\t\t\t\tEnter Stock Position(Example: A3): ";   
	cin >> stock;   

	fstream ofs("C:/Library Kiosk/bookdata/" + stock + ".txt", ios::in);
	
	if(!ofs)	{	////////file does not exist and we create a new file;
		
		ofs.open("C:/Library Kiosk/bookdata/" + stock + ".txt", ios::out);
		ofs << *author << endl
			<< *title << endl
			<< *publisher << endl
			<< price << endl
			<< stock;
	
		ofs.close();
		cout << "\n\t\t\t\t\t\tThis book has been entered in the database\n";
	}
	else	{	//////file already exists

		ofs.close();
		cout << "\n\t\t\t\t\t\t::This book already exists in the database::";

	}

	returnTomenu();
}

void book::editdata()	{

	cout << "\n\t\t\t\t\tEnter the new data for the book";
	cin.ignore();
	cout<<"\n\n\t\t\t\t\t\tEnter Author Name: ";      
	getline(cin,*author);
	cout<<"\t\t\t\t\t\tEnter Title Name: ";       
	getline(cin,*title);
	cout << "\t\t\t\t\t\tEnter Publisher Name: ";   
	getline(cin,*publisher);
	cout << "\t\t\t\t\t\tEnter Price: ";            
	cin >> price;
	cout << "\t\t\t\t\t\tEnter Stock Position(Example: A3): ";   
	cin >> stock;  

	fstream ofs("C:/Library Kiosk/bookdata/" + stock + ".txt", ios::in);
	
	if(ofs)	{	////////file exists
		
		ofs.open("C:/Library Kiosk/bookdata/" + stock + ".txt", ios::out);
		ofs << *author << endl
			<< *title << endl
			<< *publisher << endl
			<< price << endl
			<< stock;

		ofs.close();

	}
	else	{	//////file doesa not exist

		ofs.close();
		cout << "\t\t\t\t\t\t::This book does not exist in the database::";

	} 
	returnTomenu();	
}

void book::bookData(string Stock)	{
	
	string line;

	fstream ofs("C:/Library Kiosk/bookdata/" + Stock + ".txt", ios::in);	///////opening the book file to see book details
		
		if (ofs)	{		
		cout << "\n\n\t\t\t\t\t\tThese are the details of the book\n";
		getline(ofs, line);	
		cout<<"\n\t\t\t\t\t\t\tAuthor Name: " << line;
		getline(ofs, line);	
		cout << "\n\t\t\t\t\t\t\tTitle Name: " << line;
		getline(ofs, line);	
		cout << "\n\t\t\t\t\t\t\tPublisher Name: " << line;
		getline(ofs, line);	
		cout << "\n\t\t\t\t\t\t\tPrice: " << line;
		getline(ofs, line);	
		cout << "\n\t\t\t\t\t\t\tStock Position: " << line;
		ofs.close(); 		
		}
		else {
			cout << "\n\t\t\t\t\tThis book does not exist in the database";
			cout << "\n\n\t\t\t\t\t::Enter another stock value::";

		}		
		returnTomenu();
}

void book :: newbookIssue(string id, int i)	{


	int j = 0;

	while(1)	{
		
		cout << "\n\t\t\t\t\t\tEnter Stock Position(Example: A3): ";   
		cin >> stock;
		
		fstream ofs("C:/Library Kiosk/bookdata/" + stock + ".txt", ios::in);
	
		if(!ofs)	{	////////checking if the the book does not exists inb the database
			cout << "\n\t\t\t\t\tTHIS BOOK DOES NOT EXIST IN THE DATABASE";
			cout << "\n\t\t\t\t\tTo enter stock position again press 1:" 
			<< "\n\t\t\t\t\t\tTo exit press 0:"
			<< "\n\t\t\t\t\t\tYour choice: ";
			cin >> j;

			if (j == 0)	{
				exit(0);
			}

			ofs.close();
		}
		else	{	//////this case if the file exists
			ofs.close();
			break;
		}

	}

	string line;

	switch(i)	{
	case 3: 	{

	int dayOfYear;
	dayOfYear = cur_time->tm_yday;			////////// recording the day of the year

	fstream userfile("C:/Library Kiosk/studentData/" + id + "/book" + id + ".txt", ios::in);

	if(!userfile)	{	///////// file does not exist then created new file 
	
		cout << "\n\t\t\t\t\t\t::You haven't issued any books yet::\n\n";
		userfile.open("C:/Library Kiosk/studentData/" + id + "/book" + id + ".txt", ios::out);
		userfile << stock;
		userfile << " " << dayOfYear;
		userfile.close();

		cout << "\n\n\t\t\t\t\t\tLOADING";      ///////showing loading on screen
                for(int i = 0; i < 3 ; i++) {
                    cout << ".";
                    sleep(1);
                }
		system("cls");
		
		cout << "\n\t\t\t\t\t\t::You have been issued this book::";
		{
		char *timenow = ctime(&now);

		cout << "\n\n\t\t\t\t\t\tDate and time of issue: " << timenow;
		now += 864000;
		}
		
		char *timenow = ctime(&now);
		cout << "\n\t\t\t\t\t\tYou have to return the book by: " << timenow;
		databaseEntry(id,i);

		bookData(stock);

	}
	else	{	//////////reading from existing file
		
		userfile.close();
		int flag = 1;
		int count = 0;
		
		ifstream ifs("C:/Library Kiosk/studentData/" + id + "/book" + id + ".txt", ios::in);
		
		while(!ifs.eof()){
	
			count++;

			if(count == i)	{		////////checking if the number of books are less than 3(students can only issue three books at one time)
				cout << "\n\t\t\t\t\tYou have already been issued three books" << endl 
				<< "\t\t\t\t\t::Return one of your books to issue more books::";
				returnTomenu();
				break;
			}
		
			getline(ifs, line, ' ');
			booksIssued = line;
			getline(ifs, line);

			if(stock == booksIssued)	{
				flag = 0;
				break;
			}

		}

		ifs.close();

		if (flag == 0)	{
			cout << "\n\t\t\t\t\t\t::You have already been issued this book::";
			bookData(stock);
			break;
		}

		ofstream ofs("C:/Library Kiosk/studentData/" + id + "/book" + id + ".txt", ios::app);
		if (count < i)	{		////////if space for more books only then we'll add
			ofs << endl << stock << " ";
			ofs << dayOfYear;
		
		ofs.close();
		cout << "\n\n\t\t\t\t\t\tLOADING";      ///////showing loading on screen
                for(int i = 0; i < 3 ; i++) {
                    cout << ".";
                    sleep(1);
                }
		system("cls");
		cout << "\n\t\t\t\t\t\tUpdating the database";      ///////showing loading on screen
                for(int j = 0; j < 3 ; j++) {
                    cout << ".";
                    sleep(1);
                }

		system("cls");
		//string line;

		cout << "\n\t\t\t\t\t::You have been issued this book::";
		{
		char *timenow = ctime(&now);

		cout << "\n\n\t\t\t\t\t\tDate and time of issue: " << timenow;
		now += 864000;
		}
		
		char *timenow = ctime(&now);
		cout << "\n\t\t\t\t\t\tYou have to return the book by: " << timenow;
		databaseEntry(id,i);
		bookData(stock);
		}
		
	}	
	break;			////////////switch case break for student case

	}
	case 5:	{			/////////teacher case

	int dayOfYear;
	dayOfYear = cur_time->tm_yday;			////////// recording the day of the year

	fstream userfile("C:/Library Kiosk/teacherData/" + id + "/book" + id + ".txt", ios::in);

	if(!userfile)	{	///////// file does not exist then created new file 
	
		cout << "\n\t\t\t\t\t\t::You haven't issued any books yet::\n\n";
		userfile.open("C:/Library Kiosk/teacherData/" + id + "/book" + id + ".txt", ios::out);
		userfile << stock;
		userfile << " " << dayOfYear;
		userfile.close();

		bookData(stock);

		{
		char *timenow = ctime(&now);

		cout << "\n\t\t\t\t\t\tDate and time of issue: " << timenow;
		now += 864000;
		}
		
		char *timenow = ctime(&now);
		cout << "\n\n\t\t\t\t\t\tYou have to return the book by: " << timenow;
		cout << "\n\t\t\t\t\t\t::You have been issued this book::";
		databaseEntry(id,i);
		returnTomenu();
	}
	else	{	//////////reading from existing file
		
		userfile.close();
		int flag = 1;
		int count = 0;
		
		ifstream ifs("C:/Library Kiosk/teacherData/" + id + "/book" + id + ".txt", ios::in);
		
		while(!ifs.eof())	{
	
			count++;

			if(count == i)	{		////////checking if the number of books are less than 3(students can only issue three books at one time)
				cout << "\n\t\t\t\t\tYou have already been issued five books" << endl 
				<< "\t\t\t\t\t::Return one of your books to issue more books::";
				returnTomenu();
				break;
			}
		
			getline(ifs, line, ' ');
			booksIssued = line;
			getline(ifs, line);

			if(stock == booksIssued)	{
				flag = 0;
				break;
			}

		}
		ifs.close();

		if (flag == 0)	{
			cout << "\n\t\t\t\t\t::You have already been issued this book::";
			bookData(stock);
			break;
		}

		ofstream ofs("C:/Library Kiosk/teacherData/" + id + "/book" + id + ".txt", ios::app);
		if (count < i)	{		////////if space for more books only then we'll add
			ofs << endl << stock << " ";
			ofs << dayOfYear;
		
		ofs.close();
		cout << "\n\n\t\t\t\t\t\tLOADING";      ///////showing loading on screen
                for(int i = 0; i < 3 ; i++) {
                    cout << ".";
                    sleep(1);
                }
		system("cls");
		cout << "\n\t\t\t\t\t\tUpdating the database";      ///////showing loading on screen
                for(int i = 0; i < 3 ; i++) {
                    cout << ".";
                    sleep(1);
                }

		system("cls");
		//string line;

		cout << "\n\t\t\t\t\t\t::You have been issued this book::";
		{
		char *timenow = ctime(&now);

		cout << "\n\n\t\t\t\t\t\tDate and time of issue: " << timenow;
		now += 864000;
		}
		
		char *timenow = ctime(&now);
		cout << "\n\t\t\t\t\t\tYou have to return the book by: " << timenow;
		databaseEntry(id,i);
		bookData(stock);
	}
	}	
	break;			////////////switch case break for student case
	}
	}
}


void book :: bookreturn(string id, int I, int adminFlag)	{

	string timeOfEntry;
	string stockRead;

	cin.ignore();
	cout << "\n\t\t\t\t\tEnter the stock position of book you wish to return: ";
	cin >> stock;
	
	int count = 0;				/////we aere using this variable to tell us the entry we want to delete lies in which line
	int flag = 1;
	int dayOfYear;
	
	dayOfYear = cur_time->tm_yday;
	int currentDay;
	clock_t start = clock();
	
	switch(I)	{

		case 3:	{
			ifstream readForStock("C:/Library Kiosk/studentData/" + id + "/book" + id + ".txt", ios::in);

			while(!readForStock.eof())	{

				//sleep(10);
				getline(readForStock, stockRead, ' ');
				getline(readForStock, timeOfEntry);	
				count ++;

				if (stock == stockRead)	{
					
					cout << "\n\t\t\t\t\t\tThis book is in your database";

					currentDay = stoi(timeOfEntry);
					currentDay = dayOfYear - currentDay;

					if (currentDay < 10)	{
						
						char ch;
						int i=0;
						cout << "\n\t\t\t\t\tThis book will be deleted from your database in 5 seconds\n\t\t\t\t\t::Press any key to cancel this operation::\n";
						cin.clear();			
						while (! _kbhit())	{	
							if (((clock () - start)/ CLOCKS_PER_SEC ) >= 5) //////////////if no input for 5 seconds then the code terminates
							{					
								system("cls");	
								cout << "\n\n\n\t\t\t\t\t\t:TIMEOUT:" << endl;
								sleep(2);	  
								system("cls");
								removeEntry(count,id,I);								//////////////removing the book entry
								flag = 0;	 	
								returnTomenu();		
								break;			
							}
						}
						if (flag == 1)	{
							cout << "\n\t\t\t\t\t\t::removal cancelled::";
							exit(0); 
						}
						
					}
					else {
						system("cls");
						if (adminFlag = 0)	{
						cout << "\n\t\t\t\t::You have passed the deadline for returning the book::";
						int fine;
						fine = calculateFine(currentDay);
						cout << "\n\t\t\t\t\tYou are '" << (currentDay - 10) << "' days late for returning the book";
						cout << "\n\n\t\t\t\t\tYour fine for returning the book late is: " << fine << " rupees";
						cout << "\n\t\t\t\t\t::Contact the admin to pay the fine and return the book::";
						returnTomenu();
						}
						else {
							
							cout << "\n\t\t\t\t::The student has passed the deadline for returning the book::";
							int fine;
							fine = calculateFine(currentDay);
							cout << "\n\t\t\t\t\tThe student is '" << (currentDay - 10) << "' days late for returning the book";
							cout << "\n\n\t\t\t\t\tFine for returning the book late is: " << fine << " rupees";
							
							cout << "\n\t\t\t\t\tThis book will be deleted from the student's database in 5 seconds\n\t\t\t\t\t::Press any key to cancel this operation::\n";
							cin.clear();	

							while (! _kbhit())	{	
								if (((clock () - start)/ CLOCKS_PER_SEC ) >= 5) //////////////if no input for 5 seconds then the code terminates
								{					
									system("cls");	
									cout << "\n\n\n\t\t\t\t\t\t:TIMEOUT:" << endl;
									sleep(2);	  
									system("cls");
									removeEntry(count,id,I);								//////////////removing the book entry
									flag = 0;	 	
									returnTomenu();		
									break;			
								}
							}
							if (flag == 1)	{
								cout << "\n\t\t\t\t\t\t::removal cancelled::";
								returnTomenu(); 
							}
						}
						break;
					}
					
				}
				else	{
					continue;
				}
				readForStock.close();
			}
			break;
		}	//student case closed

		case 5:	{
			
			ifstream readForStock("C:/Library Kiosk/teacherData/" + id + "/book" + id + ".txt", ios::in);

			while(!readForStock.eof())	{

				//sleep(10);
				getline(readForStock, stockRead, ' ');
				getline(readForStock, timeOfEntry);	
				count ++;

				if (stock == stockRead)	{
					
					cout << "\n\t\t\t\t\t\tThis book is in your database";

					currentDay = stoi(timeOfEntry);
					currentDay = dayOfYear - currentDay;

					if (currentDay < 10)	{
						
						char ch;
						int i=0;
						cout << "\n\t\t\t\t\tThis book will be deleted from your database in 5 seconds\n\t\t\t\t\t::Press any key to cancel this operation::\n";
						cin.clear();			
						while (! _kbhit())	{	
							if (((clock () - start)/ CLOCKS_PER_SEC ) >= 5) //////////////if no input for 5 seconds then the code terminates
							{					
								system("cls");	
								cout << "\n\n\n\t\t\t\t\t\t:TIMEOUT:" << endl;
								sleep(2);	  
								system("cls");
								removeEntry(count,id,I);								//////////////removing the book entry
								flag = 0;	 	
								exit(0);		
								break;			
							}
						}
						if (flag == 1)	{
							cout << "\n\t\t\t\t\t\t::removal cancelled::";
							exit(0); 
						}
						
					}
					else {
						system("cls");
						cout << "\n\t\t\t\t\t::You have passed the deadline for returning the book::";
						int fine;
						fine = calculateFine(currentDay);
						cout << "\n\t\t\t\t\tYou are '" << (currentDay - 10) << "' days late for returning the book";
						cout << "\n\n\t\t\t\t\tYour fine for returning the book late is: " << fine << " rupees";
						cout << "\n\t\t\t\t\t::Contact the admin to pay the fine and return the book::";
						returnTomenu();
						break;
					}
					
				}
				else	{
					continue;
				}
				readForStock.close();
			}

			break;
		}	////// teacher case close 

	}//switch close
}

int book :: calculateFine(int numOfDays)	{

	int fine = 0;
	if (numOfDays < 20)	{
		fine = (numOfDays - 10) * 5;		///////// every day after 10 days of issue has a fine of 5 rupees 
		return fine;
	}
	else if (numOfDays >= 20 && numOfDays < 35)	{
		fine = 10 * 5;
		fine = fine + (numOfDays - 20) * 15;	///////every day after next 10 days of fine costs 15 rupee
		return fine;
	}
	else {
		fine = 10 * 5;
		fine = fine + (15 * 15);
		fine = fine + (numOfDays - 35) * 20;
		return fine;
	}

}

void book :: removeEntry(int linecount, string id , int i)	{

	string line;

	switch (i)
	{
	case 3:	{				///student case

		cin.clear();

		fstream tempfile("C:/Library Kiosk/tempfile.txt", ios::out | ios :: in | ios :: trunc);	
		ifstream mainfile("C:/Library Kiosk/studentData/" + id + "/book" + id + ".txt", ios::in);

			switch(linecount)	{
				case 1:	{			////////case for if the entry is in line one... then we will take that book entry out
					
					int j = 1;
					getline(mainfile,line);
					while (!mainfile.eof())
					{
						if (j == 1)	{
						getline(mainfile, line);
						tempfile << line;
						j++;
						}
						else	{
						getline(mainfile, line);
						tempfile << endl << line;
						}
					}
					mainfile.close();			///////now we disconnect the input stream from the main file and open it fro writing
					cin.ignore();
					ofstream maintoRead("C:/Library Kiosk/studentData/" + id + "/book" + id + ".txt", ios::out);
					
					tempfile.seekg(0, ios::beg);		/////setting read cursor to the file beginning 
					j = 0;
					
					while(!tempfile.eof())	{		/////reading how many lines are in teh temp file
						getline(tempfile, line);
						j++;
					}
					
					tempfile.seekg(0, ios::beg);		/////setting read cursor to the file beginning 
					for (int k = 1; k <= j;  k++)	{
						
						if (k < j)	{
						getline(tempfile, line);
						maintoRead << line << endl;
						}
						else	{
						getline(tempfile, line);
						maintoRead << line;
						}

					}
					maintoRead.close();
					tempfile.close();
					break;
				}
				default: {
					
					int j = 1;
					while (!mainfile.eof())
					{
						if (j == 1)	{
						getline(mainfile,line);
						tempfile << line;
						j++;
						}
						else if(j == linecount)	{
							getline(mainfile,line);
							j++;
						}
						else	{
						getline(mainfile, line);
						tempfile << endl << line;
						j++;
						}
					}
					mainfile.close();			///////now we disconnect the input stream from the main file and open it fro writing
					cin.ignore();
					ofstream maintoRead("C:/Library Kiosk/studentData/" + id + "/book" + id + ".txt", ios::out);
					tempfile.seekg(0, ios::beg);
					
					j = 0;	////initializing j
					
					while(!tempfile.eof())	{		/////reading how many lines are in teh temp file
						getline(tempfile, line);
						j++;
					}
					
					tempfile.seekg(0, ios::beg);		/////setting read cursor to the file beginning 
					
					for (int k = 1; k <= j;  k++)	{
						
						if (k < j)	{
						getline(tempfile, line);
						maintoRead << line << endl;
						}
						else	{
						getline(tempfile, line);
						maintoRead << line;
						}

					}
					maintoRead.close();
					tempfile.close();
					break;
				}
				}
				cin.clear();
				break;
	}
	
	case 5:	{				///teacher case
		
		cin.clear();

		fstream tempfile("C:/Library Kiosk/tempfile.txt", ios::out | ios :: in | ios :: trunc);	
		ifstream mainfile("C:/Library Kiosk/teacherData/" + id + "/book" + id + ".txt", ios::in);
			switch(linecount)	{
				case 1:	{			////////case for if the entry is in line one... then we will take that book entry out
					
					int j = 1;
					getline(mainfile,line);
					while (!mainfile.eof())
					{
						if (j == 1)	{
						getline(mainfile, line);
						tempfile << line;
						j++;
						}
						else	{
						getline(mainfile, line);
						tempfile << endl << line;
						}
					}
					mainfile.close();			///////now we disconnect the input stream from the main file and open it fro writing
					cin.ignore();
					ofstream maintoRead("C:/Library Kiosk/teacherData/" + id + "/book" + id + ".txt", ios::out);
					
					tempfile.seekg(0, ios::beg);		/////setting read cursor to the file beginning 
					j = 0;
					
					while(!tempfile.eof())	{		/////reading how many lines are in teh temp file
						getline(tempfile, line);
						j++;
					}
					
					tempfile.seekg(0, ios::beg);		/////setting read cursor to the file beginning 
					for (int k = 1; k <= j;  k++)	{
						
						if (k < j)	{
						getline(tempfile, line);
						maintoRead << line << endl;
						}
						else	{
						getline(tempfile, line);
						maintoRead << line;
						}

					}
					maintoRead.close();
					tempfile.close();
					break;
				
				}
				default: {
					
					int j = 1;
					while (!mainfile.eof())
					{
						if (j == 1)	{
						getline(mainfile,line);
						tempfile << line;
						j++;
						}
						else if(j == linecount)	{
							getline(mainfile,line);
							j++;
						}
						else	{
						getline(mainfile, line);
						tempfile << endl << line;
						j++;
						}
					}
					mainfile.close();			///////now we disconnect the input stream from the main file and open it fro writing
					cin.ignore();
					ofstream maintoRead("C:/Library Kiosk/teacherData/" + id + "/book" + id + ".txt", ios::out);
					tempfile.seekg(0, ios::beg);
					
					j = 0;	////initializing j
					
					while(!tempfile.eof())	{		/////reading how many lines are in teh temp file
						getline(tempfile, line);
						j++;
					}
					
					tempfile.seekg(0, ios::beg);		/////setting read cursor to the file beginning 
					
					for (int k = 1; k <= j;  k++)	{
						
						if (k < j)	{
						getline(tempfile, line);
						maintoRead << line << endl;
						}
						else	{
						getline(tempfile, line);
						maintoRead << line;
						}

					}
					maintoRead.close();
					tempfile.close();
					break;
				}
				
			}

		cin.clear();
		break;
	}
	}	////switch close	
}

void book :: databaseEntry(string id, int i)	{
	
	ifstream ifs("C:/Library Kiosk/adminData/issuedBooks.csv", ios::in);
	
	char *timeofissue = ctime(&now);

	now += 864000;
	char *timenow = ctime(&now);

	if(ifs)	{
		ifs.close();
		switch(i)	{
			case 3:	{
				ofstream ofs("C:/Library Kiosk/adminData/issuedBooks.csv", ios :: app);

				ofs << stock << ","
				<< id << ","
			    << "Student" << ","
			    << timeofissue;
			    //<< timenow << ","

				
				break;
			}
			case 5:
			{
				ofstream ofs("C:/Library Kiosk/adminData/issuedBooks.csv", ios :: app);
				
				ofs << stock << ","
				<< id << ","
			    << "Teacher" << ","
			    << timeofissue;
				
				break;
			}
		}
	}
	else {
		ifs.close();
		
		switch(i)	{
			case 3:	{
				ofstream ofs("C:/Library Kiosk/adminData/issuedBooks.csv", ios :: out | ios :: app);
				
				ofs << "Stock" << ","
			    << "ID" << ","
			    << "User" << ","
			    //<< "Date of Return" << ","
			    << "Date of issue" << endl;
				
				ofs << stock << ","
				<< id << ","
			    << "Student" << ","
			    << timeofissue ;

				ofs.close();

				break;
			}
			case 5:
			{
				ofstream ofs("C:/Library Kiosk/adminData/issuedBooks.csv", ios :: out | ios :: app);
				
				ofs << "Stock" << ","
			    << "ID" << ","
			    << "User" << ","
			    //<< "Date of Return" << ","
			    << "Date of issue" << endl;
				
				ofs << stock << ","
				<< id << ","
			    << "Teacher" << ","
			    << timeofissue ;
				
				ofs.close();

				break;
			}
		}

	}


}

void book :: returnTomenu()	{
	cout << "\n\n\t\t\t\t\tReturning to MENU in 15 seconds: ";
	for (int i = 1; i <= 15; i++)	{
		cout << i;
		sleep(1);
		cout << "\b";
	}
	system("cls");
}
