#include <iostream>
#include <bitset>
#include <map>

#include "parser.h"
#include "lang_specs.h"

int main() {

  std::map<std::string, std::pair<u32, command_types>> command_codes = get_command_table();

  Parser par(command_codes);

  std::vector<u32> program = par.parse_file("prog.asm");

  return 0;
}
