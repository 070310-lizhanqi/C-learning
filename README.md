# C-learning

个人 C 语言学习练习仓库。用一段段可编译、可运行的小程序，把**指针**和**内存管理**这两块最容易踩坑的内容拆开逐个验证。

每个 `.c` 文件都是一个独立、自包含的小实验，可以直接编译运行观察结果；配套的 `note.txt` 记录了当时整理的知识点。

## 目录结构

```
C-learning/
├── .vscode/                       # VS Code 编译/调试配置（tasks.json 里定义了编译任务）
├── InstallationLog.txt            # MSYS2 环境安装记录
├── code/
│   ├── First-level_pointer/       # 一级指针
│   │   ├── Exchange_Num.c                     # 用指针实现两个数的交换
│   │   ├── Pointer_traversal_of_array.c       # 用指针遍历数组
│   │   ├── sizeof_array_vs_pointer.c          # sizeof(数组) 与 sizeof(指针) 的区别
│   │   └── note.txt                           # sizeof / strlen 与各类型大小笔记
│   ├── Double_pointer/            # 二级指针与指针修饰
│   │   ├── double_ptr_demo.c                  # 二级指针的解引用层次
│   │   ├── const_ptr_demo.c                   # const 修饰指针的两种位置
│   │   └── void_ptr_demo.c                    # void* 配合枚举做泛型打印
│   └── Memory_management/         # 动态内存管理
│       ├── dyn_array_malloc.c                 # malloc 动态数组的完整流程
│       ├── implement_two_functions.c          # 手写 my_strdup / my_strndup
│       └── note.txt                           # 内存四区、堆栈区别笔记
└── .gitignore                     # 忽略编译产物、构建目录、IDE 私有配置
```

## 环境要求

- **编译器**：GCC（项目在 Windows + MSYS2 UCRT64 环境下编写，路径 `C:/msys64/ucrt64/bin/gcc.exe`）
- **编辑器**：VS Code（推荐，仓库已带好编译任务）
- **可选**：clang（用于 AddressSanitizer 检查内存错误）

C 标准：代码中使用了 `for (int i = 0; ...)` 循环内声明变量，需要 **C99 及以上**；GCC 默认的 `gnu17` 即可直接编译。

## 编译与运行

### 方式一：VS Code 任务（推荐）

仓库的 `.vscode/tasks.json` 里已经预置了 5 个任务：

| 任务名 | 作用 |
| --- | --- |
| `C: 编译当前文件` | 用 gcc 编译当前打开的 `.c`，生成同名 `.exe` |
| `C: 编译并运行当前文件` | 先编译再运行，输出显示在终端 |
| `C: clang 编译当前文件(ASan)` | clang + AddressSanitizer，生成 `xxx_asan.exe` |
| `C: clang 编译并运行(ASan)` | 上一条的编译 + 运行 |
| `C/C++: gcc.exe 生成活动文件` | 调试器默认使用的构建任务 |

用法：打开任意 `.c` 文件 → `Ctrl+Shift+B` 选择任务即可。

**关于 ASan 任务**：它会额外链接 AddressSanitizer，越界读写、use-after-free、内存泄漏都会直接报出源码行号，是排查 `malloc` / `free` 类问题的利器，适合用来验证 `Memory_management/` 下的程序。

### 方式二：命令行

```bash
# 单个文件编译运行
gcc -g -Wall code/First-level_pointer/Exchange_Num.c -o Exchange_Num.exe
./Exchange_Num.exe

# 如果想在 Windows 控制台正确显示源码里的中文，加上字符集参数
gcc -g -Wall \
    -finput-charset=UTF-8 -fexec-charset=GBK \
    code/Memory_management/dyn_array_malloc.c -o dyn_array_malloc.exe

# 用 ASan 检查内存问题
clang -g -Wall -fsanitize=address \
    code/Memory_management/implement_two_functions.c -o my_strdup_asan.exe
```

> **中文乱码说明**：源码是以 UTF-8 保存的，而 Windows 控制台默认使用 GBK 编码，所以直接用 gcc 编译时中文可能显示为乱码。`-finput-charset=UTF-8` 告诉编译器源文件是 UTF-8，`-fexec-charset=GBK` 让生成的程序按 GBK 输出，与终端匹配。注意 **clang 不支持 `-fexec-charset=GBK`**，用 ASan 任务时中文会按 UTF-8 输出（终端需为 UTF-8 才正常）。

## 各模块说明

### 1. First-level_pointer —— 一级指针

| 文件 | 知识点 | 实际输出 |
| --- | --- | --- |
| `Exchange_Num.c` | 函数参数是值传递，想修改调用方的变量必须传地址；`swap` 接收两个 `int*`，通过解引用真正交换了 `main` 里的 `i`、`j` | `20 10` / `20` |
| `Pointer_traversal_of_array.c` | 数组名在表达式中退化为首元素指针，`*(p + i)` 等价于 `p[i]` | `1 0 1 3 1 0` |
| `sizeof_array_vs_pointer.c` | `sizeof(数组名)` 得到整个数组的字节数，而 `sizeof(指针)` 永远是指针本身的大小 | `Size of array: 40` / `Size of pointer: 8` |

`sizeof_array_vs_pointer.c` 的输出很直观：`int arr[10]` 占 40 字节（10 × 4），而指向它的指针 `p` 在 64 位平台上是 8 字节。**数组名不是指针**，这一点在把数组传进函数后尤其要小心——进入函数后它已经退化成指针了，`sizeof` 拿不到原数组长度。

`note.txt` 里整理了 `sizeof`（运算符，编译期求值，统计内存占用）与 `strlen`（库函数，运行时遍历到 `'\0'` 为止，统计有效字符数）的区别，以及各基础类型在 32 位／64 位 Windows／64 位 Linux 下的大小对照表。

### 2. Double_pointer —— 二级指针与指针修饰

| 文件 | 知识点 | 实际输出 |
| --- | --- | --- |
| `double_ptr_demo.c` | 二级指针的逐层解引用：`q` 存 `p` 的地址，`*q` 是 `p` 的值（即 `a` 的地址），`**q` 才是 `a` 的值 | `a:10` / `*p:10` / `**q:10` |
| `const_ptr_demo.c` | `const` 在 `*` 前后的两种含义 | 见下 |
| `void_ptr_demo.c` | `void*` 作为"通用指针"，配合 `enum` 标记类型实现一个函数打印多种类型 | `Type: INT, Value: 5` 等 |

**`const` 修饰指针的规律**（`const_ptr_demo.c` 的核心结论）：

```c
const int *p;   // const 在 * 前：*p 只读，不能改指向的值；但 p 本身可以改指向
int *const q;   // const 在 * 后：q 只读，不能改指向；但 *q 可以改值

*p = 10;   // 编译错误
p  = &b;   // 合法
*q = 10;   // 合法
q  = &b;   // 编译错误
```

记忆口诀：**`const` 修饰它右边最近的那个东西**。`const int *p` 里 `const` 右边是 `int`，所以是"指向的内容不可改"；`int *const q` 里 `const` 右边是 `q`，所以是"指针本身不可改"。

**`void_ptr_demo.c`** 演示了 `void*` 的典型用途：`void*` 可以接收任意类型的指针，但**不能直接解引用**（编译器不知道它指向什么类型、该读几个字节），必须先强制转换成正确的类型。文件末尾的注释也点出了风险——如果传入的指针类型和枚举标记的类型对不上，就会读到错误的内存，属于未定义行为。

### 3. Memory_management —— 动态内存管理

| 文件 | 知识点 | 实际输出 |
| --- | --- | --- |
| `dyn_array_malloc.c` | `malloc` 动态数组的完整流程：读入长度 → 校验 → 分配 → 判空 → 使用 → `free` | `请输入数组元素个数:` → `1 2 3 4 5` |
| `implement_two_functions.c` | 手写 `my_strdup` / `my_strndup`，含完整的边界测试 | `全部测试通过` |

**`dyn_array_malloc.c`** 是一个写得很规范的 `malloc` 使用模板，几个关键点都覆盖到了：

1. `scanf` 的返回值要判断，输入非数字时 `n` 是未初始化的值，直接用会出问题；
2. 长度要做合法性检查（`n <= 0` 直接拒绝）；
3. `malloc` **可能失败**，返回 `NULL` 时必须检查；
4. 计算字节数时写 `(size_t)n * sizeof(int)`，避免 `int` 乘法在大长度下溢出；
5. 用完必须 `free`，否则内存泄漏。

**`implement_two_functions.c`** 实现了两个 libc 函数的手写版本，并用 `assert` 写了 4 类边界用例：

- `n` 等于原串长度 → 结果与原串相同；
- `n` 小于原串长度 → 截断，只取前 `n` 个字符；
- `n` 大于原串长度 → 遇 `'\0'` 提前停止，**不能越界读**；
- `n == 0` → 返回空字符串；
- 外加 `s == NULL` 时返回 `NULL`。

`my_strndup` 里的循环条件 `while (len < n && s[len])` 是两个条件缺一不可的典型例子：`len < n` 保证不超过 `n` 个字符，`s[len]` 保证源串更短时不会读到 `'\0'` 之后的内存。

### 4. 学习笔记

两个 `note.txt` 是配套的文字整理：

- **`First-level_pointer/note.txt`**：`sizeof` vs `strlen` 的区别，`char str[] = "Hello"` 占 6 字节（含 `'\0'`）而 `strlen` 返回 5；以及各基础类型在三种平台下的大小对照表（注意 `long` 在 Windows 64 位下是 4 字节，Linux 64 位下是 8 字节）。
- **`Memory_management/note.txt`**：内存四区（全局区、代码段、栈区、堆区）的概念；动态内存（堆区，手动分配手动释放）与静态内存（栈区，自动分配自动释放）的区别；以及一段带注释的实验代码，验证了 `malloc` 返回的堆地址在多次赋值过程中保持不变，并强调**未释放会内存泄漏、重复释放是错误**。

## 已发现可以改进的地方

以下问题目前保留在代码里，作为学习记录（编译时 `-Wall` 会给出警告）：

1. **用 `%d` 打印指针地址**：`const_ptr_demo.c`、`double_ptr_demo.c` 中的 `printf("%d %d\n", p, &a)` 等语句，`%d` 期望 `int` 而实参是指针类型。在 64 位平台上指针是 8 字节、`int` 是 4 字节，属于格式串与实参不匹配，是未定义行为。正确做法是用 `%p` 并转换类型：`printf("%p\n", (void *)p)`。
2. **用 `%lu` 打印 `sizeof` 的结果**：`sizeof_array_vs_pointer.c` 中的 `%lu` 与该平台下 `sizeof` 的实际类型不匹配（MinGW 下报 `long long unsigned int`）。`sizeof` 的返回值类型是 `size_t`，可移植的写法是 `%zu`。
3. `Exchange_Num.c` 的 `swap` 返回了 `a` 并在 `main` 里解引用打印——返回 `int*` 并非交换函数所必需，返回 `void` 语义更清晰；这里作为"函数返回指针"的练习保留。
4. `my_strdup` / `my_strndup` 中的 `printf` 提示信息混在库函数逻辑里，如果将来要做成通用工具，建议把错误提示交给调用方处理，函数本身只通过返回值报告失败。

## 后续练习方向

- [ ] `realloc` 动态扩容，实现一个可增长的动态数组
- [ ] 常见内存错误复现：越界写、use-after-free、内存泄漏（配合 ASan 任务观察报错信息）
- [ ] 函数指针与回调（`qsort` 的 `cmp` 参数）
- [ ] 指针数组 vs 数组指针（`int *a[10]` 与 `int (*a)[10]`）
- [ ] 结构体指针、链表的基本操作

## 协议

个人学习仓库，代码可自由参考。
