/*
 * װ��ģʽ:
 * ��̬�ĸ�һ���������һЩ�����ְ�𣬾����ӹ�����˵��װ��ģʽ��������������
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