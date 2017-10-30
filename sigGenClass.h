#include <VisaInstrument.h>

class SignalGenerator : public VisaInstrument
{

public:
	ViStatus setUnit(int);
	ViStatus generateSin(float, float, float, float);
	ViStatus sinSweep(float, float, float);
	ViStatus output(int);
};

