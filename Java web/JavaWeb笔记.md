# readMe
# 莫失莫忘
## 1L是什么意思
指的是数字1是长整型的，数字后边有时会加字母，不同的字母有不同的含义，比如1d指的这个1时double型，1f指的这个1是float，1L指的是long型。
## JavaEE的EE是什么意思
简单来说就是 Java enterprise edition，java企业版，多用于企业级开发，包括web开发等很多组件。
## java工程为什么在包名前加com
命名规范，按照网址倒叙命名方式，方便区分不同项目。
## DAO 是什么

## Spring 和 Sping MVC 什么关系？

> springmvc 是管理 controller 对象的容器，spring 是管理 service 和 dao 的容器。
> 所以我们在 springmvc 的配置文件里配置的扫描路径就是 controller 的路径，
>  spring 的配置文件里配的就是 service 和 dao 的路径。

# 学校版PPT指南
禁止(?)使用Lombok插件，禁止复制粘贴代码，觉得重要的代码必须自己手敲一遍，知道也不行（html除外）
我决定不再使用PDF注解，过于繁杂…你早该改了.jpg
> **纸上得来终觉浅，绝知此事要躬行！**

## Servlet基础1-2 
### request 等对象的作用周期 · · ·

 Servlet 作用： 处理客服端的Http请求并予以响应  
客户端发送请求（request）至服务器，服务器返回给客户端响应 （response）  
Servlet 生命周期五个阶段
 Tomcat服务器解析请求表单时的编码规则是：
• URL——UTF8 
• Body——ISO-8859-1
Get方法，参数在URL中 
• 浏览器的UTF8 -- 服务器的UTF8 -- response为UTF8 
Post方法，参数在body中 
• 浏览器的UTF8 -- 服务器的ISO-88591 -- 那么需要request为 UTF8 --  response为UTF8  
### 在web.xml文件里配置Servlet映射
 <servlet-name>——标准写法  servlet类名
 <servlet-class>——标准写法  servlet类的带包路径，就是package.package.java这样，
** 写错了就打不开，但是注解可以打开->用注解！！**

**每次更新必须重启server，否则结果不变（同样适用于Ubuntu上的问题🥴）**
```java
<servlet>
    <description></description>
    <servlet-name>Servlet名</servlet-name>
    <servlet-class>src下Java类的绝对路径</servlet-class>
</servlet>
<servlet-mapping>
    <servlet-name>上面写的Servlet名</servlet-name>
    <url-pattern>到时候访问的时候要输入的名，如/HelloWorld，记得加/</url-pattern>
</servlet-mapping>
```

### 指定输出的编码格式，输出中文
获得response和request编码，获取参数，输出到屏幕上的代码。
```java
response.setCharacterEncoding("utf-8");
response.setContentType("text/html;charset=UTF-8");

String pwd=request.getParameter("password");

PrintWriter out = response.getWriter();
out.println(pwd);
```
dopost方法中调用request设置格式：
  ![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1664267321433-3b81de14-c903-48db-ae86-d23d220fca40.png#averageHue=%23d6e0d8&clientId=u50067cfc-1294-4&errorMessage=unknown%20error&from=paste&height=81&id=u44e5fea2&name=image.png&originHeight=162&originWidth=1403&originalType=binary&ratio=1&rotation=0&showTitle=false&size=307812&status=error&style=none&taskId=u3d1a462d-6288-4c82-9022-545b15303b4&title=&width=702)
###  处理一系列表单元素 
```java
    	//这个paraNames是全部的表单元素
		Enumeration<String> paramNames = req.getParameterNames();
        while(paramNames.hasMoreElements())
        {
            //paraName是某一个表单元素
            String paramName = paramNames.nextElement();
            out.print("<TR><TD>" + paramName + "\n<TD>");
            
            //paramValues是该元素有几个值（单个的男/女，多个的群玉阁、月海亭……
            //如果手动操作，这里参数的名称应该和表单中的元素名字大小写一致
            String[] paramValues = req.getParameterValues(paramName);

            //仅有一个元素
            if (paramValues.length == 1)
            {
                //取出这个元素
                String paramValue = paramValues[0];
                //就是这个元素长度是0，没有数据传过来->没有操作
                if (paramValue.length() == 0)
                    out.println("<I>No Value</I>");
                else
                    out.println(paramValue);
            }
            else
            {
                out.println("<UL>");
                //遍历值的数组，输出值
                for (String paramValue : paramValues){
                    out.println("<LI>" + paramValue);
                }
                out.println("</UL>");
            }
        }
```
### getParameter & getAttribute
[getParameter和getAttribute区别(这下终于知道了)_CSDN博客](https://blog.csdn.net/m0_64210833/article/details/124148560?spm=1001.2101.3001.6650.10&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-10-124148560-blog-99984725.pc_relevant_aa)
getAttribute返回的数据类型是Object，需要转发的参数名在两个文件中应保持一致。
### fileupload，fileio下载
[https://commons.apache.org/proper/commons-fileupload/download_fileupload.cgi](https://commons.apache.org/proper/commons-fileupload/download_fileupload.cgi)
[https://commons.apache.org/proper/commons-io/download_io.cgi](https://commons.apache.org/proper/commons-io/download_io.cgi)
## JSP基础-指令
JSP 本质上就是⼀个 Servlet，主要负责交互并将最终界⾯呈现出来。  
声明变量`<% %>`或 `<%! %>`
输出 `<%= 要输出的量 %>`  
定义函数 `<%! %>`
代码 `<% %>`
` <%-- 注释 --%>  `
include 指令：插入其他 page 的内容，**可以是静态或动态页面**：`<%@ include file="HelloDate.jsp" %> `，只引用内容，地址栏不改变；或者是定义JSP页面的全局属性，如页面编码、页面用到一些包等。  
 <%@ page %>作用于整个JSP页面。包括静态的包含文件，但是不能作用于被动态包含进来的文件，如通过<jsp:include>包含的文件。 
 跳转 P30 `<jsp:forward page=“绝对URL或相对URL" />  `：**  URL地址并不发生变化   **
跳转到某个页面时附带传送数据
`<jsp:forward page="...">`
`<jsp:param name:="变量名"value="变量值"/>`
`[<jsp:param .../>`
`</jsp:forward>`
 这时目的文件必须是动态文件 (jsp或servlet可以，html不行)  
 P34 两种转发方式：转发与重定向： **转发是服务器行为，重定向是客户端行为（P36） **

**P40 include是静态引入，<jsp:include>是动态引入。**
** session单位：浏览器 **
## JSP高级
### JavaBean四个要求
要背！简单来说就是：**属性私有、提供（get，set）接口、（有）无参构造、实现序列化。**
P8：在 jsp 中写bean
 jsp:useBean在MVC中的共享范围：没有 page
## JDBC
填参数的下标是从1开始的，不是0，这一点注意一下。
**数据库字符串不用你自己写分号！！**
## mybatis
级联查询看我：
## Spring MVC / SSM
**jdk 不要用那个最新的 Oracle 17.0.2！！！**
**用电脑上 idea 帮你下的那个 jre 11 环境！！**
### 注解
1、@controller：     controller控制器层（注入服务）
2、@service ：         service服务层（注入dao）
3、@repository ：   dao持久层（实现dao访问）
4、@component：  标注一个类为Spring容器的Bean，（把普通pojo实例化到spring容器中，相当于配置文件中的<bean id="" class=""/>）
@GetMapping，处理get请求
@PostMapping，处理post请求
@PutMapping，处理put请求
@DeleteMapping，处理delete请求
### 什么是 log4j
Log4j是**一个开源项目，通过使用Log4j，我们可以控制日志信息输送的目的地是** 控制台 、文件、 GUI 组件……，也可以控制每一条日志的输出格式。
### 简单了解下 DTO 

### SSM 上手配置
视频看这个：
### SpringMVC返回ModelAndView和String的区别
省流：没有区别。
不省流：看
### ModelAndView.addObject()
> addObject(String attributeName,Object attributeValue)
> 该方法相当于 request.setAttribute，在页面上直接使用 ${attributeName}取值
> 如果方法的返回值是 ModelAndView，在创建的 html 页面可以通过${attributeName}定位到attributeValue。

# 课设
## jsp如何实现动态下拉式菜单

# IDEA相关
## 不要CV-IDEA的JavaWeb项目！！
我排了两个小时的错。。发现似乎一个项目对应一个Tomcat，你再复制了，复制品的tomcat对应的还是主项目的东西，加载的页面啥的还是主项目的东西，你在复制品里改了、或者是加了新的页面，但是主项目不知道啊，所以就会出现404访问不到，而且你在子项目里做的改动也p用没有，因为加载的还是主项目！！！
暂时不知道这个推论是否正确，不过即使原理不同，也89不离10了，感谢 **绯云2坡 **让我发现这个大问题，但是好淦噢，部署一个项目花老大劲，移植又得花好大劲，woc！！！

---

## idea导入eclipse的web项目

## idea配置maven
maven 初始 pom 文件：
```java
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>groupId</groupId>
    <artifactId>7-201002727-springMVC</artifactId>
    <version>1.0-SNAPSHOT</version>

    <properties>
        <maven.compiler.source>17</maven.compiler.source>
        <maven.compiler.target>17</maven.compiler.target>
    </properties>
    
</project>
```

**maven 是 spring MVC 或者 mybatis 那边的**
后知后觉版配置 maven （不是在一开始就选择了创建 maven 项目）：
**以后尽量不要再这样做了。。版本差错什么的受不了了啊~~~**
1.项目右击-添加框架支持，下拉，在 maven 那里打勾，确定
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1667184011969-57597d06-86d9-45aa-b36e-6547c87e6174.png#averageHue=%232d3149&clientId=ud36451ca-9ef1-4&from=paste&height=122&id=u380379dd&name=image.png&originHeight=244&originWidth=1106&originalType=binary&ratio=1&rotation=0&showTitle=false&size=98478&status=done&style=none&taskId=u8a152be7-5cdb-411f-ad9f-05616cbc5b6&title=&width=553)
出来应该是这个初始化界面：
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1667184104635-0b89fcaf-31d3-4cff-a665-afbecd5dc3d8.png#averageHue=%2327293a&clientId=ud36451ca-9ef1-4&from=paste&height=657&id=u799306b3&name=image.png&originHeight=1314&originWidth=2880&originalType=binary&ratio=1&rotation=0&showTitle=false&size=3401157&status=done&style=none&taskId=uce651e04-6b0d-41b7-8c8a-bc8a6cbf23c&title=&width=1440)
2.打开设置，将这里的仓库换成自己的
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1667184888913-56de825e-a169-454d-a89a-f00698f50368.png#averageHue=%23232538&clientId=ud36451ca-9ef1-4&from=paste&height=614&id=u5f8e932a&name=image.png&originHeight=1227&originWidth=2418&originalType=binary&ratio=1&rotation=0&showTitle=false&size=192968&status=done&style=none&taskId=u96469a9c-ff70-40e3-8307-c728994f273&title=&width=1209)
### maven 仓库全局设置

后面的 pom 上网搜吧
## idea 配置 Spring MVC

这个我没看完还是没看懂来着，总之就是不了了之的状态。

## idea 配置 SSM
ssm 初始 pom 如下：
```xml
<?xml version="1.0" encoding="UTF-8"?>

<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
	<modelVersion>4.0.0</modelVersion>

	<groupId>org.example</groupId>
	<artifactId>ssm</artifactId>
	<version>1.0-SNAPSHOT</version>
	<packaging>war</packaging>

	<name>ssm Maven Webapp</name>
	<!-- FIXME change it to the project's website -->
	<url>http://www.example.com</url>

	<properties>
		<project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
		<maven.compiler.source>1.7</maven.compiler.source>
		<maven.compiler.target>1.7</maven.compiler.target>
	</properties>

	<dependencies>
		<dependency>
			<groupId>junit</groupId>
			<artifactId>junit</artifactId>
			<version>4.11</version>
			<scope>test</scope>
		</dependency>
	</dependencies>

	<build>
		<finalName>ssm</finalName>
		<pluginManagement><!-- lock down plugins versions to avoid using Maven defaults (may be moved to parent pom) -->
			<plugins>
				<plugin>
					<artifactId>maven-clean-plugin</artifactId>
					<version>3.1.0</version>
				</plugin>
				<!-- see http://maven.apache.org/ref/current/maven-core/default-bindings.html#Plugin_bindings_for_war_packaging -->
				<plugin>
					<artifactId>maven-resources-plugin</artifactId>
					<version>3.0.2</version>
				</plugin>
				<plugin>
					<artifactId>maven-compiler-plugin</artifactId>
					<version>3.8.0</version>
				</plugin>
				<plugin>
					<artifactId>maven-surefire-plugin</artifactId>
					<version>2.22.1</version>
				</plugin>
				<plugin>
					<artifactId>maven-war-plugin</artifactId>
					<version>3.2.2</version>
				</plugin>
				<plugin>
					<artifactId>maven-install-plugin</artifactId>
					<version>2.5.2</version>
				</plugin>
				<plugin>
					<artifactId>maven-deploy-plugin</artifactId>
					<version>2.8.2</version>
				</plugin>
			</plugins>
		</pluginManagement>
	</build>
</project>
```
ssm 初始 web.xml 如下：
```xml
<!DOCTYPE web-app PUBLIC
 "-//Sun Microsystems, Inc.//DTD Web Application 2.3//EN"
 "http://java.sun.com/dtd/web-app_2_3.dtd" >

<web-app>
  <display-name>Archetype Created Web Application</display-name>
</web-app>
```
看的这篇
看到 名称什么的自己起，我的结构如下~ 这里，就要自己改了！
备注：他那个自动工具用不了，建议你老老实实自己写（）
感觉用的前端技术太高级了，有空还是得自己写一个低端版的（）
**根据该教程做出来的代码事务那里的配置文件看不懂，最后大概率不会采用这种方式（**

---

**烟花来咯🎉**
统一参考实验 7 和课设（等我做完了之后）的配置！
1.新建一个 maven 项目，不勾选“从原型创建”，也不勾选下面的 webapp；
2.项目右键-添加框架支持，把 web 应用和 spring mvc 这两个模块勾选上；
3.cv 实验 7 的配置文件，记得改改对应的数据库，包名啥的；
4.tomcat 添加配置-从工件，选 war-exploded；
5.看图，先在 WEB-INF 里新建一个目录，然后导入全部的项目库文件![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1669463603604-1f6bff8a-9945-40e1-951d-90b902b32606.png#averageHue=%231f2133&clientId=u238fa3cb-1996-4&from=paste&height=850&id=u6f7dad85&name=image.png&originHeight=1699&originWidth=2536&originalType=binary&ratio=1&rotation=0&showTitle=false&size=209238&status=done&style=none&taskId=ua02b1c35-1c3a-48eb-a275-d7cb3924a33&title=&width=1268)
6.有需要的话重启

## idea配置Spring
这个看到6.2.2

我的可以用的pom.xml文件如下（不用再配置 Java 版本）
jdk：Oracle open jdk 17.0.2
```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>

  <groupId>org.example</groupId>
  <artifactId>spring_demo</artifactId>
  <version>1.0-SNAPSHOT</version>

  <dependencies>
    <dependency>
      <groupId>junit</groupId>
      <artifactId>junit</artifactId>
      <version>4.13.2</version>
    </dependency>
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-context</artifactId>
      <version>5.3.23</version>
    </dependency>
    <dependency>
      <groupId>log4j</groupId>
      <artifactId>log4j</artifactId>
      <version>1.2.17</version>
    </dependency>
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-test</artifactId>
      <version>5.3.23</version>
    </dependency>
  </dependencies>
  <build>
    <plugins>
      <plugin>
        <groupId>org.apache.maven.plugins</groupId>
        <artifactId>maven-compiler-plugin</artifactId>
        <configuration>
          <source>17</source>
          <target>17</target>
        </configuration>
      </plugin>
    </plugins>
  </build>
</project>

```
项目结构如下：
**注：StudentBeans.xml 必须放在 resources 目录下！！不然会报错！！**
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1666268628840-da0204e9-4fca-44eb-afe7-3800f561d79f.png#averageHue=%23272738&clientId=u0d62c16e-7e8e-4&errorMessage=unknown%20error&from=paste&height=379&id=u59ab8600&name=image.png&originHeight=757&originWidth=558&originalType=binary&ratio=1&rotation=0&showTitle=false&size=417782&status=error&style=none&taskId=uab1a7871-3bc2-4d1a-89cf-f53b2654a32&title=&width=279)
## idea配置MyBatis
首先你要是一个 maven 项目，具体配置看上面的 maven 配置。
**如果还没新建项目的话必须以新建一个 maven + web 项目开始！！！**
3.这个 pom 能用：
```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>groupId</groupId>
    <artifactId>t5-22</artifactId>
    <version>1.0-SNAPSHOT</version>

    <properties>
        <maven.compiler.source>17</maven.compiler.source>
        <maven.compiler.target>17</maven.compiler.target>
    </properties>

    <!--导入依赖-->
    <dependencies>
        <!--mysql驱动包-->
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <version>5.1.46</version>
        </dependency>
        <!--mybatis相关的jar包-->
        <dependency>
            <groupId>org.mybatis</groupId>
            <artifactId>mybatis</artifactId>
            <version>3.5.5</version>
        </dependency>
        <!--Junit测试相关的jar包-->
        <dependency>
            <groupId>junit</groupId>
            <artifactId>junit</artifactId>
            <version>4.13</version>
        </dependency>
    </dependencies>
    <build>
        <!--   **.xml写在src找不到问题解决方案     -->
        <resources>
            <resource>
                <!-- directory：指定资源文件的位置 -->
                <directory>src/main/java</directory>
                <includes>
                    <!-- “**” 表示任意级目录    “*”表示任意任意文件 -->
                    <!-- mvn resources:resources :对资源做出处理，先于compile阶段  -->
                    <include>**/*.properties</include>
                    <include>**/*.xml</include>
                </includes>
                <!--  filtering：开启过滤，用指定的参数替换directory下的文件中的参数(eg. ${name}) -->
                <filtering>false</filtering>
            </resource>
            <resource>
                <directory>src/main/resources</directory>
            </resource>
        </resources>
    </build>
</project>
```
### idea 连接数据库
如图
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1667185124406-05ceb469-9275-4c0f-9e2a-1b74133caee4.png#averageHue=%232b2f44&clientId=ud36451ca-9ef1-4&from=paste&height=391&id=ia7He&name=image.png&originHeight=782&originWidth=955&originalType=binary&ratio=1&rotation=0&showTitle=false&size=119786&status=done&style=none&taskId=u2c90bd5f-708d-430b-8766-2ce5c664f3e&title=&width=477.5)
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1667185148118-d0011a5e-d429-4155-9391-4b4283e0205e.png#averageHue=%2331354e&clientId=ud36451ca-9ef1-4&from=paste&height=598&id=Z4hYh&name=image.png&originHeight=1195&originWidth=1004&originalType=binary&ratio=1&rotation=0&showTitle=false&size=478530&status=done&style=none&taskId=u0977b6f5-f16a-431a-b718-71c8ff8226d&title=&width=502)
报 10061 错误请参考排错篇：JDBC
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1667185194477-e145dd43-c480-43bb-a9e0-a4c8cc84a8de.png#averageHue=%2324263a&clientId=ud36451ca-9ef1-4&from=paste&height=718&id=HCAMN&name=image.png&originHeight=1435&originWidth=1577&originalType=binary&ratio=1&rotation=0&showTitle=false&size=146276&status=done&style=none&taskId=uf3b0bfb3-8292-4a7a-9373-967d0df72a7&title=&width=788.5)
显示你要看到的数据库
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1667185222372-1ca8b9be-c324-494d-98d3-c0a76c65825b.png#averageHue=%23222436&clientId=ud36451ca-9ef1-4&from=paste&height=267&id=WigNZ&name=image.png&originHeight=534&originWidth=945&originalType=binary&ratio=1&rotation=0&showTitle=false&size=217618&status=done&style=none&taskId=ua67422c7-10b2-4186-b9a1-743a7dc2fba&title=&width=472.5)
5.新建**软件包。**

- com.mapper：用于存放mapper映射文件，和对应的 xml 文件，即编写sql语句访问数据库的层；
- com.utils：工具类，用于封装方法调用工具；
- com.pojo：编写实体类，用于对应数据库中的多个表以及相应的属性。

![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1667202612110-dd1fc99b-790f-4ee2-9ded-74b7b88e60c3.png#averageHue=%2328293b&clientId=u4c61e7cb-3752-4&from=paste&height=346&id=u817b0704&name=image.png&originHeight=691&originWidth=379&originalType=binary&ratio=1&rotation=0&showTitle=false&size=241882&status=done&style=none&taskId=u9c5f18a1-8d4e-4dd8-b872-aef7722646c&title=&width=189.5)
在 maven 中配置 mybatis：
### mybatis 开启驼峰映射

### 插入日期类型数据

## idea 配置 JDBC 德鲁伊连接池
连的是 mysql 数据库：

### 将 resultSet 转换为 List 或 Map

## idea 配置 tomcat
[IDEA创建tomcat项目（win+idea2021）_CSDN博客](https://blog.csdn.net/m0_46623754/article/details/122838899)
## idea 配置 Servlet
**  想建Servlet必须先建tomcat项目，因为servlet是在tomcat项目的基础上部署的。**  

如果是看了上面的 tomcat ，点下面这个：

## servlet-api.jar在哪
在tomcat安装目录的lib中，不过我已经又复制了一份到 test 目录下了，我真贴心
## idea导出web项目war包

---


注意：如果有多个名字相同的参数，但是实际取的个数少于参数个数，则 只取 实际个数个 参数值，而且不会覆盖。
在网页链接里，地址和参数之间用？分隔，不同参数之间用的是&分隔，如：
```http
http://localhost:8080/hello?id=413
```
## 
# 报错
看看你的这些蠢错。。
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1665386830285-e57e41b6-5300-4dde-ac1d-9f5559f44359.png#averageHue=%232f3145&clientId=ud500617d-9417-4&errorMessage=unknown%20error&from=paste&height=98&id=ucbdb31f6&name=image.png&originHeight=104&originWidth=580&originalType=binary&ratio=1&rotation=0&showTitle=false&size=66831&status=error&style=none&taskId=u9f4fc791-fdc9-4a9c-8c13-1f61b687b55&title=&width=546)
> **已经写好的项目千万不要改名！！！重构也不行！！！😭😭😭😭😭**

## idea 不支持的发行版本xx

大同小异，先看下面这篇吧。

## 中文乱码
把 utf-8 改成 gbk 即可。
jsp 文件的话
`<%  request.setCharacterEncoding( "GB2312");%>`
221116 编辑：不确定，这俩编码方式互相改下，看哪个能用用哪个（）

## tomcat
服务器出错，之前没事的话…重启试试。

## 405
### 方法不允许
[HTTP状态 405 - 方法不允许_CSDN博客](https://blog.csdn.net/qq_46418828/article/details/124855100)
重点在于你是表单要提交数据啊，所以肯定是post请求。
### 此URL不支持Http方法POST
**描述** 请求行中接收的方法由源服务器知道，但目标资源不支持。
看看是不是doPost，doGet方法写反了？
## 
## 404 
### 源服务器未能找到目标资源的表示或者是不愿公开一个已经存在的资源表示
**如果是你鼓捣工件报这个错的话，有这时间还是新建一个项目吧，少年！**
<url-pattern>和java文件里@WebServlet注解里边的路径不能一样，会冲突。
#### 请求的资源[/GetReg]不可用
是这样的，如果你idea里tomcat配置![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1662897209141-8236efec-cdf6-47cb-8dc9-177236642bd3.png#averageHue=%233e4465&clientId=u78339b98-98e8-4&errorMessage=unknown%20error&from=paste&height=95&id=S2MaU&name=image.png&originHeight=189&originWidth=339&originalType=binary&ratio=1&rotation=0&showTitle=false&size=31408&status=error&style=none&taskId=u5fba9985-1617-4eb3-a187-847f763b6af&title=&width=169.5)的![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1662897236075-611390ba-d9c3-41da-8201-a9c367d70490.png#averageHue=%2326293e&clientId=u78339b98-98e8-4&errorMessage=unknown%20error&from=paste&height=644&id=QAWHB&name=image.png&originHeight=1702&originWidth=2056&originalType=binary&ratio=1&rotation=0&showTitle=false&size=92511&status=error&style=none&taskId=u9a9807fb-f7e4-476c-9778-758c2eef24d&title=&width=778)
“应用程序上下文”（就是你访问该应用的时候的目录），如果你这里写的是/，就是什么也没有，那么在@WebSerlet注释里也不能写别的。如果这里写了/2，到时候访问的初始界面就是http://localhost:8080/2/，你在@WebSerlet里的注释就要写/2/GetReg，才能访问到。
### SSL HTTP Connector node not found set up one in the server.xml

## jsp
### jsp out.println 用不了

### jsp Abean cannot be resolved to a type
不能直接在src下新建一个类，必须要先建一个package，再建一个类。。怪哦。。。
## Cookie
### Cookie name[]是一个保留令牌
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1664187546193-f4cc0d4e-a781-4725-ae96-241c02fe5fef.png#averageHue=%23abb3b0&clientId=u382f93bf-05cb-4&errorMessage=unknown%20error&from=paste&height=109&id=ud63565a9&name=image.png&originHeight=217&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=235208&status=error&style=none&taskId=u63d3a51a-b4ee-4152-a738-0e8a683d123&title=&width=700)
**注意，“触发”这个词！就是说不一定每次都会引起这个bug，造成的后果就是一会行一会不行，相同的代码每次结果出来都不一样（**
具体报错：


**我就要在cookie里面传中文！！！**
的解决方法：
发送时，统一转换为UTF-8：
```java
Cookie cookie = new Cookie(URLEncoder.encode(paramName, StandardCharsets.UTF_8),
                        URLEncoder.encode(value.toString(), StandardCharsets.UTF_8));
```
接收时，记得转回来：
```java
String lastLoginTime = URLDecoder.decode(value, StandardCharsets.UTF_8);
```
注意！！！即使这样，空格这个符号还是不行！
## JDBC
### 启动服务 10061 错误

### 连接上数据库了，但是怎么没有我的表
点这个1/5。。。然后勾选上你需要的数据库，你没显示怎么可能有啊。。。
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1665399494180-6c2adb4c-5294-4619-9930-c55df7e1f210.png#averageHue=%2325283b&clientId=ud500617d-9417-4&errorMessage=unknown%20error&from=paste&height=331&id=l1uQu&name=image.png&originHeight=661&originWidth=572&originalType=binary&ratio=1&rotation=0&showTitle=false&size=134412&status=error&style=none&taskId=u8939da1c-1474-413b-8c14-10a845f2489&title=&width=286)
### 无法解析表
找到侧边栏里的数据库设置，没有的话在这里
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1665399997652-4fd67c99-3e13-4b27-8e92-a235f3a9ca8b.png#averageHue=%232b2f44&clientId=ud500617d-9417-4&errorMessage=unknown%20error&from=paste&height=412&id=u9076e7d3&name=image.png&originHeight=823&originWidth=994&originalType=binary&ratio=1&rotation=0&showTitle=false&size=140713&status=error&style=none&taskId=u128d001d-7948-4e8c-a46e-30c86983f7e&title=&width=497)
点那两页纸的图标
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1665399881460-28e43d13-3b2c-4e7a-b08f-6907be71c77a.png#averageHue=%232e334a&clientId=ud500617d-9417-4&errorMessage=unknown%20error&from=paste&height=73&id=u7ea71eae&name=image.png&originHeight=146&originWidth=557&originalType=binary&ratio=1&rotation=0&showTitle=false&size=56839&status=error&style=none&taskId=u5a57a84e-c431-4538-8036-08af2fe249c&title=&width=278.5)
在弹出的框里把数据库的名字写上，身份验证选无（简单），然后测试连接，连接上就行了！
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1665399896920-01be0b25-c775-4d08-9a26-2680f66a247b.png#averageHue=%23222537&clientId=ud500617d-9417-4&errorMessage=unknown%20error&from=paste&height=722&id=ubea941e8&name=image.png&originHeight=1444&originWidth=1583&originalType=binary&ratio=1&rotation=0&showTitle=false&size=118147&status=error&style=none&taskId=u20a3186e-6efc-4d0a-864d-695d5f9d202&title=&width=791.5)
### servlet映射中的＜url pattern＞[servletDemo]无效
完整报错：Caused by: java.lang.IllegalArgumentException: servlet映射中的＜url pattern＞[xxx]无效
解决方法：servlet 类上面的`@WebServlet`注解写上斜杠，jsp 跳转的路径也写上斜杠！
## mybatis
### 设置自增主键!!!先看!!!

### URI 未注册(设置 | 语言和框架 | 架构和 DTD)
mybatis-config.xml 文件里

### Maven · Resources 找不到
网上给的都试过了，不行，又不想重装 maven …
** 解决方法：打开 idea 内置的终端（terminal），运行mvn idea:idea **
### Maven · org.apache.ibatis.binding.BindingException: Invalid bound statement (not found): com.mapper.UserMapper.isExists
已经确定没手误，命名空间配置正确，变量名映射配置正确
项目结构图：
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1667270888651-4ac9a5fb-de05-44b7-aac1-d2789659d3f8.png#averageHue=%23282839&clientId=uf05bdb33-3d02-4&from=paste&height=590&id=ufa3086aa&name=image.png&originHeight=1179&originWidth=518&originalType=binary&ratio=1&rotation=0&showTitle=false&size=612211&status=done&style=none&taskId=u0fd74aef-1ae7-457f-ace6-f2d89ce9a2d&title=&width=259)

**cv 之后记得 reimport 一下！！**
### Error querying database. Cause: Communications link failure
### Error parsing SQL Mapper Configuration. Cause: java.io.IOException: Could not find resource
这俩一块不知道怎么就解决了。。。
注：我已经配置了驼峰命名法匹配，具体怎么配置请自行 baidu/google
晕了，原来一部分原因是重启软件之后没连上数据库。。双击数据库的任意一个表就能自动连上了
然后看这个：

主要是那句 useSSL=false，具体到我的代码就是这句：
```xml
<property name="url" value="jdbc:mysql://localhost:3306/mybatis?useSSL=false" />
```
### 关于Junit 和 Tomcat
junit 是 maven 导入进来的，就是不用非得在 main 里面进行开发了。
但是这俩不能一块使，做 tomcat web 开发就不能做 junit @Test 标记，同时 @Test 的函数也不能传参数..
### java.lang.ClassNotFoundException: org.apache.ibatis.io.Resources
描述：Resources 包正确导入了，而且代码检查不出来错误，但是运行在 web 网页的时候出错了
就是虽然添加了 maven 配置，但是看解决方法来看，**maven 只是帮你把 jar 包自动下载好了，但是并没有帮你放到正确的地方（吐血）**
所以还要按照下面文章的方法把 maven 帮你下载的**所有包都手动导入到项目配置中！！！**

### Cause: org.apache.ibatis.executor.ExecutorException: Executor was closed
详细原因看
偏向解决方法一点的看
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25613446/1667377820673-b5e7360b-c300-47a5-96b3-eb9e33cd3429.png#averageHue=%23faf8f5&clientId=u86a4162c-c272-4&from=paste&height=702&id=u6cc73ebb&name=image.png&originHeight=1403&originWidth=1385&originalType=binary&ratio=1&rotation=0&showTitle=false&size=269696&status=done&style=none&taskId=ub03093fd-d7f6-48c6-967d-0ae9c3ea558&title=&width=692.5)
### org.apache.ibatis.binding.BindingException: Parameter 'xxxxx' not found
原因以及解决办法：

如果照着这个改了之后出现了红字下划线提示“一个问题”，但是其实并没有问题，就把实际调用的时候传参那里删了 再重新写一遍就行了
这篇进行了拓展，更全，使用的参数有对象的话可以参考这篇：

## Spring 🌱
自动装配看这篇：
### Unsatisfied dependency expressed through constructor parameter 0
就是实体类的构造函数里，你自己定义了传参的构造函数之后，必须再补一个无参构造函数，补上即可。
### No qualifying bean of type 'pojo.Student' available: expected singlee matching bean but found 4: pojo.Student ...
相关代码如下：
```java
@Configuration
@Import(value = {Student.class, Course.class})
public class StudentConfig
{
    @Bean("zs")
    public Student zhangSan() {
        return new Student("张三", new Course("数学", 95));
    }
    @Bean("ls")
    public Student liSi() {...}
    @Bean("we")
    public Student wangEr(){...}
}
```
```java
Student zs =  applicationContext.getBean(Student.class);
System.out.println(zs);
```
解决方法：`Student zs =  applicationContext.getBean(Student.class);`
改为 `Student zs = (Student) applicationContext.getBean("zs");`
这是因为如果是按类别查找，类里有四个都符合条件的返回函数，ide不知道该返回那个；但是如果是按名字查找的话，只有一个 bean 对应 zs，所以这次就对了。
### Unsupported class file major version 61

1. 项目 jdk 该版本，怎么改见报错第一条


### Invalid bound statement (not found): com.xxx.dao.xxxDao.selectByxx

这个我用4-（4）解决了。
123的图示看这篇：
实在不行看这篇：
### Connections could not be acquired from the underlying database
数据库配置文件那里，useSSL=true 改为 useSSL=false。。
因为我的数据库默认是免密登录的。
可以看下这个
到这一步已经不是什么大问题了，加油！！
### 一个或多个筛选器启动失败

### Mapped Statements collection already contains value for com.itheima.dao.
在使用注解的同时，也写了xml配置文件，删除其中一个即可
