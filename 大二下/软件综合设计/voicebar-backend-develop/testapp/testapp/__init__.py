import pymysql
from pymysql import install_as_MySQLdb

pymysql.version_info = (2,1,1, "final", 0)
install_as_MySQLdb()