// Project6_OldVersion.cpp : This file contains the 'main' function. Program execution begins and ends there.
// VehileManagment_TransportationSystem.cpp 
//Dr. Alnaeli, University of Wisconsin
//note: system("cls"); is ro run the system command cls that clears the screen
//improved with recursion, nodelists, and exceptions by Preston Leigh, University of Wisconsin-Stout

#include "transportation.h"
#include "testers.h"
#include "NodeList.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

string menu();
bool readingDataFromDBfile(Inventory& myInventory, ifstream& inFile, int recordsInFile);

int main()
{
	//////testing Vehicle class. You are welcome to reuse it.
	//if (testingVehicle())
	//	cout << "Class Vehicle Passed all the available tests" << endl;

	////cout << "Loading the data .";
	ifstream inFile;
	ofstream outFile;

	try { inFile.open("vehicles.txt"); } // exception for file not found/cannot open file
	catch (...) { cout << "Error opening the file! Program cannot run. Exiting error 10" << endl; exit(10); } // end try catch

	int recordsInFile = 0;
	inFile >> recordsInFile; // reading number of the records in the file.
	//inFile.ignore(1000, '\n');  // ignore the \n
	Inventory myInventory(recordsInFile); // capacity is set to numer of the records in the file.

	try { if (!(readingDataFromDBfile(myInventory, inFile, recordsInFile))) { throw 11; } }// exception for file cannot be read
	catch (int e) { if (e == 11) { cout << "Error reading data from the file, exiting code 11" << endl; exit(11); } } // end try catch

	cout << endl;
	myInventory.sortList();
	//myInventory.printList(); //testing
	cout << endl;
	cout << menu();
	int userEntry = 0;
	int seatsNo = 0;
	NodeList<Vehicle>::Iterator thisPosition = myInventory.beginIter();
	bool done = false;

	do {
		try { done = false; cin >> userEntry; if (!userEntry) throw 12; done = true; } // input checking first time
		catch (int e) { if (e == 12) { userEntry = 0; cin.clear();  cin.ignore(1000, '\n'); cout << "Incorrect input! Please input a valid option." << endl; } } // end try catch
	} while (!done); // end do while


	//system("cls") is used for clearing the console screen. cls is a Dos command

	while (userEntry != 8) {

		switch (userEntry) {
		case 0: system("cls"); break;
		case 1: system("cls");  thisPosition = myInventory.beginIter(); myInventory.printList(thisPosition); break;
		case 2: system("cls"); thisPosition = myInventory.beginIter(); myInventory.printAvailableList(thisPosition); break;
		case 3:system("cls"); thisPosition = myInventory.beginIter(); myInventory.printResevedList(thisPosition); break;
		case 4: {system("cls");
			cout << "Enter number of seats? ";
			do { // input checking for valid value (integer not below 0)
				try { done = false; cin >> seatsNo; if (!seatsNo || seatsNo < 1) throw 12; done = true; }
				catch (int e) { if (e == 12) { seatsNo = 0; cin.clear();  cin.ignore(1000, '\n'); cout << "Incorrect input! Please input a valid option." << endl; } } // end try catch
			} while (!done); // end while

			//cout<<"GPS [Y/N]?"
			if (!myInventory.found(seatsNo, thisPosition)) cout << "Not available\n"; }  // end if 
			  break;
		case 5: {system("cls");
			cout << "Please Enter the Vehicle ID: ";
			int tmpVehicleID;

			do { // input checking for valid value (integer not below 0)
				try { done = false; cin >> tmpVehicleID; if (!tmpVehicleID || tmpVehicleID < 1) throw 12; done = true; }
				catch (int e) { if (e == 12) { tmpVehicleID = 0; cin.clear();  cin.ignore(1000, '\n'); cout << "Incorrect input! Please input a valid option." << endl; } }
			} while (!done);// end do while
			try {
				if (myInventory.reserveVehicle(tmpVehicleID)) { if (!myInventory.saveToFile("vehicles.txt")) { throw 18; } } // instead of if statements, use exception
				else { throw 18; } // end else
			} // end try
			catch (int e) { if (e == 18) { cout << "Return Failed...... Make sure that the Vehicle ID is valid." << endl; break; } } // end try catch
			break;

		case 6: {system("cls");
			cout << "Please Enter the Vehicle ID: ";
			int tmpVehicleID;

			do { // input checking for valid value (integer not below 0)
				try { done = false; cin >> tmpVehicleID; if (!tmpVehicleID || tmpVehicleID < 1) throw 12; done = true; }
				catch (int e) { if (e == 12) { tmpVehicleID = 0; cin.clear();  cin.ignore(1000, '\n'); cout << "Incorrect input! Please input a valid option." << endl; } }
			} while (!done); // end do while

			try {
				if (myInventory.returnVehicle(tmpVehicleID)) { if (!myInventory.saveToFile("vehicles.txt")) { throw 18; } } // instead of if statements, use exception
				else { throw 18; }
			}
			catch (int e) { if (e == 18) { cout << "Return Failed...... Make sure that the Vehicle ID is valid." << endl; break; } } // end try catch

			break;

		case 7: {
			system("cls");
			string fileName = "";
			cout << endl << endl << "Please enter a file name without an extension(Ex: myFile) -> ";
			cin >> fileName;
			ofstream outFile;
			fileName.append(".txt");
			try { // try catch if file cannot be opened
				outFile.open(fileName);
				if (outFile.fail()) { throw 18; }
				outFile << myInventory;
				outFile.close();
			}
			catch (int e) { if (e == 18) { cout << "\nSystem was not able to create a file\n"; break; } } // end try catch

			cout << "\nData sent to file " + fileName + "\n"; } break;

		case 8: system("cls"); break;
		default: system("cls"); userEntry = 0; cin.clear();  cin.ignore(1000, '\n'); cout << "Incorrrect input! Please input a valid option." << endl; break;
		}
		}
		} // end switch
		 // exit
			  cout << menu();
			  do {
				  try { done = false; cin >> userEntry; if (!userEntry) throw 12; done = true; } // input checking
				  catch (int e) { if (e == 12) { userEntry = 0; cin.clear();  cin.ignore(1000, '\n'); cout << "Incorrect input! Please input a valid option." << endl; } }
			  } while (!done);
		
		}

		cout << "Ending the program..... Done!" << endl;

		return 0;
	
}


bool readingDataFromDBfile(Inventory& myInventory, ifstream& inFile, int recordsInFile) {
	/*reading the inventory informaton (cars that are registered) from the file to the inventory list (data structure.*/
	try {
		int vehicleID;
		string make;
		string model;
		int seats;
		bool available;
		int extarFeatures;
		NodeList<string> featuresListTmp;
		string tempstring;

		int count = 0;

		while (count < recordsInFile) {
			inFile >> vehicleID;
			inFile.ignore(1000, '\n');
			getline(inFile, make);
			getline(inFile, model);
			inFile.clear();
			inFile >> seats;
			inFile >> available;
			inFile >> extarFeatures;
			inFile.clear();
			inFile.ignore();

			for (int j = 0; j < extarFeatures; ++j) {
				getline(inFile, tempstring);
				featuresListTmp.insertBack(tempstring);
				tempstring.clear();
			}

			myInventory.push_Back(Vehicle(vehicleID, make, model, seats, available, extarFeatures, featuresListTmp));
			featuresListTmp.clear();

			++count;
		}
	}
	catch (...) {
		inFile.close();
		return false;
	}

		/*
		for (int i = 0; i < recordsInFile; ++i) { // reading the vehcile information from the file
			//cout << " .";
			inFile >> vehicleID;
			inFile.ignore(1000, '\n');
			getline(inFile, make);
			getline(inFile, model);
			inFile >> seats;
			inFile >> available;
			inFile >> extarFeatures;
			if (extarFeatures > 0)
			{
				inFile.ignore(1000, '\n');

				for (int k = 0; k < extarFeatures; ++k)
				{
					getline(inFile, tempstring);
					featuresListTmp.insertBack(tempstring);
				}
			}
			Vehicle tempVehicle(vehicleID, make, model, seats, available, extarFeatures, featuresListTmp);
			myInventory.push_Back(tempVehicle);
			featuresListTmp.clear();
		}
		*/
		inFile.close();


	return  true;
}

string menu() {

	string message;
	message = "0. Clear Screen..\n1. Print All of the registered  vehicles.\n2. Print list of the available vehicles.";
	message = message + "\n3.List of the reserved vehicles.\n4. Check availability.\n5.Reserve a vehicle.\n6. return a vehicle.\n7. Print All of the registered vehicles to a text file.\n8. Exit.\nYour Selection --> ";
	return message;
}