# 42_miniRT
Let's start this epic project!   
Add some materials we learn and try to use:   
Ray Tracing in One Weekend: https://raytracing.github.io/books/RayTracingInOneWeekend.html   
The ray tracer challenge: http://raytracerchallenge.com/  
Dynamic Bounding Volume Hierarchies: https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf   

部分目前还需要更新的点：   
1. 所有向量初始化前需检查是否满足归一化
2. 检查环境光时参数如果有错会弹出窗口并关闭（影响体验）
3. ray tracer存在大量conditional jump                              （已解决）
4. 是否检查浮点数越界的问题 （比1.000000000000001更多位）
5. Error格式问题                                                   （已解决）
6. 在检查颜色时未检查浮点数 （如255.999/255.abc）
7. 填充数字的地方未检测用字母
8. 灯光字母应为L                                                   （已解决）
9. 在球形中直径越界会导致segmant（够大就会，不需要越界）[大于50就挂了，没继续测边界在哪]
10. vector和坐标都没有int越界检查
11. sphere中ks设为invalid值会leak （可能是shape没push到fclass就出去导致）
