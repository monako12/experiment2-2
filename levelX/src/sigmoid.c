#include <math.h>
#include "parameter.h"

double sigmoid(double s);

double sigmoid(double s)
{
	double sm;
	
	sm=s;
	if(sm>SMAX)			return(MAX);
	else if(sm<SMIN)	return(MIN);
	else				return(1./(1.+exp(-sm)));
}
