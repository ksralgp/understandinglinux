# SSH
## Intro
Secure Shell (SSH) is a protocol for secure remote login and other secure network services over an insecure network. SSH provides a secure channel over an unsecured network by using a client–server architecture, connecting an SSH client application with an SSH server.[2] The protocol specification distinguishes between two major versions, referred to as SSH-1 and SSH-2.

SSH uses public-key cryptography to authenticate the remote computer and allow it to authenticate the user.

## SSH Protocal Overview
The SSH2 protocal consists of 3 main components:
* Transport Layer Protocal - provides server authentication, confidentiality, and integrity
* User Authentication Protocal - Authenticates the client-side user to the server. It runs over the transport layer protocal
* Connection Protocal - Multiplexes the encrypted encrypted tunnel into several logical channels. It runs over the user authentication protocal

The client sends a service request once a secure transport layer connection has been established.  A second service request is sent after user authentication is complete.  This allows new protocols to be defined and coexist with the protocols listed above.

The connection protocol provides channels that can be used for a wide range of purposes.  Standard methods are provided for setting up secure interactive shell sessions and for forwarding ("tunneling") arbitrary TCP/IP ports and X11 connections.

## Transport Layer Protocal
The SSH transport layer is a secure, low level transport protocol. It provides strong encryption, cryptographic host authentication, and integrity protection. Authentication in this protocol level is host-based; this protocol does not perform user authentication.

### Connection Setup
SSH works over any 8-bit clean, binary-transparent transport.  The underlying transport SHOULD protect against transmission errors, as such errors cause the SSH connection to terminate. When used over TCP/IP, the server normally listens for connections on port 22.  This port number has been registered with the IANA, and has been officially assigned for SSH.

### Key Exchange
When the connection has been established, both sides MUST send an identification string. Key exchange will begin immediately after sending this identifier. Key exchange (kex) begins by each side sending name-lists of supported algorithms. After this message, the key exchange algorithm is run. The key exchange produces two values: a shared secret K, and an exchange hash H.  Encryption and authentication keys are derived from these. The exchange hash H from the first key exchange is additionally used as the session identifier, which is a unique identifier for this connection. After key exchange completes future communication uses the keys and algorithms generated in the key exchange.

The key exchange method specifies how one-time session keys are generated for encryption and for authentication, and how the server authentication is done. A key exchange method uses explicit server authentication if the key exchange messages include a signature or other proof of the server's authenticity.  A key exchange method uses implicit server authentication if, in order to prove its authenticity, the server also has to prove that it knows the shared secret, K, by sending a message and a corresponding MAC (message authentication code) that the client can verify. The key exchange methods have been defined to work with a public key.

Security is based on the client knowing and trusting the server's public key a-priori and checking it against the public key provided during server authentication. This protocol makes no assumptions or provisions for an infrastructure or means for distributing the public keys of hosts. It is expected that this protocol will sometimes be used without first verifying the association between the server host key and the server host name.  Such usage is vulnerable to man-in-the-middle attacks.

### Service Request
After the key exchange the client requests a services IE 'ssh-userauth'.

## SSH User Authentication Protocal
User Authentication methods:
* publickey - The user authenticates by showing knowledge of a private key. In advance on the server a (public-key, private-key) pair is generated and the user holds the private key.
* password - The user sends a message with their password. This message (and the password within it) is encrypted based on the transport layer protocal setup by the key exchange
* hostbased -
* none

## SSH Connection Protocal
This protocal provides interactive login sessions, remote execution of commands, forwarded TCP/IP connections, and forwarded X11 connections. Security is not explicitly provided in this protocal as that is assumed to be setup via the Transport Layer Protocal and the User Authentication Protocal.

### Channel Mechanism
All terminal sessions, forwarded connections, etc., are channels. Either side may open a channel. Multiple channels are multiplexed into a single connection.

A session is a remote execution of a program.  The program may be a shell, an application, a system command, or some built-in subsystem. It may or may not have a tty, and may or may not involve X11 forwarding.  Multiple sessions can be active simultaneously. A pty (psuedo terminal) can be allocated for a session along with X11 forwarding. Once the session has been set up, a program is started at the remote end.  The program can be an interactive shell, a command to run, or a subsystem with a host-independent name. The subsystem session is used for things like file-transfer.

## Dictionary
Authentication - Proving identity

## Resources
https://tools.ietf.org/html/rfc4251

https://tools.ietf.org/html/rfc4253

https://en.wikipedia.org/wiki/Secure_Shell
