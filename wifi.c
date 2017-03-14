#include <goods.h>
void main()
{
	char id[8] ="59681562";
	double prace = getGoodsPrace(id);
	if(prace == 9.66)
		while(1)
			led_number(966);
		else
			while(1)
				led_number(333);
}