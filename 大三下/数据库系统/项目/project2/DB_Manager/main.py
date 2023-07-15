import re
from DBManager import DBManager


def main():
    print('====================欢迎使用数据库系统====================')

    # 生成数据库管理器对象
    dbm = DBManager()

    # 初始化环境
    dbm.init()

    # 获取用户输入的指令
    instr = input(" - 请输入指令: ")

    # 默认数据库名称
    db_name = dbm.DEFAULT_DB_NAME

    # 解析用户输入的指令
    while instr != "quit":
        # 选择数据库
        if re.fullmatch(dbm.use_dbs_instr, instr):
            db_name = dbm.analyse_use_db(instr)
        # 比较索引
        elif instr == "compare":
            dbm.analyse_instr(instr, db_name, True)
        # 普通SQL语句
        else:
            dbm.analyse_instr(instr, db_name)

        instr = input("\n==========================================================\n - 请输入指令: ")

    print("\n\n======================= 退出成功! =======================")


if __name__ == '__main__':
    main()
