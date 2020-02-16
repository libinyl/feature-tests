#include <iostream>
#include <vector>

// https://zhuanlan.zhihu.com/p/45430715
// https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=vs-2019

// g++ testLambda.cc

int main() {
    // auto a_alias = [capture](parameters)->return_type{ ... };
    auto add =
        [](int _1, int _2) -> int
        { return _1 + _2; };

    std::cout << "add:" << add(1, 2) << std::endl;

    /**********/

    int j = 1;
    auto by_val_lambda =
        [=]()->int // 可以省略 ()->int
        { return j + 1; };  // 值捕获

    auto by_ref_lambda1 =
        [&]
        { return j + 1; };  // 引用捕获

    auto by_ref_lambda2 =
        [&j]
        { return j + 1; };  // 引用捕获

    auto print =
        [=]
        {
            std::cout << "print by val lambda: " << by_val_lambda() << ", ";
            std::cout << "by ref lambda1: " << by_ref_lambda1() << ",";
            std::cout << "by ref lambda2: " << by_ref_lambda2() << std::endl;
        };

    print();
    j += 10;
    print();



    /*********/




    return 0;
}