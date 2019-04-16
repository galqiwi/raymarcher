#include "Vector3D.h"
#include "matread.h"

#define PIC_SIZE_H (1080 / 4)
#define PIC_SIZE_W (1920 / 4)

Mat m(PIC_SIZE_H, PIC_SIZE_W, CV_8UC3, Scalar(255, 255, 255));
Matread mr(m);

int main() {
	imshow("main", m);
	while (waitKey(1));
}