# 使用说明
在根目录下安装依赖
- pip install -r requirements.txt

(推荐使用虚拟环境virtualenv,不容易冲突)

然后cd到testapp下,运行

- python manage.py runserver

开发请使用develop分支，git bash 运行

- git clone -b develop https://gitee.com/wangxingran222/voicebar-backend.git

## 注意

初次运行需要使用

- python manage.py makemigrations
- python manage.py migrate

来建表

在./testapp/testapp/settings.py里面修改DATABASES的设置,推荐在本地自己搭建MySQL SERVER来调试使用