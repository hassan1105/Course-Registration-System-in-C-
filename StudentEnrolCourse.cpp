#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <string>
#include <string.h> 
#include <fstream>
#include <iomanip>

using namespace std;


//All function declaration

void clearScreen();
bool isUsernameUnique(string username);
int genVerificationCode();
void sendCodeByEmail(int verificationCode);
void createAccount();
void wellcomeScreen();
int loginMenuScreen();
void displayGoodByeMessage();
void displayMainAdminMenu(string username);
void displayTeacherMenu(string username);
void displayStudentMenu(string username);
void gotoMainMenu(string usertype,string username);
bool displayVerificationScreen();
void signIn();
int getAge(string dob);
void selectCourse(string username);
bool isCourseAlreadySelected(string c_code,string username);
bool isMaxSelCourseReached(string username);
bool isCourseAlreadyEnrolled(string c_code,string username);
void applyCourseSelection(string username,string c_code);
void applyCourseEnrollment(string username,string c_code);
int getSum(int array_courses[],int index);
void EnrollRequests(string username);
bool isMaxEnrolCourseReached(string username);
void ViewEnrolCourseList(string username);
void ViewSelectedCourseList(string username);
void ViewAssignedTeacherToCourse(string userame);
void ViewEnrolStudentInCourse(string userame);
string FindAssignedTeacherForCourse(string ccode);
void PrintTeacherDetail(string unique_id);
void PrintStudentDetail(string *unique_ids,int index);
string* FindEnrolStdInCourse(string ccode,int &index);
void CourseEnrolRequest();
void CourseAssignRequest();


int main()
{
	//required variables
	int login_choice;

    // Use current time as  
    // seed for random generator 
    srand(time(0));
 
	//iterate until user wish to exist the program
	do
	{
		//Calling login menu screen
		login_choice = loginMenuScreen();

		switch(login_choice)
		{
			//case 1 is login 
		case 1:
			//Calling signIn()
			signIn();
			break;

			//case 2 is create account
		case 2:
			//Calling createAccount()
			createAccount();
			break;

			//case 3 is terminate program
		case 3:
			//Calling displayGoodByeMessage
			displayGoodByeMessage();
			break;

		}

	}while(login_choice!=3);

	cout<<"\t";
	system("pause");

	return 0;
}

//Function Declaration



//Display the Login screen Menu
//prompt the user to enter the choice
//return the user choice
int loginMenuScreen()
{
	//variable to hold the user entered choice
	int choice;

	//do while loop to keep on receiving user choice
	//until valid choice is entered
	do
	{
		//Calling clearScreen()
		clearScreen();

		//Calling wellcomeScreen() function
		wellcomeScreen();

		//display the login screen menu
		cout<<"\n\tSelect from following options:\n";
		cout<<"\t\t1.\tLogin"<<endl
			<<"\t\t2.\tCreate New Account"<<endl
			<<"\t\t3.\tExit"<<endl;
	
		//prompt for the user choice
		cout<<"\tEnter your choice (1,2,3):\t";
		//input value from user
		cin>>choice;
	}while(!(choice==1 || choice ==2 || choice ==3));

	//return user choice
	return choice;
}

//function to clear previous screen content
void clearScreen()
{
	system("cls");
}

// Display the wellcome message
// with the title of the program
void wellcomeScreen()
{
	cout<<"\n\t*********************************************************";
	cout<<"\n\t*** Wellcome to the Student Course Enrollment Program ***";
	cout<<"\n\t*********************************************************"<<endl<<endl;
}

//Display good bye message
void displayGoodByeMessage()
{
	cout<<"\n\t**********************************************************"
		<<"\n\t*** Thanks for using Student Course Enrollment Program ***"
		<<"\n\t**********************************************************\n";
}

//function that will prompt for the basic user information
//save it to the file named Users
//generate 3 digit verification code
//save the verification code to the file named Email
void createAccount()
{
	//required arrays to hold user details from file
	string arr_fname[100],arr_lname[100],arr_dob[100],arr_contactno[100],arr_username[100],arr_password[100],arr_usertype[100];
	int numOfUsers=0;
	int num_dob =0;

	//required variables to hold the values entered by the user
	string usr_fname,usr_lname;
	string username,password;
	string dob,contact_num;
	string usr_type;
	int verification_code;
	char confirmation;
	bool ageValid=false;

	//Calling clearScreen()
	clearScreen();

	//Read all user details from file to array
	//ifstream class object
	ifstream userfileread("Users.txt");

	//check if file opens
	if(userfileread.is_open())
	{
		while(!userfileread.eof())
		{
			//read till the end of the file
			userfileread>>arr_fname[numOfUsers];
			userfileread>>arr_lname[numOfUsers];
			userfileread>>arr_dob[numOfUsers];
			userfileread>>arr_contactno[numOfUsers];
			userfileread>>arr_usertype[numOfUsers];
			userfileread>>arr_username[numOfUsers];
			userfileread>>arr_password[numOfUsers];

			numOfUsers++;
		}
		numOfUsers--;
		userfileread.close();
	}

	//Display the title
	cout<<"\n\t**************************"
		<<"\n\t*** Create new Account ***"
		<<"\n\t**************************\n"<<endl;

	cout<<"\tEnter user type (A for Admin, T for Teacher, S for Student) :";
	cin>>usr_type;

	if(usr_type=="A")
	{
		usr_type="Admin";
	}
	else if(usr_type=="T")
	{
		usr_type="Teacher";
	}
	else if(usr_type=="S")
	{
		usr_type="Student";
	}

	//prompt for the user basic information
	cout<<"\tEnter first name :";
	cin>>usr_fname;

	cout<<"\tEnter last name :";
	cin>>usr_lname;

	//loop to check if the username is unique
	do
	{
		cout<<"\tEnter Unique ID :";
		cin>>username;
	}while(!isUsernameUnique(username));
	
	cout<<"\tEnter password :";
	cin>>password;

	//loop to check the age below 67 if user type is teacher
	if(usr_type=="Teacher")
	{
		do
		{
			cout<<"\tEnter dob (dd/mm/yyyy):";
			cin>>dob;

			//convert string to number
			num_dob = getAge(dob);

			if(2018-num_dob<67)
			{
				ageValid=true;
				break;
			}
			else
			{
				cout<<"\n\tYou are over aged..."<<endl<<"\t";
				ageValid=false;
				system("pause");
				return ;
			}

		}while(!ageValid);
	}
	else
	{
		cout<<"\tEnter dob (dd/mm/yyyy):";
		cin>>dob;
	}

	cout<<"\tEnter contact No :";
	cin>>contact_num;
	
	cout<<"\n\tAre you sure to proceed with creating account (Y/N):";
	cin>>confirmation;

	//check if user want to create account
	if(confirmation=='y' || confirmation=='Y')
	{
		//Reading previous data to the arrays

		//saving user information into the file name Users.txts

		//ofstream class object
		ofstream userfile("Users.txt");

		//check if file is opened successfully
		if(userfile.is_open())
		{
			//Write previous data to the file
			for(int i=0;i<numOfUsers;i++)
			{
				userfile<<arr_fname[i]<<endl;
				userfile<<arr_lname[i]<<endl;
				userfile<<arr_dob[i]<<endl;
				userfile<<arr_contactno[i]<<endl;
				userfile<<arr_usertype[i]<<endl;
				userfile<<arr_username[i]<<endl;
				userfile<<arr_password[i]<<endl;
			}

			//storing user firstname to file
			userfile<<usr_fname<<endl;
			//storing user lastname to file
			userfile<<usr_lname<<endl;
			//storing user dob to file
			userfile<<dob<<endl;
			//storing user contact number to file
			userfile<<contact_num<<endl;
			//storing user type to file
			userfile<<usr_type<<endl;
			//storing user username to file
			userfile<<username<<endl;
			//storing user password to file
			userfile<<password<<endl;

			//closing file
			userfile.close();

			//Calling genVerificationCode()
			verification_code = genVerificationCode();

			sendCodeByEmail(verification_code);
		}
		//else display error message
		else
			cout<<"\n\tUnable to open file";
	}
}

//receive dob 
//extract year
//convert to int and return
int getAge(string dob)
{
	int n = dob.length();  
    string year;

    // declaring character array 
    char* arr_dob = new char[n+1]; 
    int i=0;

    // copying the contents of the  
    // string to char array 
    strcpy(arr_dob, dob.c_str());  
      
/*    for (int i=0; i<n; i++) 
      cout << arr_dob[i];     
  */
    // Returns first token  
    char *token = strtok(arr_dob, "/"); 
    
	i=0;

    // Keep printing tokens while one of the 
    // delimiters present in arr_dob[]. 
    while (i<3) 
    {  
		year = token;
        token = strtok(NULL, "/"); 
		i++;
    } 

	delete (arr_dob);

	return 2018-stoi(year);
}

//function to check if the username already exist
//if user exists the function will return false
//else user will return true
bool isUsernameUnique(string username)
{
	//required variable to hold the data content of file
	string temp;

	//ifstream class object to read data content from Users.txt file
	ifstream file ("Users.txt");

	//check if file exists or is open successfully
	if(file.is_open())
	{
		//reading data line by line
		//checking the username if exists then return false
		//else return true
		
		while(!file.eof())
		{
			//reading firstname and ignore
			getline(file,temp);
			//reading lastname and ignore
			getline(file,temp);
			//reading dob and ignore
			getline(file,temp);
			//reading contact number and ignore
			getline(file,temp);
			//reading user type and ignore
			getline(file,temp);
			//reading username
			getline(file,temp);

			//check if username is same as entered by new user
			if(username==temp)
			{
				//username is not unique return false
				cout<<"\tUsername already exists.\n";
				
				//closing file
				file.close();
				return false;
			}
			//reading password
			getline(file,temp);
			//reading status
			getline(file,temp);

		}

		//closing file
		file.close();
		return true;
	}
	
	//closing file
	file.close();
	return true;
}

// Generates 3 digit random number
// numbers in range [lower, upper]. 
int genVerificationCode()
{
	//declaring lower and upper limit 
	int lower=100;
	int upper=999;

	
	//number variable will hold the generated random number
	int num = (rand() % (upper - lower + 1)) + lower;

	//returning the generated random number
	return num;
}

//receive the verification code
//save verification code to the file named Email.txt
void sendCodeByEmail(int verificationCode)
{
	//ofstream class object to hold email.txt file
	ofstream emailFile("Email.txt");

	//check if file opened successfully
	if(emailFile.is_open())
	{
		//saving verification code to the file name Email.txt
		emailFile<<verificationCode<<endl;

		//closing file
		emailFile.close();

		//display message
		cout<<"\n\tVerification code has been sended to your Email\n\t";
		system("pause");
	}
	//else display error message
	else
		cout<<"\n\tUnable to open file";
}

//Display the verification screen
//Prompt the user to enter the verification code
//if code is valid then proceed further
//otherwise prompt again 
//after 3 attempt go back to login screen
bool displayVerificationScreen()
{
	//required variable to hold the verification code entered by user
	int verification_code,temp_code;
	int attempt=0;
	bool isverified=false;

	//ifstream class object
	ifstream emailFile("Email.txt");

	//check if file open successfully
	if(emailFile.is_open())
	{
		//read code from the file
		emailFile>>temp_code;

		//closing the file
		emailFile.close();
	}
	else
		cout<<"\n\tUnable to open the file!";
	
	while(attempt<3)
	{
		
		//prompt user to enter the verification code
		cout<<"\tEnter your's verification code :";
		cin>>verification_code;
		
		//check if user entered verification code is valid
		if(verification_code==temp_code)
		{
			isverified=true;
			break;
		}
		else
		{
			cout<<"\n\t"<<3-attempt<<" attempts left of 3"<<endl;
			attempt++;
		}
	}

	//check the attempts are over or isverified
	if(isverified)
	{
		return true;
	}
	else 
		return false;
}

//prompt user for username and password
//check if username and password exists
//and valid then login else display message
void signIn()
{
	//required variable to hold the username and password
	string username,password;
	string temp_username,temp_password,temp_usertype;
	string temp;
	bool isvalid=false;

	//Calling clearScreen()
	
	do
	{	
		clearScreen();

		//Display the title
		cout<<"\n\t***************************"
			<<"\n\t*** Enter Login Details ***"
			<<"\n\t***************************\n"<<endl;
	
		//ifsstream class object
		ifstream userFile("Users.txt");

		//prompt for the username
		cout<<"\n\tEnter your Username :";
		cin>>username;

		//prompt for the password
		cout<<"\tEnter your password :";
		cin>>password;

		//check if file is opened properly
		if(userFile.is_open())
		{
			//iterate through every record
			while(!userFile.eof())
			{
				//reading firstname and ignore
				getline(userFile,temp);
				//reading lastname and ignore
				getline(userFile,temp);
				//reading dob and ignore
				getline(userFile,temp);
				//reading contact number and ignore
				getline(userFile,temp);
				//reading user type and ignore
				getline(userFile,temp_usertype);
				//reading username
				getline(userFile,temp_username);
				//reading password
				getline(userFile,temp_password);

				//check if the username and password are valid
				if(username==temp_username && password==temp_password)
				{
					isvalid=true;
					break;
				}
			}

			if(!isvalid)
			{
				cout<<"\n\tInvalid username or password. Please try again...\n\t";
				system("pause");
			}
		}
		else
			cout<<"\n\tUnable to open file!";
		
		//closing file
		userFile.close();
	}while(!isvalid);


	//Calling displayVerificationScreen()
	isvalid = displayVerificationScreen();

	//check if verification code is valid
	if(isvalid)
	{
		//Calling gotoMainMenu()
		gotoMainMenu(temp_usertype,username);
	}
	else
	{
		clearScreen();
		signIn();
	}
}

//receive usertype and username
//display Main Menu according to the user type
void gotoMainMenu(string usertype,string username)
{
	//check for the user type
	if(usertype=="Admin")
	{
		displayMainAdminMenu(username);
	}
	else if(usertype =="Teacher")
	{
		displayTeacherMenu(username);
	}
	else if(usertype =="Student")
	{
		displayStudentMenu(username);
	}
}

//display Admin Menu
void displayMainAdminMenu(string username)
{
	int user_choice;

	do
	{
		//Calling clearScreen()
		clearScreen();

		//display menu
		cout<<"\n\t*************************"
			<<"\n\t*** Admin Main Menu ***"
			<<"\n\t*************************";

		cout<<"\n\n\t1. All course enrollment requests"<<endl
			<<"\t2. All course assignment requests"<<endl
			<<"\t3. sign out"<<endl;

		cout<<"\n\tEnter your choice : ";
		cin>>user_choice;

		switch(user_choice)
		{
		case 1:
			CourseEnrolRequest();
			break;
		
		case 2:
			CourseAssignRequest();
			break;
		
		case 3:
			return ;
			break;

		default:
			cout<<"\n\tInvalid choice please try again...";
		}

	}while(user_choice!=3);
}

//display Teacher Menu
void displayTeacherMenu(string username)
{
	int user_choice;

	do
	{
		//Calling clearScreen()
		clearScreen();

		//display menu
		cout<<"\n\t*************************"
			<<"\n\t*** Teacher Main Menu ***"
			<<"\n\t*************************";

		cout<<"\n\n\t1. Select Course"<<endl
			<<"\t2. View Selected Course"<<endl
			<<"\t3. View Enrolled Student in a Courses"<<endl
			<<"\t4. sign out"<<endl;

		cout<<"\n\tEnter your choice : ";
		cin>>user_choice;

		switch(user_choice)
		{
		case 1:
			selectCourse(username);
			break;
		
		case 2:
			ViewSelectedCourseList(username);
			break;

		case 3:
			ViewEnrolStudentInCourse(username);
			break;
		
		case 4:
			return ;
			break;

		default:
			cout<<"\n\tInvalid choice please try again...";
		}

	}while(user_choice!=4);
}

//display Student Menu
void displayStudentMenu(string username)
{
	int user_choice;

	do
	{
		//Calling clearScreen()
		clearScreen();

		//display menu
		cout<<"\n\t*************************"
			<<"\n\t*** Student Main Menu ***"
			<<"\n\t*************************";

		cout<<"\n\n\t1. Enroll course"<<endl
			<<"\t2. View Enrolled Courses"<<endl
			<<"\t3. View Assigned Teacher by Course"<<endl
			<<"\t4. sign out"<<endl;

		cout<<"\n\tEnter your choice : ";
		cin>>user_choice;

		switch(user_choice)
		{
		case 1:
			EnrollRequests(username);
			break;
		
		case 2:
			ViewEnrolCourseList(username);
			break;
		
		case 3:
			ViewAssignedTeacherToCourse(username);
			break;
		
		case 4:
			return ;
			break;

		default:
			cout<<"\n\tInvalid choice please try again...";
		}

	}while(user_choice!=4);
}

//view list of all courses and apply to select a course
//check if the course is not already added by this teacher
//check if more then 3 courses are selected by the teacher
void selectCourse(string username)
{
	//required variable
	int numOfCourse=0;
	string c_code[100],c_Title[100],c_creditHr[100],c_theory[100],c_lab[100];
	string temp;
	int courseSel=0;
	bool validCourse=false;

	//ifstream class object
	ifstream courseFile("Courses.txt");

	//ClearScreen
	clearScreen();

	cout<<"\n\t******************************"
		<<"\n\t*** Select Course To Teach ***"
		<<"\n\t******************************\n";

	//check maximum selected course
	if(!isMaxSelCourseReached(username))
	{
		//check if file exists or is open successfully
		if(courseFile.is_open())
		{
			//reading data line by line
			//checking the username if exists then return false
			//else return true
		
			while(!courseFile.eof())
			{
				//reading course code
				getline(courseFile,c_code[numOfCourse]);
				//reading course code
				getline(courseFile,c_Title[numOfCourse]);
				//reading course code
				getline(courseFile,c_creditHr[numOfCourse]);
				//reading course code
				getline(courseFile,c_theory[numOfCourse]);
				//reading course code
				getline(courseFile,c_lab[numOfCourse]);

				numOfCourse++;
			}

			courseFile.close();
		}
	
		if(numOfCourse<=0)
		{
			cout<<"\n\tNo courses to select...!";
			system("pause");
			return;
		}
		else
		{
			if(!isMaxSelCourseReached(username))
			{
				cout<<"\n\tSelect from following list of courses:\n";

				cout<<"\n\t"<<setw(8)<<"SrNo."<<setw(10)<<"Course Code"<<setw(50)<<"Title"<<setw(10)<<"Credit Hr"<<setw(10)<<"Theory"<<setw(10)<<"Lab"<<endl;

				for(int i=0;i<numOfCourse;i++)
				{
					cout<<"\n\t"<<setw(8)<<i+1<<setw(10)<<c_code[i]<<setw(50)<<c_Title[i]<<setw(10)<<c_creditHr[i]<<setw(10)<<c_theory[i]<<setw(10)<<c_lab[i];
				}

				do
				{
					cout<<"\n\tSelect from above list using the SrNo. as a selection :";
					cin>>courseSel;

					validCourse=isCourseAlreadySelected(c_code[courseSel-1],username);

					if(validCourse)
					{
						cout<<"\n\tCourse already selected please try other course ...!\n";
						system("pause");
						return ;
					}

				}while(validCourse);

				//applying for the course selection process
				//saving to the file
				applyCourseSelection(username,c_code[courseSel-1]);

			}
			else
			{
				cout<<"\n\tOoops! you reached maximum limit of the Course Selection...";
				cout<<endl;
				system("pause");
				return ;
			}
		}
	}
	else
	{
		cout<<"\n\tYou already have reached maximum course selection i.e 3.\n";
		system("pause");
		return;
	}
}

//check if the course is already selected by the logged in user
//if course is selected then return true
//otherwise return false
bool isCourseAlreadySelected(string c_code,string username)
{
	//required variables
	bool isAlreadySelected=false;
	string temp_tname,temp_ccode,temp_cstatus;

	//ifstream class object
	ifstream teacherSelectedCourseFile("TeacherSelectedCourses.txt");

	//check if file is ready to open successfully
	if(teacherSelectedCourseFile.is_open())
	{
		while(!teacherSelectedCourseFile.eof())
		{
			//reading teacher name from file
			getline(teacherSelectedCourseFile,temp_tname);

			if(temp_tname!="")
			{
				do{
					//reading course code from the file
					getline(teacherSelectedCourseFile,temp_ccode);

					//check if it is the last record of the course for the teacher
					if(temp_ccode!="***")
					{
						//check if the course already exists
						if(temp_ccode==c_code)
						{
							isAlreadySelected=true;
							teacherSelectedCourseFile.close();
							return true;
						}

						//reading course code approval status from the file
						getline(teacherSelectedCourseFile,temp_cstatus);
					}
					else
						break;
				}while(temp_ccode!="***");
			}
			else
				break;
		}
	}

	teacherSelectedCourseFile.close();
	return false;
}

//check if the maximum course is selected by the logged in user
//if maximum course selection reach to 3 then return true
//otherwise return false
bool isMaxSelCourseReached(string username)
{
	//required variables
	int numOfCourse=0;
	string temp_tname,temp_ccode,temp_cstatus;

	//ifstream class object
	ifstream teacherSelectedCourseFile("TeacherSelectedCourses.txt");

	//check if file is ready to open successfully
	if(teacherSelectedCourseFile.is_open())
	{
		while(!teacherSelectedCourseFile.eof())
		{
			//reading teacher name from file
			//search for the logged in teacher
			getline(teacherSelectedCourseFile,temp_tname);

			if(temp_tname!="")
			{
				//check if the teacher is current logged in teacher
				if(temp_tname==username)
				{
					do{
						getline(teacherSelectedCourseFile,temp_ccode);

						if(temp_ccode!="***")
						{
							getline(teacherSelectedCourseFile,temp_cstatus);
							numOfCourse++;
						}
						else
							break;
					}while(temp_ccode!="***");
					break;
				}
				else
				{
					do{
						getline(teacherSelectedCourseFile,temp_ccode);
					}while(temp_ccode!="***");
				}
			}
			else
				break;
		}
	}

	teacherSelectedCourseFile.close();

	if(numOfCourse==3)
	{
		return true;
	}
	else
		return false;
}

//receive teacher unique id and course code
//apply for the course to be selected with the status as pending
void applyCourseSelection(string username,string c_code)
{
	//required array list
	string temp_teachername[100],temp_ccode[100],temp_cstatus[100];
	int temp_numOfCourse[100]={0};
	int count=0,c_count=0;

	//ifstream class object
	ifstream teacherSelCoureFile("TeacherSelectedCourses.txt");

	//check if file is ready to open successfully
	if(teacherSelCoureFile.is_open())
	{
		while(!teacherSelCoureFile.eof())
		{
			//reading teacher name from file
			//search for the logged in teacher
			getline(teacherSelCoureFile,temp_teachername[count]);

			if(temp_teachername[count]!="")
			{
				do{
					getline(teacherSelCoureFile,temp_ccode[c_count]);
				
					if(temp_ccode[c_count]!="***")
					{
						getline(teacherSelCoureFile,temp_cstatus[c_count]);
					
						temp_numOfCourse[count] = temp_numOfCourse[count]+1;
					}
					else
						break;
					c_count++;
				}while(temp_ccode[c_count]!="***");	
			}
			else
				break;
			count++;
		}
	}

	teacherSelCoureFile.close();

	//writing data back with new course
	//ofstream class object
	ofstream courseSelFile("TeacherSelectedCourses.txt");

	//check if file is ready to open successfully
	if(courseSelFile.is_open())
	{
		if(count<=0)
		{
			courseSelFile<<username<<endl;
			courseSelFile<<c_code<<endl;
			courseSelFile<<"Pending"<<endl;
			courseSelFile<<"***"<<endl;
		}
		else
		{
			
			bool isNewCourseAdded=false;
			int ccode_index=0;

			for(int i=0;i<count;i++)
			{
				//writing down the course
				courseSelFile<<temp_teachername[i]<<endl;
			
				if(temp_teachername[i]==username)
				{
					for(int j=ccode_index;j<getSum(temp_numOfCourse,i);ccode_index=++j)
					{
						courseSelFile<<temp_ccode[j]<<endl;
						courseSelFile<<temp_cstatus[j]<<endl;
					}
					courseSelFile<<c_code<<endl;
					courseSelFile<<"Pending"<<endl;
					isNewCourseAdded=true;
				}
				else
				{
					for(int j=ccode_index;j<getSum(temp_numOfCourse,i);ccode_index=++j)
					{
						courseSelFile<<temp_ccode[j]<<endl;
						courseSelFile<<temp_cstatus[j]<<endl;		
					}
				}
				courseSelFile<<"***\n";
			}

			if(!isNewCourseAdded)
			{
				courseSelFile<<username<<endl;
				courseSelFile<<c_code<<endl;
				courseSelFile<<"Pending"<<endl;

				courseSelFile<<"***\n";
			}
		}
		courseSelFile.close();
	}
	else
	{
		cout<<"\n\tFile not found...!"<<endl;
		system("pause");
		return ;
	}
	
}

//function get the sum of previous index values in an array
int getSum(int array_courses[],int index)
{
	int sum=0;

	for(int i=0;i<index;i++)
	{
		sum += array_courses[i];
	}
	sum+=array_courses[index];

	return sum;
	
}

//view list of all courses and apply to enrol a course
//check if the course is already enrolled by maximum of 10 students
void EnrollRequests(string username)
{
	//required variable
	int numOfCourse=0;
	string c_code[100],c_Title[100],c_creditHr[100],c_theory[100],c_lab[100];
	string temp;
	int courseSel=0;
	bool validCourse=false;

	//ifstream class object
	ifstream courseFile("Courses.txt");

	//ClearScreen
	clearScreen();

	cout<<"\n\t******************************"
		<<"\n\t*** Select Course To Enrol ***"
		<<"\n\t******************************\n";

	//check maximum selected course
	if(!isMaxEnrolCourseReached(username))
	{
		//check if file exists or is open successfully
		if(courseFile.is_open())
		{
			//reading data line by line
			//checking the username if exists then return false
			//else return true
		
			while(!courseFile.eof())
			{
				//reading course code
				getline(courseFile,c_code[numOfCourse]);
				//reading course code
				getline(courseFile,c_Title[numOfCourse]);
				//reading course code
				getline(courseFile,c_creditHr[numOfCourse]);
				//reading course code
				getline(courseFile,c_theory[numOfCourse]);
				//reading course code
				getline(courseFile,c_lab[numOfCourse]);

				numOfCourse++;
			}

			courseFile.close();
		}
	
		if(numOfCourse<=0)
		{
			cout<<"\n\tNo courses to select...!";
			system("pause");
			return;
		}
		else
		{
			if(!isMaxEnrolCourseReached(username))
			{
				cout<<"\n\tSelect from following list of courses:\n";

				cout<<"\n\t"<<setw(8)<<"SrNo."<<setw(10)<<"Course Code"<<setw(50)<<"Title"<<setw(10)<<"Credit Hr"<<setw(10)<<"Theory"<<setw(10)<<"Lab"<<endl;

				for(int i=0;i<numOfCourse;i++)
				{
					cout<<"\n\t"<<setw(8)<<i+1<<setw(10)<<c_code[i]<<setw(50)<<c_Title[i]<<setw(10)<<c_creditHr[i]<<setw(10)<<c_theory[i]<<setw(10)<<c_lab[i];
				}

				do
				{
					cout<<"\n\tSelect from above list using the SrNo. as a selection :";
					cin>>courseSel;

					validCourse=isCourseAlreadyEnrolled(c_code[courseSel-1],username);

					if(validCourse)
					{
						cout<<"\n\tCourse already selected please try other course ...!\n";
						system("pause");
						return ;
					}

				}while(validCourse);

				//applying for the course selection process
				//saving to the file
				applyCourseEnrollment(username,c_code[courseSel-1]);

			}
			else
			{
				cout<<"\n\tOoops! you reached maximum limit of the Course Selection...";
				cout<<endl;
				system("pause");
				return ;
			}
		}
	}
	else
	{
		cout<<"\n\tYou already have reached maximum course selection i.e 5.\n";
		system("pause");
		return;
	}
}

//check if the maximum course is enrolled by the student
//if maximum course enrollment reach to 5 then return true
//otherwise return false
bool isMaxEnrolCourseReached(string username)
{
	//required variables
	int numOfCourse=0;
	string temp_sname,temp_ccode,temp_cstatus;

	//ifstream class object
	ifstream studentSelectedCourseFile("StudentEnrolledCourses.txt");

	//check if file is ready to open successfully
	if(studentSelectedCourseFile.is_open())
	{
		while(!studentSelectedCourseFile.eof())
		{
			//reading student name from file
			//search for the logged in teacher
			getline(studentSelectedCourseFile,temp_sname);

			if(temp_sname!="")
			{
				//check if the student is current logged in teacher
				if(temp_sname==username)
				{
					do{
						getline(studentSelectedCourseFile,temp_ccode);

						if(temp_ccode!="***")
						{
							getline(studentSelectedCourseFile,temp_cstatus);
							numOfCourse++;
						}
						else
							break;
					}while(temp_ccode!="***");
					break;
				}
				else
				{
					do{
						getline(studentSelectedCourseFile,temp_ccode);
					}while(temp_ccode!="***");
				}
			}
			else
				break;
		}
	}

	studentSelectedCourseFile.close();

	if(numOfCourse==5)
	{
		return true;
	}
	else
		return false;
}

//check if the course is already enrolled by the student
//if course is enrolled then return true
//otherwise return false
bool isCourseAlreadyEnrolled(string c_code,string username)
{
	//required variables
	bool isAlreadySelected=false;
	string temp_sname,temp_ccode,temp_cstatus;

	//ifstream class object
	ifstream studentSelectedCourseFile("StudentEnrolledCourses.txt");

	//check if file is ready to open successfully
	if(studentSelectedCourseFile.is_open())
	{
		while(!studentSelectedCourseFile.eof())
		{
			//reading student name from file
			getline(studentSelectedCourseFile,temp_sname);

			if(temp_sname!="")
			{
				if(temp_sname==username)
				{
					do{
						//reading course code from the file
						getline(studentSelectedCourseFile,temp_ccode);

						//check if it is the last record of the course for the student
						if(temp_ccode!="***")
						{
							//check if the course already exists
							if(temp_ccode==c_code)
							{
								isAlreadySelected=true;
								studentSelectedCourseFile.close();
								return true;
							}

							//reading course code approval status from the file
							getline(studentSelectedCourseFile,temp_cstatus);
						}
						else
							break;
					}while(temp_ccode!="***");
				}
				else
				{
					do{
						//reading course code from the file
						getline(studentSelectedCourseFile,temp_ccode);

						//check if it is the last record of the course for the student
						if(temp_ccode!="***")
						{
							//reading course code approval status from the file
							getline(studentSelectedCourseFile,temp_cstatus);
						}
						else
							break;
					}while(temp_ccode!="***");
				}
			}
			else
				break;
		}
	}

	studentSelectedCourseFile.close();
	return false;
}

//receive student unique id and course code
//apply for the course to be enrolled with the status as pending
void applyCourseEnrollment(string username,string c_code)
{
	//required array list
	string temp_studentname[100],temp_ccode[100],temp_cstatus[100];
	int temp_numOfCourse[100]={0};
	int count=0,c_count=0;

	//ifstream class object
	ifstream studentEnrolCourseFile("StudentEnrolledCourses.txt");

	//check if file is ready to open successfully
	if(studentEnrolCourseFile.is_open())
	{
		while(!studentEnrolCourseFile.eof())
		{
			//reading teacher name from file
			//search for the logged in teacher
			getline(studentEnrolCourseFile,temp_studentname[count]);

			if(temp_studentname[count]!="")
			{
				do{
					getline(studentEnrolCourseFile,temp_ccode[c_count]);
				
					if(temp_ccode[c_count]!="***")
					{
						getline(studentEnrolCourseFile,temp_cstatus[c_count]);
					
						temp_numOfCourse[count] = temp_numOfCourse[count]+1;
					}
					else
						break;
					c_count++;
				}while(temp_ccode[c_count]!="***");	
			}
			else
				break;
			count++;
		}
	}

	studentEnrolCourseFile.close();

	//writing data back with new course
	//ofstream class object
	ofstream courseEnrolFile("StudentEnrolledCourses.txt");

	//check if file is ready to open successfully
	if(courseEnrolFile.is_open())
	{
		if(count<=0)
		{
			courseEnrolFile<<username<<endl;
			courseEnrolFile<<c_code<<endl;
			courseEnrolFile<<"Pending"<<endl;
			courseEnrolFile<<"***"<<endl;
		}
		else
		{
			
			bool isNewCourseAdded=false;
			int ccode_index=0;

			for(int i=0;i<count;i++)
			{
				//writing down the course
				courseEnrolFile<<temp_studentname[i]<<endl;
			
				if(temp_studentname[i]==username)
				{
					for(int j=ccode_index;j<getSum(temp_numOfCourse,i);ccode_index=++j)
					{
						courseEnrolFile<<temp_ccode[j]<<endl;
						courseEnrolFile<<temp_cstatus[j]<<endl;
					}
					courseEnrolFile<<c_code<<endl;
					courseEnrolFile<<"Pending"<<endl;
					isNewCourseAdded=true;
				}
				else
				{
					for(int j=ccode_index;j<getSum(temp_numOfCourse,i);ccode_index=++j)
					{
						courseEnrolFile<<temp_ccode[j]<<endl;
						courseEnrolFile<<temp_cstatus[j]<<endl;		
					}
				}
				courseEnrolFile<<"***\n";
			}

			if(!isNewCourseAdded)
			{
				courseEnrolFile<<username<<endl;
				courseEnrolFile<<c_code<<endl;
				courseEnrolFile<<"Pending"<<endl;

				courseEnrolFile<<"***\n";
			}
		}
		courseEnrolFile.close();
	}
	else
	{
		cout<<"\n\tFile not found...!"<<endl;
		system("pause");
		return ;
	}
	
}

//function will receive the student usernam and 
//will display the list of courses enrolled by him
void ViewEnrolCourseList(string username)
{
	//required variable
	int numOfCourse=0;
	string c_code[100],c_Title[100],c_creditHr[100],c_theory[100],c_lab[100];
	string temp;
	int courseSel=0;
	bool validCourse=false;
	string temp_sname,temp_ccode,temp_cstatus;

	//ifstream class object
	ifstream courseFile("Courses.txt");

	//ClearScreen
	clearScreen();

	cout<<"\n\t******************************"
		<<"\n\t*** List of Enrol Courses ***"
		<<"\n\t******************************\n";

	//check if file exists or is open successfully
	if(courseFile.is_open())
	{
		//reading data line by line
		//checking the username if exists then return false
		//else return true
		
		while(!courseFile.eof())
		{
			//reading course code
			getline(courseFile,c_code[numOfCourse]);
			//reading course code
			getline(courseFile,c_Title[numOfCourse]);
			//reading course code
			getline(courseFile,c_creditHr[numOfCourse]);
			//reading course code
			getline(courseFile,c_theory[numOfCourse]);
			//reading course code
			getline(courseFile,c_lab[numOfCourse]);

			numOfCourse++;
		}

		courseFile.close();
	}

	cout<<"\n\tFollowing are the courses enrolled by the student:\n";
	
	//ifstream class object
	ifstream studentSelectedCourseFile("StudentEnrolledCourses.txt");

	//check if file is ready to open successfully
	if(studentSelectedCourseFile.is_open())
	{
		while(!studentSelectedCourseFile.eof())
		{
			//reading student name from file
			//search for the logged in student
			getline(studentSelectedCourseFile,temp_sname);

			if(temp_sname!="")
			{
				//check if the student is current logged in teacher
				if(temp_sname==username)
				{
					cout<<"\n\t"<<setw(8)<<"SrNo."<<setw(10)<<"Course Code"<<setw(50)<<"Title"<<setw(10)<<"Credit Hr"<<setw(10)<<"Theory"<<setw(10)<<"Lab"<<setw(10)<<"Status"<<endl;

					do{
						getline(studentSelectedCourseFile,temp_ccode);

						if(temp_ccode!="***")
						{

							getline(studentSelectedCourseFile,temp_cstatus);
							//search for the course details in the array
							//that are already feed with the course detail list
							//from the courses.txt file
							for(int k=0;k<numOfCourse;k++)
							{
								if(c_code[k]==temp_ccode)
								{
									cout<<"\n\t"<<setw(8)<<k+1<<setw(10)<<c_code[k]<<setw(50)<<c_Title[k]<<setw(10)<<c_creditHr[k]<<setw(10)<<c_theory[k]<<setw(10)<<c_lab[k]<<setw(10)<<temp_cstatus;
								}
							}
							
							courseSel++;
						}
						else
							break;
					}while(temp_ccode!="***");
					break;
				}
				else
				{
					do{
						getline(studentSelectedCourseFile,temp_ccode);
					}while(temp_ccode!="***");
				}
			}
			else
				break;
		}
	}

	studentSelectedCourseFile.close();

	if(courseSel<=0)
	{
		cout<<"\n\tNo courses are enrolled by you...!!!"<<endl;
	}

	cout<<endl<<"\t";
	system("pause");
}

//function will receive the student usernam and 
//will display the list of courses enrolled by him
void ViewSelectedCourseList(string username)
{
	//required variable
	int numOfCourse=0;
	string c_code[100],c_Title[100],c_creditHr[100],c_theory[100],c_lab[100];
	string temp;
	int courseSel=0;
	bool validCourse=false;
	string temp_tname,temp_ccode,temp_cstatus;

	//ifstream class object
	ifstream courseFile("Courses.txt");

	//ClearScreen
	clearScreen();

	cout<<"\n\t******************************"
		<<"\n\t*** List of Selected Courses ***"
		<<"\n\t******************************\n";

	//check if file exists or is open successfully
	if(courseFile.is_open())
	{
		//reading data line by line
		//checking the username if exists then return false
		//else return true
		
		while(!courseFile.eof())
		{
			//reading course code
			getline(courseFile,c_code[numOfCourse]);
			//reading course code
			getline(courseFile,c_Title[numOfCourse]);
			//reading course code
			getline(courseFile,c_creditHr[numOfCourse]);
			//reading course code
			getline(courseFile,c_theory[numOfCourse]);
			//reading course code
			getline(courseFile,c_lab[numOfCourse]);

			numOfCourse++;
		}

		courseFile.close();
	}

	cout<<"\n\tFollowing are the courses selected by the Teacher:\n";
	
	//ifstream class object
	ifstream teacherSelectedCourseFile("TeacherSelectedCourses.txt");

	//check if file is ready to open successfully
	if(teacherSelectedCourseFile.is_open())
	{
		while(!teacherSelectedCourseFile.eof())
		{
			//reading student name from file
			//search for the required username
			getline(teacherSelectedCourseFile,temp_tname);

			if(temp_tname!="")
			{
				//check if the teacher is current logged in teacher
				if(temp_tname==username)
				{
					cout<<"\n\t"<<setw(8)<<"SrNo."<<setw(10)<<"Course Code"<<setw(50)<<"Title"<<setw(10)<<"Credit Hr"<<setw(10)<<"Theory"<<setw(10)<<"Lab"<<setw(10)<<"Status"<<endl;

					do{
						getline(teacherSelectedCourseFile,temp_ccode);

						if(temp_ccode!="***")
						{

							getline(teacherSelectedCourseFile,temp_cstatus);
							//search for the course details in the array
							//that are already feed with the course detail list
							//from the courses.txt file
							for(int k=0;k<numOfCourse;k++)
							{
								if(c_code[k]==temp_ccode)
								{
									cout<<"\n\t"<<setw(8)<<k+1<<setw(10)<<c_code[k]<<setw(50)<<c_Title[k]<<setw(10)<<c_creditHr[k]<<setw(10)<<c_theory[k]<<setw(10)<<c_lab[k]<<setw(10)<<temp_cstatus;
								}
							}
							
							courseSel++;
						}
						else
							break;
					}while(temp_ccode!="***");
					break;
				}
				else
				{
					do{
						getline(teacherSelectedCourseFile,temp_ccode);
					}while(temp_ccode!="***");
				}
			}
			else
				break;
		}
	}

	teacherSelectedCourseFile.close();

	if(courseSel<=0)
	{
		cout<<"\n\tNo courses are selected by you...!!!"<<endl;
	}

	cout<<endl<<"\t";
	system("pause");
}

//function display the list of course along with the teacher
//detail that is assigned to the course
void ViewAssignedTeacherToCourse(string username)
{
	//required variable
	int numOfCourse=0;
	string c_code[100],c_Title[100],c_creditHr[100],c_theory[100],c_lab[100];
	string temp;
	int courseSel=0;
	bool validCourse=false;
	string temp_sname,temp_ccode,temp_cstatus;

	//ifstream class object
	ifstream courseFile("Courses.txt");

	//ClearScreen
	clearScreen();

	cout<<"\n\t******************************"
		<<"\n\t*** List of Enrol Courses ***"
		<<"\n\t***  With Teacher Detail  ***"
		<<"\n\t******************************\n";

	//check if file exists or is open successfully
	if(courseFile.is_open())
	{
		//reading data line by line
		while(!courseFile.eof())
		{
			//reading course code
			getline(courseFile,c_code[numOfCourse]);
			//reading course code
			getline(courseFile,c_Title[numOfCourse]);
			//reading course code
			getline(courseFile,c_creditHr[numOfCourse]);
			//reading course code
			getline(courseFile,c_theory[numOfCourse]);
			//reading course code
			getline(courseFile,c_lab[numOfCourse]);

			numOfCourse++;
		}

		courseFile.close();
	}

	cout<<"\n\tFollowing are the courses enrolled by the student:\n";
	
	//ifstream class object
	ifstream studentSelectedCourseFile("StudentEnrolledCourses.txt");

	//check if file is ready to open successfully
	if(studentSelectedCourseFile.is_open())
	{
		while(!studentSelectedCourseFile.eof())
		{
			//reading student name from file
			//search for the logged in student
			getline(studentSelectedCourseFile,temp_sname);

			if(temp_sname!="")
			{
				//check if the student is current logged in teacher
				if(temp_sname==username)
				{
					//cout<<"\n\t"<<setw(8)<<"SrNo."<<setw(10)<<"Course Code"<<setw(50)<<"Title"<<setw(10)<<"Credit Hr"<<setw(10)<<"Theory"<<setw(10)<<"Lab"<<setw(10)<<"Status"<<endl;

					do{
						getline(studentSelectedCourseFile,temp_ccode);

						if(temp_ccode!="***")
						{

							getline(studentSelectedCourseFile,temp_cstatus);
							//search for the course details in the array
							//that are already feed with the course detail list
							//from the courses.txt file
							for(int k=0;k<numOfCourse;k++)
							{
								if(c_code[k]==temp_ccode)
								{
									cout<<"\n\tCourse Code  :"<<c_code[k]
									<<"\n\tCourse Title		:"<<c_Title[k]
									<<"\n\tCredit Hours		:"<<c_creditHr[k]
									<<"\n\tTheory			:"<<c_theory[k]
									<<"\n\tLab				:"<<c_lab[k]
									<<"\n\tEnrollment Status:"<<temp_cstatus;

									PrintTeacherDetail(FindAssignedTeacherForCourse(temp_ccode));
									break;
									//cout<<"\n\t"<<setw(8)<<k+1<<setw(10)<<c_code[k]<<setw(50)<<c_Title[k]<<setw(10)<<c_creditHr[k]<<setw(10)<<c_theory[k]<<setw(10)<<c_lab[k]<<setw(10)<<temp_cstatus;
								}
							}
							
							courseSel++;
						}
						else
							break;
					}while(temp_ccode!="***");
					break;
				}
				else
				{
					do{
						getline(studentSelectedCourseFile,temp_ccode);
					}while(temp_ccode!="***");
				}
			}
			else
				break;
		}
	}

	studentSelectedCourseFile.close();

	if(courseSel<=0)
	{
		cout<<"\n\tNo courses are enrolled by you...!!!"<<endl;
	}

	cout<<endl<<"\t";
	system("pause");
}

//function will receive course code
//find it in the teacherSelectedCourse.txt file
//if course is assigned to teacher then return teacher name (username/unique id)
//else will return NaN
string FindAssignedTeacherForCourse(string ccode)
{
	//ifstream class object to read the data from file
	ifstream tc_file("TeacherSelectedCourses.txt");
	string teachername;
	string temp_tname,temp_ccode,temp_cstatus;
	bool isfound=false;

	//check if file is opened
	if(tc_file.is_open())
	{
		while(!tc_file.eof())
		{
			//iterate thorugh every record
			getline(tc_file,temp_tname);

			if(temp_tname!="")
			{
				do{
					getline(tc_file,temp_ccode);
					
					if(temp_ccode!="***")
					{
						getline(tc_file,temp_cstatus);
						
						//check if the course is assigned to teacher
						if(temp_ccode==ccode)
						{
							teachername=temp_tname;
							isfound=true;
						}
					}
					else
						break;
				}while(temp_ccode!="***");
				
				if(isfound)
					break;
			}
			else
				break;
		}
		tc_file.close();
		
		if(isfound)
			return teachername;
		else 
			return "NaN";
	}
	else 
		return "NaN";

}

//function will receive the teacher unique id and
//will display the detail of teacher
void PrintTeacherDetail(string unique_id)
{
	//required variable to hold the data
	string temp;
	string temp_fname,temp_lname,temp_age,temp_contactnum,temp_type,temp_pass;
	
	//Display the title bar to distinguish
	cout<<"\n\t******************************************************"
		<<"\n\t****************** Assigned Teacher ******************\n"<<endl;
	
	//check if unique id is available
	if(unique_id!="NaN")
	{
		//ifsstream class object
		ifstream userFile("Users.txt");

		//check if file is opened properly
		if(userFile.is_open())
		{
			//iterate through every record
			while(!userFile.eof())
			{
				//reading firstname 
				getline(userFile,temp_fname);
				//reading lastname 
				getline(userFile,temp_lname);
				//reading dob 
				getline(userFile,temp_age);
				//reading contact number 
				getline(userFile,temp_contactnum);
				//reading user type 
				getline(userFile,temp_type);
				//reading username
				getline(userFile,temp);
				//reading password
				getline(userFile,temp_pass);

				//check if the username is found
				if(temp==unique_id)
				{
					//display the details
					cout<<"\n\tFirst Name :"<<temp_fname
						<<"\n\tLast Name  :"<<temp_lname
						<<"\n\tAge        :"<<getAge(temp_age)
						<<"\n\tContact No :"<<temp_contactnum
						<<"\n\tType       :"<<temp_type
						<<"\n\tUsername   :"<<temp;
		
					break;
				}
			}

		}
		else
			cout<<"\n\tUnable to open file!";

		//closing file
		userFile.close();
	}
	else
	{
		cout<<"\n\tCourse is not assigned to any teacher...!!!\n";
	}
	cout<<"\n\t******************************************************"
		<<"\n\t******************************************************\n"<<endl;

}

//function display the list of course along with the
//list of enrolled students in each course
void ViewEnrolStudentInCourse(string username)
{
	//required variable
	int numOfCourse=0;
	string c_code[100],c_Title[100],c_creditHr[100],c_theory[100],c_lab[100];
	string temp;
	int courseSel=0;
	bool validCourse=false;
	string temp_tname,temp_ccode,temp_cstatus;

	//ifstream class object
	ifstream courseFile("Courses.txt");

	//ClearScreen
	clearScreen();

	cout<<"\n\t*********************************"
		<<"\n\t*** List of Assigned Courses  ***"
		<<"\n\t*** With Enrol Student Detail ***"
		<<"\n\t*********************************\n";

	//check if file exists or is open successfully
	if(courseFile.is_open())
	{
		//reading data line by line
		while(!courseFile.eof())
		{
			//reading course code
			getline(courseFile,c_code[numOfCourse]);
			//reading course code
			getline(courseFile,c_Title[numOfCourse]);
			//reading course code
			getline(courseFile,c_creditHr[numOfCourse]);
			//reading course code
			getline(courseFile,c_theory[numOfCourse]);
			//reading course code
			getline(courseFile,c_lab[numOfCourse]);

			numOfCourse++;
		}

		courseFile.close();
	}

	cout<<"\n\tFollowing are the courses assigned to the Teacher ("<<username<<"):\n";
	
	//ifstream class object
	ifstream teacherSelectedCourseFile("TeacherSelectedCourses.txt");

	//check if file is ready to open successfully
	if(teacherSelectedCourseFile.is_open())
	{
		while(!teacherSelectedCourseFile.eof())
		{
			//reading student name from file
			//search for the required username
			getline(teacherSelectedCourseFile,temp_tname);

			if(temp_tname!="")
			{
				//check if the teacher is current logged in teacher
				if(temp_tname==username)
				{
/*					cout<<"\n\t"<<setw(8)<<"SrNo."<<setw(10)<<"Course Code"<<setw(50)<<"Title"<<setw(10)<<"Credit Hr"<<setw(10)<<"Theory"<<setw(10)<<"Lab"<<setw(10)<<"Status"<<endl;
*/
					do{
						getline(teacherSelectedCourseFile,temp_ccode);

						if(temp_ccode!="***")
						{

							getline(teacherSelectedCourseFile,temp_cstatus);
							//search for the course details in the array
							//that are already feed with the course detail list
							//from the courses.txt file
							for(int k=0;k<numOfCourse;k++)
							{
								if(c_code[k]==temp_ccode)
								{
									cout<<"\n\tCourse Code  :"<<c_code[k]
									<<"\n\tCourse Title		:"<<c_Title[k]
									<<"\n\tCredit Hours		:"<<c_creditHr[k]
									<<"\n\tTheory			:"<<c_theory[k]
									<<"\n\tLab				:"<<c_lab[k]
									<<"\n\tEnrollment Status:"<<temp_cstatus;

									int maxNumOfStd=0;
									string* studentnames=FindEnrolStdInCourse(temp_ccode,maxNumOfStd);
									PrintStudentDetail(FindEnrolStdInCourse(temp_ccode,maxNumOfStd),maxNumOfStd);
									break;
								}
							}
							
							courseSel++;
						}
						else
							break;
					}while(temp_ccode!="***");
					break;
				}
				else
				{
					do{
						getline(teacherSelectedCourseFile,temp_ccode);
					}while(temp_ccode!="***");
				}
			}
			else
				break;
		}
	}

	teacherSelectedCourseFile.close();

	if(courseSel<=0)
	{
		cout<<"\n\tNo courses are selected by you...!!!"<<endl;
	}

	cout<<endl<<"\t";
	system("pause");
}

//function that receives the pointer to a string array and index
//print the students details from the users.txt file
void PrintStudentDetail(string *unique_ids,int index)
{
	//required variable to hold the data
	string temp;
	string temp_fname,temp_lname,temp_age,temp_contactnum,temp_type,temp_pass;
	int i=0;

	//Display the title bar to distinguish
	cout<<"\n\t******************************************************"
		<<"\n\t****************** Enrolled Student ******************\n"<<endl;
	
	//check if unique id is available
	if(index>0)
	{
		//ifsstream class object
		ifstream userFile("Users.txt");

		//check if file is opened properly
		if(userFile.is_open())
		{
			//iterate through every record
			while(!userFile.eof())
			{
				//reading firstname 
				getline(userFile,temp_fname);
				//reading lastname 
				getline(userFile,temp_lname);
				//reading dob 
				getline(userFile,temp_age);
				//reading contact number 
				getline(userFile,temp_contactnum);
				//reading user type 
				getline(userFile,temp_type);
				//reading username
				getline(userFile,temp);
				//reading password
				getline(userFile,temp_pass);

				if(i<index)
				{
					//check if the username is found
					if(temp==unique_ids[i])
					{
						//display the details
						cout<<"\n\tFirst Name :"<<temp_fname
							<<"\n\tLast Name  :"<<temp_lname
							<<"\n\tAge        :"<<getAge(temp_age)
							<<"\n\tContact No :"<<temp_contactnum
							<<"\n\tType       :"<<temp_type
							<<"\n\tUsername   :"<<temp;
		
						cout<<"\n\t******************************************************\n"<<endl;
						i++;
					}
				}
				else
					break;
			}

		}
		else
			cout<<"\n\tUnable to open file!";
		
		//closing file
		userFile.close();
	}
	else
	{
		cout<<"\n\tCourse is not enrolled by any student...!!!\n";
	}
	cout<<"\n\t******************************************************"
		<<"\n\t******************************************************\n"<<endl;

}

//receive the course code and index as a reference
//find the students that are enrolled in the course code
//and returns the list of students and update index variable value by
//the number of students available
string* FindEnrolStdInCourse(string ccode,int &index)
{
	//ifstream class object to read the data from file
	ifstream sc_file("StudentEnrolledCourses.txt");
	string stdname;
	static string temp_sname[100],temp_ccode,temp_cstatus;
	bool isfound=false;
	int t_index=0;

	//check if file is opened
	if(sc_file.is_open())
	{
		while(!sc_file.eof())
		{
			//iterate thorugh every record
			getline(sc_file,stdname);

			if(stdname!="")
			{
				do{
					getline(sc_file,temp_ccode);
					
					if(temp_ccode!="***")
					{
						getline(sc_file,temp_cstatus);
						
						//check if the course is assigned to teacher
						if(temp_ccode==ccode)
						{
							temp_sname[t_index]=stdname;
							t_index++;
						}
					}
					else
						break;
				}while(temp_ccode!="***");
				
			}
			else
				break;
		}
		sc_file.close();
		
	}
	
	index=t_index;

	return temp_sname;
}

//CourseAssignRequest method will display all the requests with the teacher 
//username and course code and request status
void CourseAssignRequest()
{
	//required array list
	string temp_teachername[100],temp_ccode[100],temp_cstatus[100];
	int temp_numOfCourse[100]={0};
	int count=0,c_count=0;
	int request_id1,request_id2;
	int status_response;

	//ifstream class object
	ifstream teacherSelCoureFile("TeacherSelectedCourses.txt");

	clearScreen();

	cout<<"\n\t******************************************"
		<<"\n\t********** Teacher Request List **********"
		<<"\n\t******************************************"<<endl;

	//check if file is ready to open successfully
	if(teacherSelCoureFile.is_open())
	{
		while(!teacherSelCoureFile.eof())
		{
			//reading teacher name from file
			//search for the logged in teacher
			getline(teacherSelCoureFile,temp_teachername[count]);

			if(temp_teachername[count]!="")
			{
				do{
					getline(teacherSelCoureFile,temp_ccode[c_count]);
				
					if(temp_ccode[c_count]!="***")
					{
						getline(teacherSelCoureFile,temp_cstatus[c_count]);
					
						temp_numOfCourse[count] = temp_numOfCourse[count]+1;
					}
					else
						break;
					c_count++;
				}while(temp_ccode[c_count]!="***");	
			}
			else
				break;
			count++;
		}
	}

	teacherSelCoureFile.close();

	//printing the header for table
	cout<<"\n\t"<<setw(5)<<"ID"<<setw(20)<<"Teacher Username"<<setw(20)<<"Course Code"<<setw(20)<<"Request Status"<<endl;

	//printing all the teachers request for the course with status pending to the screen
	int ccode_index=0;

	for(int i=0;i<count;i++)
	{		
		for(int j=ccode_index;j<getSum(temp_numOfCourse,i);ccode_index=++j)
		{
			cout<<"\n\t"<<setw(5)<<i<<"="<<j<<setw(20)<<temp_teachername[i]<<setw(20)<<temp_ccode[j]<<setw(20)<<temp_cstatus[j];
		}
	}

	//printing the end of the table
	cout<<"\n\t========================================================================================"<<endl;

	//prompt for the request number 
	cout<<"\n\tPlease select the ID to proceed with the request (format # 1=1) :";
	cin>>request_id1>>request_id2;

	//prompt for the status 
	cout<<"\tSelect status to respond to the request (1 for Approve, 2 for Reject) :";
	cin>>status_response;

	ccode_index=0;

	//update the status in the array
	for(int i=0;i<count;i++)
	{		
		for(int j=ccode_index;j<getSum(temp_numOfCourse,i);ccode_index=++j)
		{
			if(i==request_id1 && j==request_id2)
			{
				//update the status
				switch(status_response)
				{
				case 1:
					temp_cstatus[j]="Approve";
					break;
				case 2:
					temp_cstatus[j]="Reject";
					break;
				}
			}
		}
	}

	//writing data back with new course
	//ofstream class object
	ofstream courseSelFile("TeacherSelectedCourses.txt");

	//check if file is ready to open successfully
	if(courseSelFile.is_open())
	{
		int ccode_index=0;

		for(int i=0;i<count;i++)
		{
			//writing down the course
			courseSelFile<<temp_teachername[i]<<endl;
		
			for(int j=ccode_index;j<getSum(temp_numOfCourse,i);ccode_index=++j)
			{
				courseSelFile<<temp_ccode[j]<<endl;
				courseSelFile<<temp_cstatus[j]<<endl;
			}
			courseSelFile<<"***\n";
		}
		courseSelFile.close();
	}
	else
	{
		cout<<"\n\tFile not found...!"<<endl;
		system("pause");
		return ;
	}
}

//CourseEnrolRequest method will display all the requests with the student 
//username and course code and request status
void CourseEnrolRequest()
{
	//required array list
	string temp_studentname[100],temp_ccode[100],temp_cstatus[100];
	int temp_numOfCourse[100]={0};
	int count=0,c_count=0;
	int request_id1,request_id2;
	int status_response;

	//ifstream class object
	ifstream studentSelCoureFile("StudentEnrolledCourses.txt");

	clearScreen();

	cout<<"\n\t******************************************"
		<<"\n\t********** Student Request List **********"
		<<"\n\t******************************************"<<endl;

	//check if file is ready to open successfully
	if(studentSelCoureFile.is_open())
	{
		while(!studentSelCoureFile.eof())
		{
			//reading teacher name from file
			//search for the logged in teacher
			getline(studentSelCoureFile,temp_studentname[count]);

			if(temp_studentname[count]!="")
			{
				do{
					getline(studentSelCoureFile,temp_ccode[c_count]);
				
					if(temp_ccode[c_count]!="***")
					{
						getline(studentSelCoureFile,temp_cstatus[c_count]);
					
						temp_numOfCourse[count] = temp_numOfCourse[count]+1;
					}
					else
						break;
					c_count++;
				}while(temp_ccode[c_count]!="***");	
			}
			else
				break;
			count++;
		}
	}

	studentSelCoureFile.close();

	//printing the header for table
	cout<<"\n\t"<<setw(5)<<"ID"<<setw(20)<<"Student Username"<<setw(20)<<"Course Code"<<setw(20)<<"Request Status"<<endl;

	//printing all the student request for the course with status pending to the screen
	int ccode_index=0;

	for(int i=0;i<count;i++)
	{		
		for(int j=ccode_index;j<getSum(temp_numOfCourse,i);ccode_index=++j)
		{
			cout<<"\n\t"<<setw(5)<<i<<"="<<j<<setw(20)<<temp_studentname[i]<<setw(20)<<temp_ccode[j]<<setw(20)<<temp_cstatus[j];
		}
	}

	//printing the end of the table
	cout<<"\n\t========================================================================================"<<endl;

	//prompt for the request number 
	cout<<"\n\tPlease select the ID to proceed with the request (format # 1=1) :";
	cin>>request_id1>>request_id2;

	//prompt for the status 
	cout<<"\tSelect status to respond to the request (1 for Approve, 2 for Reject) :";
	cin>>status_response;

	ccode_index=0;

	//update the status in the array
	for(int i=0;i<count;i++)
	{		
		for(int j=ccode_index;j<getSum(temp_numOfCourse,i);ccode_index=++j)
		{
			if(i==request_id1 && j==request_id2)
			{
				//update the status
				switch(status_response)
				{
				case 1:
					temp_cstatus[j]="Approve";
					break;
				case 2:
					temp_cstatus[j]="Reject";
					break;
				}
			}
		}
	}

	//writing data back with new course
	//ofstream class object
	ofstream courseSelFile("StudentEnrolledCourses.txt");

	//check if file is ready to open successfully
	if(courseSelFile.is_open())
	{
		int ccode_index=0;

		for(int i=0;i<count;i++)
		{
			//writing down the course
			courseSelFile<<temp_studentname[i]<<endl;
		
			for(int j=ccode_index;j<getSum(temp_numOfCourse,i);ccode_index=++j)
			{
				courseSelFile<<temp_ccode[j]<<endl;
				courseSelFile<<temp_cstatus[j]<<endl;
			}
			courseSelFile<<"***\n";
		}
		courseSelFile.close();
	}
	else
	{
		cout<<"\n\tFile not found...!"<<endl;
		system("pause");
		return ;
	}
}