#!/usr/bin/python3
from collections import defaultdict
import csv
import argparse

def main() -> None: 
    parser = argparse.ArgumentParser(
        prog='application_2.py', 
        description='Process network traffic statistics.',
        usage='python application_2.py <input_file.csv> <output_file.csv>')
    
    parser.add_argument('input_file', help='PATH to the input CSV file')
    parser.add_argument('output_file', help='PATH to the output CSV file')
    args = parser.parse_args()

    input_file = args.input_file
    output_file = args.output_file
    ip_stats = defaultdict(lambda : {'packets_sent': 0, 'packets_received': 0, 'bytes_sent': 0, 'bytes_received': 0})

    try:
        with open(input_file, 'r') as file:
            reader = csv.reader(file)
            next(reader)
            for row in reader:
                if len(row) != 6:
                    print(f"Skipping invalid row: {row}")
                    continue
                ip_src, ip_dst, *ports, packet_count, byte_count = row
                try:
                    packets = int(packet_count)
                    bytes = int(byte_count)
                except ValueError:
                    print(f"Skipping invalid row (non-numeric values): {row}")
                    continue

                ip_stats[ip_src]['packets_sent'] += packets
                ip_stats[ip_src]['bytes_sent'] += bytes
                ip_stats[ip_dst]['packets_received'] += packets
                ip_stats[ip_dst]['bytes_received'] += bytes

    except FileNotFoundError:
        print(f"Error: Input file '{input_file}' not found.")
        exit(1)

    except IOError as e:
        print(f"Error reading input file: {e}")
        exit(1)

    try:    
        with open(output_file, 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(['IP Address', 'Packets Sent', 'Packets Received', 'Bytes Sent', 'Bytes Received'])

            for ip, stats in ip_stats.items():
                writer.writerow([ip, stats['packets_sent'], stats['packets_received'], stats['bytes_sent'], stats['bytes_received']])

    except IOError as e:
        print(f"Error writing to output file: {e}")
        exit(1)


if __name__ == '__main__':
    main()
