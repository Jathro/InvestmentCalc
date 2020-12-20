#include <iostream>
#include "Compound.h"
using namespace std;

// Initial Constructor
Compound::Compound(double initialInvestment, double monthlyDeposit, int interestRate, int month) {
    this->m_compMonth = month;
    this->m_compOpeningAmt = initialInvestment;
    this->m_compDeposit = monthlyDeposit;
    this->m_compBalance = initialInvestment + monthlyDeposit;
    SetCalculateInterest(this->m_compBalance, interestRate);
    this->m_compClosingAmt = this->m_compBalance + this->m_compInterestAmt;
}

// Calculates interest on supplied values
void Compound::SetCalculateInterest(double initialAmt, int& interestRate) {
    this->m_compInterestAmt = initialAmt * (((double)interestRate / (double)100) / (double)12);
}

// Prints the monthly report values
void Compound::PrintMonthReport() {
    // cout << "PRINTMONTH MONTH: " << this->compMonth << endl;
    printf("%d             ", this->m_compMonth);
    printf("%.2f           ", this->m_compOpeningAmt);
    printf("%.2f           ", this->m_compDeposit);
    printf("%.2f           ", this->m_compBalance);
    printf("%.4f           ", this->m_compInterestAmt);
    printf("%.2f\n", this->m_compClosingAmt);
}