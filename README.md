# RT-Thread-summer2022

## 作品简介

​		本作品基于十七届全国大学生智能车竞赛平衡信标组的群体挑战赛规则改编而来，实现了单片机随机在60*80的区域内点亮两个信标灯，同时控制两个车模向信标灯运动，当车出现在灯周围时，即视为灯被触发，下一个灯点亮，由此往复。

## RT-Thread使用情况及软件框架

​		线程一：图像上传到上位机进行显示；线程二：系统自动生成随机数，随机点亮信标灯；线程三：同时控制两辆车模分别向距离各自最近的信标灯运动。通过三个线程的协调调度，将RT-Thread的实时性体现出来，体现操作系统与裸机开发的区别。

​		与上位机通信部分原计划使用esp8266芯片搭配中南大学开源图传上位机“致用图传”进行图像传输，但因该部分原因，本部分总存在一些bug，无法完成，不得已选用下策，即使用是uart串口输出运行状况，未来我会不断尝试该部分的实现。

![](image/导图.png)



