#pragma once

#include <type_traits>

namespace c10 {

/**
 * Represent a function pointer as a C++ type.
 * This allows using the function pointer as a type
 * in a template and calling it from inside the template
 * allows the compiler to inline the call because it
 * knows the function pointer at compile time.
 */
template<class FuncType_, FuncType_* func_ptr_>
struct CompileTimeFunctionPointer final {
  using FuncType = FuncType_;

  static constexpr FuncType* func_ptr() {
    return func_ptr_;
  }
};

template<class T> struct is_compile_time_function_pointer : std::false_type {};
template<class FuncType, FuncType* func_ptr>
struct is_compile_time_function_pointer<CompileTimeFunctionPointer<FuncType, func_ptr>> : std::true_type {};

}

#define TORCH_FN(func) ::c10::CompileTimeFunctionPointer<decltype(func), &func>()