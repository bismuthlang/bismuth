#pragma once
#include <optional>   // optional
#include <functional> // reference_wrapper
#include <memory>     // shared_ptr

template <class T>
using optional_ref = std::optional<std::reference_wrapper<T>>;

template <class T>
using shared_set = std::set<std::shared_ptr<T>>;


template <class K, class V>
using map_to_shared = std::map<K, std::shared_ptr<V>>;

template <class T>
using ref = std::reference_wrapper<T>;


