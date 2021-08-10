// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <iostream>

enum class EClassType
{
    Default,
    ClassA,
    ClassB,
    ClassC,
};

class Base
{
public:
    virtual void Print()
    {
        std::cout << "Base\n";
    }

    static EClassType GetClassType()
    {
        return EClassType::Default;
    }
};

class A : public Base
{
public:
    virtual void Print() override
    {
        std::cout << "A\n";
    }

    static EClassType GetClassType()
    {
        return EClassType::ClassA;
    }
};

class B : public Base
{
public:
    virtual void Print() override
    {
        std::cout << "B\n";
    }

    static EClassType GetClassType()
    {
        return EClassType::ClassB;
    }
};

class C : public Base
{
public:
    virtual void Print() override
    {
        std::cout << "C\n";
    }

    static EClassType GetClassType()
    {
        return EClassType::ClassC;
    }
};


typedef void* (*FactoryMethodType)();
#define DECLARE_FACTORY_FUNCTION(ClassName) void* Create##ClassName() { return new ClassName(); }
#define FACTORY_FUNCTION_POINTER(ClassName) &Create##ClassName
#define GET_CLASSTYPE(ClassName) ClassName::GetClassType()
#define FACTORY_MAP_ROW(ClassName) {GET_CLASSTYPE(ClassName), FACTORY_FUNCTION_POINTER(ClassName)}

DECLARE_FACTORY_FUNCTION(A)
DECLARE_FACTORY_FUNCTION(B)
DECLARE_FACTORY_FUNCTION(C)

std::map<EClassType, void*> FactoryFunctionMap =
{
    {GET_CLASSTYPE(Base), FACTORY_FUNCTION_POINTER(A)},
    FACTORY_MAP_ROW(A),
    FACTORY_MAP_ROW(B),
    FACTORY_MAP_ROW(C),
};

template<class T>
T* FactoryNewInstance(EClassType InClassType, std::map<EClassType, void*>& InFactoryFunctionMap)
{
    // 找不到类型
    if (InFactoryFunctionMap.find(InClassType) == InFactoryFunctionMap.end())
    {
        return nullptr;
    }

    FactoryMethodType FactoryMethod = (FactoryMethodType)InFactoryFunctionMap[InClassType];
    T* Ret = nullptr;
    Ret = (T*)(FactoryMethod());
    return Ret;
}

int main()
{
    Base* NewInstance = FactoryNewInstance<Base>(EClassType::ClassB, FactoryFunctionMap);
    NewInstance->Print();
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
