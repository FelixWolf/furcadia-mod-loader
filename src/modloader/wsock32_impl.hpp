#ifndef WSOCK32_IMPL_H
#define WSOCK32_IMPL_H
#include <winsock2.h>

typedef int (WINAPI *closesocket_t)(SOCKET);
typedef int (WINAPI *connect_t)(SOCKET, const sockaddr*, int);
typedef u_short (WINAPI *htons_t)(u_short);
typedef unsigned long (WINAPI *inet_addr_t)(const char*);
typedef char* (WINAPI *inet_ntoa_t)(in_addr);
typedef int (WINAPI *recv_t)(SOCKET, char*, int, int);
typedef int (WINAPI *send_t)(SOCKET, const char*, int, int);
typedef int (WINAPI *setsockopt_t)(SOCKET, int, int, const char*, int);
typedef int (WINAPI *shutdown_t)(SOCKET, int);
typedef SOCKET (WINAPI *socket_t)(int, int, int);
typedef hostent* (WINAPI *gethostbyname_t)(const char*);
typedef int (WINAPI *gethostname_t)(char*, int);
typedef int (WINAPI *WSAAsyncSelect_t)(SOCKET, HWND, u_int, long);
typedef int (WINAPI *WSAGetLastError_t)(void);
typedef int (WINAPI *WSACancelBlockingCall_t)(void);
typedef int (WINAPI *WSAStartup_t)(WORD, LPWSADATA);
typedef int (WINAPI *WSACleanup_t)(void);

struct wsock32_dll {
    HMODULE dll = NULL;
    closesocket_t closesocket = nullptr;
    connect_t connect = nullptr;
    htons_t htons = nullptr;
    inet_addr_t inet_addr = nullptr;
    inet_ntoa_t inet_ntoa = nullptr;
    recv_t recv = nullptr;
    send_t send = nullptr;
    setsockopt_t setsockopt = nullptr;
    shutdown_t shutdown = nullptr;
    socket_t socket = nullptr;
    gethostbyname_t gethostbyname = nullptr;
    gethostname_t gethostname = nullptr;
    WSAAsyncSelect_t WSAAsyncSelect = nullptr;
    WSAGetLastError_t WSAGetLastError = nullptr;
    WSACancelBlockingCall_t WSACancelBlockingCall = nullptr;
    WSAStartup_t WSAStartup = nullptr;
    WSACleanup_t WSACleanup = nullptr;
};

bool setupWSock32Forwarding();
void freeWSock32();

#endif