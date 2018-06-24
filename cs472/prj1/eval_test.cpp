#include "eval.h"
#include "lexer.h"

#include <string>

#include <gtest/gtest.h>

TEST(EvalTest, Eof) {
  Lexer lexer("   ");
  EvalResult result(Eval(lexer).NextEvalResult());
  EXPECT_EQ(result.status, EvalStatus::eof);
}

TEST(EvalTest, Empty) {
  Lexer lexer("   \n");
  EvalResult result(Eval(lexer).NextEvalResult());
  EXPECT_EQ(result.status, EvalStatus::empty);
}

TEST(EvalTest, Zero) {
  Lexer lexer("   0  \n");
  EvalResult result(Eval(lexer).NextEvalResult());
  ASSERT_EQ(result.status, EvalStatus::ok);
  EXPECT_EQ(result.result, 0);
}

TEST(EvalTest, Add) {
  Lexer lexer(" \t  63 \t +2  \n");
  EvalResult result(Eval(lexer).NextEvalResult());
  ASSERT_EQ(result.status, EvalStatus::ok);
  EXPECT_EQ(result.result, 65);
}

TEST(EvalTest, Sub) {
  Lexer lexer(" \t 63 \t -20 -1\n");
  EvalResult result(Eval(lexer).NextEvalResult());
  ASSERT_EQ(result.status, EvalStatus::ok);
  EXPECT_EQ(result.result, 42);
}

TEST(EvalTest, RightAssocTest) {
  Lexer lexer("16 - (4 + 8) - (12 + ((18 - 42) + 16))");
  EvalResult result(Eval(lexer).NextEvalResult());
  ASSERT_EQ(result.status, EvalStatus::ok);
  EXPECT_EQ(result.result, 0);
}

TEST(EvalTest, StartParen) {
  Lexer lexer("(4)");
  EvalResult result(Eval(lexer).NextEvalResult());
  ASSERT_EQ(result.status, EvalStatus::ok);
  EXPECT_EQ(result.result, 4);
}

TEST(EvalTest, MissMatchRparen) {
  Lexer lexer("(1))");
  EvalResult result(Eval(lexer).NextEvalResult());
  ASSERT_EQ(result.status, EvalStatus::error);
  EXPECT_EQ(result.result, 0);
}

TEST(EvalTest, MissMatchLparen) {
  Lexer lexer("(1");
  EvalResult result(Eval(lexer).NextEvalResult());
  ASSERT_EQ(result.status, EvalStatus::error);
  EXPECT_EQ(result.result, 0);
}
