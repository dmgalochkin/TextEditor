#pragma once
#include "TString.h"

class TextEditor
{
private:
  int length;
  int x;
  int y;
  TString content;

public:
  TextEditor();

  void SetLength(int length_);
  int GetLength();

  void SetX(int x_);
  void SetY(int y_);

  int GetX();
  int GetY();

  void ShowEditor();
  void Input();
  TString GetContent();
};