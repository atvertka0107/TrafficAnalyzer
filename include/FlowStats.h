#ifndef FlowStats_h
#define FlowStats_h
#include <stdint.h>

class FlowStats {
public:
	uint32_t packet_count;
	uint32_t byte_count;	

	FlowStats();
};

#endif