// Reference: http://blog.csdn.net/10km/article/details/49847271

#ifndef XSTL_RAII_H_
#define XSTL_RAII_H_

#include <type_traits>
#include <functional>

namespace xstl {

template<typename T>
struct RemoveConstant {
    using Type = typename std::conditional< std::is_const<T>::value, 
                                            typename std::remove_const<T>::type, 
                                            T >::type;
};

class RAII {
public:
    using FunctionType = std::function<void()>;

    explicit RAII(FunctionType construct, FunctionType destruct)
            : destruct_(destruct), destruct_tag_(true) {
            construct();
    }
    RAII(RAII &&rhs)   // move constructor
            : destruct_(rhs.destruct_), destruct_tag_(rhs.destruct_tag_) {
        rhs.destruct_tag_ = false;
    }
    RAII(const RAII &raii) = delete;   // disable copy constructor
    ~RAII() { if (destruct_tag_) destruct_(); }

    RAII& operator=(const RAII &raii) = delete;   // dosable assignment operator

private:
    FunctionType destruct_;
    bool destruct_tag_;
};

template <typename Res, typename Construct, typename Destruct>
RAII MakeRAII(Res &res, Construct construct, Destruct destruct) {
    // type check
    static_assert(std::is_class<Res>::value, "Type Res is not a class or struct type.");
    static_assert(std::is_member_function_pointer<Construct>::value, "Type Construct is not a member function.");
    static_assert(std::is_member_function_pointer<Destruct>::value, "Type Destruct is not a member function.");

    auto res_addr = std::addressof(const_cast<typename RemoveConstant<Res>::type &>(res));
    return RAII(std::bind(construct, res_addr), std::bind(destruct, res_addr));
}

template <typename Res, typename Destruct>
RAII MakeRAII(Res &res, Destruct destruct) {
    // type check
    static_assert(std::is_class<Res>::value, "Type Res is not a class or struct type.");
    static_assert(std::is_member_function_pointer<Destruct>::value, "Type Destruct is not a member function.");

    auto res_addr = std::addressof(const_cast<typename RemoveConstant<Res>::Type &>(res));
    return RAII([]() {}, std::bind(destruct, res_addr));
}

}

#endif // XSTL_RAII_H_
