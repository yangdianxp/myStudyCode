# 在线文档：https://seisman.github.io/how-to-write-makefile/functions.html#patsubst
# 小知识
# @在命令前面，命令不会被显示出来

# make 参数
# -n或 --just-print 只显示命令，不执行命令
# -s或 --silent或--quiet则是全面禁止命令的显示
# -i或 --ignore-errors  Makefile中 所有命令都会忽略错误


CC = gcc
SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))

# 上面的定义指定两个目录，“src”和“../headers”，make会按照这个顺序进行搜索。
# 目录由“冒号”分隔 。（当然，当前目录永远是最高优先搜索的地方）
VPATH = src:../headers

# 注：这里的显式 “.PHONY : all” 不写的话一般情况也可以正确的执行，
# 这样make可通过隐式规则推导出， “all” 是一 个伪目标，执行make不会生成“all”文件，
# 而执行后面的多个目标。建议：显式写出是一个好习惯。
.PHONY: test
test: main

# 如果你要让上一条命令的结果应用在下一条命令时，你应该使用分号分隔这两条命令。
# 比如你的第一 条命令是cd命令，你希望第二条命令得在cd之后的基础上运行，
# 那么你就不能把这两条命令写在两行上，而 应该把这两条命令写在一行上，用分号分隔。
main: $(OBJS)
	$(CC) -o main $(OBJS)

# 给每个文件建立依赖关系
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
 
sinclude $(SRCS:.c=.d)

.PHONY: clean
clean:
	-rm main $(OBJS) *.d

# 伪目标同样也可成为依赖。
.PHONY: cleanall cleanobj cleandiff

cleanall: cleanobj cleandiff
	rm program

cleanobj: 
	rm *.o

cleandiff:
	rm *.diff
