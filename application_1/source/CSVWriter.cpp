#include "../include/CSVWriter.h"
#include <fstream>

void CSVWriter::write_csv(const std::map<Flow, FlowStats> &flow_map, const std::string &filename) {
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