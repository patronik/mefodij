#include "../include/test.h"

using namespace std;

void init() {
    setlocale(LC_ALL, "en_US.utf8");
}

TEST(MathTest, TwoPlushTwoShouldBeFour)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"2 + 2;");
    ASSERT_EQ(L"4", result->toString());
}

TEST(MathTest, FourMathOperators)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"2 + 2 * 3 - 50 / 10;");
    ASSERT_EQ(L"3", result->toString());
}

TEST(MathTest, ExpressionInParentheses)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"(2 + 2) * 3 - 50 / 10;");
    ASSERT_EQ(L"7", result->toString());
}

TEST(BooleanTest, LogicalOrOperator)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"0 || 1;");
    ASSERT_EQ(true, result->toBool());
}

TEST(BooleanTest, LogicalAndOperator)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"0 && 1;");
    ASSERT_EQ(false, result->toBool());
}

TEST(BooleanTest, TestRegex)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"'привіт світ' ~ '.*сві.*';");
    ASSERT_TRUE(result->toBool());
}

TEST(BooleanTest, LogicalOrAndAndOperator)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"(0 && 1) || так;");
    ASSERT_EQ(true, result->toBool());
}

TEST(VariableTest, MathWithVariable)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(LR"(
      мем змінна = 2;
      змінна + змінна * 3 - 50 / 10;
    )");
    ASSERT_EQ(L"3", result->toString());
}

TEST(VariableTest, MathWithConst)
{
    Mefodij::Engine mefodij{};
    EXPECT_THROW(
      mefodij.evaluateCode(
        LR"(
            конст змінна = 2; змінна = 3;
        )"
      ), 
      runtime_error
    );
}

TEST(ArrayTest, ArrayLiteral)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем контейнер = ['a' => 2, 'b' => 3, 7];
            вихід контейнер['a'] + контейнер['b'] + контейнер[0];
        )"
    );
    ASSERT_EQ(L"12", result->toString());
}


TEST(ArrayTest, ArrayMembers)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем контейнер = ['a' => 2, 7, 'b' => 3];
            вихід контейнер.перший + контейнер.другий;
        )"
    );
    ASSERT_EQ(L"9", result->toString());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
