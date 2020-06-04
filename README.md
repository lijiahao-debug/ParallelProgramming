## SX Aurora Tsubasa

---

### 术语  
| 缩写  | 定义 |
| :----------- | :----------|
|Vector Engine, VE| 由向量CPU组成，处理向量运算操作|
|Vector Host, VH|用来管理VE的主机|
|IB|无限宽带|
|HCA| host channel adapter 和其他节点通信|


---
> 基础命令

>> VEOS version  
>> `rpm -q veos`

>> 对应MPI版本位置  
>> `/opt/nec/ve/mpi`

>>直接使用命令设置环境变量  
`export PATH=/opt/nec/ve/bin:$PATH`  
也可以编辑.bashrc文件，添加上边代码，对当前用户永久生效

>查看系统信息 
>>vecmd命令帮助信息  
>>`vecmd -h`  
>> 主要有两个参数 info 和 topo 

>>显示系统树形结构,可以看到有多少VE  
>>`vecmd topo tree`

>>查看某个VE的具体信息,VE_ID可以上边的命令查询   
>>`vecmd -N VE_ID info`

> 编译运行

>>如果想让程序运行在VE，需要使用ncc编译程序,参数和gcc差不多  
>>`ncc sample.c -o sample`

>>执行通过ncc编译的程序，可以通过-N指定需要运行在哪个VE上，默认是0  
>>`ve_exec -N VE_ID ./sample`

>>可以修改默认执行的VE  
>>`export VE_NODE_NUMBER=1`

>>查看可执行文件是否是针对VE编译的  
>>`nreadelf -h sample`

> 编译MPI程序

>> 需要先设置MPI编译环境  
>> `source /opt/nec/ve/mpi/<version>/bin/necmpivars.sh`(for bash)    
>> `source /opt/nec/ve/mpi/<version>/bin/necmpivars.csh` (for csh)

>> 编译MPI程序  
>> `mpincc sample.c`
>> 可以添加 -vh 参数指定程序运行在VH上
>> `mpincc -vh sample.c`

>> 运行MPI程序  
>> `mpirun -ve [VE_ID] -np [number] ./sample`


>性能分析工具   

>+ PROGINF
>>通过设置环境变量，运行完程序后会直接显示性能报告 

>> 普通程序环境变量设置
>>`export VE_PROGINF=DETAIL` 

>> MPI程序环境变量设置
>>`export NMPI_PROGINF=YES`  

>+ FTRACE

