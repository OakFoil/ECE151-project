#include <chrono>
#include <cstdint>
#include <expected>
#include <string>

using namespace std;
using namespace std::chrono;

enum CheckPINErrors { WrongPIN, WaitNotFinished };

class Account {
private:
  uint32_t pin;
  long double balance = 0;
  unsigned failedAttempts = 0;
  steady_clock::time_point lastFailedAttempt = steady_clock::now();

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

    bool changePIN(uint32_t newPIN) {
      if (newPIN < 1e5 || newPIN >= 1e6)
        return 1;
      account.pin = newPIN;
      return 0;
    }
  };

  Account(string a, uint32_t b,
          long double c = 0) // TODO prevent constructor from constructing
                             // invalid PINS or negative balances
      : pin(b), balance(c), name(a) {}

  bool deposit(long double amount) {
    if (amount <= 0)
      return 1;

    balance += amount;

    return 0;
  }

  auto getTimeToWait() { // TODO simplify delay logic
    if (failedAttempts < 3)
      return steady_clock::duration::zero();

    auto elapsed = steady_clock::now() - lastFailedAttempt;

    return max(3s - elapsed, steady_clock::duration::zero());
  }

  expected<VerifiedView, CheckPINErrors> checkPIN(uint32_t pin) {
    if (getTimeToWait() != 0s) {
      return unexpected(WaitNotFinished);
    }

    if (failedAttempts >= 3)
      failedAttempts = 0;

    if (pin != this->pin) {
      failedAttempts++;
      lastFailedAttempt = steady_clock::now();
      return unexpected(WrongPIN);
    }

    return VerifiedView(*this);
  }

  bool operator==(const Account &) const = default;
};
