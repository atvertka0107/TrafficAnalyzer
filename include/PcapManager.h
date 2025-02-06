#ifndef PcapManager_h
#define PcapManager_h
#include <string>
#include "FlowProcessor.h"

class PcapManager {
public: 
	static void process(const std::string &filename, FlowProcessor &processor);
};

#endif