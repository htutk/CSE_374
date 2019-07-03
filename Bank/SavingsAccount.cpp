/**
 * CSE 374 18sp example
 * A simple savings account that derives from BankAccount. A SavingsAccount has
 * an interest rate and allows only 5 withdrawals per month.
 */

#include "SavingsAccount.h"
#include <ctime>

namespace bank {

SavingsAccount::SavingsAccount(
    double interestRate, std::string name)
    : BankAccount(name),
      interestRate_(interestRate),
      numTransactionsInMonth_(0) {}

double SavingsAccount::getInterestRate() const {
  return interestRate_;
}

void SavingsAccount::withdraw(int amount) {
  time_t curTime;
  if (isNewMonth(&curTime)) {
    lastMonth_ = curTime;
    numTransactionsInMonth_ = 1;
    setBalance(getBalance() - amount);
  } else if (numTransactionsInMonth_ < 5) {
    setBalance(getBalance() - amount);
    numTransactionsInMonth_++;
  } else {
    throw std::runtime_error("Cannot withdraw more than 5x per month");
  }
}

bool SavingsAccount::isNewMonth(time_t* curTime) {
  // Get the current time, and find the current month and year.
  time(curTime);
  struct tm* curTimeInfo = localtime(curTime);
  int curYear = curTimeInfo->tm_year;
  int curMonth = curTimeInfo->tm_mon;

  // Find the month and year of the last transaction.
  struct tm* oldTimeInfo = localtime(&lastMonth_);
  int oldYear = oldTimeInfo->tm_year;
  int oldMonth = oldTimeInfo->tm_mon;

  // Return true if the month/year is the same.
  return curYear == oldYear && curMonth == oldMonth;
}

}
