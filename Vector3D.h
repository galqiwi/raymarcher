#ifndef VECTOR3D_H
#define VECTOR3D_H

typedef double pt;

class Vector3D {
public:
	Vector3D() {}
	Vector3D(pt x, pt y, pt z): x(x), y(y), z(z) {}
	pt x, y, z;
};

ostream& operator<<(ostream& out, const Vector3D& v) {
	out << v.x << " " << v.y << " " << v.z << endl;
	return out;
}
istream& operator>>(istream& in, Vector3D& v) {
	in >> v.x >> v.y >> v.z;
	return in;
}

Vector3D operator+(const Vector3D& a, const Vector3D& b) {
	return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
}
Vector3D operator-(const Vector3D& a, const Vector3D& b) {
	return Vector3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3D operator*(const Vector3D& a, pt t) {
	return Vector3D(a.x * t, a.y * t, a.z * t);
}
Vector3D operator*(pt t, const Vector3D& a) {
	return Vector3D(a.x * t, a.y * t, a.z * t);
}
Vector3D operator/(const Vector3D& a, pt t) {
	return Vector3D(a.x / t, a.y / t, a.z / t);
}

pt operator*(const Vector3D& a, const Vector3D& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

pt abs2(const Vector3D& a) {
	return a.x * a.x + a.y * a.y + a.z * a.z;
}
pt abs(const Vector3D& a) {
	return hypot(a.x, a.y, a.z);
}
pt operator/(const Vector3D& a, const Vector3D& b) {
	return (a * b) / abs2(b);
}

Vector3D norm(const Vector3D& v) {
	return v / abs(v);
}

Vector3D operator%(const Vector3D& a, const Vector3D& b) {
	return Vector3D(a.y * b.z - b.y * a.z, b.x * a.z - a.x * b.z, a.x * b.y - b.x * a.y);
}

#endif