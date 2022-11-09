#include "../include/test.h"

using namespace std;

void init() {
    setlocale(LC_ALL, "en_US.utf8");
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

TEST(BooleanTest, LogicalOperators)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"(ні && 1) || (0 || так);");
    ASSERT_EQ(true, result->toBool());
}

TEST(BooleanTest, OperandComparison)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем заглушка = нал;
            мем тест = [
                нал, 1, 0.5, "привіт", заглушка, 1, 0.5
            ];
            вихід (
                тест[0] == заглушка
                && тест[1] != тест[0]
                && тест[1] != заглушка
                && тест[2] != заглушка
                && тест[2] != тест[1]
                && тест[3] != тест[0]
                && тест[3] != тест[2]
                && тест[3] != заглушка
                && тест[4] == заглушка
                && тест[4] == тест[0]
                && тест[5] != тест[0]
                && тест[5] == тест[1]
                && тест[6] != тест[0]
                && тест[6] == тест[2]
            );
        )"
    );
    ASSERT_TRUE(result->toBool());
}

TEST(BooleanTest, TestRegex)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"'привіт світ' ~ '.*сві.*';");
    ASSERT_TRUE(result->toBool());
}

TEST(VariableTest, MathWithVar)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
    LR"(
      мем тест = 2;
      тест + тест * 3 - 50 / 10;
    )");
    ASSERT_EQ(L"3", result->toString());
}

TEST(VariableTest, MathWithConstVar)
{
    Mefodij::Engine mefodij{};
    EXPECT_THROW(
      mefodij.evaluateCode(
        LR"(
            конст змінна = 2; 
            змінна = 3;
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
            мем мас = ['a' => 2, 'b' => 3, 7];
            вихід мас['a'] + мас['b'] + мас[0];
        )"
    );
    ASSERT_EQ(L"12", result->toString());
}


TEST(ArrayTest, ArrayMembers)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем мас = ['a' => 2, 7, 'b' => 3];
            вихід мас.перший + мас.другий;
        )"
    );
    ASSERT_EQ(L"9", result->toString());
}

TEST(IfConditionTest, BasicIf)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            умова (1 == 1) {
                вихід 2;
            } 
        )"
    );
    ASSERT_EQ(L"2", result->toString());
}

TEST(IfConditionTest, IfElse)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            умова (1 == 2) {
                вихід 1;
            } або {
                вихід 3;
            }
        )"
    );
    ASSERT_EQ(L"3", result->toString());
}

TEST(IfConditionTest, IfElseIf)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            умова (1 == 2) {
                вихід 1;
            } або умова (1 == 1) {
                вихід 2;
            } або {
                вихід 3;
            }
        )"
    );
    ASSERT_EQ(L"2", result->toString());
}

TEST(LoopTest, ForLoop)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем результат;
            цикл (мем і = 0; і < 10; і++) {
                результат = і;
            }
            вихід результат;
        )"
    );
    ASSERT_EQ(L"9", result->toString());
}

TEST(LoopTest, WhileLoop)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем критерій = так;
            цикл (критерій) {
                умова (критерій) {
                    критерій = ні;
                }
            }
            вихід критерій;
        )"
    );
    ASSERT_FALSE(result->toBool());
}

TEST(LoopTest, RangeLoop)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем результат;
            цикл (мем елемент: [1,2,3,4,5]) {
                результат = елемент.другий;
            }
            вихід результат;
        )"
    );
    ASSERT_EQ(L"5", result->toString());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
