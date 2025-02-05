#include <iostream>
#include <map>
#include <fstream>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

class Flow {
public:
	uint16_t src_port;
	uint16_t dst_port;
	std::string src_ip;
	std::string dst_ip;

	Flow() : src_port(0), dst_port(0) {}

	bool operator<(const Flow &other) const {
		if (src_ip != other.src_ip) return src_ip < other.src_ip;
		if (dst_ip != other.dst_ip) return dst_ip < other.dst_ip;
		if(src_port != other.src_port) return src_port < other.src_port;
		return dst_port < other.dst_port;
	}
};

class FlowStats {
public:
	uint32_t packet_count;
	uint32_t byte_count;	

	FlowStats() : packet_count(0), byte_count(0) {}
};

class FlowProcessor {
private: 
	std::map<Flow, FlowStats> flow_map;

public: 
	void process_flow(const struct pcap_pkthdr *pkthdr, const u_char *packet) {
		struct ip *ip_header = (struct ip *)(packet + 14);
		if(ip_header->ip_v != 4) return;

		Flow key;
		key.src_ip = inet_ntoa(ip_header->ip_src);
		key.dst_ip = inet_ntoa(ip_header->ip_dst);

		if (ip_header->ip_p == IPPROTO_TCP) {
			struct tcphdr *tcp_header = (struct tcphdr *)(packet + 14 + ip_header->ip_hl * 4);
			key.src_port = ntohs(tcp_header->th_sport);
			key.dst_port = ntohs(tcp_header->th_dport);
		} else if (ip_header->ip_p == IPPROTO_UDP) {
			struct udphdr *udp_header = (struct udphdr *)(packet + 14 + ip_header->ip_hl * 4);
			key.src_port = ntohs(udp_header->uh_sport);
			key.dst_port = ntohs(udp_header->uh_dport);
		} else {
			return;
		}

		FlowStats& stats = flow_map[key];
		stats.packet_count++;
		stats.byte_count += pkthdr->len;
	}

	const std::map<Flow, FlowStats>& get_flow_map() const {
		return flow_map;
	}
};

class CSVWriter {
public: 
	static void write_csv(const std::map<Flow, FlowStats> &flow_map, const std::string &filename) {
		std::ofstream csv_file(filename);
		csv_file << "Source IP,Destination IP,Source Port,Destination Port,Packet Count,Byte count\n";

		for (const auto &flow : flow_map) {
			csv_file << flow.first.src_ip << ','
			<< flow.first.dst_ip << ','
			<< flow.first.src_port << ','
			<< flow.first.dst_port << ','
			<< flow.second.packet_count << ','
			<< flow.second.byte_count << '\n';
		}
	}
};

class PcapManager {
public: 
	static void process(const std::string &filename, FlowProcessor &processor) {
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
};

class TrafficAnalyzer {
public: 
	void run(const std::string &pcap_file, const std::string &csv_file) {
		FlowProcessor processor;
		PcapManager::process(pcap_file, processor);
		CSVWriter::write_csv(processor.get_flow_map(), csv_file);
	}
};

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