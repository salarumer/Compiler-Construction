#include <iostream>
#include <stdlib.h> // Standard library for exit function
#include<conio.h> // Header file for console input/output (specific to Windows)
using namespace std;

/*
Grammar:
E -> TE'
E' -> +TE' | -TE' | null
T -> FT'
T' -> *FT' | /FT' | null
F -> id | num | (E)
*/

int count = 0; // Global variable to keep track of the position while parsing the input expression
void E(); // Function prototypes for non-terminal symbols
void Ed();
void T();
void Td();
void F();

string expr; // Global variable to store the input expression

int main() {
  cin >> expr; // Input the expression
  int l = expr.length();
  expr += "$"; // Adding '$' as end marker to the input expression
  E(); // Start parsing from the starting symbol E
  if (l == count) // If the whole input is parsed and count matches the length of input
  {
    cout << "Accepted" << endl; // Print "Accepted"
    getchar(); // Get a character from the console (used to pause the console window)
  }else
    cout << "Rejected" << endl; // Print "Rejected"
  getchar(); // Get a character from the console (used to pause the console window)
}

void E() {
  cout << "E->TE'" << endl; // Production rule
  getchar(); // Get a character from the console (used to pause the console window)
  T(); // Call T()
  Ed(); // Call Ed()
}

void Ed() {
  if (expr[count] == '+') { // If the current character is '+'
    count++; // Move to the next character
    cout << "E'->+TE'" << endl; // Production rule
    getchar(); // Get a character from the console (used to pause the console window)
    T(); // Call T()
    Ed(); // Call Ed() recursively
  }
  else if (expr[count] == '-') { // If the current character is '-'
    count++; // Move to the next character
    cout << "E'->-TE'" << endl; // Production rule
    getchar(); // Get a character from the console (used to pause the console window)
    T(); // Call T()
    Ed(); // Call Ed() recursively
  }
  else { // If the current character is not '+' or '-'
    cout << "E'->null" << endl; // Null production rule
    getchar(); // Get a character from the console (used to pause the console window)
  }
}

void T() {
  cout << "T->FT'" << endl; // Production rule
  getchar(); // Get a character from the console (used to pause the console window)
  F(); // Call F()
  Td(); // Call Td()
}

void Td() {
  if (expr[count] == '*') { // If the current character is '*'
    count++; // Move to the next character
    cout << "T'->*FT'" << endl; // Production rule
    getchar(); // Get a character from the console (used to pause the console window)
    F(); // Call F()
    Td(); // Call Td() recursively
  }
  else if (expr[count] == '/') { // If the current character is '/'
    count++; // Move to the next character
    cout << "T'->/FT'" << endl; // Production rule
    getchar(); // Get a character from the console (used to pause the console window)
    F(); // Call F()
    Td(); // Call Td() recursively
  }
  else { // If the current character is neither '*' nor '/'
    cout << "T'->null" << endl; // Null production rule
    getchar(); // Get a character from the console (used to pause the console window)
  }
}

void F() {
  if (isalpha(expr[count])) { // If the current character is an alphabet
    count++; // Move to the next character
    cout << "F->id" << endl; // Production rule
    getchar(); // Get a character from the console (used to pause the console window)
  } 
  else if (isdigit(expr[count])) { // If the current character is a digit
    count++; // Move to the next character
    cout << "F->digit" << endl; // Production rule
    getchar(); // Get a character from the console (used to pause the console window)
  } 
  else if (expr[count] == '(') { // If the current character is '('
    count++; // Move to the next character
    cout << "F->(E)" << endl; // Production rule
    getchar(); // Get a character from the console (used to pause the console window)
    E(); // Call E() recursively
    if (expr[count] != ')') { // If there is no closing bracket
      cout << "Rejected" << endl; // Print "Rejected"
      getchar(); // Get a character from the console (used to pause the console window)
      exit(0); // Exit the program
    }
    count++; // Move to the next character
  } 
  else { // If the current character is not a valid identifier or number
    cout << "Rejected" << endl; // Print "Rejected"
    getchar(); // Get a character from the console (used to pause the console window)
    exit(0); // Exit the program
  }
}
