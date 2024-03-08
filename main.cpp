#include <algorithm>
#include <iostream>

class ObjectManipulator
{
public:
    template<typename ObjectType>
    static void Invoke(ObjectType* obj)
    {
        InvokeImpl<ObjectType>(obj, nullptr);
    }

private:
    template<typename ObjectType, void(ObjectType::*)()>
    struct function_reflection_type;

    template<typename ObjectType>
    static void InvokeImpl(void* obj, function_reflection_type<ObjectType, &ObjectType::A>*)
    {
        auto* o = static_cast<ObjectType*>(obj);
        o->A();
    }

    template<typename ObjectType>
    static void InvokeImpl(void* obj, function_reflection_type<ObjectType, &ObjectType::B>*)
    {
        auto* o = static_cast<ObjectType*>(obj);
        o->B();
    }
};

class A_Class
{
public:
    void A() { std::cout << "A" << std::endl; };
};

class B_Class
{
public:
    void B() { std::cout << "B" << std::endl; };
};

int main()
{
    ObjectManipulator::Invoke(new A_Class());
    ObjectManipulator::Invoke(new B_Class());
    return 0;
}
