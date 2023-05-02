#pragma once

#include <map>
#include <cstdint>
// #include <iostream>

typedef std::map<uint8_t *, uint8_t *> Map;

//https://stackoverflow.com/questions/32926176/what-data-type-is-an-address

extern "C"
{
    uint8_t *_address_map_create()
    {
        return reinterpret_cast<uint8_t *>(new Map);
    }

    void _address_map_put(uint8_t *map, uint8_t *k, uint8_t *v)
    {
        // std::cout << "Put! " << (void*) k << ", " << (void*) v << std::endl; 
        Map *m = reinterpret_cast<Map *>(map);
        m->insert(std::pair<uint8_t *, uint8_t *>(k, v));
    }

    uint8_t * _address_map_has(uint8_t *map, uint8_t *k) {
        // std::cout << "Has? " << (void*) k << std::endl; 
        Map *m = reinterpret_cast<Map *>(map);
        auto itr = m->find(k); 

        if(itr == m->end()) return 0; 

        return itr->second; 
    }

    void _address_map_delete(uint8_t *map) {
        Map *m = reinterpret_cast<Map *>(map);
        delete m; 
    }
}