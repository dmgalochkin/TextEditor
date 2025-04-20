#include <gtest.h>
#include "TString.h"

TEST(TStringTest, DefaultConstructor)
{
  TString s;
  EXPECT_EQ(s.GetSize(), 0);
  EXPECT_EQ(s.GetData(), nullptr);
}

TEST(TStringTest, ConstructorFromCharPtr)
{
  TString s("test");
  EXPECT_EQ(s.GetSize(), 4);
  ASSERT_NE(s.GetData(), nullptr);
  EXPECT_STREQ(s.GetData(), "test");
}

TEST(TStringTest, ConstructorFromNullPtr)
{
  TString s(nullptr);
  EXPECT_EQ(s.GetSize(), 0);
  EXPECT_EQ(s.GetData(), nullptr);
}

TEST(TStringTest, CopyConstructor)
{
  TString original("hello");
  TString copy(original);
  EXPECT_EQ(copy.GetSize(), 5);
  EXPECT_STREQ(copy.GetData(), "hello");
  EXPECT_NE(copy.GetData(), original.GetData());
}

TEST(TStringTest, MoveConstructor)
{
  TString original("hello");
  TString moved(std::move(original));
  EXPECT_EQ(moved.GetSize(), 5);
  EXPECT_STREQ(moved.GetData(), "hello");
  EXPECT_EQ(original.GetSize(), 0);
  EXPECT_EQ(original.GetData(), nullptr);
}

TEST(TStringTest, GetSize)
{
  TString s("12345");
  EXPECT_EQ(s.GetSize(), 5);
}

TEST(TStringTest, GetData)
{
  TString s("hello");
  EXPECT_STREQ(s.GetData(), "hello");
}

TEST(TStringTest, SetData)
{
  TString s;
  s.SetData("new data");
  EXPECT_EQ(s.GetSize(), 8);
  EXPECT_STREQ(s.GetData(), "new data");
}

TEST(TStringTest, AdditionOperator)
{
  TString s1("hello");
  TString s2(" world");
  TString result = s1 + s2;
  EXPECT_EQ(result.GetSize(), 11);
  EXPECT_STREQ(result.GetData(), "hello world");
}

TEST(TStringTest, MultiplyOperator)
{
  TString s("ab");
  TString result = s * 3;
  EXPECT_EQ(result.GetSize(), 6);
  EXPECT_STREQ(result.GetData(), "ababab");
}

TEST(TStringTest, MultiplyByZero)
{
  TString s("test");
  TString result = s * 0;
  EXPECT_EQ(result.GetSize(), 0);
  EXPECT_STREQ(result.GetData(), "");
}

TEST(TStringTest, AssignmentOperator)
{
  TString s1("original");
  TString s2;
  s2 = s1;
  EXPECT_EQ(s2.GetSize(), 8);
  EXPECT_STREQ(s2.GetData(), "original");

  s1.SetData("modified");
  EXPECT_STREQ(s2.GetData(), "original");
}

TEST(TStringTest, SelfAssignment)
{
  TString s("original");
  s = s;
  EXPECT_EQ(s.GetSize(), 8);
  EXPECT_STREQ(s.GetData(), "original");
}

TEST(TStringTest, EqualityOperator)
{
  TString s1("abc");
  TString s2("abc");
  TString s3("abd");
  EXPECT_TRUE(s1 == s2);
  EXPECT_FALSE(s1 == s3);
}

TEST(TStringTest, InequalityOperator)
{
  TString s1("abc");
  TString s2("abc");
  TString s3("abd");
  EXPECT_FALSE(s1 != s2);
  EXPECT_TRUE(s1 != s3);
}

TEST(TStringTest, LessThanOperator)
{
  TString s1("abc");
  TString s2("abd");
  TString s3("ab");
  TString s4("abc");
  EXPECT_TRUE(s1 < s2);
  EXPECT_TRUE(s3 < s1);
  EXPECT_FALSE(s2 < s1);
  EXPECT_FALSE(s1 < s4);
}

TEST(TStringTest, GreaterThanOperator)
{
  TString s1("abc");
  TString s2("abd");
  TString s3("ab");
  TString s4("abc");
  EXPECT_FALSE(s2 < s1);
  EXPECT_TRUE(s1 > s3);
  EXPECT_FALSE(s1 > s2);
  EXPECT_FALSE(s1 > s4);
}

TEST(TStringTest, FindCharExists)
{
  TString s("hello");
  EXPECT_EQ(s.FindChar('e'), 1);
}

TEST(TStringTest, FindCharNotExists)
{
  TString s("hello");
  EXPECT_EQ(s.FindChar('z'), -1);
}

TEST(TStringTest, FindSubstringPresent)
{
  TString s("hello world");
  TString sub("world");
  EXPECT_EQ(s.FindSubstring(sub), 6);
}

TEST(TStringTest, FindSubstringAbsent)
{
  TString s("hello");
  TString sub("abc");
  EXPECT_EQ(s.FindSubstring(sub), -1);
}

TEST(TStringTest, FindEmptySubstring)
{
  TString s("test");
  TString sub("");
  EXPECT_EQ(s.FindSubstring(sub), 0);
}

TEST(TStringTest, SplitByDelimiter)
{
  TString s("a,b,c");
  int count;
  TString* parts = s.Split(',', count);
  ASSERT_EQ(count, 3);
  EXPECT_STREQ(parts[0].GetData(), "a");
  EXPECT_STREQ(parts[1].GetData(), "b");
  EXPECT_STREQ(parts[2].GetData(), "c");
  delete[] parts;
}

TEST(TStringTest, SplitWithEmptyParts)
{
  TString s(",,a,,b,");
  int count;
  TString* parts = s.Split(',', count);
  ASSERT_EQ(count, 6);
  EXPECT_STREQ(parts[0].GetData(), "");
  EXPECT_STREQ(parts[1].GetData(), "");
  EXPECT_STREQ(parts[2].GetData(), "a");
  EXPECT_STREQ(parts[3].GetData(), "");
  EXPECT_STREQ(parts[4].GetData(), "b");
  EXPECT_STREQ(parts[5].GetData(), "");
  delete[] parts;
}

TEST(TStringTest, FindAllSubstrings)
{
  TString s("ababab");
  TString sub("ab");
  int count;
  int* indices = s.FindAllSubstrings(sub, count);
  ASSERT_EQ(count, 3);
  EXPECT_EQ(indices[0], 0);
  EXPECT_EQ(indices[1], 2);
  EXPECT_EQ(indices[2], 4);
  delete[] indices;
}

TEST(TStringTest, MostFrequentChar)
{
  TString s("abracadabra");
  EXPECT_EQ(s.MostFrequentChar(), 'a');
}

TEST(TStringTest, GetUniqueChars)
{
  TString s("acacab");
  int count;
  char* unique = s.GetUniqueChars(count);
  ASSERT_EQ(count, 3);
  EXPECT_EQ(unique[0], 'a');
  EXPECT_EQ(unique[1], 'c');
  EXPECT_EQ(unique[2], 'b');
  delete[] unique;
}

TEST(TStringTest, GetCharCounts)
{
  TString s("aabbbc");
  char* chars;
  int* counts;
  int count;
  s.GetCharCounts(chars, counts, count);
  ASSERT_EQ(count, 3);
  EXPECT_EQ(chars[0], 'a');
  EXPECT_EQ(counts[0], 2);
  EXPECT_EQ(chars[1], 'b');
  EXPECT_EQ(counts[1], 3);
  EXPECT_EQ(chars[2], 'c');
  EXPECT_EQ(counts[2], 1);
  delete[] chars;
  delete[] counts;
}

TEST(TStringTest, EmptyStringOperations)
{
  TString s1;
  TString s2;
  TString result = s1 + s2;
  EXPECT_EQ(result.GetSize(), 0);
  EXPECT_STREQ(result.GetData(), "");
}

TEST(TStringTest, SubstrNormalCase)
{
  TString s("abcdefgh");
  TString sub = s.Substr(2, 3);
  EXPECT_EQ(sub.GetSize(), 3);
  EXPECT_STREQ(sub.GetData(), "cde");
}

TEST(TStringTest, SubstrOutOfBounds)
{
  TString s("abcdef");
  ASSERT_ANY_THROW(s.Substr(3, 5));
  ASSERT_ANY_THROW(s.Substr(-1, 5));
  ASSERT_ANY_THROW(s.Substr(2, -1));
}

TEST(TStringTest, SubstrZeroLength)
{
  TString s("abcdef");
  TString sub = s.Substr(2, 0);
  EXPECT_EQ(sub.GetSize(), 0);
  EXPECT_STREQ(sub.GetData(), "");
}

TEST(TStringTest, SubstrFullString)
{
  TString s("hello");
  TString sub = s.Substr(0, 5);
  EXPECT_EQ(sub.GetSize(), 5);
  EXPECT_STREQ(sub.GetData(), "hello");
}

TEST(TStringTest, PlusEqualsCharOperator) {
  TString s;
  s += 'H';
  EXPECT_STREQ(s.GetData(), "H");
  EXPECT_EQ(s.GetSize(), 1);

  s += 'i';
  EXPECT_STREQ(s.GetData(), "Hi");
  EXPECT_EQ(s.GetSize(), 2);
}

TEST(TStringTest, PlusEqualsCharToEmptyString) {
  TString s(nullptr);
  s += 'X';
  EXPECT_STREQ(s.GetData(), "X");
  EXPECT_EQ(s.GetSize(), 1);
}