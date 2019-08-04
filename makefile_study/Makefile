objects := $(patsubst %.c, %.o, $(wildcard *.c))

# 上面的定义指定两个目录，“src”和“../headers”，make会按照这个顺序进行搜索。
# 目录由“冒号”分隔 。（当然，当前目录永远是最高优先搜索的地方）
VPATH = src:../headers

# 注：这里的显式 “.PHONY : all” 不写的话一般情况也可以正确的执行，
# 这样make可通过隐式规则推导出， “all” 是一 个伪目标，执行make不会生成“all”文件，
# 而执行后面的多个目标。建议：显式写出是一个好习惯。
.PHONY : test
test : main

main : $(objects) foo.h
	cc -o main $(objects)

main.o : foo.h

foo.o : defs.h foo.h

.PHONY : clean
clean :
	-rm main $(objects)

# 伪目标同样也可成为依赖。
.PHONY : cleanall cleanobj cleandiff

cleanall : cleanobj cleandiff
	rm program

cleanobj : 
	rm *.o

cleandiff :
	rm *.diff
