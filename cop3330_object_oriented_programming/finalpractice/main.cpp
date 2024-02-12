#include "flex.h"
using namespace std;

int main()
{
	Flex a, b("Merry"), c("Christmas");
	cout << a << ',' << b << ',' << c << endl;
	b.cat(a);
	cout << b << endl;
	b.cat(c);
	cout << b << endl;
	c.cat(c);
	c.cat(c);
	cout << c << endl;
	return 0;
}
