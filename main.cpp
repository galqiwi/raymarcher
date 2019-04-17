#include "Vector3D.h"
#include "matread.h"

#define PIC_SIZE_H (1080)
#define PIC_SIZE_W (1920)
#define MAX_RAY_STEPS (100)
#define MIN_DIST (0.0001)
#define X_VIEW (1.)
#define Y_VIEW (X_VIEW * 1080. / 1920.)


Mat m(PIC_SIZE_H, PIC_SIZE_W, CV_8UC3, Scalar(255, 255, 255));
Matread mr(m);

pt frac(const pt& p) {
	return p - floor(p);
}

Vector3D frac(Vector3D a) {
	return Vector3D(frac(a.x), frac(a.y), frac(a.z));
}

pt distance2scene(Vector3D p) {
	pt dist = (abs(frac(p) - Vector3D(0.5, 0.5, 0.5)) - 0.2);
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
	return 1 - (1.0 * (finalStep - 1) / (MAX_RAY_STEPS - 2));
}

void frame_(int frame_id, int xmin, int xmax) {
	for (int x = xmin; x < xmax; x++) {
		for (int y = 0; y < PIC_SIZE_H; y++) {
			//mr.get(x, y, 0) = x;
			
			pt ax = +((((pt)x) / (PIC_SIZE_W - 1)) * 2. - 1.) * X_VIEW;
			pt ay = -((((pt)y) / (PIC_SIZE_H - 1)) * 2. - 1.) * Y_VIEW;
			Vector3D to = Vector3D(sin(ax), cos(ax) * sin(ay), -cos(ax) * cos(ay));
			int brightness = 255 * trace(Vector3D(frame_id / 60., 0, 0.5), to);
			//brightness = distance2scene(Vector3D(x / 100. - 1, 0, -y / 100. - 1)) * 255;
			mr.get(x, y, 0) = brightness;
			mr.get(x, y, 1) = brightness;
			mr.get(x, y, 2) = brightness;
			
		}
	}
}

void frame(int frame_id) {
	int n_threads = 8;
	vector<thread> threads;
	for (int i = 0; i < n_threads; i++) {
		threads.push_back(thread(frame_, frame_id, (PIC_SIZE_W * i / n_threads), (PIC_SIZE_W * (i + 1) / n_threads)));
	}
	for (int i = 0; i < n_threads; i++) {
		threads[i].join();
	}
}

int main() {
	//trace(Vector3D(0, 0, 0), norm(Vector3D(0, 0, -1)));
	//return 0;
	cout << maxFinalStep << endl;
	
	int frame_id = 0;
	while (waitKey(1)) {
		frame(frame_id);
		imshow("main", m);
		frame_id++;
		cout << "f" << endl;
		imwrite(to_string(frame_id) + ".jpg", m);
		//cvSaveImage("1", M);
	}
}