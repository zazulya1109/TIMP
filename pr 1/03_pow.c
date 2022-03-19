#include <stdio.h>
#include <math.h>

int main()
{
	double x, y;
	if (scanf("%lf%lf", &x, &y) > 0)
		printf("%lf", pow(x, y));
	return 0;
}
