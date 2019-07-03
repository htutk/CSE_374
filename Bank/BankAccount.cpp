/**
 * CSE 374 18sp example
 * A simple bank account class that we'll use as a base class for other types of
 * accounts.
 */

#include "BankAccount.h"

namespace bank {

// We must define the static variable here as well.
int BankAccount::accountCount_ = 0;

BankAccount::BankAccount(const std::string& accountHolder)
    : accountHolder_(accountHolder),
      accountId_(++accountCount_),
      balance_(0) {}

int BankAccount::getBalance() const {
  return balance_;
}

int BankAccount::getAccountId() const {
  return accountId_;
}

const std::string& BankAccount::getAccountHolder() const {
  return accountHolder_;
}

void BankAccount::deposit(int amount) {
  balance_ += amount;
}

void BankAccount::setBalance(int balance) {
  balance_ = balance;
}

}
