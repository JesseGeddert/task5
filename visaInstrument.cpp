#include <stdio.h>
#include <stdlib.h>
#include <visa.h>
#include <windows.h>
#include <VisaInstrument.h>

ViStatus VisaInstrument::Initialize(char* name)
{
	status=viOpenDefaultRM(&defaultRM);

	if(status != VI_SUCCESS) return EXIT_FAILURE;

	status=viFindRsrc(defaultRM, name, &fList, &numInst, desc);

	status=viOpen(defaultRM, desc, VI_NULL, VI_NULL, &instr);
	_sleep(2000);

	if(status != VI_SUCCESS) return EXIT_FAILURE;
	_sleep(2000);
	status=viWrite(instr, (unsigned char*)"*IDN?", 6, VI_NULL);
	if(status != VI_SUCCESS) return EXIT_FAILURE;
	_sleep(2000);
	status=viRead(instr, (unsigned char*)resultBuffer, 256, &resultCount);
	if(status != VI_SUCCESS) return EXIT_FAILURE;
	_sleep(2000);
	return VI_SUCCESS;
}

ViStatus VisaInstrument::getViStatus()
{
	return status;
}