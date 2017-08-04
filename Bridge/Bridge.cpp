/*
 * 桥接模式：
 * 将抽象部分与它的实现部分分离，使它们都可以独立的变化。
 */
#include <iostream>
#include <memory>

using namespace std;

class Implementor
{
public:
    virtual void Operation() = 0;
};

class ConcreteImplementorA : public Implementor
{
public:
    virtual void Operation() override
    {
        cout << "ConcreteImplementorA Operation" << endl;
    }
};

class ConcreteImplementorB : public Implementor
{
public:
    virtual void Operation() override
    {
        cout << "ConcreteImplementorB Operation" << endl;
    }
};

class Abstraction
{
public:
    void setImplementor(unique_ptr<Implementor>&& implementor)
    {
        implementor_ = move(implementor);
    }

    virtual void Operation() = 0;
protected:
    unique_ptr<Implementor> implementor_;
};

class RefinedAbstraction : public Abstraction
{
public:
    virtual void Operation() override
    {
        cout << "RefinedAbstraction Operation" << endl;
        implementor_->Operation();
    }
};

int main()
{
    unique_ptr<Abstraction> refined = make_unique<RefinedAbstraction>();

    refined->setImplementor(make_unique<ConcreteImplementorA>());
    refined->Operation();

    refined->setImplementor(make_unique<ConcreteImplementorB>());
    refined->Operation();

    return 0;
}