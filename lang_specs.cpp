#include "lang_specs.h"

int get_command_table(std::map<std::string, std::pair<u32, command_types>>& command_codes) {

  // RI
  command_codes.insert(std::make_pair("addi", std::make_pair(3, _RI)));
  command_codes.insert(std::make_pair("subi", std::make_pair(5, _RI)));
  command_codes.insert(std::make_pair("muli", std::make_pair(7, _RI)));
  command_codes.insert(std::make_pair("divi", std::make_pair(9, _RI)));
  command_codes.insert(std::make_pair("ori", std::make_pair(20, _RI)));
  command_codes.insert(std::make_pair("syscall", std::make_pair(1, _RI)));
  command_codes.insert(std::make_pair("lc", std::make_pair(12, _RI)));
  command_codes.insert(std::make_pair("push", std::make_pair(38, _RI)));
  command_codes.insert(std::make_pair("pop", std::make_pair(39, _RI)));
  command_codes.insert(std::make_pair("cmpi", std::make_pair(44, _RI)));
  command_codes.insert(std::make_pair("shli", std::make_pair(14, _RI)));
  command_codes.insert(std::make_pair("shri", std::make_pair(16, _RI)));
  command_codes.insert(std::make_pair("andi", std::make_pair(18, _RI)));
  command_codes.insert(std::make_pair("ori", std::make_pair(20, _RI)));
  command_codes.insert(std::make_pair("xori", std::make_pair(22, _RI)));
  command_codes.insert(std::make_pair("not", std::make_pair(23, _RI)));


  // RM
  command_codes.insert(std::make_pair("jmp",  std::make_pair(46, _RM)));
  command_codes.insert(std::make_pair("jne",  std::make_pair(47, _RM)));
  command_codes.insert(std::make_pair("jeq",  std::make_pair(48, _RM)));
  command_codes.insert(std::make_pair("jle",  std::make_pair(49, _RM)));
  command_codes.insert(std::make_pair("jl",  std::make_pair(50, _RM)));
  command_codes.insert(std::make_pair("jge",  std::make_pair(51, _RM)));
  command_codes.insert(std::make_pair("jg",  std::make_pair(52, _RM)));
  command_codes.insert(std::make_pair("calli",std::make_pair(41, _RM)));
  command_codes.insert(std::make_pair("ret", std::make_pair(42, _RI)));

  // RR
  command_codes.insert(std::make_pair("mov", std::make_pair(24, _RR)));
  command_codes.insert(std::make_pair("mul", std::make_pair(6, _RR)));
  command_codes.insert(std::make_pair("div", std::make_pair(8, _RR)));
  command_codes.insert(std::make_pair("call", std::make_pair(40, _RR)));
  command_codes.insert(std::make_pair("loadr", std::make_pair(68, _RR)));
  command_codes.insert(std::make_pair("addd", std::make_pair(32, _RR)));
  command_codes.insert(std::make_pair("subd", std::make_pair(33, _RR)));
  command_codes.insert(std::make_pair("muld", std::make_pair(34, _RR)));
  command_codes.insert(std::make_pair("divd", std::make_pair(35, _RR)));
  command_codes.insert(std::make_pair("itod", std::make_pair(36, _RR)));
  command_codes.insert(std::make_pair("dtoi", std::make_pair(37, _RR)));
  command_codes.insert(std::make_pair("add", std::make_pair(2, _RR)));
  command_codes.insert(std::make_pair("sub", std::make_pair(4, _RR)));
  command_codes.insert(std::make_pair("call", std::make_pair(40, _RR)));
  command_codes.insert(std::make_pair("shl", std::make_pair(13, _RR)));
  command_codes.insert(std::make_pair("shr", std::make_pair(15, _RR)));
  command_codes.insert(std::make_pair("and", std::make_pair(17, _RR)));
  command_codes.insert(std::make_pair("or", std::make_pair(19, _RR)));
  command_codes.insert(std::make_pair("xor", std::make_pair(21, _RR)));
  command_codes.insert(std::make_pair("cmp", std::make_pair(43, _RR)));


  return 0;

}
