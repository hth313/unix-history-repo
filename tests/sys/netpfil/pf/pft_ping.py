#!/usr/local/bin/python2.7

import argparse
import scapy.all as sp
import sys
import threading

PAYLOAD_MAGIC = 0x42c0ffee

class Sniffer(threading.Thread):
	def __init__(self, recvif):
		threading.Thread.__init__(self)

		self._recvif = recvif

		self.start()

	def run(self):
		self.packets = sp.sniff(iface=self._recvif, timeout=3)

def check_ping_request(packet, dst_ip, args):
	"""
	Verify that the packet matches what we'd have sent
	"""
	ip = packet.getlayer(sp.IP)
	if not ip:
		return False
	if ip.dst != dst_ip:
		return False

	icmp = packet.getlayer(sp.ICMP)
	if not icmp:
		return False
	if sp.icmptypes[icmp.type] != 'echo-request':
		return False

	raw = packet.getlayer(sp.Raw)
	if not raw:
		return False
	if raw.load != str(PAYLOAD_MAGIC):
		return False

	# Wait to check expectations until we've established this is the packet we
	# sent.
	if args.expect_tos:
		if ip.tos != int(args.expect_tos[0]):
			print "Unexpected ToS value %d, expected %s" \
				% (ip.tos, args.expect_tos[0])
			return False


	return True

def ping(send_if, dst_ip, args):
	ether = sp.Ether()
	ip = sp.IP(dst=dst_ip)
	icmp = sp.ICMP(type='echo-request')
	raw = sp.Raw(PAYLOAD_MAGIC)

	if args.send_tos:
		ip.tos = int(args.send_tos[0])

	req = ether / ip / icmp / raw
	sp.sendp(req, iface=send_if, verbose=False)

def main():
	parser = argparse.ArgumentParser("pft_ping.py",
		description="Ping test tool")
	parser.add_argument('--sendif', nargs=1,
		required=True,
		help='The interface through which the packet(s) will be sent')
	parser.add_argument('--recvif', nargs=1,
		help='The interface on which to expect the ICMP echo response')
	parser.add_argument('--to', nargs=1,
		required=True,
		help='The destination IP address for the ICMP echo request')

	# Packet settings
	parser.add_argument('--send-tos', nargs=1,
		help='Set the ToS value for the transmitted packet')

	# Expectations
	parser.add_argument('--expect-tos', nargs=1,
		help='The expected ToS value in the received packet')

	args = parser.parse_args()

	sniffer = None
	if not args.recvif is None:
		sniffer = Sniffer(args.recvif[0])

	ping(args.sendif[0], args.to[0], args)

	if sniffer:
		sniffer.join()

		for packet in sniffer.packets:
			if check_ping_request(packet, args.to[0], args):
				sys.exit(0)

		# We did not get the packet we expected
		sys.exit(1)

if __name__ == '__main__':
	main()
