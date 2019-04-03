#include "parser.h"


Parser::Parser(const std::map<std::string, std::pair<u32, command_types>>& command_codes) {
  this->command_codes.insert(command_codes.begin(), command_codes.end());
};


u32 Parser::parse_line(const std::string& command_line) {

  std::stringstream ss(command_line);
  std::string tmp;

  ss >> tmp; // Reading name of the command
  std::pair<u32, command_types> command_info = command_codes[tmp];


  u32 command_word = 0;

  command_word |= command_info.first;


  if ( command_info.second == _RM || command_info.second == _RI) {

    ss >> tmp;
    u32 reg = std::stoi( tmp.substr(1) );

    command_word = command_word << 4;
    command_word |= reg;

    ss >> tmp;
    u32 val = std::stoi( tmp );

    command_word = command_word << 20;
    command_word |= val&1048575; // Take only last 20 bits

  } else if (command_info.second == _RR) {

    for (int i = 0; i < 2; ++i) {
      ss >> tmp;
      u32 reg = std::stoi( tmp.substr(1) );

      command_word = command_word << 4;
      command_word |= reg;
    }

    ss >> tmp;
    u32 val = std::stoi( tmp );

    command_word = command_word << 16;
    command_word |= val&65535; // Take only last 20 bits
}

  return command_word;
}


std::vector<u32> Parser::parse_file(const std::string& file_path) {

  std::vector<u32> commands;

  std::ifstream code_file(file_path);

  std::string line;

  while( std::getline(code_file, line) ) {
    commands.push_back( this->parse_line(line) );
  }

  return commands;
}
