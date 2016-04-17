// ReadWriteFiles_Start.cpp
// Calculate gross pay, net pay, pension and deductions 
// for employees of XYZ Company
// Author: Dewi Tjin - Bob Langelaan's original ReadWriteFiles_Start.cpp modified 
// Date: April 15, 2016


#include <iostream>
#include <conio.h>  // Required for _getch() function
#include <fstream>  // Required for file input/output
#include <iomanip>  // setw(), setprecision
#include <string>	// to_string


using namespace std;

//global constants
const char* HEADER                  = "XYZ Company\n";
const char* HEADER_DASHES           = "--------------------------------\n";
const char* SOCIAL_INSURANCE_NUMBER = "Social insurance no.";
const char* NET_PAY                 = "net pay";
const char* GROSS_PAY               = "gross pay";
const char* PENSION                 = "pension";
const char* DEDUCTIONS              = "deductions";
const char* BODY_DASHES             = "--------------------------------------------------------------------\n";
const char* SUMMARY_HEADER          = "Summary\n";
const char* SUMMARY_DASHES          = "-------\n";

const char* TOTAL_EMPLOYEES         = "Number of employees processed:";
const char* TOTAL_GROSS             = "Total gross pay for all employees:";
const char* TOTAL_NET               = "Total net pay for all employees:";
const char* TOTAL_PENSION           = "Total pension withheld for all employees:";
const char* TOTAL_DEDUCTIONS        = "Total deductions for all employees:";

const int REGULAR_WORK_HOUR_LIMIT   = 40; //standard weekly regular work hours
const int WORK_HOUR_MAX             = 54; //max weekly work hours
const double PAYRATE_MULTIPLE       = 0.5;//the rate applied to the regular payrate

const double TAXABLE_CONSTANT1		= 14.00;
const double TAXABLE_CONSTANT2		= 11.00;
const double FEDERAL_CONSTANT1		= 0.14;
const double FEDERAL_CONSTANT2		= 0.00023;
const double PROVINCIAL_CONSTANT1	= 0.35;
const double PENSION_CONSTANT1		= 16.50;
const double PENSION_CONSTANT2		= 0.077;

const int SIN_MAX_LENGTH			= 9;
const int exemptionMin				= 0;
const int exemptionMax				= 19;
const int hoursWorkedMin			= 0;
const int hoursWorkedMax			= 54;
const double payRateMin				= 0.00;
const double payRateMax				= 99.99;

//prototypes
bool checkSocialSecurityNumber(long socialInsuranceNum);
bool checkExemptions(int numberOfExemptions);
bool checkHoursWorked(double hoursWorked);
bool checkPayRate(double payRate);

double calculateGrossPay(double payRate, double hoursWorked);
double calculateFederalAndProvincialDeduction(double grossPay, int numberOfExemptions);
double calculatePension(double grossPay);
double calculateNetPay(double grossPay, double deductions, double pension);

// One way to specify a file name:
const char * IN_FILE = "EmployeePayInput.txt";

// A second way to specify a file name:
#define OUT_FILE "EmployeePayOutput.txt"

int main()
{
	//Declare variables
	long socialInsuranceNum;	// social security number of employee
	int numberOfExemptions;		// store number of excemptions for employee

	double payRate = 0.0,		// store the pay rate for the employee
		hoursWorked = 0.0,		// store hours worked for the employee
		grossPay = 0.0,			// store gross pay for the employee
		netPay = 0.0,			// store netpay for the employee
		pension = 0.0,			// store pension for the employee
		deductions = 0.0,		// store deductions for the employee
		totalGrossPay = 0.0,	// total gross pay of all employees
		totalNetPay = 0.0,		// total net pay for all all employees
		totalPension = 0.0,		// total pension pay for all employees
		totalDeductions = 0.0;	// total deductions for all employees

	//Define ifstream object and open file
	ifstream ins;
	ins.open(IN_FILE);

	//Check that file opened without any issues
	if (ins.fail())
	{
		cerr << "ERROR--> Unable to open input file : " << IN_FILE << endl;
		cerr << '\n' << endl;
		_getch(); // causes execution to pause until a char is entered
		return -1; //error return code
	}

	//Define ofstream object and open file
	ofstream outs;
	outs.open(OUT_FILE);

	//Check that file opened without any issues
	if (outs.fail())
	{
		cerr << "ERROR--> Unable to open output file : " << OUT_FILE << endl;
		cerr << '\n' << endl;
		_getch(); // causes execution to pause until a char is entered
		return -2; //error return code
	}

	outs << fixed << setprecision(2); //defaults double to 0.00

	outs << HEADER;
	outs << HEADER_DASHES;
	outs << "\n";

	outs << left << setw(20) << SOCIAL_INSURANCE_NUMBER <<
		right << setw(12) << GROSS_PAY <<
		right << setw(11) << NET_PAY <<
		right << setw(11) << PENSION <<
		right << setw(14) << DEDUCTIONS << "\n";

	outs << BODY_DASHES;

	int employeeCounter = 0; //store employee counter, increments by one every time a valid data set is found
	// Process data until end of file is reached

	while (!ins.eof())
	{
		ins >> socialInsuranceNum >> payRate >> numberOfExemptions >> hoursWorked;
		bool validNumber = checkSocialSecurityNumber(socialInsuranceNum);
		bool validExemptions = checkExemptions(numberOfExemptions);
		bool validHoursWorked = checkHoursWorked(hoursWorked);
		bool validPayRate = checkPayRate(payRate);

		if (validNumber && validExemptions && validHoursWorked && validPayRate)
		{
			employeeCounter++;

			grossPay = calculateGrossPay(payRate, hoursWorked);
			totalGrossPay += grossPay;

			deductions = calculateFederalAndProvincialDeduction(grossPay, numberOfExemptions);
			totalDeductions += deductions;

			pension = calculatePension(grossPay);
			totalPension += pension;

			netPay = calculateNetPay(grossPay, deductions, pension);//deduction and pension has to be calculated first to get net pay
			totalNetPay += netPay;

			outs << left << setw(20) << socialInsuranceNum <<
				right << setw(12) << grossPay <<
				right << setw(11) << netPay <<
				right << setw(11) << pension <<
				right << setw(14) << deductions << "\n";
		}
		else
		{
			if (!validNumber)
			{
				cerr << left << setw(15) << socialInsuranceNum << "INPUT DATA ERROR:   " << "Invalid social security #" << endl;
			}

			if (!validPayRate)
			{
				cerr << left << setw(15) << socialInsuranceNum << "INPUT DATA ERROR:   " << "Invalid pay rate: " << payRate << endl;
			}

			if (!validExemptions)
			{
				cerr << left << setw(15) << socialInsuranceNum << "INPUT DATA ERROR:   " << "Invalid number of exemptions: " << numberOfExemptions << endl;
			}

			if (!validHoursWorked)
			{
				cerr << left << setw(15) << socialInsuranceNum << "INPUT DATA ERROR:   " << "Invalid hours worked: " << hoursWorked << endl;
			}
		}//end of if/else
	}//end of while 

	outs << "\n" << "\n" << "\n";

	outs << SUMMARY_HEADER;
	outs << SUMMARY_DASHES;

	outs << left << setw(37) << TOTAL_EMPLOYEES << right << setw(7) << employeeCounter << "\n";
	outs << left << setw(37) << TOTAL_GROSS << right << setw(7) << totalGrossPay << "\n";
	outs << left << setw(37) << TOTAL_NET << right << setw(7) << totalNetPay << "\n";
	outs << left << setw(37) << TOTAL_PENSION << right << setw(10) << totalPension << "\n";
	outs << left << setw(37) << TOTAL_DEDUCTIONS << right << setw(14) << totalDeductions << "\n";

	// Close files
	ins.close();
	outs.close();

	_getch(); // causes execution to pause until char is entered
}

//Fuction to check if the social insurance number is a 9 digit number
bool checkSocialSecurityNumber(long socialInsuranceNum)
{
	bool validInput;
	string sin = to_string(socialInsuranceNum);

	while (sin.length() == SIN_MAX_LENGTH && sin.at(0) != 0) {
		return true;
	}

	return false;
}

//Function to check if number of exemptions is between 0 to 19
bool checkExemptions(int numberOfExemptions)
{
	bool validInput;

	while (numberOfExemptions >= exemptionMin && numberOfExemptions <= exemptionMax) {
		return true;
	}

	return false;
}

//Function to check number of hours worked
bool checkHoursWorked(double hoursWorked)
{
	bool validInput;

	while (hoursWorked >= hoursWorkedMin && hoursWorked <= hoursWorkedMax) {
		return true;
	}

	return false;
}

//Function to check if hourly pay rate is between 0 to 99.99 - and no negative numbers
bool checkPayRate(double payRate)
{
	bool validInput;

	while (payRate >= payRateMin && payRate <= payRateMax) {
		return true;
	}

	return false;
}

//Function to calculate Gross Pay - Regular pay for the first 40 hours and 
//time and a half beyond that, up to a limit of 54 hours in any given week.
double calculateGrossPay(double payRate, double hoursWorked) {

	double grossPayAmount = 0;

	if (hoursWorked <= REGULAR_WORK_HOUR_LIMIT) {
		grossPayAmount = payRate * hoursWorked; //Regular pay for the first 40 hours		
	}
	else {
		
		if (hoursWorked <= WORK_HOUR_MAX) { //time and a half beyond that, up to a limit of 54 hours in any given week.
			grossPayAmount = payRate * REGULAR_WORK_HOUR_LIMIT;//Regular pay for the first 40 hours
			payRate += (payRate * PAYRATE_MULTIPLE);
			grossPayAmount += (payRate * (hoursWorked - REGULAR_WORK_HOUR_LIMIT));
			return grossPayAmount;
		}
	}
	return grossPayAmount;
}

//Function to calculate Deductions - Let "gross" represent gross pay and "taxable" represent taxable pay.
//Let "exempt" represent the number of exemptions.
double calculateFederalAndProvincialDeduction(double grossPay, int numberOfExemptions) {

	double taxable = 0;
	double federal = 0;
	double provincial = 0;
	double totalDeduction = 0; //federal + provincial

	taxable = grossPay - (TAXABLE_CONSTANT1 * numberOfExemptions) - TAXABLE_CONSTANT2; //calculate taxable salary

	if (taxable >= 0) { //check if taxable pay is not negative
		federal = taxable * (FEDERAL_CONSTANT1 + (FEDERAL_CONSTANT2  * taxable));
		provincial = federal * PROVINCIAL_CONSTANT1; //defined as 35 % of the amount withheld for federal income tax
		totalDeduction = federal + provincial;
		return totalDeduction;
	}

	return totalDeduction; //if taxable is less than 0 then just return 0
}

//Function to calculate pension pay
double calculatePension(double grossPay) {

	double pension = 0;

	pension = grossPay * PENSION_CONSTANT2;

	if (pension > PENSION_CONSTANT1) {
		return PENSION_CONSTANT1;//$16.50 or 7.7% of gross, whichever is less. 
	}

	return pension;
}

//Net pay - Gross pay less all deductions.
double calculateNetPay(double grossPay, double deductions, double pension) {

	double netPay = 0;

	if (grossPay >= (deductions - pension)) { //makes sure gross pay is larger than deductions 
		netPay = grossPay - deductions - pension;
		return netPay;
	}

	return 0; //if deductions exceed net pay then just return 0 for net pay
}


