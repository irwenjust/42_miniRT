#include "miniRT.h"

t_scene	*s(void)
{
	static t_scene	s;

	return (&s);
}
