#include"MyServer.h"

int main() {
	Server myServer("192.168.1.212", 54010);
	if (myServer.initSocket() == true) {
		myServer.Run();
	}
	return 0;
}