/**
 * CSE 374 18sp example
 * A simple bank account class that we'll use as a base class for other types of
 * accounts.
 */

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>

namespace bank {

class BankAccount {
 public:
  // Constructor
  explicit BankAccount(const std::string& accountHolder);

  // We don't want to allow bank accounts to be copied with a copy constructor!
  // Bad things could happen if we made copies of bank accounts. We can disable
  // the copy constructor by setting it equal to the "delete" keyword.
  BankAccount(const BankAccount& other) = delete;

  // Accessors
  int getBalance() const;
  int getAccountId() const;
  const std::string& getAccountHolder() const;

  // Modifier - add money.
  void deposit(int amount);

  // The withdraw() function is different for every type of account, so it
  // doesn't make sense to give an implementation of withdraw() in the base
  // class. By marking it virtual and setting it equal to 0, we require any
  // derived classes to implement this function themselves.
  virtual void withdraw(int amount) = 0;

 protected:
  // The setBalance function is protected so that other derived classes can
  // modify the balance.
  void setBalance(int balance);

 private:
  const std::string accountHolder_;
  const int accountId_;
  int balance_;

  static int accountCount_;
};

}

#endif
