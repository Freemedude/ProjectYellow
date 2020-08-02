//
// @author freemedude
// @date 2020-07-29
// @brief 
//

#ifndef PROJECT_YELLOW_STYLEGUIDE_H
#define PROJECT_YELLOW_STYLEGUIDE_H

union MyUnion_u

enum class MyEnum
{
    EnumValue1,
    EnumValue2,
    Count,
};

struct MyStruct
{
    int only;
    float data;
};

class MyClass
{
private:
    // Private members
    int m_myInteger = 0;
    MyStruct m_myStruct{};
    MyStruct *m_pMyStruct{};
    const int m_theConstant = 50;
    float m_pFloats[50];

public:
    MyClass* s_instance;

    MyClass();
    ~MyClass();

    void MemberFunction();

    static MyClass s_CreateMyClass();

protected:
    void TheFunction();
private:
    int HelperFunction();
};



#endif //PROJECT_YELLOW_STYLEGUIDE_H
