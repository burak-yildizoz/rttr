#ifndef RTTR_UTILITY_H_
#define RTTR_UTILITY_H_

namespace rttr
{

/**
Register property getter with lambda function.

@code
int get_my_int(const MyClass& my_class);

rttr::registration::class_<MyClass>("MyClass")
    .property_readonly("my_int"
        , rttr::as_member_func(+[](const MyClass* self) { return get_my_int(*self); })
    )
;
@endcode
*/
template <typename Return, typename Class, typename... Args>
auto as_member_func(Return(*func)(const Class*, Args...))
{
    union {
        Return(Class::*member_func)(Args...) const;
        void* func_ptr;
    } convert;
    convert.func_ptr = func;
    return convert.member_func;
}

/**
Register property setter with lambda function.

@code
class MyClass {
public:
    explicit MyClass(int my_int);

    int& get();

private:
    int my_int;
};

rttr::registration::class_<MyClass>("MyClass")
    .property("my_int"
        , &MyClass::get,
        , rttr::as_member_func(+[](MyClass* self, int my_int) { self->get() = my_int; })
    )
;
@endcode
*/
template <typename Return, typename Class, typename... Args>
auto as_member_func(Return(*func)(Class*, Args...))
{
    union {
        Return(Class::*member_func)(Args...);
        void* func_ptr;
    } convert;
    convert.func_ptr = func;
    return convert.member_func;
}

} // end namespace rttr

#endif // RTTR_UTILITY_H_
