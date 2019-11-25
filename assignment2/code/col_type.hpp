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

inline std::ostream& operator<< (std::ostream& os, const GenericDataType& v);

// implement a class DataType<T> that is derived from GenericDataType and holds the actual value


class ColType {
public:
    template <typename ValueType>
    explicit ColType(const ValueType& value);
    ColType(const ColType& other);
    ColType& operator=(const ColType& other);
    GenericDataType& get();
    const GenericDataType& get() const;
    bool operator==(const ColType& other) const;
    bool operator<(const ColType& other) const;
private:
    std::unique_ptr<GenericDataType> container;
};

#endif //ASSIGNMENT2_COLTYPE_HPP
