#ifndef HASH_TABLE_DS_H
#define HASH_TABLE_DS_H

template <typename T>
class HashTableDS{
    private:
        
    public:
        HashTableDS(){};
        virtual void insert(T& value) = 0;
        virtual T* search(int key) = 0;
        virtual void _delete(int key) = 0;

};

#endif