/*
 * 外观模式：
 * 为子系统中的一组接口提供一个一致的界面，此模式定义了一个高层接口，
 * 这个接口使得这一子系统更加容易使用。
 */
#include <iostream>

using namespace std;

class SubSystem1
{
public:
    void Operation()
    {
        cout << "SubSystem1 Operation" << endl;
    }
};

class SubSystem2
{
public:
    void Operation()
    {
        cout << "SubSystem2 Operation" << endl;
    }
};

class Facade
{
    SubSystem1 sy1;
    SubSystem2 sy2;
public:
    void WrapperOperation()
    {
        sy1.Operation();
        sy2.Operation();
    }
};

int main()
{
    Facade f;
    f.WrapperOperation();

    return 0;
}