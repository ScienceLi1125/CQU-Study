# 数据库管理系统
> CQU《数据库系统》课程项目2
> 关系型数据库采用自描述的方式进行数据库系统管理，关于关系的相关数据也存储在数据库管理系统里。针对关系型数据库存储、SQL执行，进行需求分析，并设计一个简单的数据库系统SQL引擎模块，根据设计模拟实现SQL基本操作、数据存储等，主要实现：数据库创建、表格创建、数据添加、删除、更新等操作过程中，数据库系统SQL引擎所进行的各方面的管理和操作（包含硬盘数据块）；设计索引，并比较有索引和无索引的区别。
> 模拟实现采用：python或者Java实现具体功能，设计模型所需求存储的数据可采用数据库管理系统、excel或者文本文件，可用文件模拟硬盘数据块，SQL语句采用函数实现。

## 建表操作
### 1. 选择数据库 
``` bash
use database_name   #默认为default
```

### 2. 创建数据库
``` bash
create database database_name
```

### 3. 创建表
``` bash
create table table_name (column_name column_type, ...)
```
其中 `column_type` 的可选范围为 `[int, null, varchar]`；

## 显示操作
### 1. 显示元数据
``` bash
show meta data
```

### 2. 显示数据库
``` bash
show databases
```

### 3. 显示表
``` bash
show tables
```

## 查询操作
### 1. select投影
``` bash
select * from table_name
```

### 2. select投影2
``` bash
select column_name, ... from table_name
```

### 3. select where查询
``` bash
select column_name, ... from table_name where condition
```

## 删除操作
### 1. 删除数据库
``` bash
drop database database_name
```

### 2. 删除表
``` bash
use database database_name
drop table table_name
```

### 3. 删除表项 
``` bash
use database database_name
delete from table_name where condition
```

## 插入操作
### 1. 给table_name增加表项
``` bash
insert into table_name values(value1, value2, ...)
```
如果插入值多于表的属性，会报错 "error:too many values"

## 修改操作
### 1. 修改表项
``` bash
update table_name set column_name=value where condition
```

若想清空数据库，需要删除database_meta_data.csv、table_meta_data.csv和各数据库文件夹