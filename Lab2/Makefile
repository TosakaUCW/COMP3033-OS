# Makefile for compiling task programs

# 编译器
CC = gcc
# 编译选项
CFLAGS = -Wall -Wextra -g

# 任务 1
T1_SRC = e2_t1_2330016056.c
T1_TARGET = e2_t1_2330016056

# 任务 2
T2_SRC = e2_t2_2330016056.c
T2_TARGET = e2_t2_2330016056

# 任务 3
T3_SRC = e2_t3_2330016056.c
T3_TARGET = e2_t3_2330016056

# 默认目标
all: help

# 任务 1 编译规则
$(T1_TARGET): $(T1_SRC)
	$(CC) $(CFLAGS) -o $(T1_TARGET) $(T1_SRC)

# 任务 2 编译规则
$(T2_TARGET): $(T2_SRC)
	$(CC) $(CFLAGS) -o $(T2_TARGET) $(T2_SRC)

# 任务 3 编译规则
$(T3_TARGET): $(T3_SRC)
	$(CC) $(CFLAGS) -o $(T3_TARGET) $(T3_SRC)

# 任务 1 目标并运行
t1: $(T1_TARGET)
	./$(T1_TARGET)

# 任务 2 目标并运行
t2: $(T2_TARGET)
	./$(T2_TARGET)

# 任务 3 目标并运行
t3: $(T3_TARGET)
	./$(T3_TARGET)

# 帮助目标，显示可用命令
help:
	@echo "Usage: make [task]"
	@echo "Available tasks:"
	@echo "  t1     Compile and run task 1"
	@echo "  t2     Compile and run task 2"
	@echo "  t3     Compile and run task 3"

# 清理目标文件
clean:
	rm -f $(T1_TARGET) $(T2_TARGET) $(T3_TARGET)
