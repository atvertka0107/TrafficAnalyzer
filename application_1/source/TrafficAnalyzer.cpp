#include "../include/TrafficAnayzer.h"
#include "../include/FlowProcessor.h"
#include "../include/PcapManager.h"
#include "../include/CSVWriter.h"

void TrafficAnalyzer::run(const std::string &pcap_file, const std::string &csv_file) {
    FlowProcessor processor;
    PcapManager::process(pcap_file, processor);
    CSVWriter::write_csv(processor.get_flow_map(), csv_file);
}