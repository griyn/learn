# RocksDB

# install
```
1.安装gflags
linux：sudo apt-get install -y libgflags-dev
centos：sudo yum install gflags-devel
查看/usr/lib64 or /usr/local/lib64 下有没有libgflags

2.安装rocksdb
git clone https://github.com/facebook/rocksdb.git
cd rocksdb/
make static_lib  # 生成静态库文件librocksdb.a

安装踩坑
g++: fatal error: Killed signal terminated program cc1plus
compilation terminated.
make: *** [Makefile:2462: db/db_impl/compacted_db_impl.o] Error 1
解决：内存不够了。杀一些进程试试；减小-j8参数的值。

3.配置到系统
librocksdb.a->/usr/local/lib64
Include/*->/usr/local/include

4.写demo
静态库编译方式：g++ rocksdb_test.cpp librocksdb.a -lpthread -lz -ldl
动态库编译方式: g++ rocksdb_test.cpp -lrocksdb -lpthread -lz -ldl
头文件在/usr/local/include/，librocksdb.a在当前目录。（动态库so的使用方式是 -lrocksdb

demo编译踩坑
undefined reference to xxxx 一堆没有用到的函数
解决：静态库有问题。重新编译.a，make clean && make static_lib
```
