#pragma once

#include <map>

typedef unsigned int u32;

enum command_types {_RM, _RR, _RI};
enum sys_calls {EXIT=0, SCANINT=100, SCANDOUBLE=101, PRINTINT=102, PRINTDOUBLE = 103,
                GETCHAR=104, PUTCHAR=105};

std::map<std::string, std::pair<u32, command_types>> get_command_table();
