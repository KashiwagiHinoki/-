#include<iostream>
class DataStore{
public:
    DataStore(){}
    DataStore(int mValue){
        this->mValue = mValue;
    }
    const DataStore operator+(const DataStore& rhs) const{
        DataStore tmp;
        tmp.mValue = mValue + rhs.mValue;
        return tmp;
    }
    void print(){
        printf("%d\n", mValue);
    }
    void set(int mValue){
        this->mValue = mValue;
    }
    int get(){
        return this->mValue;
    }
private:
    int mValue = 1;
};
DataStore operator+(int rhs, DataStore& lhs){
    DataStore tmp;
    tmp.set(rhs + lhs.get());
    return tmp;
}
int main(void){
    DataStore a(10);
    a = 10 + a;
    a.print();
    return 0;
}