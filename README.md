# hisql

#### 一 、介绍
hisql是一款数据库防火墙，核心基于高性能开源引擎打造，支持DB2、MySQL、MariaDB、Oracle、PostgreSQL等。

#### 二 、两种安装架构
##### 1、直接安装在数据库服务器上

​    服务器原端口3306改为其他如3308，然后防火墙占用3306即可。

    防火墙（3306)<------------->本机127.0.0.1:3306

##### 2、独立部署，反向代理W据库服务器

    防火墙（3306)<------------->数据库服务器:3306



#### 三、安装教程
支持Linux系统，保证可以上网，以root权限运行下面命令：

1、 go get -u github.com/nim4/DBShield

2 、 $ $GOPATH/bin/DBShield -h


#### 四、商业版演示地址

商业版才有WEB管理，也可以开源，演示地址 [http://59.110.1.135/dbpages/](http://59.110.1.135/dbpages/)

#### 五、源码部署请加微信号httpwaf

![](https://gitee.com/httpwaf/httpwaf/raw/master/img/wechat.png)

#### 六、来一张首页大图

![](https://gitee.com/httpwaf/hisql/raw/master/img/home.png)