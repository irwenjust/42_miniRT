# 42_miniRT
Let's start this epic project!   
This project is trying to create a ray tracing simulator by C.   
The project grade is 125/100.  

### **Recommend to run this project in Linux.**

In WSL, most functions is ok, but the color presets of light and objects cannot be displayed normally, and reset function is wrong.

This may be because our color structure store int data, not double, and it causes precision loss in WSL. However, we found this problem too late, and as the color calculated in renderer is double type, so preset color is correct when running in Linux. So we didn't modify it.

## **Authorship**

- [**yingzhan11**](https://github.com/yingzhan11) **- yzhan**  
- [**irwenjust**](https://github.com/irwenjust) **- likong**   

## **Some result image**
<table align=center>
	<thead>
		<tr>
			<th colspan=2>Basic objects</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><image src="asserts/sphere.png"></td>
			<td><image src="asserts/cone.png"></td>
		</tr>
		<tr>
			<td><image src="asserts/cylinder.png"></td>
			<td><image src="asserts/multi_lights.png"></td>
		</tr>
	</tbody>
	<thead>
		<tr>
			<th colspan=2>Reflection && Refraction</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><image src="asserts/planes.png"></td>
			<td><image src="asserts/bubbles.png"></td>
		</tr>
		<tr>
			<td><image src="asserts/glass.png"></td>
			<td><image src="asserts/mirrors.png"></td>
		</tr>
	</tbody>
	<thead>
		<tr>
			<th colspan=2>Texture && Checkboard</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><image src="asserts/solar.png"></td>
			<td><image src="asserts/earth.png"></td>
		</tr>
		<tr>
			<td><image src="asserts/sphere_checkboard.png"></td>
			<td><image src="asserts/octagon.png"></td>
		</tr>
	</tbody>
	<thead>
		<tr>
			<th colspan=2>Metal material</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><image src="asserts/snowman_metal.png"></td>
			<td><image src="asserts/stickman.png"></td>
		</tr>
	</tbody>
</table>

## **Mandatory part**  
Here are some of the features Mandatory part handles:  
- Basic ray tracing by diffuse reflection;
- Basic render color and shadow for plane, sphere and cylinder;
- Bounding volume hierarchies by aabb box and BVH tree;
- Clear, intuitive and powerful menu system;
- Use "fake class"(fclass) to manage the objects;
- Adaptive render for transform, scale and rotation objects in real-time and dynamic;

## **Bonus part**  
Here are some of the features Bonus part add:  
- Complete Phong Model(ambient + diffuse + specular);
- Color disruption: checkerboard;
- Colored and multi-spot lights;
- One other 2nd degree object: Cone;
- Smooth and bump texture;
- Reflection and refraction with each object (our bonus);
- Multiple thread render (our bonus);
- Frame rate control (our bonus);
- Multi-material overlay (our bonus);

## **Implementation**  
<table align=center>
	<thead>
		<tr>
			<th>File Name</th>
			<th>Functionality</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><strong>libft/</strong> </td>
			<td>Contains standard libft project and some of the added tools function</td>
		</tr>
		<tr>
			<td><strong>mandatory/</strong> </td>
			<td>Contains all the source files for the mandatory part</td>
		</tr>
		<tr>
			<td><strong>scenes/</strong> </td>
			<td>Contains all the .rt files</td>
		</tr>
		<tr>
			<td><strong>textures/</strong> </td>
			<td>Contains all the texture files</td>
		</tr>
		<tr>
			<td><strong>bonus/</strong> </td>
			<td>Contains all the source files for the bonus part</td>
		</tr>
		<tr>
			<td><strong>bonus/src/bvh/</strong> </td>
			<td>Generate and update aabb box and BVH tree</td>
		</tr>
		<tr>
			<td><strong>bonus/src/color/</strong> </td>
			<td>Contain all calculations and logics for color, checkboard and texture</td>
		</tr>
		<tr>
			<td><strong>bonus/src/debug/</strong> </td>
			<td>Test program</td>
		</tr>
		<tr>
			<td><strong>bonus/src/entities/</strong> </td>
			<td>Objects management</td>
		</tr>
		<tr>
			<td><strong>bonus/src/fclass/</strong> </td>
			<td>Generate and manage the "fake class"</td>
		</tr>
		<tr>
			<td><strong>bonus/src/hook/</strong> </td>
			<td>Menu system operate management</td>
		</tr>
		<tr>
			<td><strong>bonus/src/init/</strong> </td>
			<td>Initialize data</td>
		</tr>
		<tr>
			<td><strong>bonus/src/intersection/</strong> </td>
			<td>Handle intersection for different shapes</td>
		</tr>
		<tr>
			<td><strong>bonus/src/menu/</strong> </td>
			<td>Menu system design management</td>
		</tr>
		<tr>
			<td><strong>bonus/src/parser/</strong> </td>
			<td>Preprocess the source data</td>
		</tr>
		<tr>
			<td><strong>bonus/src/renderer/</strong> </td>
			<td>Core rendering part</td>
		</tr>
		<tr>
			<td><strong>bonus/src/tools/</strong> </td>
			<td>All of tools functions</td>
		</tr>
		<tr>
			<td><strong>bonus/src/uv/</strong> </td>
			<td>UV coordinate calculation</td>
		</tr>
		<tr>
			<td><strong>bonus/src/vector/</strong> </td>
			<td>Vector calculation</td>
		</tr>
	</tbody>
</table>

## **Compilation**   
### **Mandatory**
To compile this project you should run `make` in the terminal.    
To run the program needs to follow this:   
```sh  
$ ./miniRT scenes/scene_name 
```   
For example: `./miniRT scenes/example.rt`  
### **Bonus**
To compile this project you should run `make bonus` in the terminal.    
To run the program needs to follow this:   
```sh  
$ ./miniRT scenes/bonus/scene_name 
```   
For example: `./miniRT scenes/bonus/example.rt`  

## **Some tips**
- Some materials we learn and try to use:   
Ray Tracing in One Weekend: https://raytracing.github.io/books/RayTracingInOneWeekend.html   
The ray tracer challenge: http://raytracerchallenge.com/  
Dynamic Bounding Volume Hierarchies: https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf
- We use Minilibx library. It doesn't support resize windows. And may have some limitations on texture format also.
- We did not consider the issue of multi-platform trials. Currently it can only promise works on the Ubuntu system.
- Yeah we really proud that this project has been finished! Even there still could be better and better. Cheers!



