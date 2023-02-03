#include <iostream>
#include "rocksdb/db.h"

int main() {
    // 打开一个rocksdb
    rocksdb::DB* db;
    rocksdb::Options options;
    // 如果没有则新建
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, "./testdb", &db);
    if (!status.ok()) {
        // https://github.com/facebook/rocksdb/blob/433d7e4594fd4d14f81e0f4a09be826328fe6ffa/include/rocksdb/status.h
        std::cout << "create rocksdb FAILED, error:" << status.ToString() << std::endl;
        delete db;
        return 1;
    }
    std::cout << "create rocskdb SUCCESS" << std::endl;

    // 写数据
    // https://github.com/facebook/rocksdb/blob/433d7e4594fd4d14f81e0f4a09be826328fe6ffa/include/rocksdb/db.h
    std::string wkey = "Tom";
    std::string wvalue = "He is a dick";
    // 默认写入的是DefaultColumnFamily()的cf，名字是"default"
    // 写入的值的大小必须小于4GB
    status = db->Put(rocksdb::WriteOptions(), wkey, wvalue);
    if (!status.ok()) {
        std::cout << "rocksdb put FAILED, error:" << status.ToString() << std::endl;
        delete db;   
        return 1;
    }
    std::cout << "rocksdb put SUCCESS" << std::endl;

    // 读数据
    std::string rvalue;
    status = db->Get(rocksdb::ReadOptions(), wkey, &rvalue);
    if (!status.ok()) {
        std::cout << "rocksdb get FAILED, error:" << status.ToString() << std::endl;
        delete db;
        return 1;
    }
    std::cout << "rocksdb get SUCCESS, key:" << wkey << " value:" << rvalue << std::endl;

    // 迭代器
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
    std::cout << "start scan:" << std::endl;
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::cout << it->key().ToString() << ":" << it->value().ToString() << std::endl;
    }
    if (!it->status().ok()) {
        std::cout << "rocksdb scan FAILED, error:" << it->status().ToString() << std::endl;    
    }

    // 关闭rocksdb
    status = db->Close();
    if (!status.ok()) {
        std::cout << "rocksdb close FAILED, error:" << status.ToString() << std::endl;   
    }
    delete db;

    return 0;
}
