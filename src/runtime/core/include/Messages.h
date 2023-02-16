#pragma once
/**
 * @file Messages.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief Manages the various types of messages in a queue
 * @version 0.1
 * @date 2022-12-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <variant>
#include "stdint.h" // uint8_t

struct Value {
    uint8_t * v; 
};

struct START_LOOP {}; 
struct END_LOOP {}; 
struct SEL {
    unsigned int i; //TODO: Will have to be handled better
};

typedef std::variant<Value, START_LOOP, END_LOOP, SEL> Message; 