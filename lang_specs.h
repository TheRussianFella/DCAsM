#pragma once

#include <map>

typedef unsigned int u32;

enum command_types {_RM, _RR, _RI};

std::map<std::string, std::pair<u32, command_types>> get_command_table();
