#pragma once

template <typename T>
std::optional<T> anyOpt2Val(const std::any &a) // https://stackoverflow.com/questions/66969536/how-to-correctly-check-any-cast-available
{
    if (const std::optional<T> *v = std::any_cast<std::optional<T>>(&a))
        return *v;
    // else
    std::cout << "10" << std::endl;
    return {};
}

template <typename T>
std::optional<T> any2Opt(const std::any &a) // https://stackoverflow.com/questions/66969536/how-to-correctly-check-any-cast-available
{
    if (const T *v = std::any_cast<T>(&a))
        return *v;
    else
        return {};
}