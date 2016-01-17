#include <dll_loader.h>
#include <he_server_main.h>

int main()
{
	g_DllLoader.LoadServerDLL(L"bin\\server.dll");
	printf("OK!");
	getchar();
	printf(srv_GetName().c_str());
	getchar();
}