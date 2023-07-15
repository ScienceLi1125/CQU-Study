## 实验一
&emsp;&emsp;实现编译器前端的词法分析和语法分析部分，目标是分析输入的源文件得到一颗抽象语法树。

&emsp;&emsp;注意，实验只允许修改 \src 和 \include 路径下的文件，否则可能无法通过测评。

**实验步骤**：使用 lab1 实验框架
1. 在 `src\front\lexical.cpp` 中实现 `include\front\lexical.h` 中声明的函数，思路同作业一；
2. 在 `src\front\lexical.cpp` 中将作业 1 中主函数构造 token 数组的过程封装为 `Scanner::run()` 函数，到此通过词法分析测试；
3. 修改 `src\front\abstract_syntax_tree.cpp` 中 AstNode 的构造函数，加入 push_back 操作，以节省语法分析时的 push_back 操作；
4. 在 `src\front\syntax.cpp` 中定义辅助函数 Match_XX 为每种产生式的构造提供可选的终结符/非终结符，以集合方式返回。需要注意的是，新定义的函数需要在 `include\front\syntax.h` 中进行声明；
5. 在 `src\front\syntax.cpp` 中定义辅助函数 retreat 为匹配失败的情形恢复原状态，该函数同样需要声明；
6. 在 `src\front\syntax.cpp` 中定义函数 parseXX 构造产生式，到此通过语法分析测试；


**编译**：
1. `cd build`：进入 build 文件夹；
2. `cmake ..`：读取 CMakeLists.txt 文件获取项目的构建配置和规则，生成构建配置和相应的构建脚本；
3. `make`：根据 Makefile 中的规则和依赖关系，自动化地编译源代码并生成可执行文件；

如果 VSCode 上安装了 CMake 扩展，可以直接一键 `配置所有项目`，不必再在终端输入指令。

**执行**：
1. `cd ..\bin`：进入 bin 文件夹；
2. `.\compiler <src_filename> [-step] -o <output_filename> -O1`：使用单独样例文件进行测试并输出结果；

    &emsp;-step 支持以下几种输入：

    &emsp;&emsp;s0: 词法结果 token 串

    &emsp;&emsp;s1: 语法分析结果语法树, 以 json 格式输出

    &emsp;&emsp;s2: 语义分析结果, 以 IR 程序形式输出

    &emsp;&emsp;S: RISC-v 汇编

    &emsp;<src_filename>: 测试样例文件路径

    &emsp;<output_filename>: 输出样例文件路径

    如: `.\compiler ..\test\testcase\basic\00_main.sy s0 -o test.out -O1`

上述两个步骤适用于编写与调试阶段，支持单个文件测试以及连接 gdb 调试。如果程序已经无误，可以使用 python 脚本进行测试。

**测试**：
1. `cd ..\test`：进入 test 文件夹；
2. `python build.py`：进入到 build 目录, 执行 `cmake ..` 和 `make` 语句；
3. `python run.py s0`：运行可执行文件 compiler 编译所有测试用例, 打印 compiler 返回值和报错, 输出编译结果至 /test/output；
4. `python score.py s0`：将 run.py 生成的编译结果与标准结果进行对比并打分；
