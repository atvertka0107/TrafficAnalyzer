#ifndef CSVWriter_h
#define CSVWriter_h
#include "Flow.h"
#include "FlowStats.h"
#include <map>
#include <string>

class CSVWriter {
public: 
	static void write_csv(const std::map<Flow, FlowStats> &flow_map, const std::string &filename);
};

#endif