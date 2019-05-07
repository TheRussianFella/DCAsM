#include "parser.h"
#include <algorithm>
#include <cctype>
#include <locale>

#include <iostream>

// Utilities

// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

inline bool is_integer(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

   char * p;
   strtol(s.c_str(), &p, 10);

   return (*p == 0);
}

// Parser

Parser::Parser(const std::map<std::string, std::pair<u32, command_types>>& command_codes) {
  this->command_codes.insert(command_codes.begin(), command_codes.end());
};


u32 Parser::get_namings(const std::string& line, std::map<std::string, u32>& namings_map) {

  if ( is_integer(line ))
    return std::stoi(line);
  else {
    u32 val = namings_map[line];
    return val;
  }
}


u32 Parser::parse_line(const std::string& command_line, std::map<std::string, u32>& namings_map) {

  std::stringstream ss(command_line);
  std::string tmp;

  ss >> tmp; // Reading name of the command

  int label_idx = tmp.find(":");
  int comment_idx = tmp.find(";");

  label_idx = (label_idx == std::string::npos) ? 0 : label_idx + 1;
  comment_idx = (comment_idx == std::string::npos) ? tmp.size() : comment_idx - 1;

  tmp = tmp.substr(label_idx, comment_idx);
  
  // Checking if the line is a naming or an end statement
  if (!tmp.compare("end") || !tmp.size())
    return 0;

  if (tmp == "word")
    return 1;

  std::pair<u32, command_types> command_info = command_codes[tmp];


  u32 command_word = 0;

  command_word |= command_info.first;

  if ( command_word == 41 || command_word == 42 || ( command_word >= 46 && command_word <= 52) ) { // calli and different jumps
    ss >> tmp; // Read address
    u32 val = get_namings(tmp, namings_map);

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
    u32 val = get_namings(tmp, namings_map);

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
    u32 val = get_namings(tmp, namings_map);

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

  std::map<std::string, u32> namings_map;

  int cur_pos = 0;

  while(std::getline(code_file, line)) {
    if (line.find(":") != std::string::npos)
      namings_map.insert(std::make_pair( line.substr(0, line.size()-1), cur_pos ) );
    else
      cur_pos += 1;
  }

  // Parsing code istelf

  std::ifstream file(file_path);

  u32 parsed_line;
  while( std::getline(file, line) ) {

    trim(line);
    parsed_line = this->parse_line(line, namings_map);

    if ( parsed_line )
      commands.push_back(parsed_line);

  }


  // Add starting point

  commands.insert(commands.begin(), namings_map["main"]);

  return commands;
}
