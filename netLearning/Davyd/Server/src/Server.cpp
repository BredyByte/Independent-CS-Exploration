#include "Server.hpp"

const int MAX_CLIENTS = 100;
const int PORT = 8080;

Server::Server() {

}

Server::Server(Server const &src) {
	*this = src;
}

Server &Server::operator=(Server const &src) {
	(void)src;
	return *this;
}

Server::~Server() {

}

int getServerSocket() {
	int listening = socket(PF_INET, SOCK_STREAM, 0);
	if (listening == -1) {
		perror("Can't create a socket");
		_exit(1);
	}
	return listening;
}

void Server::_fillServerAddr() {
	_server_addr.sin_family = AF_INET;
	_server_addr.sin_port = htons(PORT);
	_server_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(_server_addr.sin_zero), '\0', 8);
}

void printServerInfo() {
	char hostName[1024];
    gethostname(hostName, 1024);
    std::cout << "Server started on " << hostName << std::endl;

	hostent* host = gethostbyname(hostName);
	if (host == NULL) {
		herror("gethostbyname");
		_exit(1);
	}

	std::cout << "IP Address: " << inet_ntoa(*(in_addr*)*host->h_addr_list) << std::endl;
}

void createNewpollfd(int some_socket, std::vector<pollfd> &_poll_fds) {
	pollfd listen_pollfd;
	listen_pollfd.fd = some_socket;
	listen_pollfd.events = POLLIN;
	_poll_fds.push_back(listen_pollfd);
}

std::string getErrorPage() {
	std::string page_html = "<!DOCTYPE html>"
					"<html lang=\"en\">"
					"<head>"
					"    <meta charset=\"UTF-8\">"
					"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
					"    <title>Error 404 Page</title>"
					"    <link rel=\"stylesheet\" href=\"./main.css\">"
					"</head>"
					"<body>"
					"    <h1>Error 404</h1>"
					"    <h2>Page not found</h2>"
					"    <a href=\"/\">Back</a>"
					"</body>"
					"</html>";
	return page_html;
}

std::string getIndexPage() {
	std::string page_html = "<!DOCTYPE html>"
					"<html lang=\"en\">"
					"<head>"
					"    <meta charset=\"UTF-8\">"
					"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
					"    <title>Index Page</title>"
					"    <link rel=\"stylesheet\" href=\"./main.css\">"
					"    <script src=\"./index.js\"></script>"
					"</head>"
					"<body>"
					"    <h1>🖕</h1>"
					"    <a href=\"/\">Back</a>"
					"</body>"
					"</html>";
	return page_html;

}

void Server::_startServerLoop() {
	createNewpollfd(_listen_sock, _poll_fds);

	while(1) {
		int ret = poll(reinterpret_cast<pollfd *>(&_poll_fds[0]), static_cast<unsigned int>(_poll_fds.size()), -1);
		if (ret == -1) {
			perror("poll failed");
			_exit(1);
		}

        std::vector<pollfd>::iterator it;
        std::vector<pollfd>::iterator end = _poll_fds.end();

		for (it = _poll_fds.begin(); it != end; it++) {
			if (it->revents & POLLIN) {
				if (it->fd == _listen_sock) {
					sockaddr_in client;
					socklen_t addr_size = sizeof(sockaddr_in);

					int client_sock = accept(_listen_sock, reinterpret_cast<sockaddr*>(&client), &addr_size);
					if (client_sock == -1) {
						perror("Can't accept client");
						continue;
					}
					if (_poll_fds.size()-1 < MAX_CLIENTS)
                    {
						createNewpollfd(client_sock, _poll_fds);
						std::cout << "New client connected" << std::endl;
					}
					else
					{
						std::cout << "Server is full" << std::endl;
						send(client_sock, "too many clients!!!", 20, 0);
						close(client_sock);
						continue;
                    }
				}
				else {
					char buffer[1024];
					int bytes = recv(it->fd, buffer, 1024, 0);
					if (bytes <= 0) {
						if (bytes == 0) {
							std::cout << "Client disconnected" << std::endl;
						}
						else {
							perror("Unable to read from socket");
						}
						std::cout << "Closing socket" << std::endl;
						close(it->fd);
						_poll_fds.erase(it);
					}
					else {
						std::istringstream request(buffer);
						std::string request_line;
						getline(request, request_line);

						std::istringstream iss(request_line);
						std::string method;
						std::string page;
						iss >> method >> page;

						std::string response;

						std::cout << "Received:___________\n " << buffer << std::endl;
						if (method == "GET") {
							if (page == "/") {
								std::string page_html = getIndexPage();

								std::stringstream ss;
								ss << page_html.size();

								response += "HTTP/1.1 200 OK\r\n";
								response += "Content-Type: text/html\r\n";
								response += "Content-Length: " + ss.str() + "\r\n";
								// to report and allow - Content-Security-Policy-Report-Only
								response += "Content-Security-Policy: default-src 'self'; script-src 'none'; style-src 'none'; report-uri /csp-violation-report-endpoint;\r\n";
								response += "Connection: close\r\n";
								response += "\r\n"; // End of headers
								response += page_html; // Message body

								send(it->fd, response.c_str(), response.size(), 0);
							}
							else if (page.find(".css") != std::string::npos) {
								std::string page_html = "a { color: red; background: black;} a:hover {color: black; background: red;}";

								std::stringstream ss;
								ss << page_html.size();

								response += "HTTP/1.1 200 OK\r\n";
								response += "Content-Type: text/css\r\n";
								response += "Content-Length: " + ss.str() + "\r\n";
								response += "Connection: close\r\n";
								response += "\r\n"; // End of headers
								response += page_html; // Message body

								send(it->fd, response.c_str(), response.size(), 0);
							}
							else if (page.find(".js") != std::string::npos) {
								std::string page_html = "console.log(\"Heelo World!!\")";

								std::stringstream ss;
								ss << page_html.size();

								response += "HTTP/1.1 200 OK\r\n";
								response += "Content-Type: text/javascript\r\n";
								response += "Content-Length: " + ss.str() + "\r\n";
								response += "Connection: close\r\n";
								response += "\r\n";
								response += page_html;

								send(it->fd, response.c_str(), response.size(), 0);
							}
							else {
								std::string page_html = getErrorPage();

								std::stringstream ss;
								ss << page_html.size();

								response += "HTTP/1.1 404 Not Found\r\n";
								response += "Content-Type: text/html\r\n";
								response += "Content-Length: " + ss.str() + "\r\n";
								response += "Connection: close\r\n";
								response += "\r\n"; // End of headers
								response += page_html; // Message body

								send(it->fd, response.c_str(), response.size(), 0);
							}
						}
						if (method == "POST") {
							// documentation -> https://developer.mozilla.org/en-US/docs/Web/HTTP/CSP
							if (page == "/csp-violation-report-endpoint") {
								time_t currentTime;
								struct tm *localTime;
								char timestamp[100];
								time(&currentTime); // Get the current time
								localTime = localtime(&currentTime); // Convert the current time to the local time
								strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localTime); // Format the timestamp

								std::string report = std::string("Timestamp: ") + timestamp + "\nCSP Violation Report:\n" + request_line; // Assuming request contains the violation report
								report += buffer; // Assuming request contains the violation report
								report += "\r\n";
								std::ofstream reportFile("csp_violation_report.txt", std::ios::app); // Open file in append mode
								reportFile << report << std::endl;
								reportFile.close();

								// Send a response back to the browser
								std::string response = "HTTP/1.1 202 OK\r\n";
								response += "Content-Type: text/plain\r\n";
								response += "Content-Length: 0\r\n";
								response += "Connection: close\r\n";
								response += "\r\n";
								send(it->fd, response.c_str(), response.size(), 0);
							}
						}
						memset(buffer, 0, 1024);
						std::cout << "Response:__________ \n" << response << std::endl;
					}
				}
			}
			else if (it->revents & POLLERR) {
				 if (it->fd == _listen_sock)
                {
                    perror("listen socket error");
                    _exit(1);
                }
                else
                {
					perror("client socket error");
					close(it->fd);
					_poll_fds.erase(it);
                }
			}
		}
	}
}

void Server::startServer() {
	// Create Socket
	_listen_sock = getServerSocket();
	_fillServerAddr();
	_poll_fds.reserve(MAX_CLIENTS);
	int yes = 1;
	if (setsockopt(_listen_sock, SOL_SOCKET, SO_REUSEADDR,  &yes, sizeof(int)) == -1) {
		perror("setsockopt failed");
    	_exit(-1);
	}

	if (setsockopt(_listen_sock, SOL_SOCKET, SO_BROADCAST,  &yes, sizeof(int)) == -1) {
		perror("setsockopt failed");
    	_exit(-1);
	}

	if(bind(_listen_sock, reinterpret_cast<sockaddr*>(&_server_addr), sizeof(_server_addr)) == -1) {
		perror("Can't bind to IP/port");
		_exit(-1);
	}

	if (listen(_listen_sock, SOMAXCONN) == -1) {
		perror("Can't listen");
		_exit (-1);
	}

	printServerInfo();

	_startServerLoop();
}
