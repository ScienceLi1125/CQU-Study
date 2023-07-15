 --创建四个表并为其属性选择合适的域、合适的主码和外键约束，插入表中数据
CREATE TABLE  teacher (
    T_ID INT PRIMARY KEY,
    TNAME VARCHAR(20),
    DEPT VARCHAR(20),
    SALARY INT
);

INSERT INTO teacher (T_ID, TNAME, DEPT, SALARY) VALUES
(14001, 'Katz', 'CS', 75000),
(14002, 'Crick', 'Biology', 72000),
(14003, 'Gold', 'Physics', 87000),
(14004, 'Einstein', 'Physics', 95000),
(14005, 'Kim', 'CS', 65000),
(14006, 'Wu', 'Finance', 90000),
(14007, 'Brandt', 'CS', 65000),
(14008, 'Singh', 'Finance', 80000);

CREATE TABLE student (
    S_ID VARCHAR(20) PRIMARY KEY,
    SNAME VARCHAR(20),
    DEPT VARCHAR(20),
    AGE INT,
    GENDER VARCHAR(2)
);

INSERT INTO student (S_ID, SNAME, DEPT, AGE, GENDER) VALUES
('S1', 'Wangfeng', 'Physics', 20, 'M'),
('S2', 'Liu fang', 'Physics', 19, 'M'),
('S3', 'Chen yun', 'CS', 22, 'M'),
('S4', 'Wu kai', 'Finance', 19, 'M'),
('S5', 'Liu li', 'CS', 21, 'F'),
('S6', 'Dongqing', 'Finance', 18, 'F'),
('S7', 'Li', 'CS', 19, 'F'),
('S8', 'Chen', 'CS', 21, 'F'),
('S9', 'Zhang', 'Physics', 19, 'M'),
('S10', 'Yang', 'CS', 22, 'F'),
('S11', 'Wang', 'CS', 19, 'F');

CREATE TABLE course (
    CID VARCHAR(20) PRIMARY KEY,
    CNAME VARCHAR(20),
    DEPT VARCHAR(20),
    CREDITS FLOAT,
    TEACHER VARCHAR(20));

INSERT INTO course (CID, CNAME, DEPT, CREDITS, TEACHER) VALUES
('C1', 'DB', 'CS', 2.0, 'Li'),
('C2', 'maths', 'Mathematics', 2.0, 'Ma'),
('C3', 'chemistry', 'Chemistry', 2.5, 'Zhou'),
('C4', 'physics', 'Physics', 1.5, 'Shi'),
('C5', 'OS', 'CS', 2.0, 'Wen'),
('C6', 'Database', 'CS', 2.0, 'Katz'),
('C7', 'Algorithm', 'CS', 2.5, 'Gold'),
('C8', 'Java', 'CS', 1.5, 'Einstein'),
('C9', 'Marketing', 'Finance', 2.0, 'Wu');

CREATE TABLE SC (
    S_ID VARCHAR(20),
    CID VARCHAR(20),
    GRADE INT,
    PRIMARY KEY (S_ID, CID),
    FOREIGN KEY (S_ID) REFERENCES student(S_ID),
    FOREIGN KEY (CID) REFERENCES course(CID)
);

INSERT INTO SC (S_ID, CID, GRADE) VALUES
('S1', 'C1', 70),
('S1', 'C3', 81),
('S2', 'C4', 92),
('S2', 'C2', 85),
('S3', 'C1', 65),
('S3', 'C5', 57),
('S4', 'C1', 87),
('S5', 'C4', 83);

 --修改信息：在student表中，为姓名为‘Zhang’且系信息错填为‘Physics’的同学修改信息，将其系信息修改为‘CS’
UPDATE student
SET DEPT = 'CS'
WHERE SNAME = 'Zhang' AND DEPT = 'Physics';

 --删除信息：删除teacher表中，属于Finance学院的教师信息
DELETE FROM teacher
WHERE DEPT = 'Finance';

 --case语句修改信息：在teacher表中，为工资低于或等于70000的教师增长10%的工资，为工资高于70000的教师增长5%的工资
UPDATE teacher
SET SALARY = CASE
    WHEN SALARY <= 70000 THEN SALARY * 1.1
    ELSE SALARY * 1.05
END;

 --数据查询：基于teacher表，找出“物理系Physics和生物系Biology”所有教师的名字和工资
SELECT TNAME, SALARY
FROM teacher
WHERE DEPT = 'Physics' OR DEPT = 'Biology';

 --数据查询：基于teacher表，列出教师所在的各个系名，要求每个系名仅出现一次
SELECT DISTINCT dept
FROM teacher;

 --数据查询：基于teacher表，希望查看“若将每位教师的工资提高20%后”各位教师的姓名和工资是多少
SELECT TNAME, SALARY*1.2 as NewSALARY
FROM teacher;

 --数据查询：基于表student、SC和course，查看到计算机系CS的每位学生所选课程的所有信息，包括学生姓名、所在系、课程名称、课程学分的情况
SELECT student.SNAME, student.DEPT, course.CNAME, course.CREDITS
FROM student JOIN SC ON student.S_ID = SC.S_ID JOIN course ON SC.CID = course.CID
WHERE student.DEPT = 'CS';

 --复杂查询：查询全体学生的姓名、年龄
SELECT SNAME, AGE
FROM student;

 --复杂查询：查询所有选修过课的学生的学号
SELECT DISTINCT S_ID
FROM SC;

 --复杂查询：查询考试成绩低于60分的学生的学号
SELECT DISTINCT S_ID
FROM SC
WHERE GRADE < 60;

 --复杂查询：查询年龄在20至23之间的学生姓名、性别和年龄
SELECT SNAME, GENDER, AGE
FROM student
WHERE AGE BETWEEN 20 AND 23;

 --复杂查询：查询所有姓liu的学生的学号、姓名和年龄
SELECT S_ID, SNAME, AGE
FROM student
WHERE SNAME LIKE '%Liu%';

 --复杂查询：查询学习C1课程的学生最高分数
SELECT MAX(GRADE)
FROM SC
WHERE CID = 'C1';

 --复杂查询：查询各个课程号与相应的选课人数
SELECT CID, COUNT(*) AS S_NUM
FROM SC
GROUP BY CID;

 --复杂查询：查询选修C3课程的学生的姓名
SELECT student.SNAME FROM student, SC
WHERE student.S_ID = SC.S_ID AND SC.CID = 'C3';

 --复杂查询：查询每一门课程的平均成绩
SELECT CID, AVG(GRADE) AS AVG_GRADE
FROM SC
GROUP BY CID;

 --删除筛选：学生只能选择自己学院开设的课程。发现CS学院有的同学选择了其他学院开设的课程。在SC表中删除这些错选的记录
DELETE FROM SC
WHERE S_ID IN (
    SELECT student.S_ID FROM student
    WHERE student.DEPT = 'CS'
) AND CID NOT IN (
    SELECT course.CID FROM course
    WHERE course.DEPT = 'CS'
);
