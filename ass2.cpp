/***********************************************************************************
 * CSCI251/851 - Assignment 2
 * ass2.cpp - Contains function definitions for phone database program
 * Put you name, login and the date last modified here.
 *
 ***********************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <stdio.h>

using namespace std;

// ============== Constants ==========================================

const char cDataFileName[] = "phone.txt";
const int cMaxRecs = 250;  // Max records in database
const int cMaxNChars = 20; // Max chars in name
const int cMaxLChars = 30; // Max chars in location
const int cMaxPChars = 8;  // Max chars in phone no


// ============= User Defined types ==================================

struct PhoneRecord{
	char PhoneNo[cMaxPChars+1];
	char FamilyName[cMaxNChars+1];
	char GivenName[cMaxNChars+1];
	int StreetNo;
	char StreetName[cMaxLChars+1];
	char Suburb[cMaxLChars+1];
	int PostCode;
};


// ============= Global Data =========================================

PhoneRecord *gRecs[cMaxRecs];
int gNumRecs=0;
void CheckRecord(char Phone);
void WriteFile();



// ============= Private Function Prototypes =========================

void DisplayRecord(int i); // Displays record i on screen


// ============= Public Function Definitions =========================

void ReadFile()
{//Load Phone records from text datafile into array
	ifstream fin;
	fin.open(cDataFileName);
	if (!fin.good())
	{
		cerr << "Could not open data file!\n";
		exit(1);
	}
	gNumRecs=0;
	char Tmp[100];
	int i;
	for(i=0;i<cMaxRecs;i++)
	{
		fin >> Tmp;
		if(fin.fail()) break; // then eof
		gRecs[i] = new PhoneRecord;
		strcpy(gRecs[i]->PhoneNo, Tmp);  
		fin >> gRecs[i]->GivenName;
		fin >> gRecs[i]->FamilyName;
		fin >> gRecs[i]->StreetNo;
		fin.ignore();
		fin.getline(gRecs[i]->StreetName,cMaxLChars+1);
		fin.getline(gRecs[i]->Suburb,cMaxLChars+1);
		fin >> gRecs[i]->PostCode; 
	}
	gNumRecs=i;
	fin.close();
	cout<< "\nThere are "<< gNumRecs <<" records in the Phone database\n";
}

void DisplayRecords()
{// Displays 5 records one at a time
	int j = 0;	
	while (j < gNumRecs) {
		for(int i=0;i<5;i++)
		{
			DisplayRecord(j);
			j++;
		}
		cout<<"Display next record (y/n)> ";
		char Ans;
		cin>>Ans;
		cout<<endl;
		if(Ans=='n') return;
		}
}


void AddRecord()
{// Adds a new record to the database array
	// if DB not full	
	if (gNumRecs < cMaxRecs){
		PhoneRecord *newRec = new PhoneRecord; //      create new PhoneRecord, must delete after usage. 
		
		
		bool flag = true;
		while(flag == true)	{
			//cin.ignore();
			cout << "Enter phone number: \n"; //    get data from user and assign to new record's fields 
			//cin >> newRec->PhoneNo;
			while(!(cin>>newRec->PhoneNo) || strlen(newRec->PhoneNo) != 8){
				cerr << "Phone number needs to be 8 digits"<<endl;
			}
			for (int i =0; i<8; i++)	//loop checks if each character added is of numeric value.
			{
				if(!isdigit(newRec->PhoneNo[i])){
				 cerr << "Phone number needs to be only numbers"<<endl;	 
				 i = 0;
				 flag = true;
				 break; //end loop
				}
				flag = false;
			}  
		}
		
		cout << "Enter family name: \n";
		cin >> newRec->FamilyName;
		newRec->FamilyName[0] = toupper(newRec->FamilyName[0]); //first letter to upper case.	
		
		
		cout << "Enter given name: \n";
		cin >> newRec->GivenName;
		newRec->GivenName[0] = toupper(newRec->GivenName[0]); //first letter to upper case.	

		cout << "Enter street number: \n"; 
		while(!(cin>>newRec->StreetNo))	{	//while loop for testing street number
			cout << "Invalid input, try again" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}	
		
		cin.ignore();  // eat newline 
		cout << "Enter street name: \n";
		cin.getline(newRec->StreetName,30);
		newRec->StreetName[0] = toupper(newRec->StreetName[0]); //first letter to upper case.	
		
		cout << "Enter suburb name: \n";
		cin.getline(newRec->Suburb,30);
		newRec->StreetName[0] = toupper(newRec->StreetName[0]); //first letter to upper case.	
		
		cout << "Enter postcode: \n";
		while(!(cin >> newRec->PostCode)){
			cout << "Invalid input" << endl;
			cin.clear();
			cin.ignore(4, '\n');	
		}

		gRecs[gNumRecs+1] = newRec;			//increment gNumRecs	 	
		WriteFile();	// execute writefile() function
		cout << "Record added to Database" << endl;	//      print "record added to DB" message
		
	} else { 	
		cout << "Error Database is full!" << endl; 	//      print "Error: DB Full!" message
	}
}

void WriteFile()
{
	ofstream fout;
	fout.open("phone.txt", ios::app);	//      append new record to the DB file
	if(!fout.good())
	{
		cout << "Could not locate file ""phone.txt" << endl;
		exit(0);
	}
	if(gNumRecs<cMaxRecs)
	{	
		fout << gRecs[gNumRecs+1]->PhoneNo << endl;
		fout << gRecs[gNumRecs+1]->GivenName << endl;	
		fout << gRecs[gNumRecs+1]->FamilyName << endl;
		fout << gRecs[gNumRecs+1]->StreetNo << endl;
		fout << gRecs[gNumRecs+1]->StreetName << endl;
		fout << gRecs[gNumRecs+1]->Suburb << endl;
		fout << gRecs[gNumRecs+1]->PostCode << endl;
	}
	fout.close(); //close the output of the file.
	gNumRecs++; //update the total number of records
	ReadFile();
}

void SearchRecords()
{	// Searches database array for phone number 
	char userInput[cMaxPChars+1];
	bool noRecord = false;

	// cout<<"SearchRecord()- Not yet implemented\n";
	cout << "Please enter user phone number: "; // get phone no. from user
	cin >> userInput;

	if (cin.good()){// search array for record
		
		for (int i =0; i < gNumRecs; i++)
		{
			// if found
			if (strcmp(userInput, gRecs[i]->PhoneNo)==0){
				noRecord = false; 
				// display record
				cout << gRecs[i]->GivenName <<", "<<gRecs[i]->FamilyName<<", "
				<< gRecs[i]->StreetNo<<", "<<gRecs[i]->StreetName<<", "<<gRecs[i]->Suburb<<", "<<gRecs[i]->PostCode<< endl;
				break;
			} else {
				noRecord = true; 
			}		
		}
		if (noRecord == true){
			cout<<"Record not found!"<<endl;
		}
	} 
}


void CleanUp()
{// Deletes all dynamic data in gRecs array
 
	for (int i=0; i < gNumRecs; i++)
	{
		delete gRecs[i]; 	
	}

	cout<<"\n\t*** Thanks for using the Phone DB ***\n";
}
// ============= Private Functions Definitions =========================



void DisplayRecord(int i)
{// Displays record i on screen
	cout<<gRecs[i]->PhoneNo <<"   "
	<<gRecs[i]->GivenName<<" "
	<<gRecs[i]->FamilyName <<", "
	<<gRecs[i]->StreetNo <<" "
	<<gRecs[i]->StreetName<<", "
	<<gRecs[i]->Suburb<<", "
	<<gRecs[i]->PostCode;
	cout << endl;
}
