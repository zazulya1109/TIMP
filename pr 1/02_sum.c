#include <stdio.h>

int main()
{
	double a, b;
	if (scanf("%lf%lf", &a, &b) > 0)
		printf("%lf", a + b);
	return 0;
}
