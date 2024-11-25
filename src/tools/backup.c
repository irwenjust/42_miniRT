#include "miniRT.h"

t_camera copy_camera(t_camera camera)
{
	return ((t_camera){
		.coordinate = vector_copy(camera.coordinate),
		.normal = vector_copy(camera.normal),
		.fov = camera.fov
	});
}

void backup_scene()
{
	s()->ori_camera = copy_camera(s()->camera);
	//copy light
		//fclass
	//copy shape
}