#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits>
# define M_PI 3.14159265358979323846

int n;
double volume, box_volume;
struct point {
	int x, y, z;
	double radius;
} points[10], box[2];

bool visited[10];

double min(double a, double b) {
	if (a < b)
		return a;
	else
		return b;
}

double calc_volume(point a, point b) {
	return sqrt((double)(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}

double put(int i) {
	int j;
	double radius_min = std::numeric_limits<double>::max();
	double tmp[6];
	tmp[0] = abs(points[i].x-box[0].x);
	tmp[1] = abs(points[i].y-box[0].y);
	tmp[2] = abs(points[i].z-box[0].z);
	tmp[3] = abs(points[i].x-box[1].x);
	tmp[4] = abs(points[i].y-box[1].y);
	tmp[5] = abs(points[i].z-box[1].z);
	for (j = 0 ; j < 6 ; j++)
		if (tmp[j] < radius_min)
	  		radius_min = tmp[j];
	for (j = 0 ; j < n ; j++)
		if (i != j && visited[j])
			radius_min = min(radius_min, calc_volume(points[i], points[j])-points[j].radius);

	return radius_min;
}

void run(int step, double volume_used) {
	if (step == n) {
		if (volume_used > volume)
			volume = volume_used;
		return;
	} else {
		for (int i = 0; i < n ; i++) {
			 if (!visited[i]) {
				 visited[i] = true;
				 points[i].radius = put(i);
				 if (points[i].radius > 0)
					 run(step+1, volume_used+(4.0/3.0)*M_PI*points[i].radius*points[i].radius*points[i].radius);
				 else
					 run(step+1, volume_used);
				 visited[i] = false;
			 }
		}
	}
}

int main() {
	int TC = 0;
	while (true) {
		scanf("%d", &n);
		if (!n)
			return 0;
		scanf("%d%d%d%d%d%d", &box[0].x, &box[0].y, &box[0].z, &box[1].x, &box[1].y, &box[1].z);
		box_volume = abs((box[0].x-box[1].x)*(box[0].y-box[1].y)*(box[0].z-box[1].z));
		for (int i = 0 ; i < n ; i++) {
			scanf("%d%d%d", &points[i].x, &points[i].y, &points[i].z);
			points[i].radius = 0;
		}
		memset(visited, false, sizeof(visited));
		volume = 0;
		run(0, 0.0);
		printf("Box %d: %d\n\n", ++TC, (int)round(box_volume-volume));
	}
	return 0;	
}
