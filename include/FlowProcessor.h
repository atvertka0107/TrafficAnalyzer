#ifndef FlowProcessor_h
#define FlowProcessor_h
#include <map>
#include "Flow.h"
#include "FlowStats.h"
#include <pcap.h>

class FlowProcessor {
private: 
	std::map<Flow, FlowStats> flow_map;
public: 
	void process_flow(const struct pcap_pkthdr *pkthdr, const u_char *packet);
	const std::map<Flow, FlowStats>& get_flow_map() const;
};

#endif