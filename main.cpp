#include <iostream>
#include <string>
#include <memory>

class Toy{
    std::string name;
public:
    Toy(const std::string &_name): name(_name){
        std::cout << "Create toy " << name << std::endl;
    };

    Toy(): name("SomeToy"){
        std::cout << "Create SomeToy" << std::endl;
    };

    std::string getName(){
       return name;
    }

    ~Toy(){
       std::cout << "Toy " << name << " was deleted " << std::endl;
    }
};

class shared_toy_ptr{
    Toy* toy = nullptr;
    int* count = nullptr;
public:
    shared_toy_ptr(Toy* _toy){
        toy = _toy;
        if(_toy == nullptr){ 
            count = new int(0);
        } else {
            count = new int(1);
        }
    }

    shared_toy_ptr(): shared_toy_ptr(nullptr) {};

    void inc_count(){
        if (count != nullptr)
            *count += 1;
    }

    void dec_count(){
        if (count != nullptr)
            *count -= 1;
    }

    //конструктор копирования
    shared_toy_ptr(const shared_toy_ptr& oth){
        toy = oth.toy;
        count = oth.count;     //делимся указателем на счетчик
        inc_count();       //увеличиваем общий счетчик
    }

    shared_toy_ptr& operator= (const shared_toy_ptr& oth){
        if(this == &oth)
            return *this;
            dec_count();
        if(use_count() == 0){// удаляем, если больше нет владельцев
            std::cout << "Delete toy " << toy->getName() << std::endl;
            delete toy;
            toy = nullptr;
            delete count;
            *count = 0;
        }
        toy = oth.toy;
        count = oth.count;
        inc_count();

        return *this;
    }

    int use_count(){
        return *count;
    }

    Toy* operator->() {
        return toy;
    }
    
    Toy& operator*() {
        return *toy;
    }

    ~shared_toy_ptr(){
        if(*count > 0)
            dec_count();
        if(*count == 0){
            std::cout << "Delete shared toy " << toy->getName() << std::endl;
            delete toy;
            toy = nullptr;
            delete count;
            *count = 0;
        }
    }
};

shared_toy_ptr make_shared_toy(const std::string& name){
    return shared_toy_ptr(new Toy(name));
};
shared_toy_ptr make_shared_toy(const Toy& toy){
    return shared_toy_ptr(new Toy(toy));
};

int main(int, char**){
    std::cout << "Hello, from 31_2_shared_toy_ptr!\n";

    Toy t("Ball");
    shared_toy_ptr ptr = make_shared_toy(t);
    shared_toy_ptr ptr1 = make_shared_toy("Bone");

    std::cout << "Count ptr: "<< ptr.use_count() << " : " << ptr->getName() << std::endl;
    std::cout << "Count ptr: "<< ptr1.use_count() << " : " << ptr1->getName() << std::endl;


    return 0;
}
