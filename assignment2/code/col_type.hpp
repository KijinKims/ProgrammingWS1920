#ifndef ASSIGNMENT2_COLTYPE_HPP
#define ASSIGNMENT2_COLTYPE_HPP

#include <memory>
#include <ostream>

class GenericDataType {
public:
    virtual ~GenericDataType() = default;
    virtual std::unique_ptr<GenericDataType> clone() const = 0;
    friend std::ostream& operator<<(std::ostream& os, const GenericDataType& v);
    virtual bool operator==(const GenericDataType& other) const = 0;
    virtual bool operator<(const GenericDataType& other) const = 0;
protected:
    virtual void print(std::ostream& os) const = 0;
};

inline std::ostream& operator<< (std::ostream& os, const GenericDataType& v){
    v.print(os);
    return os;
};

// implement a class DataType<T> that is derived from GenericDataType and holds the actual value
template <typename T>
class DataType : public GenericDataType {
public:
    explicit DataType(const T& v){this->value = v;}
    std::unique_ptr<GenericDataType> clone() const override {
        GenericDataType* ptr = new DataType<T>(value);
        std::unique_ptr<GenericDataType> new_ptr = std::unique_ptr<GenericDataType>(ptr);
        return new_ptr;
    }
    bool operator==(const GenericDataType& other) const override {
        return value == dynamic_cast<const DataType&>(other).value;
    }
    bool operator<(const GenericDataType& other) const override {
        return value < dynamic_cast<const DataType&>(other).value;
    }
protected:
    T value;
    void print(std::ostream& os) const override {
        os << value;
    }
};

class ColType {
public:
    template <typename ValueType>
    explicit ColType(const ValueType& value){
        GenericDataType* ptr = new DataType<ValueType>(value);
        container = std::unique_ptr<GenericDataType>(ptr);
    }

    ColType(const ColType& other){
        *container = *other.container;
    }
    ColType& operator=(const ColType& other){
        *container = *other.container;
    }
    GenericDataType& get(){
        return *container;
    }
    const GenericDataType& get() const{
        return *container;
    }
    bool operator==(const ColType& other) const{
        (*container).operator==(*(other.container)) ;
    }
    bool operator<(const ColType& other) const{
        (*container).operator<(*(other.container));
    }
private:
    std::unique_ptr<GenericDataType> container;
};

#endif //ASSIGNMENT2_COLTYPE_HPP
