#include"MyServer.h"

int main() {
	Server myServer("127.0.0.1",54010);
	if (myServer.initSocket() == true) {
		myServer.Run();
	}
	return 0;
}