#pragma once
#include <iostream>

using namespace std;

template <typename T> T prompt(string str) {
  cout << str << ":\n";

  T input;
  cin >> input;

  return input;
}

template <typename T> void output(T out) { cout << out << "\n"; }
