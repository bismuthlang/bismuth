/**
 * @file wpl_runtime.c
 * @author gpollice
 * @brief Runtime library for WPL. Link this object 
 *  file with WPL programs.
 * @version 0.1
 * @date 2022-10-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>

// The WPL program entry function
int program();

int argCount;
char **args;

/**
 * @brief mai program that calls the WPL program() function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[]) {
  argCount = argc;
  args = argv;
  return program();
}

/**
 * @brief Returns the number of arguments on the command line.
 *  There is always one, the program name
 * 
 * @return int the number of arguments
 */
int getArgCount() {
  return argCount;
}

/**
 * @brief Get an argument from the command line as a string
 * 
 * @param i 
 * @return char* 
 */
char *getStrArg(int i) {
  if (i < 0 || i >= argCount) {
    fprintf(stderr, "Attempt to access an argument out of bounds -- aborting!\n");
    exit(-1);
  }
  return args[i];
}

/**
 * @brief Get an argument from the command line as an integer
 * 
 * @param i 
 * @return int 
 */
int getIntArg(int i) {
  if (i < 0 || i >= argCount) {
    fprintf(stderr, "Attempt to access an argument out of bounds -- aborting!\n");
    exit(-1);
  }
  return atoi(args[i]);
}