#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>

#define max 20 
using namespace std;
int num, appRecord;
// Structure of Employee
struct employee {
	string name, designation;
	long int code, sal;
	int exp, age;
};
// Array of Employees to store the data in the form of the Structure of the Array
employee emp[max];

void show();
void header();
void footer();
void menu();
void build();
void addRecord();
void delRecord();
void deleteIndex(int i);
void searchRecord();
void displayRecord();
void updateRecord();
bool saveRecord(bool);
bool readRecord();
int getInt(string msg);

main(){
	system("Color F1"); // Sets Background Color (F = Bright White) and Text Color (1 = Blue)
	char ch;
	bool read = readRecord();

	if(read){
		header();
		show();
	}
	else{
		cout<<" Cannot read existing data. Do you still want to continue? (y/n): ";
		cin>>ch;
		if(ch == 'y' || ch == 'Y'){
			header();
			show();
		}
		footer();
	}
}
void show(){
	
	int ch, n;
	menu();
	ch = getInt("-> ");
	switch(ch){
		case 1:
			build();
			break;
		case 2:
			addRecord();
			break;
		case 3:
			delRecord();
			break;
		case 4:
			searchRecord();
			break;
		case 5:
			displayRecord();
			break;
		case 6:
			updateRecord();
			break;
		case 7:	
			footer();		
			break;
		default:
			cout<<"Invalid Choice\n";
			cout<<"Valid Choice: (1-7)\n";
			show();//recursive function it is calling itself 
			break;	
	}
	
}
void build()
{
	int j=0;
	cout << "Build The Table\n";
	cout << "Maximum Entries can be "<< max << endl;

	num = getInt("Enter the number of entries required:\t");
	while (!(num>0 && num<=20))
	{
		num = getInt("Enter the number of entries required:\t");
	}
	
	if (num > 20) {
		cout << "Maximum number of entries are "<< max << endl;
		num = 20;
	}
	cout << "Enter the following data:\n";
	
	for (int i = 0; i < num; i++) {
		
		cout<<"Enter Record of Employee :\n";
		
		emp[i].code = getInt("Employee ID :\t");

		bool isRepeat = false;
		
		for(int j = 0; j < i; j++){
			if(emp[i].code == emp[j].code){
				isRepeat = true;
				cout<<"This employee id already exists\n";
				break;
			}
		}
		
		if(isRepeat){
			i--;
			continue;	
		}

		cout << "Name:\t";
		cin>>emp[i].name;

		cout << "Designation:\t";
		cin>>emp[i].designation;

		emp[i].exp = getInt("Experience in years:\t"); 
		
		emp[i].age = getInt("Age: \t");

		emp[i].sal = getInt("Salary :\t");

	}
	
	bool saved = saveRecord(false);
	if(!saved){
		cout<<"\n Error saving data. Please retry..";
	}
	else{
		cout<<"\nRecord inserted successfully\n";
	}
	char ch;
	cout<<"Do you want to continue?(y/n)\t";
	cin>>ch;
	if(ch=='y'||ch=='Y'){
		show();
	}
	else{
		footer();
	}
	
}
void addRecord(){
	int n;
	n = getInt("How many records you want to enter: \t");
	while (!(n>0 && n<=20))
	{
		n = getInt("How many records you want to enter: \t");
	}

	appRecord = n;
	if (num + n < max) {
		int j = 0;
		cout << "****************Enter employee information******************\n\n";
		for(int i = num; i < num+n; i++){
			cout<<"Enter Record of Employee :\n";
	
			emp[i].code = getInt("Employee ID: \t");

			// to check if id is unique
			bool isRepeat = false;
			
			for(int j = 0; j < i; j++){
				if(emp[i].code == emp[j].code){
					isRepeat = true;
					cout<<"This employee id already exists\n";
					break;
				}
			}
			
			if(isRepeat){
				i--;
				continue;	
			}

			cout << "Name: \t";
			cin>>emp[i].name;

			cout << "Designation: \t";
			cin>>emp[i].designation;

			emp[i].exp = getInt("Experience in years:\t"); 
			
			emp[i].age = getInt("Age: \t");

			emp[i].sal = getInt("Salary :\t");

		}
		cout<<"\nRecords inserted successfully\n";
		num+=n;
	}
	else {
		if(max-num == 0){
			cout << "Employee Table Full\n";
			char ch;
			cout<<"Do you want to continue?(y/n)\t";
			cin>>ch;
			if(ch=='y'||ch=='Y'){
				show();
			}
			else{
				footer();
			}
		}
		else{
			cout<<" Only "<<max-num<<" employees can be added.\n";
			char ch;
			cout<<"Do you want to continue?(y/n)\t";
			cin>>ch;
			if(ch=='y'||ch=='Y'){
				show();
			}
			else{
				footer();
			}
		}
	}
	
	bool saved = saveRecord(true);
	if(!saved){
		cout<<"\n Error saving data. Please retry..";
	}

	char ch;
	cout<<"Do you want to continue?(y/n)\t";
	cin>>ch;
	if(ch=='y'||ch=='Y'){
		show();
	}
	else{
		footer();
	}
}
// Function to delete record at index i
void deleteIndex(int i)
{
	for (int j = i; j < num - 1; j++) {
		emp[j].name = emp[j + 1].name;
		emp[j].code = emp[j + 1].code;
		emp[j].designation = emp[j + 1].designation;
		emp[j].exp = emp[j + 1].exp;
		emp[j].age = emp[j + 1].age;
		emp[j].sal = emp[j + 1].sal;
	}
	
}

// Function to delete record
void delRecord()
{
	if(num == 0){
		cout<<"\n There is no data available to delete. Please enter employee's details before deleting it!\n\n";	
	}
	else{

		int code = getInt("Enter employee ID to delete the record:\t");
		for (int i = 0; i < num; i++) {
			if (emp[i].code == code) {
				deleteIndex(i);
				num--;
				cout<<"Record deleted\n\n";
				break;
			}
			
		}
	}	
	char ch;
	cout<<"Do you want to continue?(y/n)\t";
	cin>>ch;
	if(ch=='y'||ch=='Y'){
		show();
	}
	else{
		footer();
	}
}


void searchRecord(){
	if(num == 0){
		cout<<"\n There is no data available to search. Please enter employee's details before searching it!\n\n";	
	}
	else{
		cout<<"=============="<<endl;
		cout<<"Employee Id\n";
		cout<<"=============="<<endl;
		
		for (int i = 0; i < num; i++) {
			cout <<emp[i].code<<endl;
			cout<<"=============="<<endl;
		}

		int code = getInt("Enter employee ID to search the record:\t");
		int found=0;
		for (int i = 0; i < num; i++) {

			// If the data is found
			if (emp[i].code == code) {
				found=1;
				cout<<"\nRecord found!\n";
				cout<<"================================================================================"<<endl;
				cout<<"Employee Id\tEmployee Name\tDesignation\tAge\tSalary\tExperience\n\n";
				cout<<"================================================================================"<<endl;
				
				cout <<"\t"<<emp[i].code<<"\t"<<emp[i].name<<"\t\t"<<emp[i].designation<<"\t"<<emp[i].age<<"\t"<<emp[i].sal<<"\t\t"<<emp[i].exp<<endl;
				
				cout<<"================================================================================"<<endl;
				
				break;
			}
			
		}
		if(found==0){
			cout<<"Data not found!\n";
		}
	}	
	char ch;
	cout<<"Do you want to continue?(y/n)\t";
	cin>>ch;
	if(ch=='y'||ch=='Y'){
		show();
	}
	else{
		footer();
	}

}
void displayRecord(){
	if(num == 0){
		cout<<"\n There is no data available to display. Please enter employee's details before displaying it!\n\n";	
	}
	else{
		//to display all records
		cout<<"======================================================================================"<<endl;
		cout<<"S.No\tEmployee Id\tEmployee Name\tDesignation\tAge\tSalary\t  Experience\n\n";
		cout<<"======================================================================================"<<endl;
		
		for (int i = 0; i < num; i++) {

			cout <<i+1<<"\t"<<emp[i].code<<"\t\t"<<emp[i].name<<"\t\t"<<emp[i].designation<<"\t\t"<<emp[i].age<<"\t"<<emp[i].sal<<"\t\t"<<emp[i].exp<<endl;
			
			cout<<"======================================================================================"<<endl;
		}
	}
	char ch;
	cout<<"Do you want to continue?(y/n)\t";
	cin>>ch;
	if(ch=='y'||ch=='Y'){
		show();
	}
	else{
		footer();
	}
}
void updateRecord(){
	if(num == 0){
		cout<<"\n There is no data available to update. Please enter employee's details before updating it!\n\n";	
	}
	else{
		cout<<"====================================="<<endl;
		cout<<"Employee Id\tEmployee Name\n\n";
		cout<<"====================================="<<endl;
		
		
		for (int i = 0; i < num; i++) {

			cout <<emp[i].code<<"\t\t"<<emp[i].name<<endl;
			cout<<"====================================="<<endl;
			
		}
		int code = getInt("Enter employee ID to update the record:\t");
		int found=0,c,empId,expe,age,sal;
		string empName,desig;
		for (int i = 0; i < num; i++) {

			// If the data is found
			if (emp[i].code == code) {

				cout<<"======================================================================================"<<endl;
				cout<<"Employee Id\tEmployee Name\tDesignation\tAge\tSalary\t  Experience\n\n";
				cout<<"======================================================================================"<<endl;
				
				cout <<emp[i].code<<"\t\t"<<emp[i].name<<"\t\t"<<emp[i].designation<<"\t"<<emp[i].age<<"\t"<<emp[i].sal<<"\t\t"<<emp[i].exp<<endl;	
				cout<<"======================================================================================"<<endl;
				

				found=1;
				do
				{
					cout<<"What do you want to update?\n";
					cout<<"1.Employee Id\n2.Employee Name\n3.Designation\n4.Experience\n5.Salary\n6.Age\n7.Exit\n";
					cin>>c;
					if (c==1)
					{
						empId = getInt("Employee Id: \t");
						emp[i].code=empId;
						cout<<"Record Updated\n\n";
					}
					else if (c==2)
					{
						cout << "Employee Name: \t";
						cin>>empName;
						emp[i].name=empName;
						cout<<"Record Updated\n\n";
						
					}
					else if (c==3)
					{
						cout << "Designation: \t";
						cin>>desig;
						emp[i].designation=desig;
						cout<<"Record Updated\n\n";			
					
					}
					else if (c==4)
					{
						expe = getInt("Experience in years: \t");
						emp[i].exp=expe;
						cout<<"Record Updated\n\n";
					
					}
					else if (c==5)
					{
						sal = getInt("Salary: \t");
						emp[i].sal=sal;				
						cout<<"Record Updated\n\n";
					
					}
					else if (c==6)
					{
						age = getInt("Age: \t");
						emp[i].age=age;
						cout<<"Record Updated\n\n";
					
					}
					else if(c==7){
						
					}
					else 
					{
						cout << "Invalid Input \nValid input (1-6)\n";
					}
						
				}
				while (c!=7);
				
				
				saveRecord(false);
				break;
			}
			
		}
		if(found==0){
			cout<<"Data not found!\n";
		}
	}
	char ch;
	cout<<"Do you want to continue?(y/n)\t";
	cin>>ch;
	if(ch=='y'||ch=='Y'){
		show();
	}
	else{
		footer();
	}

}

bool readRecord(){
	ifstream o("Files/empData.txt");
	string readText, sepText[10];

	// record number
	int k = 0;
	if(o.is_open()){
		while(!o.eof()){
			// reads the line and stores it in readText string
			getline(o, readText);
			// j is column number, i is character number
			int i = 0, j = 0;
			while(true){
				if(readText[i] == ','){
					i++;
					j++;
					continue;
				}
				else if(readText[i] == '\0')
					break;
				
				sepText[j] += readText[i++];
			}
			if(sepText[0] == "\0"){
				cout<<"\n No data to be read, Press any key to continue..";
				getch();
				cout<<endl;
				return true;
			}

			string code = sepText[0];
			emp[k].code = stoi(code); //string to int conversion using stoi function

			emp[k].name = sepText[1];
			string age = sepText[2];
			emp[k].age = stoi(age);
			emp[k].designation = sepText[3];
			string exp = sepText[4];
			emp[k].exp = stoi(exp);
			string sal = sepText[5];
			emp[k].sal = stoi(sal);

			// reset all string to empty for the next record
			sepText[0] = sepText[1] = sepText[2] = sepText[3] = sepText[4] = sepText[5] = "";
			k++;
		}
		num = k;
		o.close();
		return true;
	}
	else{
		return false;
	}
}

bool saveRecord(bool append){
	if(!append){
		ofstream o("Files/empData.txt");
		if(o.is_open()){
			for(int i=0;i<num;i++){
				o<<emp[i].code<<"," + emp[i].name + ","<<emp[i].age<<"," + emp[i].designation + ","<<emp[i].exp<<","<<emp[i].sal;
				if(i < num - 1)
					o<<endl;
			}
			o.close();
			return true;
		}
		else{
			return false;
		}
	}
	else{
		ofstream o("Files/empData.txt", ios_base::app);
		if(o.is_open()){
			for(int i = num-appRecord; i < num; i++){
				o<<endl<<emp[i].code<<"," + emp[i].name + ","<<emp[i].age<<"," + emp[i].designation + ","<<emp[i].exp<<","<<emp[i].sal;
			}
			o.close();
			return true;
		}
		else{
			return false;
		}
	}
}

int getInt(string msg) {
	string myVar;
	bool isValidInt;
	do{
		isValidInt = true;
		cout << msg ;
		// getline(cin,myVar);
		cin >> myVar;
		char x;
		for(int i=0;i<myVar.length();i++){
			
			x = myVar[i];
			//48-57 0-9
			if(x<48 || x>57){
				isValidInt = false;
				break;
			}
		}
	} while (!isValidInt);
	int a = stoi(myVar);
	return a;
}


void menu(){
	
		cout<<"-----------------------------------------------\n";
		cout<<"\t\tMENU\n";
		cout<<"-----------------------------------------------\n";
		cout<<"Enter your choice:\n";
		cout<<"1.Build an employee table\n";
		cout<<"2.Add a new record\n";
		cout<<"3.Delete a record\n";
		cout<<"4.Search a record\n";
		cout<<"5.Display all records\n";
		cout<<"6.Update a record\n";
		cout<<"7.Exit\n";
		cout<<"-----------------------------------------------\n";
}

void header(){
	/*Header Start Here*/
	cout<<"===============================================\n";
	cout<<" \t\t\"C++\"\t\t\t\n";
	cout<<"===============================================\n";
	cout<<"\n\n";

	cout<<"_______________________________________________\n";
	cout<<"\t\tPROJECT X\n";
	cout<<"_______________________________________________\n";
	
	cout<<"***********************************************\n";
	cout<<"*\t\t\t\t\t      *\n";
	cout<<"*\t\"EMPLOYEE MANAGEMENT SYSTEM\"\t      *\n";
	cout<<"*\t\t\t\t\t      *\n";
    cout<<"***********************************************\n";

	cout<<"\n";
	/*Header End Here*/	
}
void footer(){
	/*Footer Start Here*/
	cout<<"\n\n";
	cout<<"===============================================\n";
	cout<<"++++++++++++++ \t \"End\"\t+++++++++++++++++++++++\t\t\n";
	cout<<"===============================================\n";
	cout<<"\n\n\n";
	/*Footer End Here*/
}


