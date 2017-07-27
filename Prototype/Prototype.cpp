/*
 * 原型模式：
 * 用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象
 */
#include <iostream>
#include <memory>

using namespace std;

class Prototype
{
public:
    virtual ~Prototype()
    {
    }
    virtual unique_ptr<Prototype> clone() = 0;
};

class ConcretePrototype : public Prototype
{
public:
    ConcretePrototype()
    {
    }

    ConcretePrototype(const ConcretePrototype &obj)
    {
        cout << "ConcretePrototype copy" << endl;
    }

    virtual unique_ptr<Prototype> clone() override
    {
        return make_unique<ConcretePrototype>(*this);
    }
};

int main()
{
    unique_ptr<Prototype> p = make_unique<ConcretePrototype>();
    unique_ptr<Prototype> clone1 = p->clone();
    unique_ptr<Prototype> clone2 = p->clone();

    return 0;
}