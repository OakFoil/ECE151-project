#include "bank.cpp"
#include <algorithm>
#include <iostream>

using namespace std;

template <typename T> T prompt(string str) {
  cout << str << ":\n";

  T input;
  cin >> input;

  return input;
}

template <typename T> void output(T out) { cout << out << "\n"; }

Account &getAccount(Bank &bank) {
  Account *accountRef = nullptr;

  while (true) {
    auto input = prompt<string>("Enter Account ID Or Name");

    if (all_of(input.begin(), input.end(), ::isdigit))
      accountRef = bank.searchAccountByID(stoull(input));
    else if (all_of(input.begin(), input.end(), ::isalpha))
      accountRef = bank.searchAccountByName(input);
    else
      cout << "Invalid Input\n";
    if (accountRef == nullptr)
      output("Invalid ID Or Name");
    else
      return *accountRef;
  }
}

Account::VerifiedView getVerifiedView(Bank &bank) {
  auto &account = getAccount(bank);

  while (true) {
    auto pin = prompt<uint32_t>(
        "Enter PIN"); // TODO make PIN not visible while entering

    auto optionalVerifiedView = account.checkPIN(pin);

    if (!optionalVerifiedView.has_value())
      output("Wrong PIN");
    else
      return optionalVerifiedView.value();
  }
}

void handleOperation(Account::VerifiedView verifiedView) {
  while (true) {
    auto op =
        prompt<unsigned int>("1) Get Balance\n2) deposit\n3) withdraw\n4) "
                             "Change PIN\nEnter Operation");

    if (op == 1) {
      cout << "Balance is ";
      output(verifiedView.getBalance());
      return;
    } else if (op == 2)
      while (true) {
        auto amount = prompt<long double>("Enter Amount");

        if (verifiedView.deposit(amount))
          output("Invalid Amount");
        else {
          output("Amount Deposited Successfully");
          return;
        }
      }
    else if (op == 3)
      while (true) {
        auto amount = prompt<long double>("Enter Amount");

        if (verifiedView.withdraw(amount))
          output("Invalid Amount");
        else {
          output("Amount Withdrawn Successfully");
          return;
        }
      }
    else if (op == 4)
      while (true) {
        auto newPIN = prompt<uint32_t>("Enter New PIN");

        if (verifiedView.changePIN(newPIN))
          output("PIN must be 6 digits");

        else {
          output("PIN Changed Successfully");
          return;
        }
      }
    else
      output("Invalid operation");
  }
}

void uiLoop(Bank &bank) { // TODO add option to cancel in each stage
  auto verifiedView = getVerifiedView(bank);

  cout << "Hello ";
  output(verifiedView.account.name);

  handleOperation(verifiedView);
}
