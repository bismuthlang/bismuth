/**
 * @file bismuth_runtime.c
 * @author Alex Friedman (ahfriedman.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>

// The program entry function
void program(unsigned int i);

unsigned int Execute(void (*func)(unsigned int));
void* ReadChannel(unsigned int aId);

void waitForAllToFinish(); 

int argCount;
char **args;

/**
 * @brief main program that calls the program() function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[]) {
  argCount = argc;
  args = argv;

  unsigned int idOut = Execute(&program);
  
  void * ptr = ReadChannel(idOut);

  waitForAllToFinish();
  return 0; 
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