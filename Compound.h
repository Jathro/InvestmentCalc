#ifndef COMPOUND_H
#define COMPOUND_H
using namespace std;

class Compound {

    public:
        Compound(double initialInvestment, double monthlyDeposit, int interestRate, int month);
        void SetCalculateInterest(double t_initialAmt, int& t_interestRate);
        int GetCurrentMonth() {return m_compMonth;}
        double GetClosingBalance() {return m_compClosingAmt;}
        double GetEarnedInterest() {return m_compInterestAmt;}
        double GetMonthlyDeposit() {return m_compDeposit;}
        void PrintMonthReport();

    private:
        int m_compMonth;
        double m_compOpeningAmt;
        double m_compDeposit;
        double m_compClosingAmt;
        double m_compInterestAmt;
        double m_compBalance;
};
#endif