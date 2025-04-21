#include "TString.h"
#include <iostream>
#include <cstring>

char& TString::operator[](int i) const
{
  return data[i];
}

TString::TString()
{
  data = nullptr;
  size = 0;
}

TString::TString(char* data_)
{
  if (data_ == nullptr)
  {
    data = nullptr;
    size = 0;
  } else {
    size = strlen(data_);
    data = new char[size + 1];
    for (int i = 0; i < size; ++i)
    {
      data[i] = data_[i];
    }
    data[size] = '\0';
  }
}

TString::TString(const TString & p)
{
  size = p.GetSize();
  data = new char[size + 1];
  for (int i = 0; i < size; ++i)
  {
    data[i] = p[i];
  }
  data[size] = '\0';
}

TString::TString(TString &&p)
{
  size = p.size;
  data = p.data;
  p.data = nullptr;
  p.size = 0;
}

TString::~TString()
{
  if (data != nullptr)
    delete[] data;
}

int TString::GetSize() const
{
  return size;
}

char* TString::GetData()
{
  return data;
}

void TString::SetData(char* data_)
{
  if (data != nullptr)
    delete[] data;
  if (data_ == nullptr)
  {
    data = nullptr;
    size = 0;
  } else {

    size = strlen(data_);
    data = new char[size + 1];
    for (int i = 0; i < size; ++i)
    {
      data[i] = data_[i];
    }
    data[size] = '\0';
  }
}

TString TString::operator+(const TString &p)
{
  int n = GetSize();
  int m = p.GetSize();
  char* newData = new char[n + m + 1];
  for (int i = 0; i < n + m; ++i)
  {
    if (i < n)
      newData[i] = data[i];
    else
      newData[i] = p.data[i - n];
  }
  newData[n + m] = '\0';
  TString newString = TString(newData);
  delete[] newData;
  return newString;
}

TString TString::operator*(int k)
{
  int n = GetSize();
  char* newData = new char[n * k + 1];
  for (int i = 0; i < n * k; ++i)
  {
    newData[i] = data[i % n];
  }
  newData[n * k] = '\0';
  TString newString = TString(newData);
  delete[] newData;
  return newString;
}

TString& TString::operator=(const TString &p)
{
  if (&p == this)
    return *this;
  if (data != nullptr)
    delete[] data;
  size = p.GetSize();
  data = new char[size + 1];
  for (int i = 0; i < size; ++i)
  {
    data[i] = p[i];
  }
  data[size] = '\0';
  return *this;
}

bool TString::operator==(const TString &p)
{
  if (GetSize() != p.GetSize()) return false;
  for (int i = 0; i < size; ++i)
  {
    if (data[i] != p[i])
      return false;
  }
  return true;
}

bool TString::operator!=(const TString &p)
{
  return !(*this == p);
}

bool TString::operator<(const TString &p)
{
  int m = p.GetSize();
  for (int i = 0; i < std::min(size, m); ++i)
  {
    if (data[i] < p[i])
      return true;
    if (data[i] > p[i])
      return false;
  }
  if (size < m)
    return true;
  else
    return false;
}

bool TString::operator>(const TString &p)
{
  int m = p.GetSize();
  for (int i = 0; i < std::min(size, m); ++i)
  {
    if (data[i] > p[i])
      return true;
    if (data[i] < p[i])
      return false;
  }
  if (size > m)
    return true;
  else
    return false;
}

std::ostream& operator<<(std::ostream& o, TString& p)
{
  for (int i = 0; i < p.size; ++i)
  {
    o << p.data[i];
  }
  return o;
}

std::istream& operator>>(std::istream& i, TString& p)
{
  char buffer[256];
  i >> buffer;
  p.SetData(buffer);
  return i;
}

int TString::FindChar(char c)
{
  for (int i = 0; i < size; ++i)
  {
    if (data[i] == c)
      return i;
  }
  return -1;
}

int TString::FindSubstring(const TString& sub)
{
  int subLen = sub.GetSize();
  if (subLen == 0)
    return 0;
  if (size < subLen)
    return -1;
  for (int i = 0; i + subLen - 1 < size; ++i)
  {
    bool match = true;
    for (int j = 0; j < subLen; ++j)
    {
      if (data[i + j] != sub.data[j])
      {
        match = false;
        break;
      }
    }
    if (match)
      return i;
  }
  return -1;
}

TString* TString::Split(char delimiter, int &resultCount)
{
  int delimiterCount = 0;
  for (int i = 0; i < size; ++i)
  {
    if (data[i] == delimiter)
      delimiterCount++;
  }
  resultCount = delimiterCount + 1;
  TString* result = new TString[resultCount];

  int start = 0, current = 0;
  for (int i = 0; i < size; ++i)
  {
    if (data[i] == delimiter)
    {
      int len = i - start;
      char* part = new char[len + 1];
      strncpy(part, data + start, len);
      part[len] = '\0';
      result[current++] = TString(part);
      delete[] part;
      start = i + 1;
    }
  }

  int len = size - start;
  char* part = new char[len + 1];
  strncpy(part, data + start, len);
  part[len] = '\0';
  result[current] = TString(part);
  delete[] part;

  return result;
}

int* TString::FindAllSubstrings(const TString &sub, int &resultCount)
{
  int subLen = sub.GetSize();
  resultCount = 0;
  if (subLen == 0 || subLen > size)
    return nullptr;

  int* indices = new int[size];
  int count = 0;

  for (int i = 0; i + subLen - 1 < size;)
  {
    bool match = true;
    for (int j = 0; j < subLen; ++j)
    {
      if (data[i + j] != sub[j])
      {
        match = false;
        break;
      }
    }
    if (match)
    {
      indices[count++] = i;
      i += subLen;
    } else {
      i++;
    }
  }

  if (count == 0)
  {
    delete[] indices;
    return nullptr;
  }

  int* result = new int[count];
  for (int i = 0; i < count; ++i)
  {
    result[i] = indices[i];
  }
  delete[] indices;
  resultCount = count;
  return result;
}

char TString::MostFrequentChar()
{
  if (size == 0)
    return '\0';
  const int ASCII_SIZE = 128;
  int counts[ASCII_SIZE] = {0};

  for (int i = 0; i < size; ++i)
  {
    counts[data[i]]++;
  }

  int maxCount = 0;
  char maxChar = '\0';
  for (int i = 0; i < ASCII_SIZE; ++i)
  {
    if (counts[i] > maxCount)
    {
      maxCount = counts[i];
      maxChar = static_cast<char>(i);
    }
  }
  return maxChar;
}

char* TString::GetUniqueChars(int &uniqueCount)
{
  const int ASCII_SIZE = 128;
  int was[ASCII_SIZE] = {0};
  uniqueCount = 0;

  for (int i = 0; i < size; ++i)
  {
    char c = data[i];
    if (!was[c])
    {
      was[c] = 1;
      uniqueCount++;
    }
  }

  for (int i = 0; i < ASCII_SIZE; ++i)
    was[i] = 0;

  char* result = new char[uniqueCount];
  int index = 0;
  for (int i = 0; i < size; ++i)
  {
    char c = data[i];
    if (!was[c])
    {
      result[index++] = c;
      was[c] = 1;
    }
  }
  return result;
}

void TString::GetCharCounts(char* &chars, int* &counts, int &uniqueCount)
{
  const int ASCII_SIZE = 128;
  int tempCounts[ASCII_SIZE] = {0};
  uniqueCount = 0;

  for (int i = 0; i < size; ++i)
    ++tempCounts[data[i]];

  for (int i = 0; i < ASCII_SIZE; ++i)
    if (tempCounts[i] > 0)
      uniqueCount++;

  chars = new char[uniqueCount];
  counts = new int[uniqueCount];
  int index = 0;
  for (int i = 0; i < ASCII_SIZE; ++i)
  {
    if (tempCounts[i] > 0)
    {
      chars[index] = static_cast<char>(i);
      counts[index] = tempCounts[i];
      ++index;
    }
  }
}

TString TString::Substr(int pos, int len)
{
  if (len < 0)
    throw "Negative length";
  if (pos < 0 || pos + len - 1 >= size)
    throw "Out of bounds";

  char* subData = new char[len + 1];
  for (int i = 0; i < len; ++i)
  {
    subData[i] = data[pos + i];
  }
  subData[len] = '\0';

  TString result(subData);
  delete[] subData;
  return result;
}

TString& TString::operator+=(char c)
{
  char* newData = new char[size + 2];
  if (data != nullptr)
    strncpy(newData, data, size);

  newData[size] = c;
  newData[size + 1] = '\0';

  if (data != nullptr)
    delete[] data;

  data = newData;
  ++size;
  return *this;
}