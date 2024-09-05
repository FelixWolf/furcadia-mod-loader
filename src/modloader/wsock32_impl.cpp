#include <winsock2.h>
#include "wsock32_impl.hpp"

HMODULE LoadDllIfExists(const char* dllPath)
{
    // Check if the DLL file exists
    DWORD fileAttr = GetFileAttributesA(dllPath);
    if (fileAttr == INVALID_FILE_ATTRIBUTES)
        return NULL;
    
    // Load the DLL
    HMODULE hDll = LoadLibraryA(dllPath);
    if (hDll == NULL)
        return NULL;
    
    return hDll;
}

wsock32_dll wsock32;

bool setupWSock32Forwarding()
{
    if (wsock32.dll == NULL)
    {
        wsock32.dll = LoadDllIfExists("C:\\windows\\syswow64\\wsock32.dll");
        if (wsock32.dll == NULL)
            wsock32.dll = LoadDllIfExists("C:\\windows\\system32\\wsock32.dll");
        
        if (wsock32.dll == NULL)
            return false;
            
        wsock32.closesocket = (closesocket_t)GetProcAddress(wsock32.dll, "closesocket");
        wsock32.connect = (connect_t)GetProcAddress(wsock32.dll, "connect");
        wsock32.htons = (htons_t)GetProcAddress(wsock32.dll, "htons");
        wsock32.inet_addr = (inet_addr_t)GetProcAddress(wsock32.dll, "inet_addr");
        wsock32.inet_ntoa = (inet_ntoa_t)GetProcAddress(wsock32.dll, "inet_ntoa");
        wsock32.recv = (recv_t)GetProcAddress(wsock32.dll, "recv");
        wsock32.send = (send_t)GetProcAddress(wsock32.dll, "send");
        wsock32.setsockopt = (setsockopt_t)GetProcAddress(wsock32.dll, "setsockopt");
        wsock32.shutdown = (shutdown_t)GetProcAddress(wsock32.dll, "shutdown");
        wsock32.socket = (socket_t)GetProcAddress(wsock32.dll, "socket");
        wsock32.gethostbyname = (gethostbyname_t)GetProcAddress(wsock32.dll, "gethostbyname");
        wsock32.gethostname = (gethostname_t)GetProcAddress(wsock32.dll, "gethostname");
        wsock32.WSAAsyncSelect = (WSAAsyncSelect_t)GetProcAddress(wsock32.dll, "WSAAsyncSelect");
        wsock32.WSAGetLastError = (WSAGetLastError_t)GetProcAddress(wsock32.dll, "WSAGetLastError");
        wsock32.WSACancelBlockingCall = (WSACancelBlockingCall_t)GetProcAddress(wsock32.dll, "WSACancelBlockingCall");
        wsock32.WSAStartup = (WSAStartup_t)GetProcAddress(wsock32.dll, "WSAStartup");
        wsock32.WSACleanup = (WSACleanup_t)GetProcAddress(wsock32.dll, "WSACleanup");
    }
    return true;
}

void freeWSock32()
{
    if (wsock32.dll != NULL)
        FreeLibrary(wsock32.dll);
    wsock32.dll = NULL;
}

// Forwarding Functions
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
extern "C" __declspec(dllexport) int WINAPI closesocket(SOCKET s)
{
    return wsock32.closesocket(s);
}

extern "C" __declspec(dllexport) int WINAPI connect(SOCKET s, const sockaddr* addr, int addrlen)
{
    return wsock32.connect(s, addr, addrlen);
}

extern "C" __declspec(dllexport) u_short WINAPI htons(u_short hostshort)
{
    return wsock32.htons(hostshort);
}

extern "C" __declspec(dllexport) unsigned long WINAPI inet_addr(const char* cp)
{
    return wsock32.inet_addr(cp);
}

extern "C" __declspec(dllexport) char* WINAPI inet_ntoa(in_addr in)
{
    return wsock32.inet_ntoa(in);
}

extern "C" __declspec(dllexport) int WINAPI recv(SOCKET s, char* buf, int len, int flags)
{
    return wsock32.recv(s, buf, len, flags);
}

extern "C" __declspec(dllexport) int WINAPI send(SOCKET s, const char* buf, int len, int flags)
{
    return wsock32.send(s, buf, len, flags);
}

extern "C" __declspec(dllexport) int WINAPI setsockopt(SOCKET s, int level, int optname, const char* optval, int optlen)
{
    return wsock32.setsockopt(s, level, optname, optval, optlen);
}

extern "C" __declspec(dllexport) int WINAPI shutdown(SOCKET s, int how)
{
    return wsock32.shutdown(s, how);
}

extern "C" __declspec(dllexport) SOCKET WINAPI socket(int af, int type, int protocol)
{
    return wsock32.socket(af, type, protocol);
}

extern "C" __declspec(dllexport) hostent* WINAPI gethostbyname(const char* name)
{
    return wsock32.gethostbyname(name);
}

extern "C" __declspec(dllexport) int WINAPI gethostname(char* name, int namelen)
{
    return wsock32.gethostname(name, namelen);
}

extern "C" __declspec(dllexport) int WINAPI WSAAsyncSelect(SOCKET s, HWND hWnd, u_int wMsg, long lEvent)
{
    return wsock32.WSAAsyncSelect(s, hWnd, wMsg, lEvent);
}

extern "C" __declspec(dllexport) int WINAPI WSAGetLastError(void)
{
    return wsock32.WSAGetLastError();
}

extern "C" __declspec(dllexport) int WINAPI WSACancelBlockingCall(void)
{
    return wsock32.WSACancelBlockingCall();
}

extern "C" __declspec(dllexport) int WINAPI WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData)
{
    return wsock32.WSAStartup(wVersionRequested, lpWSAData);
}

extern "C" __declspec(dllexport) int WINAPI WSACleanup(void)
{
    return wsock32.WSACleanup();
}
#pragma GCC diagnostic pop