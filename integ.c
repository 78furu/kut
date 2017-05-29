#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <float.h>

//Konstansok def.

double massOfEarth = 5.9736e24;
double massOfMoon = 7.349e22;
double posOfApogeum = 405500000;
double velOfApogeum = 964;
double posOfPerigeum = 363300000;
double velOfPerigeum = 1076;
double gravConst = 6.67384e-11;

double deriv(double* x, double* y, int i){ 
	return -(gravConst*massOfEarth*x[i - 1] / pow((x[i - 1] *x[i-1]) + (y[i - 1] * y[i-1]), (3.0 / 2.0)));
}

double energy(double* x, double* y, double* vx, double* vy, int i) {
	double kin, pot;
	kin = 0.5*massOfMoon*(vx[i] * vx[i] + vy[i] * vy[i]);
	pot = gravConst*massOfEarth*massOfMoon* pow(x[i] * x[i] + y[i] * y[i], -0.5);
	return kin-pot ;
}


int main() {

// A kimeneti fajlokat egy res.txt nevu fajlba menti.

	int time = 99999;
	int step = 1000;

	FILE* resultFile = fopen("res.txt", "w+");

	double *t, *x, *y, *vx, *vy, *E;
	t = (double*)calloc(time, sizeof(double));
	x = (double*)calloc(time, sizeof(double));
	y = (double*)calloc(time, sizeof(double));
	vx = (double*)calloc(time, sizeof(double));
	vy = (double*)calloc(time, sizeof(double));
	E = (double*)calloc(time, sizeof(double));

	y[0] = 0;
	x[0] = posOfApogeum;
	vx[0] = 0;
	vy[0] = -velOfApogeum;
	t[0] = 0;

	int i;

	for (i = 1; i < time; i++) {
		x[i] = x[i - 1] + step*vx[i - 1];
		y[i] = y[i - 1] + step*vy[i - 1];
		vx[i] = vx[i - 1] + step*deriv(x, y, i);
		vy[i] = vy[i - 1] + step*deriv(y, x, i);
		t[i] = t[i - 1] + step;
	}

	for (i = 0; i < time; i++) {
		E[i] = energy(x, y, vx, vy, i);
	}

	for (i = 0; i < time; i++) {
		fprintf(resultFile, "%lf \t %lf \t %lf \t %lf  \t %lf \t %lf \n", t[i], x[i], y[i], E[i], vx[i],vy[i]);
	}

	fclose(resultFile);

	return 0;
}
