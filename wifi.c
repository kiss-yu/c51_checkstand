#include <goods.h>
void main()
{
	char id[8] ="59681562";
	double prace = getGoodsPrace(id);
	while(1)
		led_number((int)prace);
}