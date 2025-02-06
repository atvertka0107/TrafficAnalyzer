#ifndef Flow_h
#define Flow_h
#include <stdint.h>
#include <string>

class Flow {
public:
	uint16_t src_port;
	uint16_t dst_port;
	std::string src_ip;
	std::string dst_ip;

	Flow();

	bool operator<(const Flow &other) const;
};

#endif