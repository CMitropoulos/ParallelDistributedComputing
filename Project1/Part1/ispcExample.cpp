
int main(){
	unsigned int width = 768, height = 512;
	float x0 = -2., x1 = 1.;
	float y0 = -1., y1 = 1.;
	int maxIterations = 256;
	int *buf = new int[width*height];

	mandelbrot_ispc(x0, y0, x1, y1, width, height, maxIterations, buf);

}	