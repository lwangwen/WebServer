/*
 * @Author       : wangwenl
 * @Date         : 2023-03-05
 */ 
#include <unistd.h>
#include "server/webserver.h"


int main(int argc, char **argv) {
    
    int PORT = 9999;                        // 端口默认9999
    int TRIGMODE = 3;                       // 默认为ET模式
    int TIMEOUT = 60000;                    // 默认超时时间
    bool LINGER = false;                    // 默认不开启优雅退出
    int MYSQLPORT = 3306;                   // 数据库端口
    char* MYSQL_USER = "root";              // 数据库用户名
    char* MYSQL_PWD = "Wang0503";           // 默认数据库密码
    char* MYSQL_DATABASE = "webServer";     // 默认数据库名
    int THREAD_NUM = 8;                     // 线程池数量
    int MYSQL_NUM = 6;                      // 连接池数量
    bool LOG = true;                        // 日志开关
    int LOG_LEVEL = 1;                      // 日志等级
    int LOG_QUEUE = 1024;                   // 异步日志队列大小


    WebServer server(
        PORT, TRIGMODE, TIMEOUT, LINGER,                                                /* 端口 ET模式 timeoutMs 优雅退出  */
        MYSQLPORT, MYSQL_USER, MYSQL_PWD, MYSQL_DATABASE,                               /* Mysql配置 */
        THREAD_NUM, MYSQL_NUM, LOG, LOG_LEVEL, LOG_QUEUE);                              /* 连接池数量 线程池数量 日志开关 日志等级 日志异步队列容量 */
    server.Start();
} 
  