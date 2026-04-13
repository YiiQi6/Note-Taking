// ============================================
// Cherno C++ - Virtual Destructors (虚析构函数)
// ============================================
// 虚析构函数：当通过基类指针删除派生类对象时，确保派生类的析构函数被调用

#include <iostream>

class Base
{
public:
    Base() { std::cout << "Base constructed" << std::endl; }

    // 虚析构函数 - 如果没有 virtual，派生类的析构函数不会被调用！
    virtual ~Base() { std::cout << "Base destructed (virtual)" << std::endl; }

    virtual void Print() { std::cout << "Base::Print()" << std::endl; }
};

class Derived : public Base
{
public:
    Derived() { std::cout << "Derived constructed" << std::endl; }
    ~Derived() { std::cout << "Derived destructed" << std::endl; }

    void Print() override { std::cout << "Derived::Print()" << std::endl; }
};

// ============================================
// Cherno强调的问题：如果析构函数不是虚的
// ============================================
class BaseBad
{
public:
    BaseBad() { std::cout << "BaseBad constructed" << std::endl; }
    // 非虚析构函数 - 问题！
    ~BaseBad() { std::cout << "BaseBad destructed (NON-VIRTUAL!)" << std::endl; }

    virtual void Print() { std::cout << "BaseBad::Print()" << std::endl; }
};

class DerivedBad : public BaseBad
{
public:
    DerivedBad() { std::cout << "DerivedBad constructed" << std::endl; }
    ~DerivedBad() { std::cout << "DerivedBad destructed - BUT WON'T BE CALLED!" << std::endl; }

    void Print() override { std::cout << "DerivedBad::Print()" << std::endl; }
};

int main()
{
    std::cout << "===== Virtual Destructors =====" << std::endl;

    // ============================================
    // 正确情况：使用虚析构函数
    // ============================================
    std::cout << "\n--- Correct: Virtual Destructor ---" << std::endl;
    std::cout << "Creating Derived object via Base pointer..." << std::endl;

    Base* ptr = new Derived();
    std::cout << "\nDeleting through Base pointer:" << std::endl;
    delete ptr;  // 正确！调用 Derived::~Derived() 然后 Base::~Base()

    // ============================================
    // 错误情况：使用非虚析构函数
    // ============================================
    std::cout << "\n--- Wrong: Non-Virtual Destructor ---" << std::endl;
    std::cout << "Creating DerivedBad object via BaseBad pointer..." << std::endl;

    BaseBad* badPtr = new DerivedBad();
    std::cout << "\nDeleting through BaseBad pointer:" << std::endl;
    delete badPtr;  // 问题！只调用 BaseBad::~BaseBad()，DerivedBad::~DerivedBad() 不会被调用！

    // ============================================
    // Cherno的总结
    // ============================================
    std::cout << "\n--- Summary ---" << std::endl;
    std::cout << "规则：如果一个类有虚函数，那么它的析构函数也应该是虚的！" << std::endl;
    std::cout << "原因：通过基类指针删除派生类对象时，虚析构函数确保正确的清理顺序" << std::endl;

    // ============================================
    // 多层继承中的虚析构函数
    // ============================================
    std::cout << "\n--- Multi-level Inheritance ---" << std::endl;

    class GrandBase
    {
    public:
        GrandBase() { std::cout << "GrandBase constructed" << std::endl; }
        virtual ~GrandBase() { std::cout << "GrandBase destructed" << std::endl; }
    };

    class Middle : public GrandBase
    {
    public:
        Middle() { std::cout << "Middle constructed" << std::endl; }
        ~Middle() { std::cout << "Middle destructed" << std::endl; }
    };

    class Child : public Middle
    {
    public:
        Child() { std::cout << "Child constructed" << std::endl; }
        ~Child() { std::cout << "Child destructed" << std::endl; }
    };

    GrandBase* multiPtr = new Child();
    std::cout << "Deleting multi-level object:" << std::endl;
    delete multiPtr;
    std::cout << "正确的析构顺序：Child -> Middle -> GrandBase" << std::endl;

    return 0;
}
