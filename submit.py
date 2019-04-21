s_ = """#include<map>\n#include<vector>\n
	#include<cstring>\n#include<iostream>\n
	#include<climits>\n#include<sstream>\n
	#include<fstream>\n#include<algorithm>\n#define NUM_REGISTERS 14\n
	#define MEMORY_SIZE 1048575"""
s = ""
files = ['lang_specs.h', 'lang_specs.cpp', 'parser.h',
'parser.cpp', 'processor.h', 'processor.cpp',
'main.cpp']

for f_name in files:
	with open(f_name, 'r') as f:
		d = f.read()
		s += d

s = list(filter(lambda x: '#' not in x, s.split("\n")))

with open('subm.cpp', 'w+') as f:
	f.write("\n".join(s_.split("\n")+s))
