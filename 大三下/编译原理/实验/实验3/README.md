## 实验三
&emsp;&emsp;由实验二的中间表示IR经过目标代码生成，生成可以与sylib.a链接的risc-v汇编。

&emsp;&emsp;注意，实验只允许修改 \src 和 \include 路径下的文件，否则可能无法通过测评。不要修改 Generator 下的 gen() 函数名，因为 main.cpp 中调用 `generator.gen()` 。

**环境配置**：

&emsp;&emsp;本实验采用 WSL/Ubuntu + Docker 环境，实验二中已经拉取了镜像 `frankd35/demo:v3`，因此只需要修改 CMake、创建容器、挂载目录即可：

1. 在 CMakeLists.txt 中指定 x86-linux 的编译器：
```
# 增加以下指令以兼容 Docker
set(CMAKE_C_COMPILER    "/usr/bin/x86_64-linux-gnu-gcc-7")
set(CMAKE_CXX_COMPILER  "/usr/bin/x86_64-linux-gnu-g++-7")
```
2. 在 CMakeLists.txt 中修改所需 CMake 版本
```
# 修改以下指令以兼容 Docker
cmake_minimum_required(VERSION 3.10)
project(compiler)
```
3. 在 Ubuntu 终端创建容器并挂载目录：`docker run -it -v /home/scienceli1125/Project/Lab3:/coursegrader frankd35/demo:v3`；
4. 因为我们希望以库的形式提供 IR 测评相关的函数实现，所以还需要在/lib下根据使用的linux平台将对应的库文件重命名为 libxx.a 才能通过编译，即
```
├─lib
|   ├─libIR-x86-win.a
|   ├─libIR.a
|   ├─libTools-x86-win.a
|   └ libTools.a
```

**实验过程**：使用lab2框架
1. 补全 .vscode 文件夹以配置环境；
2. 补全 lab1 和 lab2 的代码，通过测试；
3. 在 `src\backend\generator.cpp` 中实现 `include\backend\generator.h` 中声明的函数；

**进入容器**：
1. `sudo service docker start`：启动 Docker；
2. `docker start 204996ca5ffd`：运行容器；
3. `docker exec -it 204996ca5ffd bash`：进入容器；
3. `cd coursegrader`：进入挂载目录；

**编译**：
1. `cd build`：进入 build 文件夹；
2. `cmake ..`：读取 CMakeLists.txt 文件获取项目的构建配置和规则，生成构建配置和相应的构建脚本；
3. `make`：根据 Makefile 中的规则和依赖关系，自动化地编译源代码并生成可执行文件；

**执行**：
1. `cd ../bin`：进入 bin 文件夹；
2. `./compiler <src_filename> [-step] -o <output_filename> -O1`：使用单独样例文件进行测试并输出结果；

    &emsp;-step 支持以下几种输入：

    &emsp;&emsp;s0: 词法结果 token 串

    &emsp;&emsp;s1: 语法分析结果语法树, 以 json 格式输出

    &emsp;&emsp;s2: 语义分析结果, 以 IR 程序形式输出

    &emsp;&emsp;S: RISC-v 汇编

    &emsp;<src_filename>: 测试样例文件路径

    &emsp;<output_filename>: 输出样例文件路径

    如: `./compiler ../test/testcase/basic/00_main.sy S -o test.out -O1`

上述两个步骤适用于编写与调试阶段，支持单个文件测试以及连接 gdb 调试。如果程序已经无误，可以使用 python 脚本进行测试。

**测试**：
1. `cd ../test`：进入 test 文件夹；
2. `python3 build.py`：进入到 build 目录, 执行 `cmake ..` 和 `make` 语句；
3. `python3 run.py S`：运行可执行文件 compiler 编译所有测试用例, 打印 compiler 返回值和报错, 输出编译结果至 /test/output。注意使用 python3 执行，因为 subprocess.run 是在 Python 3.5 版本中引入的新函数，旧版 Python 无法执行；
4. `python3 score.py S`：将 run.py 生成的编译结果与标准结果进行对比并打分；

**结束容器**：
1. `exit`：退出当前容器，容器自动停止；
2. `sudo service docker stop`：关闭 Docker；