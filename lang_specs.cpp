#include "lang_specs.h"

std::map<std::string, std::pair<u32, command_types>> get_command_table() {

  std::map<std::string, std::pair<u32, command_types>> command_codes;

  // RI
  command_codes.insert(std::make_pair("addi", std::make_pair(3, _RI)));
  command_codes.insert(std::make_pair("ori", std::make_pair(20, _RI)));
  command_codes.insert(std::make_pair("syscall", std::make_pair(1, _RI)));
  command_codes.insert(std::make_pair("lc", std::make_pair(12, _RI)));
  command_codes.insert(std::make_pair("ret", std::make_pair(42, _RI)));


  // RM
  command_codes.insert(std::make_pair("jmp",  std::make_pair(46, _RM)));
  command_codes.insert(std::make_pair("jne",  std::make_pair(47, _RM)));
  command_codes.insert(std::make_pair("jeq",  std::make_pair(48, _RM)));
  command_codes.insert(std::make_pair("jle",  std::make_pair(49, _RM)));
  command_codes.insert(std::make_pair("jl",  std::make_pair(50, _RM)));
  command_codes.insert(std::make_pair("jge",  std::make_pair(51, _RM)));
  command_codes.insert(std::make_pair("jg",  std::make_pair(52, _RM)));
  command_codes.insert(std::make_pair("calli",std::make_pair(41, _RM)));

  // RR
  command_codes.insert(std::make_pair("mov", std::make_pair(24, _RR)));
  command_codes.insert(std::make_pair("mul", std::make_pair(6, _RR)));
  command_codes.insert(std::make_pair("call",std::make_pair(40, _RR)));

  return command_codes;

}
