#include "account.cpp"
#include <vector>

using namespace std;

class Bank {
public:
  vector<Account> entries;

  long long getID(Account account) { // TODO make IDs random
    for (size_t i = 0; i < entries.size(); i++)
      if (entries[i] == account)
        return i;

    return -1;
  }

  Account *searchAccountByName(string name) {
    for (auto &entry : entries) {
      if (entry.name == name)
        return &entry;
    }

    return nullptr;
  }

  Account *searchAccountByID(unsigned long long id) {
    if (id > entries.size())
      return nullptr;

    return &entries[id];
  }

  void addAccount(Account account) { entries.push_back(account); }
};
