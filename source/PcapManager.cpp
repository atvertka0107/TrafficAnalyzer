#include "../include/PcapManager.h"
#include <pcap.h>
#include <stdexcept>

void PcapManager::process(const std::string &filename, FlowProcessor &processor){
    char errbuf[PCAP_ERRBUF_SIZE];
		pcap_t *handle = pcap_open_offline(filename.c_str(), errbuf);

		if (!handle) {
			throw std::runtime_error("Error opening pcap file: " + std::string(errbuf));
		}

		pcap_loop(handle, 0, [](u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
			FlowProcessor *processor = reinterpret_cast<FlowProcessor*>(user);
			processor->process_flow(pkthdr, packet);
		}, reinterpret_cast<u_char*>(&processor));

		pcap_close(handle);
}