# 42_miniRT
Let's start this epic project!   
Add some materials we learn and try to use:   
Ray Tracing in One Weekend: https://raytracing.github.io/books/RayTracingInOneWeekend.html   
The ray tracer challenge: http://raytracerchallenge.com/  
Dynamic Bounding Volume Hierarchies: https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf   

部分目前还需要更新的点：   
1. 所有向量初始化前需检查是否满足归一化 
2. 检查环境光时参数如果有错会弹出窗口并关闭（影响体验）                    （maybe已解决）
3. ray tracer存在大量conditional jump                              （已解决）
5. Error格式问题                                                   （已解决）
8. 灯光字母应为L                                                   （已解决）
9. 在球形中直径越界会导致segmant（够大就会，不需要越界）[大于50就挂了，没继续测边界在哪]
11. sphere中ks设为invalid值会leak （可能是shape没push到fclass就出去导致）


（在新的validate parse arg里添加）

4. 是否检查浮点数越界的问题 （比1.000000000000001更多位）【是指rt里的比如brightness和ks之类的？】  (已解决，check_nbr)
	before dot. 12nbr eg.214748364859.5 is max, but the image is strange. (99999999999like is more than 12,but ok, so set the precision as belor 8)
	8 nbr can mantains a good image
	the total number in double is 15 max, excluding -+, include .
   
7. 填充数字的地方未检测用字母                                        (已解决，check_arg_format)
   
6. 在检查颜色时未检查浮点数 （如255.999/255.abc） 【rt文件输入颜色是否允许浮点数格式？还是必须整数,同14的问题】 int   (已解决)
15. color结构里存的是int，一般光追计算颜色可能会算成浮点数，是否要改成double？ (已解决)

10. vector和坐标都没有int越界检查  【vector结构里是double】  (已解决)
    
12. 如果数字里有 . ，其前后没有数字，也能通过                         (已解决，check_arg_format)
    
14. 只有负号或者加号，后面没有数字时，也能通过检查                    （已解决，加在ft_isnum里了）
    
16. ks可以是小数，shininess必须是整数？checkerboard只能是0或1？transparency是0-1的小数？高度直径等设置range为多少【非bug，是否要规定】

17. when camera and light both inside or on the surface of a shape, segmentation  (dont have this bug now)

Mandatory part
1.如果某一行后面有空格，args数量会多一个，最后一个是\n，然后报错，是否要让这种是正确的

2.camera fov edit每次加减量现在是10，如果是1视角变化会毕竟慢，不确定bonus卡不卡，要不要改成1

3.相机进圆柱体之后，只能看到盖，看不到壁，之前就有的问题，subject和eva好像都没要求这个

4.if plane normal is 0,-1,0, light is above the plane, and camera is above too, which means we see the back of this plane, the color would be dark than the plane's real color. is it ok?
if ambient is 0, the plane show balck
but if the normal is 0,1,0, the plane is always light,even the back side compare to light.
"
# Ambient lighting
#N  Brightness[0,1]  Color[0-255]
A   0              255,255,255

# Camera
#N  Center   Normal[-1,1]  FOV[0-180,!=]
C   0,0,-5   0,0,1         100

# Light
#N  Center  Brightness[0,1]  Color[0-255]
L   0,20,10   0.7              255,255,255

# Spheres
#N  Center   Diameter[>0]  Color[0-255]
sp  0,0,15   5             255,0,0

# Plane
#N  Center   Normal[-1,1]  Color[0-255]
pl  0,-5,0   0,-1,0        255,255,255

# Cylinder
#N  Center   Normal[-1,1]  Diameter[>0]  Height[>0]  Color[0-255]
cy  -8,0,10   0,0,1        3             10          190,50,0
"

**IMPORTANT**
5. in .h file, the line as below are all wrong in norminette
	# define WARM_W		(t_color){255, 239, 214, 0}
	# define RADIAN(angle) ((angle * PI) / 180.0f)
	# define UPVECTOR (t_vector){0.0, 1.0, 0.0}
	# define VEC_MIN (t_vector){0.0001, 0.0001, 0.0001}
	# define FRAME_TIME (1000000 / FRAME_RATE)