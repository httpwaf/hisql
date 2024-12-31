# hisql

#### 一 、介绍
hisql是一款开源数据库防火墙，支持MySQL、MariaDB、Oracle、PostgreSQL等。

#### 二 、两种安装架构
##### 1、直接安装在数据库服务器上

​    服务器原端口3306改为其他如3307，然后防火墙占用3306即可。

    防火墙（3306)<------------->本机127.0.0.1:3307

##### 2、独立部署，反向代理W据库服务器

    防火墙（3306)<------------->数据库服务器:3306



#### 三、安装教程
支持Linux系统，保证可以上网，以root权限运行下面命令：

1、 安装第三方编译库：

        CentOS：yum install sqlite-devel.x86_64
        
        Ubuntu：sudo apt-get install libsqlite3-dev
        
2 、make

3、./hisql或者./hisql -c ./hisql.conf启动运行，默认占用3307端口，反向代理本机3306端口

4、test_sql_injection.txt有常见的SQL注入语句，用任何MySQL管理工具连接3307端口执行，hisql如果打印出报警语句，则运行正常。


#### 四、商业版演示地址

开源版本仅支持MySQL，商业版才有WEB管理，核心基于更高性能的语义分析和机器学习引擎，也可以开源，演示地址 [http://101.42.31.94/dbpages/](http://101.42.31.94/dbpages/)

更多产品演示[http://101.42.31.94:9998/prochtml/open_source.html](http://101.42.31.94:9998/prochtml/open_source.html)

#### 五、源码部署请加微信号httpwaf

![](https://gitee.com/httpwaf/httpwaf/raw/master/img/wechat.png)

#### 六、来一张首页大图

![](https://gitee.com/httpwaf/hisql/raw/master/img/home.png)
