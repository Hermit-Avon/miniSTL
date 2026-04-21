# miniSTL 学习项目需求文档

## 1. 项目目标
通过手写一个简化版 STL（miniSTL），系统强化以下 C++ 能力：

- 模板编程（class template、function template、偏特化）
- 资源管理与 RAII（构造/析构、拷贝/移动语义）
- 迭代器抽象与泛型算法协作
- 异常安全（basic/strong guarantee）
- 工程化能力（单元测试、基准测试、文档与代码规范）

## 2. 范围定义（MVP）
先实现一个可用的最小集合，再逐步扩展：

### 2.1 必做容器

- `vector<T>`
- `list<T>`（双向链表）
- `deque<T>`（可作为进阶，若时间有限可放第二阶段）
- `stack<T, Container>`（容器适配器）
- `queue<T, Container>`（容器适配器）

### 2.2 必做迭代器与 traits

- 迭代器分类标签（input/output/forward/bidirectional/random access）
- `iterator_traits`
- 容器自身迭代器（至少支持 `vector` 和 `list`）

### 2.3 必做算法（最小可用）

- 非修改类：`find`、`count`、`equal`
- 修改类：`copy`、`fill`、`swap`
- 排序/有序相关：`sort`（可先仅支持随机迭代器）

### 2.4 必做工具组件

- `allocator<T>`（最简版，封装 `::operator new/delete`）
- `construct/destroy`（对象原地构造与析构）
- `move`、`forward`、`pair`（可精简实现）

## 3. 非目标（当前阶段不做）

- 不追求 100% 对齐标准库全部接口
- 不要求所有算法都支持 constexpr
- 不实现并行算法与执行策略
- 不实现完整 `std::string`、`unordered_*`、`map/set` 红黑树（后续扩展）

## 4. 功能要求（按模块）

## 4.1 `vector<T>`

至少提供：

- 构造：默认构造、`n` 个元素构造、范围构造、拷贝构造、移动构造
- 赋值：拷贝赋值、移动赋值、initializer_list 赋值（可选）
- 元素访问：`operator[]`、`at`、`front`、`back`、`data`
- 迭代：`begin/end`、`cbegin/cend`
- 容量：`size`、`capacity`、`empty`、`reserve`、`shrink_to_fit`（可选）
- 修改：`push_back`、`pop_back`、`insert`、`erase`、`clear`、`resize`、`swap`

关键行为要求：

- 扩容策略明确（如 1.5 倍或 2 倍）
- 扩容和插入时保持异常安全，不得内存泄漏
- 失效规则文档化（iterator/reference 何时失效）

## 4.2 `list<T>`

至少提供：

- 双向链表节点设计（含哨兵节点）
- `begin/end`，支持前后移动迭代
- `push_front/push_back/pop_front/pop_back`
- `insert/erase/clear`
- `size/empty/front/back`

关键行为要求：

- 单次插入/删除为 O(1)
- 删除节点后不访问悬垂指针
- 保证析构完整释放所有节点

## 4.3 迭代器与算法协作

- 算法应通过迭代器工作，而非绑定具体容器
- 为不同迭代器类别提供必要重载或 tag dispatch
- 至少给出 3 个“不同容器 + 同一算法”的演示测试

## 5. 质量要求

### 5.1 编码规范

- C++17 或 C++20（建议 C++17 起步）
- 打开警告并视作错误：`-Wall -Wextra -Werror -pedantic`
- 模块划分清晰：`include/`、`src/`、`tests/`

### 5.2 测试要求

至少包含以下测试类型：

- 功能测试：每个公开接口至少 1 个用例
- 边界测试：空容器、单元素、大量元素
- 语义测试：拷贝后独立、移动后可析构且状态可定义
- 异常测试：人为注入异常（如构造抛异常）验证无泄漏

建议工具：

- 单元测试：GoogleTest / Catch2（二选一）
- 内存检查：ASan、Valgrind（至少一种）

### 5.3 性能观察（非硬指标）

- 与 `std::vector/std::list` 做简单对比（push/insert/遍历）
- 记录时间复杂度是否符合预期
- 输出 benchmark 报告（markdown 即可）

## 6. 分阶段实施计划

### 阶段 0：基础设施

- 搭建 CMake 工程
- 引入测试框架
- 搭建 CI（可选，GitHub Actions）

验收标准：

- 能一键构建并运行测试

### 阶段 1：内存与工具层

- `allocator`、`construct/destroy`、`move/forward`
- `iterator_traits` 和基础 type traits（可最小集）

验收标准：

- 基础工具测试通过

### 阶段 2：`vector`

- 完成核心接口与迭代器
- 补齐异常安全与边界测试

验收标准：

- `vector` 主要接口测试通过
- ASan 下无明显内存问题

### 阶段 3：`list`

- 完成双向链表及其迭代器
- 完成常见修改操作

验收标准：

- `list` 主要接口测试通过

### 阶段 4：算法与适配器

- 实现 `find/copy/fill/sort`
- 实现 `stack/queue`
- 完成跨容器算法测试

验收标准：

- 算法可在不同容器迭代器上工作

### 阶段 5：总结与扩展

- 性能对比报告
- 复盘设计取舍
- 规划 `deque`、`rb_tree`、`map/set` 扩展

验收标准：

- 形成可阅读的技术总结文档

## 7. 交付物

- 源码（`include/` + `src/`）
- 测试代码（`tests/`）
- 构建脚本（`CMakeLists.txt`）
- 本需求文档（`miniSTL_requirements.md`）
- 进展记录（`progress.md`，每阶段至少一次总结）

## 8. 建议目录结构

```text
miniSTL/
  include/
    mini_stl/
      vector.h
      list.h
      iterator.h
      algorithm.h
      allocator.h
      utility.h
  src/
  tests/
    test_vector.cpp
    test_list.cpp
    test_algorithm.cpp
  benchmark/
  docs/
  CMakeLists.txt
  miniSTL_requirements.md
```

## 9. 完成定义（Definition of Done）

满足以下条件视为第一版完成：

- 必做容器、迭代器、算法全部通过测试
- 在 ASan 或 Valgrind 下无确定性内存泄漏
- 关键接口复杂度符合预期（如 `vector` 尾插均摊 O(1)）
- 已产出阶段总结，能解释核心设计取舍
