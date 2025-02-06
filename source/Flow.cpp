#include "../include/Flow.h"

Flow::Flow() : src_port(0), dst_port(0) {}

bool Flow::operator<(const Flow &other) const {
    if (src_ip != other.src_ip) return src_ip < other.src_ip;
    if (dst_ip != other.dst_ip) return dst_ip < other.dst_ip;
    if(src_port != other.src_port) return src_port < other.src_port;
    return dst_port < other.dst_port;
}