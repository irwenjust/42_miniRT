#include "miniRT.h"

static t_vector camera_position(t_vector min, t_vector max, int preset)
{
    t_vector vec;

    ft_bzero(&vec, sizeof(t_vector));
    vec.x = (min.x + max.x) / 2;
    vec.y = (min.y + max.y) / 2;
    vec.z = (min.z + max.z) / 2;
    if (preset == 1)
        vec.z = min.z - 10;
    else if (preset == 2)
        vec.z = max.z + 10;
    else if (preset == 3)
        vec.y = max.y + 10;
    else if (preset == 4)
        vec.y = min.y - 10;
    else if (preset == 5)
        vec.x = min.x - 10;
    else if (preset == 6)
        vec.x = max.x + 10;    
    return ((t_vector){vec.x, vec.y, vec.z});
}

void camera_preset(int preset)
{
    t_camera new_camera;

    new_camera = copy_camera(s()->camera);
    new_camera.coordinate = camera_position(s()->bvh->box.min, s()->bvh->box.max, preset);
    if (preset == 1)
        new_camera.normal = vector_normalize(vector_add(C_FRONT, VEC_MIN));
    else if (preset == 2)
        new_camera.normal = vector_normalize(vector_add(C_BACK, VEC_MIN));
    else if (preset == 3)
        new_camera.normal = vector_normalize(vector_add(C_TOP, VEC_MIN));
    else if (preset == 4)
        new_camera.normal = vector_normalize(vector_add(C_BOTTOM, VEC_MIN));
    else if (preset == 5)
        new_camera.normal = vector_normalize(vector_add(C_LEFT, VEC_MIN));
    else if (preset == 6)
        new_camera.normal = vector_normalize(vector_add(C_RIGHT, VEC_MIN));
    s()->camera = copy_camera(new_camera);
    init_viewport();
}