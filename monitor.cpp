/*
Project Name: Local Area Network Monitoring System
Author      : Kshitij Ban, Niraj Mandal
Date        : 2-10-2026
Description : Low-level socket programming in C++
*/

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <cstdlib>
#include <string>
#include <fcntl.h>
#include <cerrno>
using namespace std;

// Global HTTP header template
string buf =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n";

bool handel_browser(string);
int poke_ip(string);
int create_socket(int type);
bool bind_socket(int socket_fd, sockaddr_in addr);
bool start_listening(int socket_fd, int backlog = 5);
string build_response(const string &txt);
string get_lan_ip();
string get_base_ip(string );
int main() {
    string ip = get_lan_ip();
    cout << "Server LAN IP: " << ip << endl;
    string base_ip = get_base_ip(ip);
    string list;
    for (int i=1 ; i<=255; i++){
        string tmp_ip = base_ip + to_string(i);
        cout<<"Poking IP: "<<tmp_ip<<endl;
        int status = poke_ip(tmp_ip);

        if (status == -1) {
            cout << "Socket Failed\n";
        }
        else if (status == -2) {
            cout << "IP error\n";
        }
        else if (status == 0) {
            cout << "Host Down\n";
        }
        else {
            cout << "Host UP\n";
            list += "<h2>"+tmp_ip + " is up</h2>";
        }

    }
	if(!handel_browser(list)){
        perror("Frontend->Backend Connection status: Failed");
        exit(EXIT_FAILURE);
    }
   
    return 0;
}
int poke_ip(string ip) {
	int port = 443;
    int c_sock = create_socket(SOCK_STREAM);
    if (c_sock == -1) {
        return -1;
    }

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    setsockopt(c_sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&tv, sizeof(tv));

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
        close(c_sock);
        return -2;
    }

    if (connect(c_sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(c_sock);
        return 0;   
    }

    close(c_sock);
    return 1;      
}

// Create a socket
int create_socket(int type) {
    int s_sock = socket(AF_INET, type, 0);
    if (s_sock < 0) {
        perror("Socket creation failed");
        return -1;
    }
    return s_sock;
}

// Bind socket to address
bool bind_socket(int socket_fd, sockaddr_in addr) {
    if (bind(socket_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Binding failed");
        close(socket_fd);
        return false;
    }
    return true;
}

// Start listening
bool start_listening(int socket_fd, int backlog) {
    if (listen(socket_fd, backlog) < 0) {
        perror("Listen failed");
        close(socket_fd);
        return false;
    }
    cout << "Server listening on port 9898\n";
    return true;
}

// Build HTTP response
string build_response(const string &txt) {
    string body = "<html>" + txt + "</html>";
    return buf + "Content-Length: " + to_string(body.size()) + "\r\n\r\n" + body;
}

// Get LAN IP of machine
string get_lan_ip() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("UDP socket creation failed");
        return "0.0.0.0";
    }

    sockaddr_in remote{};
    remote.sin_family = AF_INET;
    remote.sin_port = htons(53);  // arbitrary port
    inet_pton(AF_INET, "8.8.8.8", &remote.sin_addr);

    connect(sock, (sockaddr*)&remote, sizeof(remote));

    sockaddr_in local{};
    socklen_t len = sizeof(local);
    getsockname(sock, (sockaddr*)&local, &len);

    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &local.sin_addr, ip, sizeof(ip));

    close(sock);
    return string(ip);
}

string get_base_ip(string ip){
     size_t pos = ip.rfind('.');
    return ip.substr(0, pos + 1); 
}

bool handel_browser(string list){
 int s_sock = create_socket(SOCK_STREAM);
    if (s_sock == -1) {
       return false;
    }

    int opt = 1;
    if (setsockopt(s_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(s_sock);
       return false;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9898);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (!bind_socket(s_sock, addr)) {
        return false;
    }

    if (!start_listening(s_sock)) {
       return false;
    }

    
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    int c_sock = accept(s_sock, (sockaddr*)&client_addr, &client_len);
    if (c_sock < 0) {
        perror("Client accept failed");
        close(s_sock);
        return false;
    }

    cout << "Client connected from "
         << inet_ntoa(client_addr.sin_addr)
         << ":" << ntohs(client_addr.sin_port) << endl;

   string data = "<h1 style = ' text-align: center;'>LAN MONITORING TOOL</h1>" + list;

    string response = build_response(data);

    if (send(c_sock, response.data(), response.size(), 0) < 0) {
        cout << "Send failed" << endl;
    }

    close(c_sock);
    close(s_sock);
    return true;
}
