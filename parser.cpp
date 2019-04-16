#include "parser.h"

Parser::Parser(const std::map<std::string, std::pair<u32, command_types>>& command_codes) {
  this->command_codes.insert(command_codes.begin(), command_codes.end());
};

int Parser::insert_namings(std::string& line, const std::map<std::string, int>& namings_map) {

  size_t pos;

  for (auto it = namings_map.begin(); it != namings_map.end(); ++it) {
    pos = line.find(it->first);
    if (pos != std::string::npos)
      line.replace(pos, it->first.size(), it->first);
  }

  return 0;
}

u32 Parser::parse_line(const std::string& command_line, const std::map<std::string, int>& namings_map) {

  std::stringstream ss(command_line);
  std::string tmp;

  ss >> tmp; // Reading name of the command

  // Checking if the line is a naming or an end statement
  if (tmp.find(":") != std::string::npos || tmp.compare("end"))
    return 0;

  std::pair<u32, command_types> command_info = command_codes[tmp];


  u32 command_word = 0;

  command_word |= command_info.first;

  if ( command_word == 41 || ( command_word >= 46 && command_word <= 52) ) { // calli and different jumps
    ss >> tmp; // Read address
    insert_namings(tmp, namings_map);
    u32 val = std::stoi( tmp );

    command_word = command_word << 24;
    command_word |= val&1048575;

    return command_word;
  }


  if ( command_info.second == _RM || command_info.second == _RI) {

    ss >> tmp;
    u32 reg = std::stoi( tmp.substr(1) );

    command_word = command_word << 4;
    command_word |= reg;

    ss >> tmp;
    insert_namings(tmp, namings_map);
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
    insert_namings(tmp, namings_map);
    u32 val = std::stoi( tmp );

    command_word = command_word << 16;
    command_word |= val&65535; // Take only last 16 bits
}

  return command_word;
}


std::vector<u32> Parser::parse_file(const std::string& file_path) {

  std::vector<u32> commands;

  // Parsing namings

  std::ifstream code_file(file_path);
  std::string line;

  std::map<std::string, int> namings_map;

  int cur_pos = 0;

  while(std::getline(code_file, line)) {
    if (line.find(":") != std::string::npos)
      namings_map.insert(std::make_pair( line.substr(0, line.size()-1), cur_pos ) );
    else
      cur_pos += 1;
  }

  // Parsing code istelf

  u32 parsed_line;
  while( std::getline(code_file, line) ) {

    parsed_line = this->parse_line(line, namings_map);

    if ( parsed_line )
      commands.push_back(parsed_line);

  }

  return commands;
}
