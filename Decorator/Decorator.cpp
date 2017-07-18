/*
 * 装饰模式:
 * 动态的给一个对象添加一些额外的职责，就增加功能来说，装饰模式比生成子类更灵活
 */
#include <iostream>
#include <memory>

using namespace std;

class Component
{
public:
    virtual void Operation() = 0;
    virtual ~Component()
    {
    }
};

class ConcreteComponent:public Component
{
public:
    virtual void Operation() override
    {
        cout << "ConcreteComponent" << endl;
    }
};

class Decorator :public Component
{
public:
    void SetComponent(unique_ptr<Component> &st)
    {
        sc_ = move(st);
    }

    virtual void Operation() override
    {
        if (sc_)
        {
            sc_->Operation();
        }
    }
protected:
    unique_ptr<Component> sc_;
};

class ConcreteDecoratorA :public Decorator
{
public:
    virtual void Operation() override
    {
        sc_->Operation();
        cout << "ConcreteDecoratorA" << endl;
    }
};

class ConcreteDecoratorB :public Decorator
{
public:
    virtual void Operation() override
    {
        sc_->Operation();
        cout << "ConcreteDecoratorB" << endl;
    }
};

int main()
{
    {
        unique_ptr<Component> cp = make_unique<ConcreteComponent>();
        unique_ptr<Decorator> cp1 = make_unique<ConcreteDecoratorA>();
        unique_ptr<Decorator> cp2 = make_unique<ConcreteDecoratorB>();

        cp1->SetComponent(cp);
        unique_ptr<Component> cpp = move(cp1);
        cp2->SetComponent(cpp);

        cp2->Operation();
    }
    cout << "----------------------------------" << endl;
    {
        unique_ptr<Component> cp = make_unique<ConcreteComponent>();
        unique_ptr<Decorator> cp1 = make_unique<ConcreteDecoratorA>();
        unique_ptr<Decorator> cp2 = make_unique<ConcreteDecoratorB>();

        cp2->SetComponent(cp);
        unique_ptr<Component> cpp = move(cp2);
        cp1->SetComponent(cpp);

        cp1->Operation();
    }
}