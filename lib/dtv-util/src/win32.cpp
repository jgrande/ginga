#include <windows.h>

extern int main( int , char** );

int WINAPI WinMain(	HINSTANCE, HINSTANCE, LPTSTR, int ) {
	return main(__argc,__argv);
}
