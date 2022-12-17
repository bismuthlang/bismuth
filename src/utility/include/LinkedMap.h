#pragma once

#include <vector>   // Vectors
#include <map>      // Map
#include <optional> // Optionals
#include <iostream> // cout

using namespace std;

// TODO: DO BETTER, MAY NEED DESTRUCTORS

template <typename K, typename V>
class LinkedMap
{
private:
    map<K, unsigned int> indexes;
    vector<V> values;

public:
    LinkedMap()
    {
    }

    optional<unsigned int> getIndex(K k) const
    {
        auto ans = indexes.find(k);

        if (ans == indexes.end())
            return {};

        return ans->second;
    }

    optional<V> lookup(K k) const
    {
        optional<unsigned int> index = getIndex(k);

        if (index)
            return values.at(index.value());

        return {};
        // return values.at(ans->second);
    }

    optional<V> insert(K k, V v)
    {
        optional<unsigned int> index = getIndex(k);

        if (index)
        {
            // optional<V> wrapper = v;
            optional<V> old = values.at(index.value());

            values[index.value()] = v;

            return old;
        }

        indexes.insert({k, values.size()});
        values.push_back(v);

        return {};
    }

    optional<V> insert(pair<K, V> p)
    {
        return insert(p.first, p.second);
    }

    vector<pair<K, V>> getElements() const
    {
        vector<pair<K, V>> ans(values.size());
        // ans.reserve(values.size());

        for (auto e : indexes)
        {
            // cout << e.first << "@" << e.second << " vs " << values.size() << std::endl;
            ans[e.second] = {e.first, values.at(e.second)};
        }

        return ans;
    }
};