# phonedata
电话号码归属数据库,phone number location database

## 描述
打造全球最大最全的电话号码数据库

## 特性
1. 支持国内物联网和虚拟号码
2. 支持移动和座机号码
3. 支持国外号码(计划中)
4. 支持位置信息
5. 支持广电,移动,联通,电信号码
6. 支持卫星号码
7. 支持获取运营商
8. 支持携号转网

## 数据库最新日期
2025.04.14

#### 索引区数量
517259

## 数据格式
协议头可以在https://github.com/libxengine/libxengine/blob/master/XEngine_Include/XEngine_ProtocolHdr.h 找到.所属项目是https://github.com/libxengine/libxengine  
电话号码数据格式有四个分区,他们分别是头分区.运营商分区,位置分区,号码分区.每个分区前面有一个XENGINE_PROTOCOLHDR的协议头  
可以通过协议头来验证数据格式是否正确,协议头wHeader和wTail可以验证是否是标准协议  
unOperatorType和unOperatorCode 可以验证协议类型,wCrypto可以验证后续内容是否加密,unPacketSize可以得到数据大小

#### 头分区
XENGIEN_PROTOCOLHDR+版本号.30个字节头+8个字节版本,一共38个字节分区头.具体格式如下  
XENGINE_PROTOCOLHDR+20240622

#### 运营商分区
XENGIEN_PROTOCOLHDR+类型-运营商名称,....,通过空格分割,通过-符号映射,协议头的wPacketSerial被设置为映射列表个数  
XENGINE_PROTOCOLHDR+0-UNKNOW 1-CMCC 2-CUCC....等等比如0表示未知,1表示CMCC中国移动

#### 位置分区
XENGIEN_PROTOCOLHDR+省份-城市-区号,30个字节头.后续大小不固定,通过头中的负载大小来确定后续内容大小.具体格式如下  
XENGINE_PROTOCOLHDR+028-四川-成都

#### 号码分区
XENGINE_PROTOCOLHDR的负载大小为索引区个数大小,不是负载后续大小,索引区数据格式大小不固定,通过\n来分割每个索引.  
具体格式是:号码,区号,号码类型,是否转网(转网后面需要跟上-原始网络类型),如下:  
XENGINE_PROTOCOLHDR+1994088-028-2-0,比如 如果是联通转短信1994088-028-2-0-1

## 如何贡献数据库
有两种方法可以提交合并新的电话号码.但是他们的格式你都需要按照下面的格式填写  
序号-号码-运营商-省份-城市-区号-携号转网(非携号转网设置为0,否则设置为原原运营商类型编号)  
1,199408840,电信,四川,成都,028,0  
按照上面的格式,以逗号分割,每行一个,序号需要自加,如果不清楚也可以按照下面的方法填写  
1,199408840,x,x,x,x,x   这种方法表示未知

#### 使用issues 
如果你想要简单方便,可以使用提交问题的方法提交新的电话号码给我们.  
你可以直接在问题列表新建个问题,把你想要加入的电话号码写到里面.可以不填写序号,比如:  
199408840,电信,四川,成都,0  

#### 使用PR
通过PR合并,这是推荐的方法,这种方式你将能够参与贡献,并且你的名字将在贡献列表中显示.  
写入格式按照上面的要求写入,比如,你想合并一个电信的号码,那么就在CTCC.txt添加:  
1,199408840,电信,四川,成都,028,0  
你需要把电话号码写入到Phone文件夹下的指定文件中.按照运营商:  
| 运营商英语| 运营商中文 |
| -------- | --------- |
| CMCC     | 中国移动   |
| CUCC     | 中国联通   |
| CTCC     | 中国电信   |
| CRTG     | 中国广电   |
| CTCC_V   | 电信虚拟   |
| CUCC_V   | 联通虚拟   |
| CMCC_V   | 移动虚拟   |
| CTCC_I   | 电信座机   |
| CUCC_I   | 联通座机   |
| CMCC_I   | 移动座机   |
| SATE     | 卫星通信   |
| IOT      | 物联网     |

###### 参与贡献
Fork 本仓库  
新建 Feat_xxx 分支  
提交代码  
新建 Pull Request  

## 代码结构
 - Data     数据库
 - Phone    提交记录文件夹
 - Source   示例文件夹
 - XEngine_PhoneNumber 原始数据转换程序

#### 示例代码

| 当前状态  | 编程语言 | 描述                  | 贡献者               |
|:-----    | :----    |:---------------------|:--------------------|
| 待开始    | [golang](Source/golang)         | golang 查询客户端实现        | 待确定 |
| 待开始    | [php](Source/php)               | php 查询客户端实现           | 待确定 |
| 待开始    | [java](Source/java)             | java 查询客户端实现          | 待确定 |
| 待开始    | [lua](Source/lua)               | 纯 lua 查询客户端实现        | 待确定 |
| 已完成    | [c/c++](Source/C/)               |  c/c++ 查询客户端实现        | [xengine](https://github.com/libxengine) |
| 待开始    | [rust](Source/rust)             | rust 查询客户端实现          | 待确定 |
| 待开始    | [python](Source/python)         | python 查询客户端实现        | 待确定 |
| 待开始    | [nodejs](Source/nodejs)         | nodejs 查询客户端实现        | 待确定 |
| 待开始    | [csharp](Source/csharp)         | csharp 查询客户端实现        | 待确定 |
| 待开始    | [erlang](Source/erlang)         | erlang 查询客户端实现        | 待确定 |
| 待开始    | [php_ext](Source/php7_ext)      | php c 扩展 xdb 查询客户端实现 | 待确定 |
| 待开始    | [nginx](Source/nginx)           | nginx 扩展 xdb 查询客户端实现 | 待确定 |

## 免责声明
本数据库仅用于学习研究,不得用于任何商业或非法用途,否则,一切后果请用户自负  
本数据库来源互联网,版权归原作者所有,本人只是整理,如有侵权,请告知删除