#include "processor.h"
#include <bitset>

/////// Constructor
Processor::Processor() {

  this->command_table.insert(std::make_pair(3, &Processor::addi ));
  this->command_table.insert(std::make_pair(46, &Processor::jmp ));
  this->command_table.insert(std::make_pair(24, &Processor::mov ));

  this->frame = MEMORY_SIZE-1;
  this->stack_pointer = MEMORY_SIZE-1;
  this->program_pointer = 0;
}


/////// Parsing
u32 Processor::get_command_num(u32 word) {
  return word >> (32 - 8);
}

int Processor::parse_rm(u32 word, int& reg, int& value) {
  reg = (word >> 20) & 15;
  value = word & 1048575; // 20 bits
  return 0;
}

int Processor::parse_rr(u32 word, int& in_reg, int& out_reg, int& value) {
  in_reg = (word >> 20) & 15;
  out_reg = (word >> 16) & 15;
  value = (word & 65535) | ((UINT_MAX - 65535) * ((word >> 15) & 1));
  return 0;
}

int Processor::parse_ri(u32 word, int &reg, int &value) {
  reg = (word >> 20) & 15;
  value = (word & 1048575) | ((UINT_MAX - 1048575) * ((word >> 19) & 1));
  return 0;
}

/////// Interface
int Processor::exec() {

  u32 word = memory[program_pointer++];

  processor_function func = command_table[get_command_num(word)];

  int code = (this->*func)(word);

  return code;
}

int Processor::load_program(std::vector<u32> program) {

  for (int i = 0; i < program.size(); ++i)
    memory[i] = program[i];

  this->frame = MEMORY_SIZE-1;
  this->stack_pointer = MEMORY_SIZE-1;
  this->program_pointer = 0;

  std::memset(data_registers, 0, NUM_REGISTERS);

  return 0;
}

//////// Commands

// RI
int Processor::addi(u32 word) {

  int reg, value;
  parse_ri(word, reg, value);

  std::cout << "ADDI: " << reg << " " << value << "\n";
  
  return 1;
}

// RM
int Processor::jmp(u32 word) {

  int reg, value;
  parse_rm(word, reg, value);

  std::cout << "JMP: " << reg << " " << value << "\n";

  return 1;
}

// RR
int Processor::mov(u32 word) {

  int in_reg, out_reg, value;
  parse_rr(word, in_reg, out_reg, value);

  std::cout << "MOV: " << in_reg << " " << out_reg << " " << value << "\n";

  return 1;
}
