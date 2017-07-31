/*
 * 建造者模式：
 * 将一个复杂对象的构建与它的表示分离，是这样同样的构建过程可以创建不同的表示
 */
#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

class Product
{
public:
    Product()
    {
        cout << "Product Done" << endl;
    }
};

class Builder
{
public:
    virtual void BuildPartA() = 0;
    virtual void BuildPartB() = 0;
    virtual void BuildPartC() = 0;
    virtual unique_ptr<Product> GetProduct() = 0;
};

class ConcreteBuilder : public Builder
{
public:
    ConcreteBuilder()
    {
        component_.push_back("ConcreteBuilder");
    }
    virtual void BuildPartA() override
    {
        component_.push_back("Add PartA");
    }

    virtual void BuildPartB() override
    {
        component_.push_back("Add PartB");
    }

    virtual void BuildPartC() override
    {
        component_.push_back("Add PartC");
    }

    virtual unique_ptr<Product> GetProduct() override
    {
        for (auto e : component_)
        {
            cout << e << endl;
        }
        return make_unique<Product>();
    }
private:
    vector<string> component_;
};

class Director
{
public:
    void setBuilder(unique_ptr<Builder>& builder)
    {
        builder_ = move(builder);
    }

    unique_ptr<Builder>& getBuilder()
    {
        return builder_;
    }

    void Construct()
    {
        builder_->BuildPartA();
        builder_->BuildPartB();
        builder_->BuildPartC();
    }
private:
    unique_ptr<Builder> builder_;
};

int main()
{
    unique_ptr<Builder> builder = make_unique<ConcreteBuilder>();
    Director director;
    director.setBuilder(builder);
    director.Construct();

    auto product = director.getBuilder()->GetProduct();

    return 0;
}