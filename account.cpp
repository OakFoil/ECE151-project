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
        return true;
      account.balance -= amount;
      return false;
    }

    bool deposit(long double amount) {
      if (amount <= 0)
        return true;
      account.balance += amount;
      return false;
    }

    void changePIN(uint32_t newPIN) { // TODO add restrictions on PIN
      account.pin = newPIN;
    }
  };

  Account(string a, uint32_t b, long double c = 0)
      : name(a), pin(b), balance(c) {}

  optional<VerifiedView>
  checkPIN(uint32_t pin) { // TODO add dely between PIN checks
    if (pin == this->pin)
      return VerifiedView(*this);
    return nullopt;
  }

  bool operator==(const Account &) const;
};
