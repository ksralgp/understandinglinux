# Internet Protocol Suite
## Protocols
A communication protocol is a system of rules that allows two or more entities in a communication system to transmit information. The protocol defines the rules, syntax, semantics and synchronization of communication and possible error recovery methods. Protocols may be implemented by hardware, software, or a combination of both.

Complex communication protocols are often designed as a set of simpler cooperating protocols. This is called a protocol suite. A protocol suite is often implemented as a layering of protocols. Each protocol in this stack of layers accomplishes a specific part of the communication and interacts with the others layers in a limited fashion. 

The Internet Protocol suite is used for communication over the Internet. This suite of protocols is commonly referred as TCP/IP.
## Architectural Assumption of the TCP/IP
TCP/IP is based around the architecture of the interent:
* Hosts are the consumers of communication on the internet
* Multiple hosts can be connected together onto a network and communicate with each other using the Internet Protocol suite
* Multiple networks can be connected together using computers called IP routers or IP gateways. These routers facilitate communication between hosts on different networks. These two hosts use the internet protocol in the same way two hosts on the same network would.

## The Internet Protocol Suite: TCP/IP
A host needs to implement TCP/IP to communicate on the Internet. TCP/IP is structured as a protocol stack with four abstract layers. Multiple protocol choices might be available at a layer. All of the protocol choices for a layer adhere to a set of underlying requirements for that layer.

Layer | Description | Supported Protocols
----- | ----------- | -----------------
Application Layer | Responsible for encoding/decoding the intended message between applications running on hosts communicating over the internet | HTTP, SSH, DNS, etc.
Transport Layer | Responsible for the channel over which data is sent between applications running on hosts communicating over the internet | TCP, UDP
Internet Layer | Responsible for routing data from a source host to a destination host | Internet Protocol (IP)
Link Layer | Responsible for routing data on the network the host is physically connected to | Ethernet, WLAN

Beyond hosts, IP routers are a critical architectural assumption of TCP/IP. They facilitiate the flow of infromation across networks. An IP router only needs to implement the lowest two layers of TCP/IP: Link Layer and Internet Layer. Given that an IP routers purpose is different than that of a host, its requirements per the Internet protocol are different than that of a host.

## Internet Protocol (IP)
The internet protocol is central to TCP/IP. It is directly concerned with sending data between hosts. The key concepts behind IP are

Concept | Description
------- | -----------
IP Address | A host has an identifying address called an IP address. The format of this address depends on the IP version being used. Note that things get a little more complicated with private networks (LANs)
IP Packet | The unit of data handled by IP. <br><br> During transmission IP builds an IP packet from data provided by the transport layer. Its primary role is to create a header with information about the sending IP address, destination IP address, and general information about the data payload. This packet is passed to the link layer for transmission over the network. <br><br>During receiving, IP is responsible for determining if a packet is intended for this host. If it is, it then strips the IP packet header and passes the payload to the appropriate transmission protocol.
Routing | Routing is the process of selecting the next location that an IP packet should be sent. This next location is either another host on the same network or an IP Router/Gateway on the same network. The route is encoded as an IP address on the host's network and the Link Layer is instructed to send the IP packet to this location. <br><br>It is important to distinguish the destination IP of an IP packet from an IP packet's route. While both are IP addresses, the route determines the next location the packet should be sent. The destination determines the final location (host) a packet is intended for. Additionally, only the destination IP is encoded in the IP packet. TCP/IP relies on the link layer to send an IP packet to its intended route.

## ARP: Requirement on the Link Layer
Todo

## User Datagram Protocol (UDP)
UDP is a connectionless transport layer protocol. A UDP message has an associated source and destination port number. These port numbers determine how data is routed from the transport layer to the application layer. The source port also provides an address to repsond to in the abscence of any other information. The unit of information transmitted over UDP is called a datagram and consists of:
* Source Port
* Destination Port
* Length: Size of header + Application Data
* Checksum
* Application Data (payload)

## Transmission Control Protocol (TCP)
TCP is connection-oriented, end-to-end reliable transport layer protocol. Like UDP, a message in TCP has an associated source and destination port number. The unit of information transmitted over TCP is called a segment and consists of:
* Source Port
* Destination Port
* Sequence Number
* Acknowledgement Number
* Data offset
* Flags
* Window Size
* Checksum
* Application Data (payload)

The additional header fields in comparison to UDP are needed to implement the additional features of TCP like an established connection and reliable transport.

## Data Encapsulation
For transmission, data and control/routing information (TCP port, destination IP, next hop IP,etc) flows down the layers of TCP/IP
<pre>
Application : [Application Data]
Transport   : [[Transport Header][Application Data]] --> [Transport Data]
Internet    : [[Internet Header][Transport Data]] --> [Internet Data]
Link        : [[Link Header][Internet Data]] --> [Link Data]
</pre>
At each layer, the control/routing information is used to re-package data from the upper layer with a protocol specific header.

Receiving data flows up the set of layers. At each layer, the protocol header determines where the data is routed. As data moves upward the header associated with the lower part of the stack is stripped from the datagram. Note the stripping is conceptual, as certain parts of lower level headers info, like IP addresses, needs to flow upward.

# References 
https://docs.oracle.com/cd/E19455-01/806-0916/6ja85398m/index.html

https://man7.org/linux/man-pages/man7/tcp.7.html

https://man7.org/linux/man-pages/man7/ip.7.html

https://en.wikipedia.org/wiki/Internet_protocol_suite

https://en.wikipedia.org/wiki/Communication_protocol

https://datatracker.ietf.org/doc/html/rfc1122

https://datatracker.ietf.org/doc/html/rfc1180

https://datatracker.ietf.org/doc/html/rfc791

https://en.wikipedia.org/wiki/IPv4

https://en.wikipedia.org/wiki/IP_routing

https://datatracker.ietf.org/doc/html/rfc768

https://en.wikipedia.org/wiki/User_Datagram_Protocol

https://datatracker.ietf.org/doc/html/rfc761

http://www.cs.toronto.edu/~ahchinaei/teaching/2016jan/csc358/Lecture05-1p.pdf
