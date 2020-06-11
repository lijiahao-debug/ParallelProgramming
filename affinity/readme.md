## 绑定进程到cpu核

---
CPU affinity 是一种调度属性(scheduler property), 它可以将一个进程"绑定" 到一个或一组CPU上.

CPU affinity 使用十六进制(32 bit)掩码的方式表示,转换成二进制后，1代表当前位置的processor被使用:  
`0x1  processor 0`  
`0x3 11 processor 0,1`  
`0xe 1110 processor 1,2,3`

---
## taskset 命令

查看进程使用的cpu  
`taskset -pc <PID>`  
进程和核绑定  
`taskset -pc <core_ID> <PID>`


---

---