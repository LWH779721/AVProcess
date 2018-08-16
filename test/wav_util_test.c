#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "wav/wav_util.h"

int main(int argc, char **args)
{
	wav_info_dump(args[1]);
	
	return 0;
}