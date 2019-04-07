#include <vector>
#include <map>
#include <cstring>
#include <iostream>
#include <climits>

#include "lang_specs.h"

#define MEMORY_SIZE 1000
#define NUM_REGISTERS 12

class Processor {

private:

  typedef int (Processor::*processor_function)(u32);

  u32 data_registers[NUM_REGISTERS] = {0};
  u32 frame;
  u32 stack_pointer;
  u32 program_pointer;

  u32 memory[MEMORY_SIZE] = {0};
  std::map<u32, processor_function> command_table;


  u32 get_command_num(u32 word);
  int parse_rm(u32 word, int& reg, int& value);
  int parse_rr(u32 word, int& in_reg, int& out_reg, int& value);
  int parse_ri(u32 word, int& reg, int& value);

  // RI Commands
  int addi(u32 word);
  int syscall(u32 word);
  int lc(u32 word);
  
  // RM Commands
  int jmp(u32 word);

  // RR Commands
  int mov(u32 word);
  int mul(u32 word);

public:

  Processor();

  int load_program(std::vector<u32> program);
  int exec();

};
