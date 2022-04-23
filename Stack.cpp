#include "Stack.h"


Stack::Stack(StackContainer container)
    : _containerType(container)
{
    switch (container)
    {
    case StackContainer::List: {
        _pimpl = static_cast<IStackImplementation*>(new ListStack());    // конкретизируйте под ваши конструкторы, если надо
        break;
    }
    case StackContainer::Vector: {
        _pimpl = static_cast<IStackImplementation*>(new VectorStack());    // конкретизируйте под ваши конструкторы, если надо
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container)
    : _containerType(container)
{
    switch (container)
    {
    case StackContainer::List: {
        _pimpl = static_cast<IStackImplementation*>(new ListStack(valueArray, arraySize));    // конкретизируйте под ваши конструкторы, если надо
        break;
    }
    case StackContainer::Vector: {
        _pimpl = static_cast<IStackImplementation*>(new VectorStack(valueArray, arraySize));    // конкретизируйте под ваши конструкторы, если надо
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
}

Stack::Stack(Stack& copyStack)
    : Stack(copyStack._containerType)
{
    size_t tmpSize = copyStack.size();
    ValueType* tmpArray = new ValueType[tmpSize];
    for(auto i = 0; i < tmpSize; i++) {
        tmpArray[tmpSize - 1 - i] = copyStack.top();
        copyStack.pop();
    }
    for(auto i = 0; i < tempSize; i++) {
        copyStack.push(tmpArray[i]);
        push(tmpArray[i]);
    }   
    delete[] tmpArray;
}

Stack& Stack::operator=(Stack& copyStack)
{
    if(&copyStack == this) {
        return *this;
    }
    delete _pimpl;
    Stack tmp(copyStack);
    _pimpl = tmp._pimpl;
    tmp._pimpl = nullptr;
    _containerType = tmp._containerType;
    return *this;
}

Stack::Stack(Stack&& moveStack) noexcept {
    _pimpl = moveStack._pimpl;
    moveStack._pimpl = nullptr;
    _containerType = moveStack._containerType;
    moveStack._containerType = StackContainer::Undefined;
}

Stack& Stack::operator=(Stack&& moveStack) noexcept {
    if(&moveStack == this) {
        return *this;
    }
	delete[] _pimpl;
    _pimpl = moveStack._pimpl;
    moveStack._pimpl = nullptr;
    _containerType = moveStack._containerType;
    moveStack._containerType = StackContainer::Undefined;
    return *this;
}

Stack::~Stack()
{
    delete _pimpl;        // композиция!
}

void Stack::push(const ValueType& value)
{
    // можно, т.к. push определен в интерфейсе
    _pimpl->push(value);
}

void Stack::pop()
{
    _pimpl->pop();
}

const ValueType& Stack::top() const
{
    return _pimpl->top();
}

bool Stack::isEmpty() const
{
    return _pimpl->isEmpty();
}

size_t Stack::size() const
{
    return _pimpl->size();
}
