#include "TextEditor.h"
#include <conio.h>
#include <windows.h>
#include <iostream>

TextEditor::TextEditor()
{
  x = 0;
  y = 0;
  content = TString();
}

void TextEditor::SetLength(int length_)
{
  if (length_ <= 0)
    throw "Non positive length";
  length = length_;
}

int TextEditor::GetLength()
{
  return length;
}

void TextEditor::SetX(int x_)
{
  x = x_;
}

void TextEditor::SetY(int y_)
{
  y = y_;
}

int TextEditor::GetX()
{
  return x;
}

int TextEditor::GetY()
{
  return y;
}

void TextEditor::ShowEditor()
{
  COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y)};
  coord.X -= 1;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
  std::cout << '|' << std::string(length, '_') << '|';
  coord.X += 1;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TextEditor::Input()
{
  content.SetData(nullptr);

  ShowEditor();
  COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};

  while (true)
  {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    int ch = _getch();
    if (ch == 13)
      break;

    if (ch == 8)
    {
      if (content.GetSize() > 0)
      {
        content = content.Substr(0, content.GetSize() - 1);
        std::cout << "\b_\b";
        coord.X--;
      }
      continue;
    }

    if (content.GetSize() < length && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == ' '))
    {
      content += static_cast<char>(ch);
      std::cout << static_cast<char>(ch);

      coord.X++;
    }
  }
}

TString TextEditor::GetContent()
{
  return content;
}