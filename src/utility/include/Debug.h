#pragma once
#define DEBUG_MODE 1

#if DEBUG_MODE
#define DEBUG(x) x
#define DEBUG_CERR(x) (std::cerr << __FILE__ << " " << __PRETTY_FUNCTION__ << ":" << __LINE__ << " " << (x) << std::endl)
#else 
#define DEBUG(x)
#define DEBUG_CERR(x)
#endif

