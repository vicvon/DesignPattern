/*
 * 抽象工厂模式：
 * 提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类
 *
 * 抽象工厂模式与工厂方法模式最大的区别在于，工厂方法模式针对的是一个产品等级结构，
 * 而抽象工厂模式则需要面对多个产品等级结构，一个工厂等级结构可以负责多个不同产品等
 * 级结构中的产品对象的创建。当一个工厂等级结构可以创建出分属于不同产品等级结构的一
 * 个产品族中的所有对象时，抽象工厂模式比工厂方法模式更为简单、有效率。
 */
#include <iostream>
#include <memory>

using namespace std;

class AbstractProductA
{
public:
    virtual void say() = 0;
};

class ProductA1 : public AbstractProductA
{
public:
    virtual void say() override
    {
        cout << "ProductA1 Say" << endl;
    }
};

class ProductA2 : public AbstractProductA
{
public:
    virtual void say() override
    {
        cout << "ProductA2 Say" << endl;
    }
};

class AbstractProductB
{
public:
    virtual void cry() = 0;
};

class ProductB1 : public AbstractProductB
{
public:
    virtual void cry() override
    {
        cout << "ProductB1 Cry" << endl;
    }
};

class ProductB2 : public AbstractProductB
{
public:
    virtual void cry() override
    {
        cout << "ProductB2 Cry" << endl;
    }
};

class AbstractFactory
{
public:
    virtual unique_ptr<AbstractProductA> createProductA() = 0;
    virtual unique_ptr<AbstractProductB> createProductB() = 0;
};

class ConcreteFactory1 : public AbstractFactory
{
public:
    virtual unique_ptr<AbstractProductA> createProductA() override
    {
        return make_unique<ProductA1>();
    }
    virtual unique_ptr<AbstractProductB> createProductB() override
    {
        return make_unique<ProductB1>();
    }
};

class ConcreteFactory2 : public AbstractFactory
{
public:
    virtual unique_ptr<AbstractProductA> createProductA() override
    {
        return make_unique<ProductA2>();
    }
    virtual unique_ptr<AbstractProductB> createProductB() override
    {
        return make_unique<ProductB2>();
    }
};

int main()
{
    auto f1 = make_unique<ConcreteFactory1>();
    auto pa1 = f1->createProductA();
    pa1->say();
    auto pb1 = f1->createProductB();
    pb1->cry();

    auto f2 = make_unique<ConcreteFactory2>();
    auto pa2 = f2->createProductA();
    pa2->say();
    auto pb2 = f2->createProductB();
    pb2->cry();

    return 0;
}