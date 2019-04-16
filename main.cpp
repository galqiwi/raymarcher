#include "Vector3D.h"
#include "matread.h"

#define PIC_SIZE_H (1080 / 4)
#define PIC_SIZE_W (1920 / 4)
#define MAX_RAY_STEPS (200)
#define MIN_DIST (0.0001)
#define X_VIEW (1.)
#define Y_VIEW (X_VIEW * 1080. / 1920.)


Mat m(PIC_SIZE_H, PIC_SIZE_W, CV_8UC3, Scalar(255, 255, 255));
Matread mr(m);

pt distance2scene(Vector3D p) {
	pt dist = (abs(p - Vector3D(0, 0, -1)) - 0.4);
	return dist > 0 ? dist:0;
}

int maxFinalStep = 0;

pt trace(Vector3D p, Vector3D to) {
	pt path = 0.0;
	int finalStep = MAX_RAY_STEPS - 1;
	for (int i = 0; i < MAX_RAY_STEPS; i++) {
		Vector3D current_p = p + to * path;
		pt dpath = distance2scene(current_p);
		if (dpath < MIN_DIST) {
			finalStep = i;
			break;
		}
		path += dpath;
		//cout << i << " " << path << endl;
	}
	if (finalStep != MAX_RAY_STEPS - 1)
		maxFinalStep = max(maxFinalStep, finalStep);
	return 1 - (1.0 * finalStep / (MAX_RAY_STEPS - 1));
}

int main() {
	//trace(Vector3D(0, 0, 0), norm(Vector3D(0, 0, -1)));
	//return 0;
	for (int x = 0; x < PIC_SIZE_W; x++) {
		for (int y = 0; y < PIC_SIZE_H; y++) {
			//mr.get(x, y, 0) = x;
			
			pt ax = +((((pt)x) / (PIC_SIZE_W - 1)) * 2. - 1.) * X_VIEW;
			pt ay = -((((pt)y) / (PIC_SIZE_H - 1)) * 2. - 1.) * Y_VIEW;
			Vector3D to = Vector3D(sin(ax), cos(ax) * sin(ay), -cos(ax) * cos(ay));
			int brightness = 255 * trace(Vector3D(0, 0, 0), to);
			//brightness = distance2scene(Vector3D(x / 100. - 1, 0, -y / 100. - 1)) * 255;
			mr.get(x, y, 0) = brightness;
			mr.get(x, y, 1) = brightness;
			mr.get(x, y, 2) = brightness;
			
		}
		if (x % 50 == 0)
			cout << x << endl;
	}
	cout << maxFinalStep << endl;
	imshow("main", m);
	while (waitKey(1));
}