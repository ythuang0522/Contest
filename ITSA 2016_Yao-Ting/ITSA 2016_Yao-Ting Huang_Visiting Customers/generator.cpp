#include <cstdlib>
#include <cmath>
#include <limits>
#include <stdio.h>

int generateGaussianNoise(double mu, double sigma)
{
	const double epsilon = std::numeric_limits<double>::min();
	const double two_pi = 2.0*3.14159265358979323846;

	static double z0, z1;
	static bool generate;
	generate = !generate;

	if (!generate)
	   return z1 * sigma + mu;

	double u1, u2;
	do
	 {
	   u1 = rand() * (1.0 / RAND_MAX);
	   u2 = rand() * (1.0 / RAND_MAX);
	 }
	while ( u1 <= epsilon );

	z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
	return (int) (z0 * sigma + mu);
}

int main()
{
	int num, mu, sigma;
	scanf("%d %d %d", &num, &mu, &sigma);
	printf("%d\n", num);
	for(int i=0; i < num; i++)
	{
		int first = abs(generateGaussianNoise(mu, sigma))%25;
		int second = abs(generateGaussianNoise(mu, sigma))%25;
		int profit = abs(generateGaussianNoise(500, 500))%1000+1;
		if(first > second)
		{
			int tmp = first;
			first = second;
			second = tmp;
		}
			
		printf("%d %d %d\n", first, second, profit);
	}

	return 0;
}
