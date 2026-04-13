// ============================================
// Cherno C++ - Type Casting (类型转换)
// ============================================
// C++ 四种类型转换操作符：static_cast, reinterpret_cast, const_cast, dynamic_cast

#include <iostream>

// 为演示 dynamic_cast 定义继承结构
class Base
{
public:
    virtual void Print() { std::cout << "Base" << std::endl; }
    virtual ~Base() {}
};

class Derived : public Base
{
public:
    void Print() override { std::cout << "Derived" << std::endl; }
};

class Other : public Base
{
public:
    void Print() override { std::cout << "Other" << std::endl; }
};

int main()
{
    std::cout << "===== Type Casting =====" << std::endl;

    // ============================================
    // 1. static_cast - Cherno说这是最常用的
    // ============================================
    std::cout << "\n--- 1. static_cast ---" << std::endl;
    std::cout << "用于编译期已知的良性转换" << std::endl;

    // 基本类型转换
    double d = 3.14;
    int i = static_cast<int>(d);
    std::cout << "double 3.14 -> int: " << i << std::endl;

    // 向上转型 (upcasting) - 派生类到基类，总是安全
    Derived derived;
    Base* basePtr = static_cast<Base*>(&derived);
    basePtr->Print();  // 调用 Derived::Print()

    // void* 转换
    void* voidPtr = &derived;
    Base* baseFromVoid = static_cast<Base*>(voidPtr);
    std::cout << "void* -> Base* conversion" << std::endl;

    // ============================================
    // 2. reinterpret_cast - Cherno强调这是危险的
    // ============================================
    std::cout << "\n--- 2. reinterpret_cast ---" << std::endl;
    std::cout << "低层次重新解释位模式，危险！" << std::endl;

    // 指针类型重新解释
    int value = 65;  // ASCII 'A'
    char* charPtr = reinterpret_cast<char*>(&value);
    std::cout << "int* " << &value << " -> char*: " << *charPtr << std::endl;

    // 整数到指针
    intptr_t addr = reinterpret_cast<intptr_t>(&value);
    std::cout << "int* -> intptr_t: " << std::hex << addr << std::dec << std::endl;

    // 指针到指针的重新解释
    long* longPtr = reinterpret_cast<long*>(&value);
    std::cout << "int* -> long*: " << *longPtr << std::endl;

    // ============================================
    // 3. const_cast - 添加或移除 const
    // ============================================
    std::cout << "\n--- 3. const_cast ---" << std::endl;
    std::cout << "用于添加或移除 const/volatile 属性" << std::endl;

    const int constValue = 100;
    // int* ptr1 = &constValue;  // 错误：不能从 const int* 赋值为 int*

    // 使用 const_cast 移除 const
    int* ptr = const_cast<int*>(&constValue);
    std::cout << "const int* -> int*: " << *ptr << std::endl;

    // Cherno提醒：修改原本就是 const 的对象是未定义行为！
    std::cout << "警告：修改通过 const_cast 移除 const 的对象是未定义行为！" << std::endl;

    // ============================================
    // 4. dynamic_cast - 运行时类型检查
    // ============================================
    std::cout << "\n--- 4. dynamic_cast ---" << std::endl;
    std::cout << "需要RTTI支持，用于向下转型（基类到派生类）" << std::endl;

    // 创建 Derived 对象，通过 Base* 指针访问
    Base* basePtr1 = new Derived();

    // 向下转型：Base* -> Derived*
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr1);
    if (derivedPtr)
    {
        std::cout << "Base* -> Derived*: Success" << std::endl;
        derivedPtr->Print();
    }

    // 尝试转换为不兼容的类型
    Other* otherPtr = dynamic_cast<Other*>(basePtr1);
    if (otherPtr == nullptr)
    {
        std::cout << "Base* -> Other*: Failed (nullptr returned)" << std::endl;
    }

    // 引用类型的 dynamic_cast（失败时抛出异常）
    Base& baseRef = *basePtr1;
    try
    {
        Derived& derivedRef = dynamic_cast<Derived&>(baseRef);
        std::cout << "Base& -> Derived&: Success" << std::endl;
    }
    catch (const std::bad_cast&)
    {
        std::cout << "Base& -> Derived&: Failed" << std::endl;
    }

    delete basePtr1;

    // ============================================
    // Cherno的总结：避免 C 风格转换
    // ============================================
    std::cout << "\n--- C++ Casts vs C-style Cast ---" << std::endl;
    std::cout << "C风格转换可以完成所有四种转换，但太危险！" << std::endl;

    Base* b = new Derived();
    // Derived* d1 = (Derived*)b;  // C风格 - 危险！
    Derived* d2 = dynamic_cast<Derived*>(b);  // C++风格 - 安全，失败返回nullptr

    std::cout << "始终优先使用 C++ 的四种转换操作符" << std::endl;

    delete b;

    // ============================================
    // 转换安全性总结 - Cherno的要点
    // ============================================
    std::cout << "\n--- Summary ---" << std::endl;
    std::cout << "static_cast:      基本类型转换、向上转型（安全）" << std::endl;
    std::cout << "dynamic_cast:     向下转型，带运行时检查（安全）" << std::endl;
    std::cout << "const_cast:       添加/移除 const（中等风险）" << std::endl;
    std::cout << "reinterpret_cast: 位重新解释（非常危险）" << std::endl;

    return 0;
}
