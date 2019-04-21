#include "processor.h"

/////// Constructor
Processor::Processor() {

  this->command_table.insert(std::make_pair(3,  &Processor::addi ));
  this->command_table.insert(std::make_pair(5,  &Processor::subi ));
  this->command_table.insert(std::make_pair(24, &Processor::mov ));
  this->command_table.insert(std::make_pair(1,  &Processor::syscall ));
  this->command_table.insert(std::make_pair(12, &Processor::lc ));
  this->command_table.insert(std::make_pair(6,  &Processor::mul ));
  this->command_table.insert(std::make_pair(41,  &Processor::calli ));
  this->command_table.insert(std::make_pair(42,  &Processor::ret ));

  this->command_table.insert(std::make_pair(46, &Processor::jmp ));
  this->command_table.insert(std::make_pair(47, &Processor::jne ));
  this->command_table.insert(std::make_pair(48, &Processor::jeq ));
  this->command_table.insert(std::make_pair(49, &Processor::jle ));
  this->command_table.insert(std::make_pair(50, &Processor::jl ));
  this->command_table.insert(std::make_pair(51, &Processor::jge ));
  this->command_table.insert(std::make_pair(52, &Processor::jg ));

  this->command_table.insert(std::make_pair(38, &Processor::push ));
  this->command_table.insert(std::make_pair(39, &Processor::pop ));
  this->command_table.insert(std::make_pair(44, &Processor::cmpi ));
  this->command_table.insert(std::make_pair(68, &Processor::loadr ));
  this->command_table.insert(std::make_pair(32, &Processor::addd ));
  this->command_table.insert(std::make_pair(33, &Processor::subd ));
  this->command_table.insert(std::make_pair(34, &Processor::muld ));
  this->command_table.insert(std::make_pair(35, &Processor::divd ));
  this->command_table.insert(std::make_pair(36, &Processor::itod ));
  this->command_table.insert(std::make_pair(37, &Processor::dtoi ));


  this->frame = MEMORY_SIZE-1;
  this->data_registers[14] = MEMORY_SIZE; // Stack pointer
  this->program_pointer = 0;
  this->flags = 0;
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

double Processor::get_double(int reg) {

    long num = 0;

    num |= data_registers[reg+1];
    num = num << 32;
    num |= data_registers[reg];

    double* d = reinterpret_cast<double*>(&num);

    return *d;
}

int Processor::dump_double(double num, int reg) {

  long* p = reinterpret_cast<long*>(&num);

  data_registers[reg] = (*p) & 4294967295; // 32 bits
  data_registers[reg+1] = ((*p) >> 32) & 4294967295;

  return 0;
}

/////// Interface
int Processor::exec() {

  u32 word = memory[program_pointer++];

  processor_function func = command_table[get_command_num(word)];
  int code = (this->*func)(word);

  return code;
}

int Processor::load_program(const std::vector<u32>& program) {

  this->program_pointer = program[0];

  for (int i = 1; i < program.size(); ++i)
    memory[i-1] = program[i];

  this->frame = MEMORY_SIZE-1;

  std::memset(data_registers, 0, NUM_REGISTERS);
  this->data_registers[14] = MEMORY_SIZE;

  return 0;
}

//////// Commands

// RI
int Processor::addi(u32 word) {

  int reg, value;
  parse_ri(word, reg, value);

  data_registers[reg] += value;

  return 0;
}

int Processor::subi(u32 word) {

  int reg, value;
  parse_ri(word, reg, value);

  data_registers[reg] -= value;

  return 0;
}

int Processor::syscall(u32 word) {

  int reg, value;
  parse_ri(word, reg, value);

  int ret_val = 0;

  switch (value) {
    case EXIT:
      ret_val = 1;
      break;
    case SCANINT:
      std::cin >> data_registers[reg];
      break;
    case PRINTINT:
      std::cout << data_registers[reg];
      break;
    case SCANDOUBLE: {
      double d;
      std::cin >> d;
      dump_double(d, reg);
      break;
    }
    case PRINTDOUBLE:
      std::cout << get_double(reg);
      break;
    case GETCHAR:
      std::cin >> data_registers[reg];
      break;
    case PUTCHAR:
      std::cout << static_cast<char>(data_registers[reg]);
      break;
    default:
      ret_val = 1;
      std::cout << "No such syscall!\n";
      break;
  }

  return ret_val;
}

int Processor::lc(u32 word) {

  int reg, value;
  parse_ri(word, reg, value);

  data_registers[reg] = value;

  return 0;
}

int Processor::push(u32 word) {

  int reg, value;
  parse_ri(word, reg, value);

  data_registers[14] -= 1;

  memory[data_registers[14]] = data_registers[reg] + value;

  return 0;
}

int Processor::pop(u32 word) {

  int reg, value;
  parse_ri(word, reg, value);

  data_registers[reg] = memory[data_registers[14]] + value;
  memory[data_registers[14]] = 0;
  data_registers[14] += 1;

  return 0;
}

int Processor::cmpi(u32 word) {

  int reg, value;
  parse_ri(word, reg, value);

  if (data_registers[reg] > value)
    flags = 1;
  else if (data_registers[reg] == value)
    flags = 0;
  else
    flags = -1;

  return 0;
}
// RM

int Processor::calli(u32 word) {

  int reg, value;
  parse_rm(word, reg, value);

  // Place return point in stack
  data_registers[14] -= 1;
  memory[data_registers[14]] = program_pointer;

  program_pointer = value;

  return 0;
}

int Processor::jmp(u32 word) {

  int reg, value;
  parse_rm(word, reg, value);

  program_pointer = value;

  return 0;
}

int Processor::jne(u32 word) {
  if (flags != 0)
    return jmp(word);
  return 0;
}

int Processor::jeq(u32 word) {
  if (flags == 0)
    return jmp(word);
  return 0;
}

int Processor::jle(u32 word) {
  if (flags <= 0)
    return jmp(word);
  return 0;
}

int Processor::jl(u32 word) {
  if (flags < 0)
    return jmp(word);
  return 0;
}

int Processor::jge(u32 word) {
  if (flags >= 0)
    return jmp(word);
  return 0;
}

int Processor::jg(u32 word) {
  if (flags > 0)
    return jmp(word);
  return 0;
}

int Processor::ret(u32 word) {

  int reg, value;
  parse_rm(word, reg, value);

  program_pointer = memory[data_registers[14]];

  data_registers[14] += value + 1;

  return 0;
}
// RR
int Processor::mov(u32 word) {

  int in_reg, out_reg, value;
  parse_rr(word, in_reg, out_reg, value);

  data_registers[in_reg] = data_registers[out_reg] + value;

  return 0;
}

int Processor::mul(u32 word) {

  int in_reg, out_reg, value;
  parse_rr(word, in_reg, out_reg, value);

  long result = data_registers[in_reg] * (data_registers[out_reg] + value);

  data_registers[in_reg] = result & 4294967295; // First 32 bits
  data_registers[in_reg+1] = (result >> 32) & 4294967295; // Last 32 bits

  return 0;
}

int Processor::loadr(u32 word) {

  int in_reg, out_reg, value;
  parse_rr(word, in_reg, out_reg, value);

  data_registers[in_reg] = memory[data_registers[out_reg] + value];

  return 0;
}

int Processor::addd(u32 word) {

  int in_reg, out_reg, value;
  parse_rr(word, in_reg, out_reg, value);

  double a, b;
  a = get_double(in_reg);
  b = get_double(out_reg);

  dump_double(a + b + value, in_reg);

  return 0;
}

int Processor::subd(u32 word) {

  int in_reg, out_reg, value;
  parse_rr(word, in_reg, out_reg, value);

  double a, b;
  a = get_double(in_reg);
  b = get_double(out_reg);

  dump_double(a - b + value, in_reg);

  return 0;
}

int Processor::muld(u32 word) {

  int in_reg, out_reg, value;
  parse_rr(word, in_reg, out_reg, value);

  double a, b;
  a = get_double(in_reg);
  b = get_double(out_reg);

  dump_double((a * b) + value, in_reg);

  return 0;
}

int Processor::divd(u32 word) {

  int in_reg, out_reg, value;
  parse_rr(word, in_reg, out_reg, value);

  double a, b;
  a = get_double(in_reg);
  b = get_double(out_reg);

  dump_double((a / b) + value, in_reg);

  return 0;
}

int Processor::itod(u32 word) {

  int in_reg, out_reg, value;
  parse_rr(word, in_reg, out_reg, value);

  double num = static_cast<double>(data_registers[out_reg]);

  dump_double(num, in_reg);

  return 0;
}

int Processor::dtoi(u32 word) {

  int in_reg, out_reg, value;
  parse_rr(word, in_reg, out_reg, value);

  u32 num = static_cast<u32>(get_double(out_reg));

  data_registers[in_reg] = num;

  return 0;
}
