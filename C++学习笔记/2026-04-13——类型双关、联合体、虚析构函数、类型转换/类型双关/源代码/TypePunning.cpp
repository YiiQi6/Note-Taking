// ============================================
// Cherno C++ - Type Punning (类型双关)
// ============================================
// 类型双关：同一块内存可以被解释为不同的类型

#include <iostream>
#include <string>
#include <cstring>

// Cherno常用的向量结构，用于演示类型双关
struct Vec3
{
    float x, y, z;
};

int main()
{
    std::cout << "===== Type Punning =====" << std::endl;

    // ============================================
    // 方法1：通过指针进行类型双关 (reinterpret_cast)
    // ============================================
    std::cout << "\n--- Method 1: Pointer casting ---" << std::endl;

    Vec3 vector = {1.0f, 2.0f, 3.0f};

    // 将 Vec3* 强制转换为 float*
    float* f = (float*)&vector;
    // 或者使用 reinterpret_cast
    float* f2 = reinterpret_cast<float*>(&vector);

    std::cout << "Vec3 = {" << vector.x << ", " << vector.y << ", " << vector.z << "}" << std::endl;
    std::cout << "As float array: {" << f[0] << ", " << f[1] << ", " << f[2] << "}" << std::endl;

    // ============================================
    // 方法2：通过联合体 (Union) 进行类型双关
    // ============================================
    std::cout << "\n--- Method 2: Using Union ---" << std::endl;

    // Cherno演示的整数到浮点的类型双关
    union
    {
        float f;
        int i;
    } converter;

    converter.f = 1.0f;
    std::cout << "float 1.0f as int: " << converter.i << std::endl;
    std::cout << "int 1065353216 as float: " << converter.f << std::endl;

    // ============================================
    // 方法3：使用 memcpy (最安全的方式)
    // ============================================
    std::cout << "\n--- Method 3: Using memcpy ---" << std::endl;

    double d = 3.14159;
    long long bits;
    std::memcpy(&bits, &d, sizeof(double));

    std::cout << "double " << d << " as long long: " << bits << std::endl;

    // ============================================
    // Cherno的实际例子：读取浮点数的二进制表示
    // ============================================
    std::cout << "\n--- Practical Example: Float binary representation ---" << std::endl;

    float value = 0.5f;
    int* bitsPtr = reinterpret_cast<int*>(&value);

    std::cout << "float " << value << " = 0x" << std::hex << *bitsPtr << std::dec << std::endl;
    std::cout << "Expected 0x3f000000 for 0.5f in IEEE 754" << std::endl;

    // ============================================
    // 重要提醒：strict aliasing 规则
    // ============================================
    std::cout << "\n--- Important: Strict Aliasing ---" << std::endl;
    std::cout << "某些类型双关方式可能导致未定义行为！" << std::endl;
    std::cout << "推荐使用 memcpy 方式，它是安全且定义良好的" << std::endl;

    return 0;
}
