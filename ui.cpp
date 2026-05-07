#include "ui/account.cpp"

// Written By Youssef Hamdy
void addAccount(Bank &bank) {
  string accountName;
  uint32_t pin;

  cout << "Enter account name\n";
  cin >> accountName;

  cout << "Enter PIN\n";
  cin >> pin;

  Account newAccount(accountName, pin);

  bank.addAccount(newAccount);

  cout << "Account added successfully\n";

  cout << "Account ID is: " << bank.getID(newAccount) << "\n";
}

// Written By Youssef Hamdy
void transferMoney(Bank &bank) {
  unsigned long long senderID;
  unsigned long long recieverID;
  uint32_t pin;
  long double moneySent;

  cout << "Enter your account ID\n";
  cin >> senderID;

  Account *sender = bank.searchAccountByID(senderID);

  if (sender == nullptr) {
    cout << "Invalid sender account\n";
    return;
  }

  cout << "Enter your PIN\n";
  cin >> pin;

  auto verifiedView = sender->checkPIN(pin);

  if (!verifiedView.has_value()) {
    cout << "Wrong PIN\n";
    return;
  }

  cout << "Enter reciever account ID\n";
  cin >> recieverID;

  Account *reciever = bank.searchAccountByID(recieverID);

  if (reciever == nullptr) {
    cout << "Invalid reciever account ID\n";
    return;
  }

  cout << "Enter amount of money to be sent\n";
  cin >> moneySent;

  if (verifiedView->withdraw(moneySent)) {
    cout << "Avilable money is less than needed to be sent\n";
  } else {
    reciever->deposit(moneySent);

    cout << "Money transferred successfully\n";
  }
}

void uiLoop(Bank &bank) { // TODO add option to cancel in each stage
  while (true) {
    auto input = prompt<string>(
        "1) Login\n2) Add Account\n3) Transfer Money\nEnter Operation");

    if (input == "q")
      return;

    auto op = stoi(input);

    switch (op) {
    case 1:
      login(bank);
      break;
    case 2:
      addAccount(bank);
      break;
    case 3:
      transferMoney(bank);
      break;
    default:
      output("Invalid Operation");
    }
  }
}
