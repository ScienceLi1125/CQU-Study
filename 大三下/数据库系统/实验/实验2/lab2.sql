-- 创建部门表
CREATE TABLE Department(
    department_id VARCHAR(8) PRIMARY KEY,
    department_name VARCHAR(16) NOT NULL,
    duty VARCHAR(16),
    building VARCHAR(16)
)
-- 创建员工表
CREATE TABLE Employee(
    employee_id VARCHAR(8) PRIMARY KEY,
    employee_name VARCHAR(16) NOT NULL,
    sex BOOLEAN,
    department VARCHAR(8) NOT NULL,
    job VARCHAR(16),
    salary INTEGER,
    telephone VARCHAR(16) NOT NULL,
    seniority INTEGER,
    office VARCHAR(16),
    FOREIGN KEY (department)
        REFERENCES Department(department_id)
)

-- 向部门表中添加数据
INSERT INTO Department (department_id,department_name,duty,building) VALUES
('CQU001','行政部门','行政','主教A'),
('CQU002','财务部门','财政','主教B'),
('CQU003','技术部门','技术','主教C'),
('CQU004','客服部门','客服','主教D');

-- 向员工表中添加数据
INSERT INTO Employee (employee_id,employee_name,sex,department,job,salary,telephone,seniority,office) VALUES
('20170001','李老师',1,'CQU001','行政主管',6000,'10086',5,'201'),
('20160031','王老师',0,'CQU002','财务主管',5000,'10088',3,'303'),
('20200045','张老师',1,'CQU003','技术工程师',8000,'10087',6,'212'),
('20190076','孙老师',0,'CQU004','后勤主任',7000,'10089',4,'113'),
('20180082','李老师',1,'CQU001','行政科员',4000,'10085',1,'408');

-- 检查表中数据
SELECT * FROM Department
SELECT * FROM Employee
