
#include <string>
#include <iostream>
#include <fstream>
#include "transportation.h"
#include "NodeList.h"
using namespace std;

/****************************Class Vehicle Method Implementations***************************************/
Vehicle::Vehicle() {
	/*default constructor
	//fields are initialized with default data.
	//for the vehicle object, an empty dynamic array is allocated.
	*/
	vehicleID = -1;
	make = "NA";
	model = "NA";
	seats = 0;
	available = true;
	extarFeatures = 0;
	
}
Vehicle::Vehicle(int _vehicleID_, string _make_, string _model_, int _seats_, bool _available_, int _extarFeatures_, NodeList<string> _otherFeaturesList_)
{
		/*overloaded constructor
		//fields are initialized with data sent via the constructor.
		//the array of features is sent fro outsite as a pointer.
		*/
		vehicleID = _vehicleID_;
		make = _make_;
		model = _model_;
		seats = _seats_;
		available = _available_;
		extarFeatures = _extarFeatures_;
		otherFeaturesList = _otherFeaturesList_;
}


//-------------
// if (v1>v2) 
bool Vehicle::operator> (const Vehicle& v) {
	/*
	// overloading the greater than operator >. number of seats is used for
	//comparing the vehcle. If equal, then the number of extra features is used to break the ties.
	*/
	return ((seats > v.seats) || ((seats == v.seats) && (extarFeatures > v.extarFeatures)));
}

bool Vehicle::operator< (const Vehicle& v) { // used seats then extrafeatures as keys
		/*
	// overloading the less than operator <. number of seats is used for
	//comparing the vehcle. If equal, then the number of extra features is used to break the ties.
	*/
	return ((seats < v.seats) || ((seats == v.seats) && (extarFeatures < v.extarFeatures)));
}


bool Vehicle::operator==(const Vehicle& v) // uses seats then extrafeatures as keys to compare between Vehicle objects
{
	/*
// overloading the equality operator ==. Number of seats and extra features are used
//for determining if two vehicles are equal.
*/
	return (this->seats == v.seats && this->extarFeatures == v.extarFeatures);
}

bool Vehicle::operator<=(const Vehicle& v) // seats is the key
{
	/* overloading operator <= */
	return ((this->seats == v.seats && this->extarFeatures == v.extarFeatures) || ((seats < v.seats) || ((seats == v.seats) && (extarFeatures < v.extarFeatures))));
}
bool Vehicle::operator>=(const Vehicle& v) // seats is the key
{	/* overloading operator >= */
	return ((this->seats == v.seats && this->extarFeatures == v.extarFeatures) || ((seats > v.seats) || ((seats == v.seats) && (extarFeatures > v.extarFeatures))));

}

bool Vehicle::operator!=(const Vehicle& v) // seats is the key
{
	/* overloading the  operator != not equal*/
	return (!((this->seats == v.seats) && (this->extarFeatures == v.extarFeatures)));
}


//Rule of Three:
//destructor
Vehicle::~Vehicle() {
	
};
// copy constructor	
Vehicle::Vehicle(const Vehicle& org) {
	vehicleID = org.vehicleID;
	make = org.make;
	model = org.model;
	seats = org.seats;
	available = org.available;
	extarFeatures = org.extarFeatures;
	otherFeaturesList = org.otherFeaturesList;
}
//assignment operator overloading
Vehicle Vehicle::operator=(const Vehicle& rhs) {
	if (this != &rhs)
	{
		vehicleID = rhs.vehicleID; // nullptr? exception handled
		make = rhs.make;
		model = rhs.model;
		seats = rhs.seats;
		available = rhs.available;
		extarFeatures = rhs.extarFeatures;
		otherFeaturesList = rhs.otherFeaturesList;
	}
	return *this;
}

/******** Friend Functions to the Vehicle***********/
ostream& operator<<(ostream& out, const Vehicle& objV)
// overloading the insertion operator <<
{
	cout << "------------------------------------------\n";
	cout << "ID: " << objV.vehicleID << endl;
	cout << "Make: " << objV.make << endl;
	cout << "Model: " << objV.model << endl;
	cout << "Vumber of seats: " << objV.seats << endl;
	if (objV.available)
		cout << "Availability: available" << endl;
	else
		cout << "Availability: Not available" << endl;
	cout << "Extra Features[" << objV.extarFeatures << "]: " << endl;
	if (objV.extarFeatures < 1)
		cout << "Basic trim" << endl;

	else {
		cout << "[";
		NodeList<string>::Iterator testitr = objV.otherFeaturesList.begin();
		for (NodeList<string>::Iterator itr = objV.otherFeaturesList.begin(); itr != objV.otherFeaturesList.end(); ++itr) 
		{

			if (++testitr == objV.otherFeaturesList.end())
			{
				cout << *itr;
			}

			else
			{
				cout << *itr << ", ";
			}
		}
		cout << "]" << endl;
	}
	return out;
}
ofstream& operator<<(ofstream& out, const Vehicle& objV)
// overloading the insertion operator << for the output file stream
{
	out << objV.vehicleID << endl;
	out << objV.make << endl;
	out << objV.model << endl;
	out << objV.seats << endl;
	out << objV.available << endl;
	out << objV.extarFeatures << endl;
	for (NodeList<string>::Iterator itr = objV.otherFeaturesList.begin(); itr != objV.otherFeaturesList.end(); ++itr)
	{
			out << *itr << endl;
	}
	return out;
}



/****************************Class Inventory Method Implementations***************************************/
//default constructor
Inventory::Inventory() {
	capacity = 100; //default size
	registredVehiclesNo = 0;
	
}

//constructor II
Inventory::Inventory(int _capacity_) {
	capacity = _capacity_;
	registredVehiclesNo = 0;

	//	registredVehiclesNo = capacity;
}
Inventory::~Inventory() //destructor
{
	
}
//copy constructor
Inventory::Inventory(const Inventory& obj) {
	capacity = obj.capacity;
	registredVehiclesNo = obj.registredVehiclesNo;
	v_List = obj.v_List;
}

//assignment overloading.
Inventory Inventory::operator=(const Inventory& rhs) {
	if (this != &rhs) {
		capacity = rhs.capacity;
		registredVehiclesNo = rhs.registredVehiclesNo;
		v_List = rhs.v_List;
	}
	return *this;
}
//
bool Inventory::push_Back(Vehicle  ve) {
	/*inserting vehilce object to the inventory list*/
	
	if (registredVehiclesNo < capacity) {
		v_List.insertBack(ve);
		++registredVehiclesNo;
		return true;
	}
	else
		return false;
}// end of push_back
//
void Inventory::sortList() {
	/*sorts the inventory list in decreasing order. See the operator > overloading for the class Vehicle*/
	for (int i = 0; i < registredVehiclesNo; i++)
		for (int j = i + 1; j < registredVehiclesNo; j++)
			if (v_List.at(j) > v_List.at(i)) {
				Vehicle strTmpTask = v_List.at(j);
				v_List.at(j) = v_List.at(i);
				v_List.at(i) = strTmpTask;
			}
}
void Inventory::printList(NodeList<Vehicle>::Iterator thisPosition) { // RECURSIVE PRINT LIST
	/*
	while (thisPosition != v_List.end()) { // iterative
		cout << (*thisPosition) << endl;
		++thisPosition;
	}
	*/
	if (thisPosition != v_List.end()) 
	{
		cout << (*thisPosition) << endl;
		printList(++thisPosition);
	}
}
void Inventory::printResevedList(NodeList<Vehicle>::Iterator thisPosition) {  //recursive print list of the reserved vehicles
	
	/*
	if (thisPosition != v_List.end()) {
		if (!(*thisPosition).status()) { cout << *thisPosition; }
		printList(++thisPosition);
	}
	*/
	if (thisPosition != v_List.end()) 
	{
		if (!((*thisPosition).status()))
		{ 
			cout << (*thisPosition); 
		}
		
		printResevedList(++thisPosition);
	}
}
void Inventory::printAvailableList(NodeList<Vehicle>::Iterator thisPosition) {// recursive print list of the available vehicles
	
	/*
	if (thisPosition != v_List.end()) {
		if ((*thisPosition).status()) { cout << *thisPosition; }
		printList(++thisPosition);
	}
	*/
	if (thisPosition != v_List.end()) 
	{
		if ((*thisPosition).status()) 
		{ 
			cout << *thisPosition; 
		}
		
		printAvailableList(++thisPosition);
	}
}
bool Inventory::found(int seatsNo, NodeList<Vehicle>::Iterator thisPosition) {
	// print list of the available vehicles that has AT LEAST seatsNo seats.
	//Pre-conditions: seatsNo is a positive value > 0

	/*
	int count = 0;
	bool Yes = false;
	for (count = 0; count < registredVehiclesNo; ++count)
		if (v_List.at(count).status() && v_List.at(count).getSeats() >= seatsNo) {
			cout << v_List.at(count);

		}
	return Yes;
	*/

	if (thisPosition != v_List.end()) {
		if ((*thisPosition).getSeats() >= seatsNo && (*thisPosition).status())
		{
			cout << (*thisPosition);
		}

		found(seatsNo, ++thisPosition);
	}

	return false;
}

int Inventory::checkID(int _vehicleID_) {
	/*Project 6: Refactoring is needed here. You need to reimplement this method in recursive way.*/
	for (int i = 0; i < registredVehiclesNo; ++i) 
	{
		if (v_List.at(i).getID() == _vehicleID_) 
		{
			return i;
		}
	}

	return -1;
}

bool Inventory::reserveVehicle(int _vehicleID_) {

	int tmpVehicleID = checkID(_vehicleID_);

	/*
	for (NodeList<Vehicle>::Iterator itr = v_List.begin(); itr != objV.otherFeaturesList.end(); ++itr)
	{
		cout << *itr << ", ";
	}
	*/

	if (tmpVehicleID > -1 && v_List.at(tmpVehicleID).status()) //found and available
	{  	
		v_List.at(tmpVehicleID).reserve();

		return true;
	}

	return false;
}
bool Inventory::returnVehicle(int _vehicleID_) {

	int tmpVehicleID = checkID(_vehicleID_);

	if ((tmpVehicleID > -1) && (!(v_List.at(tmpVehicleID).status()))) //found and reserved available
	{  			
		v_List.at(tmpVehicleID).unReserve();

		return true;
	}

	return false;
}

//
//
bool Inventory::saveToFile(string fileName) {
	/*this method prints the list data in a text file (received as a parameter) */
	//pre-conditions: fileName is a valid file name.  something.txt
	ofstream outFile;
	outFile.open(fileName);
	if (outFile.fail()) return false;
	outFile << size() << endl;
	for (int i = 0; i < size(); ++i) // updating the database
	{ 
		outFile << v_List.at(i);
	}

	outFile.close();
	return true;

}


/************** Freind functions to class Inventory ******************/


ofstream& operator<<(ofstream& outfile, const Inventory& objV)
// overleaoding the insertion operator << for the output file stream
{

	for (int i = 0; i < objV.registredVehiclesNo; i++) 
	{
		outfile << objV.v_List.at(i);
		//outfile << "------------------------------------------\n";
	}
	return outfile;
}

