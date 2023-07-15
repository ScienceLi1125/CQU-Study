## 实验二
&emsp;&emsp;将实验一的抽象语法树经过语义分析和语法制导翻译，生成中间表示 IR。

&emsp;&emsp;注意，实验只允许修改 \src 和 \include 路径下的文件，否则可能无法通过测评。

**环境配置**：

&emsp;&emsp;由于本地环境不兼容，因此本实验采用 WSL/Ubuntu + Docker 环境进行编译，配置过程参考 [WSL/Ubuntu+Docker配置](https://blog.csdn.net/m0_51976564/article/details/130688533)。配置完成后按照指导书上步骤拉取镜像、指定编译器、创建容器、挂载目录：

1. 拉取镜像：`docker pull frankd35/demo:v3`；
2. 在 CMakeLists.txt 中指定 x86-linux 的编译器：
```
# 增加以下指令以兼容 Docker
set(CMAKE_C_COMPILER    "/usr/bin/x86_64-linux-gnu-gcc-7")
set(CMAKE_CXX_COMPILER  "/usr/bin/x86_64-linux-gnu-g++-7")
```
3. 在 CMakeLists.txt 中修改所需 CMake 版本
```
# 修改以下指令以兼容 Docker
cmake_minimum_required(VERSION 3.10)
project(compiler)
```
4. 创建容器并挂载目录：`docker run -it -v /home/scienceli1125/Project/Lab2:/coursegrader frankd35/demo:v3`。因为我的代码框架目录被放在 \\wsl.localhost\Ubuntu-22.04\home\scienceli1125\Project\Lab2 下，所以需要将其映射到 Docker 容器的 coursegrader 下。执行该指令后，Docker 会创建并运行一个新的容器并为该容器分配一个唯一的容器 ID，界面进入以 root 身份登录的容器命令行，那长串字符串就是容器的 ID。如果想要结束当前容器，执行 `exit` 即可。挂载目录可以使容器能够访问和操作 Linux 上的文件，而无需将这些文件复制到容器内部；

**实验过程**：使用lab2框架
1. 补全 .vscode 文件夹以配置环境；
2. 补全 lab1 代码，通过语法分析测试；
3. 阅读 `include\ir` 下声明的函数及其在 `src\ir` 中的实现，了解 IR 下函数、指令、操作数、操作符和程序的表示形式；
4. 阅读 `include\tools` 下声明的函数及其在 `src\tools\ir_executor.cpp` 中的实现，主要用于输入输出和函数计时（无关语义分析）；
5. 在 `src\front\semantic.cpp` 中实现 `include\front\semantic.h` 中声明的函数；

**进入容器**：
1. `sudo service docker start`：启动 Docker；
2. `docker start 9fac9e61e269`：运行容器；
3. `docker exec -it 9fac9e61e269 bash`：进入容器；
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

    如: `./compiler ../test/testcase/basic/00_main.sy s2 -o test.out -O1`

上述两个步骤适用于编写与调试阶段，支持单个文件测试以及连接 gdb 调试。如果程序已经无误，可以使用 python 脚本进行测试。

**测试**：
1. `cd ../test`：进入 test 文件夹；
2. `python3 build.py`：进入到 build 目录, 执行 `cmake ..` 和 `make` 语句；
3. `python3 run.py s2`：运行可执行文件 compiler 编译所有测试用例, 打印 compiler 返回值和报错, 输出编译结果至 /test/output。注意使用 python3 执行，因为 subprocess.run 是在 Python 3.5 版本中引入的新函数，旧版 Python 无法执行；
4. `python3 score.py s2`：将 run.py 生成的编译结果与标准结果进行对比并打分；

**结束容器**：
1. `exit`：退出当前容器，容器自动停止；
2. `sudo service docker stop`：关闭 Docker；