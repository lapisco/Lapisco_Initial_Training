#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

void on_Mouse(int e, int x, int y, int d, void *ptr)
{
	Point*p=(Point*)ptr;
	p->x=x;
	p->y=y;
}