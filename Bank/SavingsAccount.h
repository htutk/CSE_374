/**
 * CSE 374 18sp example
 * A simple savings account that derives from BankAccount. A SavingsAccount has
 * an interest rate and allows only 5 withdrawals per month.
 */

#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "BankAccount.h"

namespace bank {

class SavingsAccount : public BankAccount {
 public:
  SavingsAccount(double interestRate, std::string name);

  double getInterestRate() const;

  // Deducts the amount from this account, but throws a runtime_error if there
  // are no more available transactions for the month.
  virtual void withdraw(int amount) override;

 private:
  bool isNewMonth(time_t* curTime);

  double interestRate_;
  time_t lastMonth_;
  int numTransactionsInMonth_;
};

}

#endif
