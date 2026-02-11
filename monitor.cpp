/*
Project Name: Local Area Network Monitoring System
Author      : Kshitij Ban, Niraj Mandal
Date        : 2-10-2026
Description : Low-level socket programming in C++
*/

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <cstdlib>
#include <string>
using namespace std;

string buf =
    "HTTP/1.1 200 OK\r\n"        // Status line
    "Content-Type: text/html\r\n" // Content type
    ;           // Body

int create_socket();
string msg(string);

int main() {
	
    int s_sock = create_socket();
   if (s_sock == -1)
   {
   	exit(EXIT_FAILURE);
   }
    // Accept client
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    int c_sock = accept(s_sock, (sockaddr*)&client_addr, &client_len);
    if (c_sock < 0) {
        perror("Client accept failed");
        close(s_sock);
        exit(EXIT_FAILURE);
    }

    cout << "Client connected from "
         << inet_ntoa(client_addr.sin_addr)
         << ":" << ntohs(client_addr.sin_port) << endl;
      string data = "<h1>Kshitij Ban, Niraj Mandal </h1>";
      buf = msg(data);
	if ( send(c_sock, buf.data(), buf.size(), 0)< 0)
	{
	cout<<"Not sent";
	}
    close(c_sock);
    close(s_sock);

    return 0;
}
int create_socket(){
 int s_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (s_sock < 0) {
        perror("Server socket creation failed");
        return -1;
    }
	int opt = 1;
if (setsockopt(s_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    perror("setsockopt failed");
    close(s_sock);
    exit(EXIT_FAILURE);
}

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9898);
    addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(s_sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Binding failed");
        close(s_sock);
        return -1;
    }

    // Listen
    if (listen(s_sock, 1) < 0) {
        perror("Listen failed");
        close(s_sock);
        return -1;
    }

    cout << "Server listening on port 9898\n";
	return s_sock;
}
string msg(string txt){
string temp = "<html> "+txt+"</html";
return  buf + "Content-Length: " + to_string(temp.size()) + "\r\n\r\n" + temp ;
}
