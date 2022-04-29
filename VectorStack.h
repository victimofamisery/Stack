#pragma once

#include "StackImplementation.h"
#include "Vector.h"

class VectorStack : public IStackImplementation {
public:
    VectorStack();
    VectorStack(const ValueType* rawArray, const size_t size);
    // добавление в хвост
    void push(const ValueType& value) override;
    // удаление с хвоста
    void pop() override;
    // посмотреть элемент в хвосте
    const ValueType& top() const override;
    // проверка на пустоту
    bool isEmpty() const override;
    // размер 
    size_t size() const override;
    // виртуальный деструктор
    ~VectorStack() override;
private:
    Vector _vector;
};
