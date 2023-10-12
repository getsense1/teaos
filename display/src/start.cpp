#include "screen.h"


_screen _vis;

int main () {

	_vis.init_video();
	_vis.print(reinterpret_cast<const uint8_t *>("Hello World\n"));


}
