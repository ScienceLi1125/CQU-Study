'''企业员工管理系统 ———— 数据库增删查改操作
# 创建表
cur.execute("CREATE TABLE student(id integer,name varchar,sex varchar);")
# 插入数据
cur.execute("INSERT INTO student(id,name,sex) VALUES(%s,%s,%s)",(1,'Aspirin','M'))
cur.execute("INSERT INTO student(id,name,sex) VALUES(%s,%s,%s)",(2,'Taxol','F'))
cur.execute("INSERT INTO student(id,name,sex) VALUES(%s,%s,%s)",(3,'Dixheral','M'))
# 执行查询操作
cur.execute('SELECT * FROM student')
# 获取查询操作的结果，返回一个元组列表，每个元组代表查询结果中的一行数据
results=cur.fetchall()
print (results)
# 提交事务
conn.commit()
# 关闭数据库连接，释放资源
conn.close()
'''

import psycopg2
import traceback
from prettytable import PrettyTable

# 增加员工信息
def Creat_Employee(cur):
    print("--------增加员工信息--------")
    employee_id = input("请输入员工编号：")
    employee_name = input("请输入员工姓名：")
    sex = input("请输入员工性别（未定按回车继续）：")
    department = input("请输入员工部门：")
    job = input("请输入员工职位（未定按回车继续）：")
    salary = input("请输入员工工资（未定按回车继续）：")
    telephone = input("请输入员工电话：")
    seniority = input("请输入员工工龄（未定按回车继续）：")
    office = input("请输入员工办公室（未定按回车继续）：")

    if(sex == ""):
        sex = "0"
    if(job == ""):
        job = "0"
    if(salary == ""):
        salary = "0"
    if(seniority == ""):
        seniority = "0"
    if(office == ""):
        office = "000"

    try:
        cur.execute("INSERT INTO Employee VALUES(%s,%s,%s,%s,%s,%s,%s,%s,%s);", 
                    (employee_id,employee_name,sex,department,job,salary,telephone,seniority,office))
        conn.commit()
        print("添加成功！")
    except Exception as e:
        print("添加失败，请检查！")
        print("An exception occurred: ", e)
        print(traceback.format_exc())
    return


# 删除员工信息
def Delet_Employee(cur):
    print("--------删除员工信息--------")
    employee_id = input("请输入要删除的员工编号：")

    try:
        cur.execute("DELETE FROM Employee WHERE employee_id=%s;", (employee_id,))
        conn.commit()
        print("删除成功！")
    except Exception as e:
        print("删除失败，请检查！")
        print("An exception occurred: ", e)
        print(traceback.format_exc())
    return


# 查询员工信息
def Query_Employee(cur):
    print("--------查询员工信息--------")
    print("1.按员工编号查询员工信息")
    print("2.按部门编号查询员工信息")
    print("3.查询企业所有员工信息")
    choice = input("请输入查询员工的查询方式（只输入序号）：")
    if(choice == '1'):
        employee_id = input("请输入待查询的员工编号：")
        try:
            cur.execute("SELECT * FROM Employee WHERE employee_id=%s;", (employee_id,))
            print("查询成功！")
            results = cur.fetchall()
            table = PrettyTable()   # 调用API创建PrettyTable对象
            table.add_column('编号', [Employee[0] for Employee in results])
            table.add_column('姓名', [Employee[1] for Employee in results])
            table.add_column('性别', [Employee[2] for Employee in results])
            table.add_column('部门', [Employee[3] for Employee in results])
            table.add_column('职位', [Employee[4] for Employee in results])
            table.add_column('工资', [Employee[5] for Employee in results])
            table.add_column('电话', [Employee[6] for Employee in results])
            table.add_column('工龄', [Employee[7] for Employee in results])
            table.add_column('办公室', [Employee[8] for Employee in results])
            print(table)
        except Exception as e:
            print("查询失败，请检查！")
            print("An exception occurred: ", e)
            print(traceback.format_exc())
    elif(choice == '2'):
        department = input("请输入待查询的部门编号：")
        try:
            cur.execute("SELECT COUNT(*) FROM Employee WHERE department=%s", (department,))
            print("查询成功！")
            results = cur.fetchall()
            print("%s共有%d个员工，他们的相关信息见下表" % (department, results[0][0]))
            cur.execute("SELECT * FROM Employee WHERE department=%s", (department,))
            results = cur.fetchall()
            table = PrettyTable()
            table.add_column('编号', [Employee[0] for Employee in results])
            table.add_column('姓名', [Employee[1] for Employee in results])
            table.add_column('电话', [Employee[6] for Employee in results])
            print(table)
        except Exception as e:
            print("查询失败，请检查！")
            print("An exception occurred: ", e)
            print(traceback.format_exc())  
    elif(choice == '3'):
        cur.execute("SELECT COUNT(*) FROM Employee")
        results = cur.fetchall()
        print("企业共有%d个员工，他们的相关信息见下表" % (results[0][0]))
        cur.execute("SELECT * FROM Employee")
        results = cur.fetchall()
        table = PrettyTable()
        table.add_column('编号', [Employee[0] for Employee in results])
        table.add_column('姓名', [Employee[1] for Employee in results])
        table.add_column('部门', [Employee[3] for Employee in results])
        table.add_column('电话', [Employee[6] for Employee in results])
        print(table)
    else:
        print("查询失败，请检查！")
    return


# 修改员工信息
def Update_Employee(cur):
    print("--------修改员工信息--------")
    try:
        employee_id = input("请输入待修改的员工编号：")
        if(input("是否修改该员工姓名(Y/N)：") == 'Y'):
            employee_name = input("请输入该员工新姓名：")
            cur.execute("UPDATE Employee SET employee_name=%s WHERE employee_id=%s;",(employee_name, employee_id))
            conn.commit()
        if(input("是否修改该员工性别(Y/N)：") == 'Y'):
            sex = input("请输入该员工新性别：")
            cur.execute("UPDATE Employee SET sex=%s WHERE employee_id=%s;",(sex, employee_id))
            conn.commit()
        if(input("是否修改该员工部门(Y/N)：") == 'Y'):
            department = input("请输入该员工新部门：")
            try:
                cur.execute("UPDATE Employee SET department=%s WHERE employee_id=%s;", (department, employee_id))
                conn.commit()
            except Exception:
                print("该部门不存在，请检查")
        if(input("是否修改该员工职位(Y/N)：") == 'Y'):
            job = input("请输入该员工新职位：")
            cur.execute("UPDATE Employee SET job=%s WHERE employee_id=%s;", (job, employee_id))
            conn.commit()
        if(input("是否修改该员工工资(Y/N)：") == 'Y'):
            salary = input("请输入该员工新工资：")
            cur.execute("UPDATE Employee SET salary=%s WHERE employee_id=%s;",(salary, employee_id))
            conn.commit()
        if(input("是否修改该员工电话(Y/N)：") == 'Y'):
            telephone = input("请输入该员工新电话：")
            cur.execute("UPDATE Employee SET telephone=%s WHERE employee_id=%s;",(telephone, employee_id))
            conn.commit()
        if(input("是否修改该员工工龄(Y/N)：") == 'Y'):
            seniority = input("请输入该员工新工龄：")
            cur.execute("UPDATE Employee SET seniority=%s WHERE employee_id=%s;",(seniority, employee_id))
            conn.commit()
        if(input("是否修改该员工办公室(Y/N)：") == 'Y'):
            office = input("请输入该员工新办公室：")
            cur.execute("UPDATE Employee SET office=%s WHERE employee_id=%s;",(office, employee_id))
            conn.commit()
        print("修改成功！")
    except Exception as e:
        print("修改失败，请检查！")
        print("An exception occurred: ", e)
        print(traceback.format_exc())
    return

if __name__ == "__main__":
    # 创建连接对象
    conn=psycopg2.connect(database="db_2020_01",user="db_user2020_27",
                        password="db_user@123",host="116.205.157.173",port=8000)
    # 创建指针对象
    cur=conn.cursor()

    # 创建Department表和Employee表
    cur.execute("CREATE TABLE IF NOT EXISTS Department(department_id VARCHAR(8) PRIMARY KEY,department_name VARCHAR(16) NOT NULL,duty VARCHAR(16),building VARCHAR(16));")
    cur.execute("CREATE TABLE IF NOT EXISTS Employee(employee_id VARCHAR(8) PRIMARY KEY,employee_name VARCHAR(16) NOT NULL,sex BOOLEAN,department VARCHAR(8) NOT NULL,job VARCHAR(16),salary INTEGER,telephone VARCHAR(16) NOT NULL,seniority INTEGER,office VARCHAR(16),FOREIGN KEY (department) REFERENCES Department(department_id));")
    # 向部门表中添加数据
    cur.execute("INSERT INTO Department (department_id,department_name,duty,building) VALUES(%s,%s,%s,%s)",('CQU001','行政部门','行政','主教A'))
    cur.execute("INSERT INTO Department (department_id,department_name,duty,building) VALUES(%s,%s,%s,%s)",('CQU002','财务部门','财政','主教B'))
    cur.execute("INSERT INTO Department (department_id,department_name,duty,building) VALUES(%s,%s,%s,%s)",('CQU003','技术部门','技术','主教C'))
    cur.execute("INSERT INTO Department (department_id,department_name,duty,building) VALUES(%s,%s,%s,%s)",('CQU004','客服部门','客服','主教D'))
    
    # 提交事务
    conn.commit()

    # 企业员工管理系统主菜单
    print("----------------欢迎使用CQU企业员工管理系统----------------")
    print("    增加员工信息请输入1")
    print("    删除员工信息请输入2")
    print("    查询员工信息请输入3")
    print("    修改员工信息请输入4")
    print("    退出请输入Q")
    while True:
        print("--------------------------------")
        choice = input("请根据需求选择序号进行相应操作：")
        if(choice == '1'):
            Creat_Employee(cur)
        elif(choice == '2'):
            Delet_Employee(cur)
        elif(choice == '3'):
            Query_Employee(cur)
        elif(choice == '4'):
            Update_Employee(cur)
        print("--------------------------------")
        if(input("输入Q退出，其余任意键继续") == 'Q'):
            break
    print("----------------成功退出CQU企业员工管理系统----------------")
    
    # 关闭数据库连接，释放资源
    conn.close()