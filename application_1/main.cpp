#include <iostream>
#include "include/TrafficAnayzer.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <pcap file> <output csv file>" << std::endl;
		return 1;
	}
	try {
		TrafficAnalyzer analyzer;
		analyzer.run(argv[1], argv[2]);
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}