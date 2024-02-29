#include "header.hpp"

/*
	USAGE:

	run the porgram - will be a server
	open other terminal and execute this "telnet localhost 54000 - will be a client"
*/

/*The plan:
1 - Create Socket
2 - Bind the socket to a IP /port
3 - Mark the socket for listening in
4 - Accept a call
5 - Close the listening socket
6 - While recieving - deplay messag, echo message
7 - Close socket
*/

int main() {
	// Create Socket
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	// std::cout << listening -> 3 - like open();
	if (listening == -1) {
		std::cerr << "Can't create a socket" << std::endl;
		return -1;
	}

	// Bind the socket to a IP /port
    sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	// The same -> hint.sin_addr.s_addr = inet_addr("0.0.0.0");
	if (inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr) == -1) {
		std::cerr << "inet_pton failed" << std::endl;
		return -1;
	}
	memset(&(hint.sin_zero), '\0', 8);

	int opt = 1;
	if (setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
		std::cerr << "setsockopt failed" << std::endl;
		return -2;
	}

	// Cast the sockaddr_in pointer to sockaddr pointer
	if(bind(listening, reinterpret_cast<sockaddr*>(&hint), sizeof(hint)) == -1) {
		std::cerr << "Can't bind to IP/port" << std::endl;
		return -2;
	}

	//Mark the socket for listening in
	if (listen(listening, SOMAXCONN) == -1) {
		std::cerr << "Can't listen" << std::endl;
		return -3;
	}

	//Accept a call
	int resp = multyClient(listening);
	return resp;
}

