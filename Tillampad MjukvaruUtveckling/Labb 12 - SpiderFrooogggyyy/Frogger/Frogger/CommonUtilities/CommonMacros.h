#ifndef COMMONMACROS_HEADER
#define COMMONMACROS_HEADER

#pragma warning(disable: 4005) //macro redefinition!

		#define MIN(a,b)  ((a) < (b) ? (a) : (b))
		#define MAX(a,b)  ((a) > (b) ? (a) : (b))

		#define SAFE_DELETE(ptr) if ((ptr) != NULL) { delete (ptr); (ptr) = NULL; } 
		#define SAFE_ARRAY_DELETE(ptr) if (ptr != NULL) { delete [] ptr; ptr = NULL; }        

#define RANDOM_FLOAT(aMin, aMax)	(static_cast<float>((rand() / (static_cast<float>(RAND_MAX) + 1.0)) * (aMax - aMin) + aMin))

#endif
