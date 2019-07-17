#include "image.h"

int main()
{
	Image image1("images/specular.tif");
	Image image2("images/sea1.jpg");
	Image image3("images/sea2.jpg");
	image1.show();
	image2.show();
	image3.show();

	return 0;
}