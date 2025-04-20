#pragma once
#include <iostream>
class TString
{
private:
  char* data;
  int size;
public:
  int GetSize() const;
  char* GetData();
  void SetData(char* data_);

  TString();
  TString(char* data_);
  TString(const TString & p);
  TString(TString && p);
  ~TString();

  TString operator+ (const TString & p);
  TString operator* (int k);

  TString& operator= (const TString & p);

  bool operator== (const TString & p);
  bool operator!= (const TString & p);
  bool operator< (const TString & p);
  bool operator> (const TString & p);

  TString& operator+= (char c);

  char& operator[] (int i) const;

  friend std::ostream& operator<<(std::ostream& o, TString& p);
  friend std::istream& operator>>(std::istream& i, TString& p);

  int FindChar(char c);
  int FindSubstring(const TString &sub);
  TString* Split(char delimiter, int &resultCount);
  int* FindAllSubstrings(const TString &sub, int &resultCount);
  char MostFrequentChar();
  char* GetUniqueChars(int &uniqueCount);
  void GetCharCounts(char* &chars, int* &counts, int &uniqueCount);
  TString Substr(int pos, int len);
};