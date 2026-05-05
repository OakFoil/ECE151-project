#include <cmath>
#include <cstdint>
#include <optional>
#include <string>

using namespace std;

class Account {
private:
  uint32_t pin;
  long double balance = 0;

public:
  string name;

  class VerifiedView {
    friend class Account;

    VerifiedView(Account &a) : account(a) {}

  public:
    Account &account;

    long double getBalance() const { return account.balance; }

    bool withdraw(long double amount) {
      if (amount > account.balance)
        return 1;

      account.balance -= amount;

      return 0;
    }

    bool deposit(long double amount) {
      if (amount <= 0)
        return 1;

      account.balance += amount;

      return 0;
    }

    bool changePIN(uint32_t newPIN) { // TODO add restrictions on PIN
      if (ceil(log10(newPIN)) != 6)
        return 1;
      account.pin = newPIN;
      return 0;
    }
  };

  Account(string a, uint32_t b,
          long double c = 0) // TODO prevent constructor from constructing
                             // invalid PINS or negative balances
      : name(a), pin(b), balance(c) {}

  optional<VerifiedView>
  checkPIN(uint32_t pin) { // TODO add dely between PIN checks
    if (pin == this->pin)
      return VerifiedView(*this);

    return nullopt;
  }

  bool operator==(const Account &) const;
};
