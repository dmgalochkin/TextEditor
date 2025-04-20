#include <iostream>
#include "TString.h"
#include "TextEditor.h"
int main()
{
  int length, x, y;
  TextEditor editor;
  std::cout << "Length: ";
  std::cin >> length;
  editor.SetLength(length);
  std::cout << '\n';
  std::cout << "X: ";
  std::cin >> x;
  editor.SetX(x);
  std::cout << '\n';
  std::cout << "Y: ";
  std::cin >> y;
  editor.SetY(y);
  std::cout << '\n';
  editor.Input();

  TString res = editor.GetContent();

  std::cout << "\n\nResult: " << res << '\n';
  std::cout << '\n';
  system("pause");
}