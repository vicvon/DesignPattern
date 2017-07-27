/*
 *
 */
#include <iostream>
#include <memory>

using namespace std;

class Product
{
public:
    virtual ~Product()
    {
    }
    virtual void say() = 0;
};

class ConcreteProduct : public Product
{
public:
    ConcreteProduct()
    {
        cout << "Create ConcreteProduct" << endl;
    }
    virtual void say() override
    {
        cout << "ConcreteProduct Say" << endl;
    }
};

class Factory
{
public:
    virtual ~Factory()
    {
    }
    virtual unique_ptr<Product> CreateProduct() = 0;
};

class ConcreteFactory : public Factory
{
public:
    virtual unique_ptr<Product> CreateProduct() override
    {
        return make_unique<ConcreteProduct>();
    }
};

int main()
{
    ConcreteFactory factory;
    unique_ptr<Product> product = factory.CreateProduct();
    product->say();

    return 0;
}