#pragma once
#include <optional>
#include <functional>

template<typename T> T lazy_value_or(std::optional<T> opt, std::function<T()> generator) {
    if(opt) return opt.value(); 
    return generator(); 
}