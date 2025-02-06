#ifndef TrafficAnalyzer_h
#define TrafficAnalyzer_h
#include <string>

class TrafficAnalyzer {
public: 
	void run(const std::string &pcap_file, const std::string &csv_file);
};

#endif