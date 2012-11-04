//Copyright (C) 2012 Sean McNamara <smcnam@gmail.com>
//License is WTFPL: http://sam.zoy.org/wtfpl/

#include <unistd.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>

void main(int argc, char **argv)
{
	int _argc = argc+1;
	char **_argv = calloc(_argc, sizeof(char*));
	//NOTE: last element of _argv is always NULL due to calloc
	memcpy(_argv, argv, sizeof(char*) * argc);
	execv("/usr/lib/vmware/bin/vmware-vmx.real", _argv);
}
