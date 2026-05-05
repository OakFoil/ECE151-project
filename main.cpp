#include "ui.cpp"

using namespace std;

Bank bank;

int main() {
  bank.entries = {{"Mark", 0, 1e6},
                  {"Abdallah", 10, 1e6},
                  {"Mazen", 123, 1},
                  {"Youssef", 321, 1e3}};

  while (true)
    uiLoop(bank);

  return 0;
}
