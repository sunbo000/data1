#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <vector>
#include <string>
#include <sstream>
#include <gtest/gtest.h>
using namespace std;

// 函数声明
void generateExercise(int grade, int numExercises);
string generateSimpleExercise(int maxNumber, bool allowSubtraction);
string generateComplexExercise(int maxNumber, int minOperators, int maxOperators);
int getRandomNumber(int min, int max);
char getRandomOperator();
int calculate(string expression);
TEST(GenerateExerciseTest, Grade1) {
    int grade = 1;
    int number = 1;
    generateExercise(grade, number);
}
TEST(GenerateExerciseTest, Grade2) {
    int grade = 2;
    int number = 1;
    generateExercise(grade, number);
}
TEST(GenerateExerciseTest, Grade3) {
    int grade = 3;
    int number = 1;
    generateExercise(grade, number);
}
TEST(GenerateExerciseTest, Grade6) {
    int grade = 6;
    int number = 1;
    generateExercise(grade, number);
}
TEST(GenerateExerciseTest, Grade7) {
    int grade = 7;
    int number = 1;
    generateExercise(grade, number);
}
TEST(GenerateExerciseTest, Grade0) {
    int grade = 2;
    int number = 0;
    generateExercise(grade, number);
}
TEST(GenerateExerciseTest, Grade) {
    int grade = 2;
    int number = -1;
    generateExercise(grade, number);
}

int main(int argc,char**argv) {
    //int grade, numExercises;

    //// 输入年级和题目数量
    //cout << "请输入年级（1-6）：";
    //cin >> grade;
    //cout << "请输入题目数量：";
    //cin >> numExercises;

    //// 设置随机种子
    //srand(static_cast<unsigned int>(time(0)));

    //// 生成题目
    //generateExercise(grade, numExercises);

    //return 0;
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

void generateExercise(int grade, int numExercises) {
    if (numExercises<0) {
        cout << "题目数量不能为负数。" << endl;
        return;
    }
    for (int i = 0; i < numExercises; ++i) {
        string anser;
        switch (grade) {
        case 1:
            anser = generateSimpleExercise(20, false);
            cout << anser << endl;
            cout << calculate(anser) << endl;
            break;
        case 2:
            anser = generateSimpleExercise(50, true);
            cout << anser << endl;
            cout << calculate(anser) << endl;
            break;
        case 3:
            anser=generateComplexExercise(1000, 2, 3);
            cout << anser << endl;
            cout << calculate(anser) << endl;
            break;
        case 4:
        case 5:
        case 6:
            anser = generateComplexExercise(10000, 3, 4);
            cout << anser << endl;
            cout << calculate(anser) << endl;
            break;
        default:
            cout << "无效的年级输入" << endl;
            return;
        }
    }
}

string generateSimpleExercise(int maxNumber, bool allowSubtraction) {
    int number1 = getRandomNumber(1, maxNumber);
    int number2 = getRandomNumber(1, maxNumber);
    char operator_ = getRandomOperator();
    switch (operator_) {
    case '+':
        if (number1 + number2 >= maxNumber) {
            swap(number1, number2);
        }
        break;
    case '-':
        if (number1 - number2 < 0) {
            swap(number1, number2);
        }
        break;
    }
    return to_string(number1) + " " + operator_ + " " + to_string(number2) + " = ?";
}

string generateComplexExercise(int maxNumber, int minOperators, int maxOperators) {
    vector<char> operators;
    for (int i = 0; i < getRandomNumber(minOperators, maxOperators); ++i) {
        operators.push_back(getRandomOperator());
    }

    string exercise = to_string(getRandomNumber(1, maxNumber));

    for (char op : operators) {
        int number = getRandomNumber(1, maxNumber);
        exercise += " " + string(1, op) + " " + to_string(number);
    }

    exercise += " = ?";

    return exercise;
}
   
int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

char getRandomOperator(bool allowSubtraction) {
    const char operators[] = { '+', '-', '*', '/' };
    int index = rand() % (allowSubtraction ? 4 : 2);
    return operators[index];
}

char getRandomOperator() {
    const char operators[] = { '+', '-', '*', '/' };
    return operators[rand() % 4];
}

int calculate(string expression) {
    stringstream ss(expression);
    int result = 0;
    char op;
    int num;

    ss >> result;
    while (ss >> op >> num) {
        switch (op) {
        case '+':
            result += num;
            break;
        case '-':
            result -= num;
            break;
        case '*':
            result *= num;
            break;
        case '/':
            if (num != 0) {
                result /= num;
            }
            else {
                std::cerr << "Error: Division by zero." << std::endl;
                return 0;
            }
            break;
        default:
            std::cerr << "Error: Unknown operator." << std::endl;
            return 0;
        }
    }

    return result;
}
