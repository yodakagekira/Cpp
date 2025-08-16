#define _WIN32_WINNT 0x0600
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main(int argc, char* argv[]) {
    SOCKET clientSocket = INVALID_SOCKET;
    int port = 55555;


    const char* serverIP = "127.0.0.1";

    WSADATA wsaData{};
    WORD wversionReq = MAKEWORD(2, 2);
    int wsaerr;

    cout << "==== W11 Sockets ========" << endl;
    cout << "==== CLIENT ====" << endl;

    cout << "Step 1 - Set up DLL" << endl;
    wsaerr = WSAStartup(wversionReq, &wsaData);
    if (wsaerr == 0) {
        cout << "The Winsock dll found!" << endl;
        cout << "The status: " << wsaData.szSystemStatus << endl;
    } else {
        cout << "Winsock dll not found" << endl;
        return 1;
    }

    cout << "Step 2 - Set up Client Socket" << endl;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Error at socket() " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    } else {
        cout << "socket() is OK!" << endl;
    }

    cout << "Step 3 - Connect to Server" << endl;
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    // NOTE: pass &serverAddr.sin_addr (not &...s_addr)
    if (InetPtonA(AF_INET, serverIP, &serverAddr.sin_addr) != 1) {
        cout << "InetPtonA failed: " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "connect() failed with error " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    } else {
        cout << "connect() is OK!" << endl;
    }

    cout << "Step 4 - Send Data to Server" << endl;
    char buffer[512];
    cout << "Enter message to send: " << flush; // ensure prompt shows
    if (!cin.getline(buffer, sizeof(buffer))) {
        cout << "No input read (EOF?)." << endl;
    } else {
        int sent = send(clientSocket, buffer, (int)strlen(buffer), 0);
        if (sent == SOCKET_ERROR) {
            cout << "send() failed with error " << WSAGetLastError() << endl;
        } else {
            cout << "send() is OK, data sent (" << sent << " bytes)!" << endl;
        }
    }

    cout << "Step 5 - Close Socket and Cleanup" << endl;
    closesocket(clientSocket);
    WSACleanup();
    cout << "Client shutdown complete." << endl;

    return 0;
}
