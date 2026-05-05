#include "bank.cpp"
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

Bank bank;

template <typename T> T prompt(string str) {
  cout << str << ":\n";
  T input;
  cin >> input;
  return input;
}

template <typename T> void output(T out) { cout << out << "\n"; }

void uiLoop() { // TODO add option to cancel in each stage and do not restart
                // loop on each error
  auto input = prompt<string>("Enter Account ID Or Name");
  Account *accountRef = nullptr;
  if (all_of(input.begin(), input.end(), ::isdigit))
    accountRef = bank.searchAccountByID(stoull(input));
  else if (all_of(input.begin(), input.end(), ::isalpha))
    accountRef = bank.searchAccountByName(input);
  else {
    cout << "Invalid Input\n";
    return;
  }
  if (accountRef == nullptr) {
    output("Invalid ID Or Name");
    return;
  }
  auto &account = *accountRef;
  auto pin =
      prompt<uint32_t>("Enter PIN"); // TODO make PIN not visible while entering
  auto optionalVerifiedView = account.checkPIN(pin);
  if (!optionalVerifiedView.has_value()) {
    output("Wrong PIN");
    return;
  }
  auto verifiedView = optionalVerifiedView.value();
  cout << "Hello ";
  output(verifiedView.account.name);
  auto op = prompt<unsigned int>("1) Get Balance\n2) deposit\n3) withdraw\n4) "
                                 "Change PIN\nEnter Operation");
  if (op == 1) {
    cout << "Balance is ";
    output(verifiedView.getBalance());
  } else if (op == 2) {
    auto amount = prompt<long double>("Enter Amount");
    if (verifiedView.deposit(amount)) {
      output("Invalid Amount");
      return;
    } else
      output("Amount Deposited Successfully");
  } else if (op == 3) {
    auto amount = prompt<long double>("Enter Amount");
    if (verifiedView.withdraw(amount)) {
      output("Invalid Amount");
      return;
    } else
      output("Amount Withdrawn Successfully");
  } else if (op == 4) {
    auto newPIN = prompt<uint32_t>("Enter New PIN");
    verifiedView.changePIN(newPIN);
    output("PIN Changed Successfully");
  } else {
    output("Invalid operation");
    return;
  }
}

int main() {
  bank.entries = {{"Mark", 0, 1e6},
                  {"Abdallah", 10, 1e6},
                  {"Mazen", 123, 1},
                  {"Youssef", 321, 1e3}};
  while (true)
    uiLoop();
  return 0;
}
