#define _WIN32_WINNT 0x0600
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main(int argc, char* argv[]) {
    SOCKET serverSocket = INVALID_SOCKET, acceptSocket = INVALID_SOCKET;
    int port = 55555;

    WSADATA wsaData{};
    WORD wversionReq = MAKEWORD(2, 2);
    int wsaerr;

    cout << "==== SERVER ====" << endl;
    cout << "Step 1 - Set up DLL" << endl;
    wsaerr = WSAStartup(wversionReq, &wsaData);
    if (wsaerr == 0) {
        cout << "The Winsock dll found!" << endl;
        cout << "The status: " << wsaData.szSystemStatus << endl;
    } else {
        cout << "Winsock dll not found" << endl;
        return 1;
    }

    cout << "Step 2 - Set up Server Socket" << endl;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Error at socket() " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    } else {
        cout << "socket() is OK!" << endl;
    }

    // Optional: quick rebind during dev
    BOOL yes = TRUE;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&yes, sizeof(yes));

    cout << "Step 3 - Bind Socket" << endl;
    sockaddr_in service{};
    service.sin_family = AF_INET;
    service.sin_port = htons(port);
    service.sin_addr.s_addr = htonl(INADDR_ANY); // listen on all interfaces
    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "bind() failed with error " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    } else {
        cout << "bind() is OK!" << endl;
    }

    cout << "Step 4 - Initiate Listen" << endl;
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "listen() failed with error " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    } else {
        cout << "listen() is OK, I'm waiting for connections..." << endl;
    }

    cout << "Step 5 - Accept Connection from Client" << endl;
    sockaddr_in clientService{};
    int clientServiceSize = sizeof(clientService);
    acceptSocket = accept(serverSocket, (SOCKADDR*)&clientService, &clientServiceSize);
    if (acceptSocket == INVALID_SOCKET) {
        cout << "accept() failed with error " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    } else {
        char ipstr[INET_ADDRSTRLEN]{};
        inet_ntop(AF_INET, &clientService.sin_addr, ipstr, sizeof(ipstr));
        cout << "accept() is OK! Client: " << ipstr << ":" << ntohs(clientService.sin_port) << endl;
    }

    cout << "Step 6 - Receive Data from Client" << endl;
    char recvBuffer[512];
    while (true) {
        int bytesReceived = recv(acceptSocket, recvBuffer, sizeof(recvBuffer) - 1, 0);
        if (bytesReceived > 0) {
            recvBuffer[bytesReceived] = '\0';
            cout << "Received message from client: " << recvBuffer << endl;
        } else if (bytesReceived == 0) {
            cout << "Connection closed by client." << endl;
            break;
        } else {
            cout << "recv() failed with error " << WSAGetLastError() << endl;
            break;
        }
    }

    cout << "Step 7 - Close Socket and Cleanup" << endl;
    closesocket(acceptSocket);
    closesocket(serverSocket);
    WSACleanup();
    cout << "Server shutdown complete." << endl;
    return 0;
}
