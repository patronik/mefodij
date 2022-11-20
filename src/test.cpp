#include "../include/test.h"

using namespace std;

void init() {
    setlocale(LC_ALL, "en_US.utf8");
}

TEST(MathTest, SimpleMath)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"5 + 7 - 2 / 2 + 3 * 3");
    ASSERT_EQ(L"20", result->toString());
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

TEST(BooleanTest, LogicalWithMathOperators)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"1 < 1.15 && 2 >= 0.5 && 0.4 > 0.1 && 1.7 < 2.0");
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

TEST(MemberAccess, LengthMember)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"'привіт'.довжина;");
    ASSERT_EQ(L"6", result->toString());
}

TEST(MemberAccess, SizeMember)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"[1,2,3].розмір;");
    ASSERT_EQ(L"3", result->toString());
}

TEST(MemberAccess, TypeMemberWithString)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"'привіт'.тип;");
    ASSERT_EQ(Mefodij::Keyword::typeString, result->toString());
}

TEST(MemberAccess, TypeMemberWithNumber)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"123.тип;");
    ASSERT_EQ(Mefodij::Keyword::typeInt, result->toString());
}

TEST(MemberAccess, AssignToTmpMember)
{
    Mefodij::Engine mefodij{};
    EXPECT_THROW(
      mefodij.evaluateCode(L"123.тип = '123';"), 
      runtime_error
    );
}

TEST(TypeCasting, DoubleToString)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"мем тест = (строка) 1.5;");
    ASSERT_EQ(Mefodij::Keyword::typeString, result->getType());
    ASSERT_EQ(L"1.5", result->toString());
}

TEST(TypeCasting, IntToString)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"мем тест = (строка) 33;");
    ASSERT_EQ(Mefodij::Keyword::typeString, result->getType());
    ASSERT_EQ(L"33", result->toString());
}

TEST(TypeCasting, ArrayToNull)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(L"мем тест = (нал) [1,2,3];");
    ASSERT_EQ(Mefodij::Keyword::typeNull, result->getType());
    ASSERT_EQ(L"", result->toString());
}


TEST(VariableTest, SimpleAssignment)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем змінна = 2; 
        )"
      );
    ASSERT_EQ(L"2", result->toString());
}

TEST(VariableTest, AssignmentToNonVar)
{
    Mefodij::Engine mefodij{};
    EXPECT_THROW(
      mefodij.evaluateCode(
        LR"(
            5 = 2; 
        )"
      ), 
      runtime_error
    );
}

TEST(VariableTest, AliasingInTheSameScope)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем змінна = 2; 
            мем тест = 4;

            змінна = &тест;

            змінна == тест 
            && змінна == 4;
        )"
      );
    ASSERT_TRUE(result->toBool());
}

TEST(VariableTest, ReferenceToArrayElem)
{
    Mefodij::Engine mefodij{};
    EXPECT_THROW(
      mefodij.evaluateCode(
        LR"(
            мем змінна = [1,2,3]; 
            мем тест = [5,6,7]; 

            змінна[0] = &тест[0];

            змінна[0] == тест[0] 
            && змінна[0] == 5;
        )"
      ), 
      runtime_error
    );
}

TEST(VariableTest, AliasingFromOuterScope)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем змінна = 2; 
            функція тест() {
                мем тест = 4;
                тест = &змінна;
                вихід тест;
            }
            тест();
        )"
      );
    ASSERT_EQ(L"2", result->toString());
}

TEST(VariableTest, ReferencingOfNonVar)
{
    Mefodij::Engine mefodij{};
    EXPECT_THROW(
      mefodij.evaluateCode(
        LR"(
            мем змінна = &2; 
        )"
      ), 
      runtime_error
    );
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

TEST(ArrayTest, InArrayCoreFuncSuccess)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем мас = ['a' => 2, 7, 'b' => 3];
            вМасиві(7, мас);
        )"
    );
    ASSERT_TRUE(result->toBool());
}


TEST(ArrayTest, InArrayCoreFuncFail)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем мас = ['a' => 2, 7, 'b' => 3];
            вМасиві(72, мас);
        )"
    );
    ASSERT_FALSE(result->toBool());
}

TEST(ArrayTest, SortNumArrayAsc)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем мас = [3,2,1];
            сортувати(мас, 1);
            вихід мас[0];
        )"
    );
    ASSERT_EQ(L"1", result->toString());
}

TEST(ArrayTest, SortNumArrayDesc)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем мас = [1,2,3];
            сортувати(мас, -1);
            вихід мас[0];
        )"
    );
    ASSERT_EQ(L"3", result->toString());
}

TEST(ArrayTest, SortStringArrayAsc)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем мас = ["ав", "аб", "аа"];
            сортувати(мас, 1);
            вихід мас[0];
        )"
    );
    ASSERT_EQ(L"аа", result->toString());
}

TEST(ArrayTest, SortStringArrayDesc)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем мас = ["привіт", "світ"];
            сортувати(мас, -1);
            вихід мас[0];
        )"
    );
    ASSERT_EQ(L"світ", result->toString());
}

TEST(ArrayTest, SortMixedArrayAsc)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем мас = ["ав", "аб", 5, "аа"];
            сортувати(мас, 1);
            вихід мас[0];
        )"
    );
    ASSERT_EQ(L"5", result->toString());
}

TEST(ArrayTest, SortMixedArrayDesc)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
            мем мас = ["ав", "аб", 5, "аа", "ю"];
            сортувати(мас, -1);
            вихід мас[0];
        )"
    );
    ASSERT_EQ(L"ю", result->toString());
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

TEST(FunctionTest, ReferenceVarInUpperScope)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
          мем пі = 3.14;
          функція радіус(довжина) {
            вихід довжина / (2 * пі);
          }  
          радіус(6);
        )"
    );
    ASSERT_NEAR(0.95, result->getDouble(), 0.01);
}


TEST(FunctionTest, TwoParams)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
          функція додати(а, б) {
            вихід а + б;
          }  
          додати(2, 2);
        )"
    );
    ASSERT_EQ(L"4", result->toString());
}

TEST(FunctionTest, OneDefaultParam)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
          функція додати(а, б = 1) {
            вихід а + б;
          }  
          додати(2);
        )"
    );
    ASSERT_EQ(L"3", result->toString());
}

TEST(FunctionTest, TwoDefaultParams)
{
    Mefodij::Engine mefodij{};
    auto result = mefodij.evaluateCode(
        LR"(
          функція додати(а = 1, б = 1) {
            вихід а + б;
          }  
          додати();
        )"
    );
    ASSERT_EQ(L"2", result->toString());
}

int main(int argc, char **argv) {
  init();
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
