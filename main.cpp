#include "image.h"

int main()
{
	Image image1("specular.tif");
	Image image2("sea1.jpg");
	Image image3("sea2.jpg");
	image1.show();
	image2.show();
	image3.show();

	return 0;
}