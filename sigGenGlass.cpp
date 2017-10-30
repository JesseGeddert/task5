#include <stdio.h>
#include <stdlib.h>
#include <visa.h>
#include <windows.h>
#include <sigGenClass.h>

ViStatus SignalGenerator::setUnit(int option)
{
	if(option == 0)
	{
		status=viWrite(instr, (unsigned char*)"VOLT:UNIT VPP", 14, VI_NULL);
		_sleep(2000);
	}
	if(option == 1)
	{
		status=viWrite(instr, (unsigned char*)"VOLT:UNIT RMS", 14, VI_NULL);
		_sleep(2000);
	}
	if(option == 2)
	{
		status=viWrite(instr, (unsigned char*)"VOLT:UNIT DRM", 14, VI_NULL);
		_sleep(2000);
	}
	if(option<0 || option>2)	status = EXIT_FAILURE;

	return VI_SUCCESS;
}

ViStatus SignalGenerator::generateSin(float freq, float phase, float voltage, float dcOffset)
{
	char commandString[128];
	sprintf(commandString, "APPL:SIN %f, %f, %f", freq, voltage, dcOffset);
	status=viWrite(instr, (unsigned char*)commandString, sizeof commandString, VI_NULL);
	_sleep(2000);
	sprintf(commandString, "PHAS %f", phase);
	status=viWrite(instr, (unsigned char*)commandString, sizeof commandString, VI_NULL);
	_sleep(2000);
	//sprintf(commandString, "OUTP ON");
	//status=viWrite(instr, (unsigned char*)commandString, sizeof commandString, VI_NULL);
	//_sleep(2000);
  	return VI_SUCCESS;
}

ViStatus SignalGenerator::sinSweep(float startFreq, float endFreq, float sweepTime)
{
	char commandString[128];

	if(startFreq>endFreq)	status=EXIT_FAILURE;

	sprintf(commandString, "FUNC SIN");
	status=viWrite(instr, (unsigned char*)commandString, sizeof commandString, VI_NULL);
	_sleep(2000);
	sprintf(commandString, "SWE:STAT ON");
	status=viWrite(instr, (unsigned char*)commandString, sizeof commandString, VI_NULL);
	_sleep(2000);
	sprintf(commandString, "SWE:STAT LIN");
	status=viWrite(instr, (unsigned char*)commandString, sizeof commandString, VI_NULL);
	_sleep(2000);
	sprintf(commandString, "FREQ:STAR %f", startFreq);
	status=viWrite(instr, (unsigned char*)commandString, sizeof commandString, VI_NULL);
	_sleep(2000);
	sprintf(commandString, "FREQ:STOP %f", endFreq);
	status=viWrite(instr, (unsigned char*)commandString, sizeof commandString, VI_NULL);
	_sleep(2000);
	sprintf(commandString, "SWE:TIME %f", sweepTime);
	status=viWrite(instr, (unsigned char*)commandString, sizeof commandString, VI_NULL);
	_sleep(2000);
	sprintf(commandString, "TRIG:SOUR IMM", startFreq);
	status=viWrite(instr, (unsigned char*)commandString, sizeof commandString, VI_NULL);
	_sleep(2000);

	printf("Sweep initialized\n");
	fflush(stdout);

	return EXIT_SUCCESS;
}

ViStatus SignalGenerator::output(int outp)
{
	char commandString[128];

	if(outp == 0)
	{
		sprintf(commandString, "OUTP OFF");
		status=viWrite(instr, (unsigned char*)commandString, sizeof commandString, VI_NULL);
		_sleep(2000);
	}
	if(outp == 1)
	{
		sprintf(commandString, "OUTP ON");
		status=viWrite(instr, (unsigned char*)commandString, sizeof commandString, VI_NULL);
		_sleep(2000);
	}
	if(outp<0 || outp>1)	status = EXIT_FAILURE;
	return VI_SUCCESS;
}
