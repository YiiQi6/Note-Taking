// ============================================
// Cherno C++ - Unions (联合体)
// ============================================
// 联合体：所有成员共享同一块内存

#include <iostream>

// Cherno常用的2D实体结构
struct Vec2
{
    float x, y;
};

// ============================================
// 联合体的基本用法 - Cherno演示的核心例子
// ============================================
struct Entity
{
    float x, y;

    // 匿名联合体 - Cherno在视频中强调的用法
    union
    {
        int id;
        float score;
    };
};

int main()
{
    std::cout << "===== Unions =====" << std::endl;

    // ============================================
    // 基本联合体演示
    // ============================================
    std::cout << "\n--- Basic Union Demo ---" << std::endl;

    Entity e;
    e.x = 2.0f;
    e.y = 5.0f;

    // 写入 id（整数）
    e.id = 42;
    std::cout << "Set e.id = 42" << std::endl;
    std::cout << "e.id = " << e.id << std::endl;
    std::cout << "e.score = " << e.score << " (score 和 id 共享内存！)" << std::endl;

    // 写入 score（浮点数）
    e.score = 100.5f;
    std::cout << "\nSet e.score = 100.5f" << std::endl;
    std::cout << "e.score = " << e.score << std::endl;
    std::cout << "e.id = " << e.id << " (id 的值被 score 覆盖了！)" << std::endl;

    // ============================================
    // 命名联合体
    // ============================================
    std::cout << "\n--- Named Union ---" << std::endl;

    struct EntityNamed
    {
        float x, y;

        union Data
        {
            int id;
            float score;
        } data;
    };

    EntityNamed en;
    en.x = 1.0f;
    en.y = 2.0f;
    en.data.id = 99;

    std::cout << "EntityNamed data.id = " << en.data.id << std::endl;
    std::cout << "EntityNamed data.score = " << en.data.score << std::endl;

    // ============================================
    // 联合体的实际应用场景 - Cherno讲解的场景
    // ============================================
    std::cout << "\n--- Practical Use Case ---" << std::endl;
    std::cout << "场景：当某些字段不会同时使用时，节省内存" << std::endl;

    struct Player
    {
        Vec2 position;
        Vec2 velocity;

        union
        {
            int score;
            int health;
        }; // 玩家要么有分数，要么有生命值，不会同时使用
    };

    Player p;
    p.position.x = 10.0f;
    p.position.y = 20.0f;
    p.score = 1000;

    std::cout << "Player position: (" << p.position.x << ", " << p.position.y << ")" << std::endl;
    std::cout << "Player score: " << p.score << std::endl;

    // ============================================
    // 联合体用于类型双关 (与类型双关视频关联)
    // ============================================
    std::cout << "\n--- Union for Type Punning ---" << std::endl;

    union FloatInt
    {
        float f;
        int i;
    };

    FloatInt fi;
    fi.f = 3.14f;
    std::cout << "float 3.14f stored as int: " << fi.i << std::endl;

    return 0;
}
