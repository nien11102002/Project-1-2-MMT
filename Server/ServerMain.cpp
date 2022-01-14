#include"MyServer.h"

int main() {
	Server myServer("192.168.0.178", 54010);// để set IP server bằng IP máy tính cá nhân.
	if (myServer.initSocket() == true) {
		myServer.Run();
	}
	return 0;
}
