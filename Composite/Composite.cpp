/*
 * 组合模式：
 * 将对象组合成树形结构以表示“部分-整体”的层次结构。组合模式使得
 * 用户对单个对象和组合对象的使用具有一致性。
 */
#include <iostream>
#include <string>
#include <list>
#include <memory>

using namespace std;

class Component
{
public:
    virtual void Add(unique_ptr<Component> &component) = 0;
    virtual void Remove(unique_ptr<Component> &component) = 0;
    virtual void Display(int depth) = 0;
};

class Leaf : public Component
{
public:
    Leaf(string& name) :name_(name)
    {
    }

    virtual void Add(unique_ptr<Component> &component) override
    {
    }

    virtual void Remove(unique_ptr<Component> &component) override
    {
    }

    virtual void Display(int depth) override
    {
        cout << string(depth, '-') << name_ << endl;
    }
private:
    string name_;
};

class Composite :public Component
{
public:
    Composite(string& name) :name_(name)
    {
    }

    virtual void Add(unique_ptr<Component> &component) override
    {
        child.push_back(move(component));
    }

    virtual void Remove(unique_ptr<Component> &component) override
    {
        child.remove(component);
    }

    virtual void Display(int depth) override
    {
        cout << string(depth, '-') << name_ << endl;
        for (auto& e : child)
        {
            e->Display(depth + 2);
        }
    }
private:
    string name_;
    list<unique_ptr<Component>> child;
};

int main()
{
    unique_ptr<Component> root = make_unique<Composite>(string("root"));

    unique_ptr<Component> leafA = make_unique<Leaf>(string("LeafNodeA"));
    unique_ptr<Component> leafB = make_unique<Leaf>(string("LeafNodeB"));

    root->Add(leafA);
    
    unique_ptr<Component> childTree = make_unique<Composite>(string("childTree"));
    unique_ptr<Component> leafC = make_unique<Leaf>(string("LeafNodeC"));
    unique_ptr<Component> leafD = make_unique<Leaf>(string("LeafNodeD"));

    childTree->Add(leafC);
    childTree->Add(leafD);

    root->Add(childTree);
    root->Add(leafB);

    root->Display(1);

    return 0;
}