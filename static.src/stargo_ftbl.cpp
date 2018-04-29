#include "vsopenapi.h"

extern "C" SRPDLLEXPORT void *StarGo_GetFunctionTbl_FromContol(class ClassOfSRPControlInterface *SRPControl)
{
	return SRPControl -> GetCFunctionTable();
}
