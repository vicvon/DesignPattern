/*
 * 模版方法模式：
 * 定义一个操作中的算法骨架，而将一些步骤延迟到子类中。模版方法使得子类可以不改变一个算法
 * 的结构即可重定义该算法的某些特定步骤
 */
#include <iostream>
#include <memory>

using namespace std;

class AbstractClass
{
public:
    virtual void TemplateMethod()
    {
        PrimitiveOperation1();
        PrimitiveOperation2();
    }
    virtual void PrimitiveOperation1() = 0;
    virtual void PrimitiveOperation2() = 0;
};

class ConcreteClassA : public AbstractClass
{
public:
    virtual void PrimitiveOperation1() override
    {
        cout << "ConcreteClassA PrimitiveOperation1" << endl;
    }
    virtual void PrimitiveOperation2() override
    {
        cout << "ConcreteClassA PrimitiveOperation2" << endl;
    }
};

class ConcreteClassB : public AbstractClass
{
public:
    virtual void PrimitiveOperation1() override
    {
        cout << "ConcreteClassB PrimitiveOperation1" << endl;
    }
    virtual void PrimitiveOperation2() override
    {
        cout << "ConcreteClassB PrimitiveOperation2" << endl;
    }
};

int main()
{
    unique_ptr<AbstractClass> p1 = make_unique<ConcreteClassA>();
    unique_ptr<AbstractClass> p2 = make_unique<ConcreteClassB>();

    p1->TemplateMethod();
    p2->TemplateMethod();
    return 0;
}