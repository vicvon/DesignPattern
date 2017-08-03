/*
 * 适配器模式：
 * 将一个类的接口转换成客户希望的另外一个接口。Adapter模式使得原本由于
 * 接口不兼容而不能一起工作的那些类可以一起工作。
 */
#include <iostream>
#include <memory>
#include <type_traits>

using namespace std;

class Target
{
public:
    virtual void Request() = 0;
};

class Adaptee
{
public:
    void specificRequest()
    {
        cout << "Adaptee specificRequest" << endl;
    }
};

class Adapter : public Target
{
public:
    Adapter(unique_ptr<Adaptee>& adaptee):adaptee_(move(adaptee))
    {
    }

    virtual void Request() override
    {
        adaptee_->specificRequest();
    }
private:
    unique_ptr<Adaptee> adaptee_;
};

int main()
{
    unique_ptr<Adaptee> ad = make_unique<Adaptee>();
    unique_ptr<Target> target = make_unique<Adapter>(ad);

    target->Request();

    return 0;
}