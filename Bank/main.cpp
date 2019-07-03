/**
 * CSE 374 18sp example
 * A simple client program that uses a SavingsAccount.
 */

#include <iostream>

#include "BankAccount.h"
#include "SavingsAccount.h"

int main() {
  bank::SavingsAccount s(1, "Melissa");
  s.deposit(100);
  try {
    s.withdraw(2);
    s.withdraw(2);
    s.withdraw(2);
    s.withdraw(2);
    s.withdraw(2);
    s.withdraw(2);
  } catch (std::runtime_error err) {
    std::cout << "couldn't withdraw" << std::endl;
  }

  std::cout << "Balance at end: " << s.getBalance() << std::endl;

  return 0;
}
