#pragma once
#define DEBUG_MODE 0

#if DEBUG_MODE
#define DEBUG(x) x
#define DEBUG_CERR(x) (std::cerr << __FILE__ << " " << __FUNCTION__ << ":" << __LINE__ << " " << (x) << std::endl)
#else 
#define DEBUG(x)
#define DEBUG_CERR(x)
#endif

