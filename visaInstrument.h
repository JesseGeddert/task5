#ifndef __VISAINST_H
#define __VISAINST_H

class VisaInstrument
{
protected:
	ViStatus status;
	ViSession defaultRM;
	ViSession instr;
	ViFindList fList;
	ViUInt32 numInst;
	ViChar desc[VI_FIND_BUFLEN];
	ViChar resultBuffer[256];
	ViUInt32 resultCount;

public:
	ViStatus Initialize(char*);
	void idn();
	ViStatus getViStatus();
};

#endif
