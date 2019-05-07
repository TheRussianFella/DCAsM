#include <vector>
#include <map>
#include <cstring>
#include <iostream>
#include <climits>

#include "lang_specs.h"

#define MEMORY_SIZE 1048575
#define NUM_REGISTERS 16

class Processor {

private:

  typedef int (Processor::*processor_function)(u32);

  u32 *data_registers;
  u32 frame;
  u32 program_pointer;
  u32 flags;

  u32 *memory;
  std::map<u32, processor_function>* command_table;


  u32 get_command_num(u32 word);
  int parse_rm(u32 word, int& reg, int& value);
  int parse_rr(u32 word, int& in_reg, int& out_reg, int& value);
  int parse_ri(u32 word, int& reg, int& value);
  double get_double(int reg);
  int dump_double(double num, int reg);

  // RI Commands
  int addi(u32 word);
  int subi(u32 word);
  int muli(u32 word);
  int divi(u32 word);
  int syscall(u32 word);
  int lc(u32 word);
  int push(u32 word);
  int pop(u32 word);
  int cmpi(u32 word);
  int shli(u32 word);
  int shri(u32 word);
  int andi(u32 word);
  int ori(u32 word);
  int xori(u32 word);
  int _not(u32 word);


  // RM Commands
  int calli(u32 word);
  int ret(u32 word);
  int jmp(u32 word);
  int jne(u32 word);
  int jeq(u32 word);
  int jle(u32 word);
  int jl(u32 word);
  int jge(u32 word);
  int jg(u32 word);

  // RR Commands
  int mov(u32 word);
  int mul(u32 word);
  int div(u32 word);
  int loadr(u32 word);
  int addd(u32 word);
  int subd(u32 word);
  int muld(u32 word);
  int divd(u32 word);
  int dtoi(u32 word);
  int itod(u32 word);
  int add(u32 word);
  int sub(u32 word);
  int call(u32 word);
  int shl(u32 word);
  int shr(u32 word);
  int _and(u32 word);
  int _or(u32 word);
  int _xor(u32 word);
  int cmp(u32 word);


public:

  Processor();
  ~Processor();

  int load_program(const std::vector<u32>& program);
  int exec();

};
