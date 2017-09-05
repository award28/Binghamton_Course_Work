#include "lexer.h"

#include <string>

#include <gtest/gtest.h>

TEST(LexerTest, Eof) {
  Token eof(TokenKind::eof, "");
  EXPECT_EQ(eof, Lexer("").NextToken());
  EXPECT_EQ(eof, Lexer(" \t ").NextToken());
}

TEST(LexerTest, Newline) {
  Token nl(TokenKind::nl, "\n");
  EXPECT_EQ(nl, Lexer("\n").NextToken());
  EXPECT_EQ(nl, Lexer(" \t \n").NextToken());
}
  
TEST(LexerTest, Parenthesis) {
  Token lperen(TokenKind::lperen, "(");
  EXPECT_EQ(lperen, Lexer("(").NextToken());
  EXPECT_EQ(lperen, Lexer(" \t (").NextToken());
  Token rperen(TokenKind::rperen, ")");
  EXPECT_EQ(rperen, Lexer(")").NextToken());
  EXPECT_EQ(rperen, Lexer(" \t )").NextToken());
}

TEST(LexerTest, Operators) {
  Token add(TokenKind::add, "+");
  EXPECT_EQ(add, Lexer("+").NextToken());
  EXPECT_EQ(add, Lexer(" \t +").NextToken());
  Token sub(TokenKind::sub, "-");
  EXPECT_EQ(sub, Lexer("-").NextToken());
  EXPECT_EQ(sub, Lexer(" \t -").NextToken());
}

TEST(LexerTest, Integers) {
  for (auto i : {0, 1, 12, 1<<16,}) {
    std::string s = std::to_string(i);
    Token expected(TokenKind::integer, s, i);
    EXPECT_EQ(expected, Lexer(s).NextToken());
    EXPECT_EQ(expected,
	      Lexer(" \t " + s).NextToken());
  }
}

TEST(LexerTest, Sequence1) {
  int i1 = 63;
  int i2 = 20;
  int i3 = 11;
  auto tokens = {
    Token(TokenKind::integer, std::to_string(i1), i1),
    Token(TokenKind::add, "+"),
    Token(TokenKind::integer, std::to_string(i2), i2),
    Token(TokenKind::sub, "-"),
    Token(TokenKind::integer, std::to_string(i3), i3),
    Token(TokenKind::nl, "\n"),
    Token(TokenKind::eof, ""),
  };
  std::string s;
  for (auto token : tokens) {
    s += " \t"; s += token.lexeme;
  }
  Lexer lexer = Lexer(s);
  int i = 0;
  for (auto token : tokens) {
    EXPECT_EQ(token, lexer.NextToken()) <<
      "for index " << i;
    ++i;
  }
}

