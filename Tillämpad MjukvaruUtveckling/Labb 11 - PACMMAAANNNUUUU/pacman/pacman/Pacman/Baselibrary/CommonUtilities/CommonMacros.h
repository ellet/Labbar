#ifndef COMMONMACROS_HEADER
#define COMMONMACROS_HEADER

namespace CommonUtilities
{
	namespace Macros
	{
		#define MIN(a,b)  ((a) < (b) ? (a) : (b))
		#define MAX(a,b)  ((a) > (b) ? (a) : (b))
		#ifndef SAFE_DELETE
		#define SAFE_DELETE(a) delete (a); a=NULL;
		#endif
		#ifndef SAFE_RELEASE
		#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
		#endif
	};
};

namespace CU = CommonUtilities;

#endif
