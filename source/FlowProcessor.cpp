#include "../include/FlowProcessor.h"
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

void FlowProcessor::process_flow(const struct pcap_pkthdr *pkthdr, const u_char *packet) {
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

const std::map<Flow, FlowStats>& FlowProcessor::get_flow_map() const {
    return flow_map;
}