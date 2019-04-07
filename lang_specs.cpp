#include "lang_specs.h"

std::map<std::string, std::pair<u32, command_types>> get_command_table() {

  std::map<std::string, std::pair<u32, command_types>> command_codes;

  // RI
  command_codes.insert(std::make_pair("addi", std::make_pair(3, _RI)));
  command_codes.insert(std::make_pair("ori", std::make_pair(20, _RI)));
  command_codes.insert(std::make_pair("syscall", std::make_pair(1, _RI)));
  command_codes.insert(std::make_pair("lc", std::make_pair(12, _RI)));

  // RM
  command_codes.insert(std::make_pair("jmp", std::make_pair(46, _RM)));

  // RR
  command_codes.insert(std::make_pair("mov", std::make_pair(24, _RR)));
  command_codes.insert(std::make_pair("mul", std::make_pair(6, _RR)));

  return command_codes;

}
