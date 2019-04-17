#include <iostream>
#include <bitset>
#include <map>

#include "parser.h"
#include "lang_specs.h"
#include "processor.h"

int main() {

  std::map<std::string, std::pair<u32, command_types>> command_codes = get_command_table();

  Parser par(command_codes);
  std::vector<u32> program = par.parse_file("examples/sqr.asm");

  Processor proc;
  proc.load_program(program);

  while(! proc.exec() ) {}

  return 0;
}
