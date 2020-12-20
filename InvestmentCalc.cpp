/*
Name: Peter Slusarz
Date: 11/29/2020
*/

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Compound.h"

using namespace std;

// Validate user input is a digit
bool StringToDouble(string input, double& output) {
    for (char c : input) {
        if (!isdigit(c)) {
            return false;
        }
    }
    string::size_type sz;
    output = stod(input, &sz);
    return true;
}

// Validate user input is a digit
bool StringToInt(string input, int& output) {
    for (char c : input) {
        if (!isdigit(c)) {
            return false;
        }
    }
    string::size_type sz;
    output = stod(input, &sz);
    return true;
}

// Print Data Input
void PrintDataInput(double& t_initInvestment, double& t_monthlyDeposit, int& t_annualInterest, int& t_numOfYears) {
    cout << "\n\n************Data Input************" << endl;
    printf("Initial Investment Amount: $%.2f", t_initInvestment);
    printf("\nMonthly Deposit: $%.2f", t_monthlyDeposit);
    cout << "\nAnnual Interest: %";
    printf("%d", t_annualInterest);
    printf("\nNumber of years: %d\n", t_numOfYears);
}

// Validate input values are valid
void DataInput (double& t_initInvestment, double& t_monthlyDeposit, int& t_annualInterest, int& t_numOfYears, int& numMonths, int& dataInput) {
    char menuInput;
    string temp;
    bool done = false;

    if (dataInput == 0 ) {
        PrintDataInput(t_initInvestment, t_monthlyDeposit, t_annualInterest, t_numOfYears);
        ++dataInput;
    }

    cout << "\nEnter the following values:" << endl;
    while (!done) {
        cout << "Initial Investment Amount:" << endl;
        cin >> temp;
        if (StringToDouble(temp, t_initInvestment)) {break;} {cout << "Please enter a valid number\n";}
    }
    done = false;
    while (!done) {
        cout << "Monthly Deposit:" << endl;
        cin >> temp;
        if (StringToDouble(temp, t_monthlyDeposit)) {break;} {cout << "Please enter a valid number\n";}
    }
    done = false;
    while (!done) {
        cout << "Annual Interest:" << endl;
        cin >> temp;
        if (StringToInt(temp, t_annualInterest)) {break;} {cout << "Please enter a valid number\n";}
    }
    done = false;
    while (!done) {
        cout << "Number of years:" << endl;
        cin >> temp;
        if (StringToInt(temp, t_numOfYears)) {break;} {cout << "Please enter a valid number\n";}
    }
    numMonths = t_numOfYears * 12;
    PrintDataInput(t_initInvestment, t_monthlyDeposit, t_annualInterest, t_numOfYears);
    cout << "\nPress any key to continue" << endl;
    cin >> menuInput;
}

// Get closing balance from last element in vector
double GetPreviousClosing(vector<shared_ptr<Compound>> t_currCompound) {
    return t_currCompound.back()->GetClosingBalance();
}

// Print yearly details
void PrintCompoundInterestYearly(vector<shared_ptr<Compound>> t_compoundVector) {
    double yearlyBalance;
    if (t_compoundVector.at(0)->GetMonthlyDeposit() > 0) {
        cout << "\n\n   Balance and Interest With Additional Monthly Deposits" << endl;
    }
    else {
        cout << "\n\n   Balance and Interest Without Additional Monthly Deposits" << endl;
    }
    cout << "====================================================================" << endl;
    cout << "Year                "
         << "Year End Balance        "
         << "Year End Earned Interst " << endl;
    cout << "--------------------------------------------------------------------" << endl;

    yearlyBalance = 0;
    for (int i = 0; i < t_compoundVector.size(); ++i) {
        if ((i + 1) % 12 != 0) {
            yearlyBalance += t_compoundVector.at(i)->GetEarnedInterest();
        }
        else {
            yearlyBalance += t_compoundVector.at(i)->GetEarnedInterest();
            printf("%d%20s", (i + 1) / 12, "$");
            printf("%.2f", t_compoundVector.at(i)->GetClosingBalance());
            printf("%20s%.2f","$", yearlyBalance);
            yearlyBalance = 0;
            cout << endl;
        }
    }
}

int main() {
    double investmentInput = 1;
    double depositInput = 50;
    int interestInput = 5;
    int numYearsInput = 5;
    int numMonths = numYearsInput * 12;
    char menuInput;
    int dataInput = 0;
    vector<shared_ptr<Compound>> interestVecDeposit;
    vector<shared_ptr<Compound>> interestVec;
    shared_ptr<Compound> currMonthDeposit(nullptr);
    shared_ptr<Compound> currMonth(nullptr);

    while (menuInput != 'x') {
    DataInput(investmentInput, depositInput, interestInput, numYearsInput, numMonths, dataInput);

    for (int i = 1; i <= numMonths; ++i) {
        if (i == 1) {
            currMonthDeposit = make_shared<Compound> (investmentInput, depositInput, interestInput, i);
            currMonth = make_shared<Compound> (investmentInput, 0.00, interestInput, i);
        }
        else {
            currMonthDeposit = make_shared<Compound> (GetPreviousClosing(interestVecDeposit), depositInput, interestInput, i);
            currMonth = make_shared<Compound> (GetPreviousClosing(interestVec), 0.00, interestInput, i);
        }
        
        interestVec.push_back(currMonth);
        interestVecDeposit.push_back(currMonthDeposit);
    }

    PrintCompoundInterestYearly(interestVec);
    PrintCompoundInterestYearly(interestVecDeposit);

    interestVec.clear();
    interestVecDeposit.clear();

    cout << "Press any key to enter new values(x to exit)" << endl;
    cin >> menuInput;
    }
    return 0;
}