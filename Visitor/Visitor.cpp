/*
 * 访问者模式：
 * 表示一个作用于某对象结构中的各元素的操作。它使你可以在不改变各元素的类
 * 的前提下定义作用于这些元素的新操作。
 */
#include <iostream>
#include <memory>
#include <list>

using namespace std;

class ConcreteElementA;
class ConcreteElementB;

class Visitor
{
public:
    virtual void VisitConcreteElementA(ConcreteElementA& concreteElementA) = 0;
    virtual void VisitConcreteElementB(ConcreteElementB& concreteElementB) = 0;
};

class ConcreteVisitorA : public Visitor
{
public:
    virtual void VisitConcreteElementA(ConcreteElementA& concreteElementA) override
    {
        cout << "VisitConcreteElementA concreteElementA" << endl;
    }

    virtual void VisitConcreteElementB(ConcreteElementB& concreteElementB) override
    {
        cout << "VisitConcreteElementA concreteElementB" << endl;
    }
};

class ConcreteVisitorB : public Visitor
{
public:
    virtual void VisitConcreteElementA(ConcreteElementA& concreteElementA) override
    {
        cout << "VisitConcreteElementB concreteElementA" << endl;
    }

    virtual void VisitConcreteElementB(ConcreteElementB& concreteElementB) override
    {
        cout << "VisitConcreteElementB concreteElementB" << endl;
    }
};

class Element
{
public:
    virtual void Accept(shared_ptr<Visitor>& visitor) = 0;
};

class ConcreteElementA : public Element
{
public:
    virtual void Accept(shared_ptr<Visitor>& visitor) override
    {
        cout << "ConcreteElementA Accept" << endl;
        visitor->VisitConcreteElementA(*this);
    }
};

class ConcreteElementB : public Element
{
    virtual void Accept(shared_ptr<Visitor>& visitor) override
    {
        cout << "ConcreteElementB Accept" << endl;
        visitor->VisitConcreteElementB(*this);
    }
};

class ObjectStructure
{
public:
    void Attach(shared_ptr<Element>& element)
    {
        elements_.push_back(element);
    }

    void Detach(shared_ptr<Element>& element)
    {
        if (element != nullptr)
            elements_.remove(element);
    }

    void Accept(shared_ptr<Visitor>& visitor)
    {
        for (auto e : elements_)
        {
            e->Accept(visitor);
        }
    }
private:
    list<shared_ptr<Element>> elements_;
};

int main()
{
    ObjectStructure obj;
    shared_ptr<Element> ea = make_shared<ConcreteElementA>();
    shared_ptr<Element> eb = make_shared<ConcreteElementB>();

    obj.Attach(ea);
    obj.Attach(eb);

    shared_ptr<Visitor> va = make_shared<ConcreteVisitorA>();
    shared_ptr<Visitor> vb = make_shared<ConcreteVisitorB>();

    obj.Accept(va);

    obj.Accept(vb);

    return 0;
}