#include"MyServer.h"

int main() {
	Server myServer("Your IP", 54010);// để set IP server bằng IP máy tính cá nhân.
	if (myServer.initSocket() == true) {
		myServer.Run();
	}
	return 0;
}
