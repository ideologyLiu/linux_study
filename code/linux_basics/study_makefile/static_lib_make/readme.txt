制作静态库
	ar rcs 库名 所有的.o文件
使用静态
	gcc main.c -o 生成文件名 -I头文件库路径 -L静态库路径 -l制定库的名字
	例子：gcc main.c -o mybin -I./mathlib/include -L./mathlib/lib -lcal
# 4. 编译的时候指定库信息
	-L: 指定库所在的目录
	-l: 指定库的名字, 掐头(lib)去尾(.a) ==> calc
# -L -l, 参数和参数值之间可以有空格, 也可以没有  -L./ -lcalc	