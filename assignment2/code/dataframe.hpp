#ifndef ASSIGNMENT2_DATAFRAME_HPP
#define ASSIGNMENT2_DATAFRAME_HPP

#include <list>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "col_type.hpp"

// This is needed to be able to deduce the first type of a passed lambda object
template<typename Ret, typename Arg, typename... Rest>
Arg first_argument_helper(Ret(*) (Arg, Rest...));

template<typename Ret, typename F, typename Arg, typename... Rest>
Arg first_argument_helper(Ret(F::*) (Arg, Rest...));

template<typename Ret, typename F, typename Arg, typename... Rest>
Arg first_argument_helper(Ret(F::*) (Arg, Rest...) const);

template <typename F>
decltype(first_argument_helper(&F::operator())) first_argument_helper(F);

template <typename T>
using first_argument_t = decltype(first_argument_helper(std::declval<T>()));


class Dataframe {
public:
    class Invalid{};

    template<typename T>
    void add_column(std::vector<T> vect){
        std::vector<ColType> new_col;

        for(T& e:vect){
            new_col.push_back(ColType(e));
        }

        data.push_back(new_col);
    }

    int nrows(){
        return data.back().size();
    }

    int ncols(){
        return data.size();
    }

    friend std::ostream& operator<< (std::ostream& os, const Dataframe& df);

    template<typename Fun>
    void apply(const size_t i, Fun l) {
        // to get the value of the dataframe and the correct type requested by the user
        // use this->get_orig_type_<first_argument_t<Fun>>()
    }

    template<typename Fun>
    void apply(const std::string& c, Fun l);

private:
    std::list<std::vector<ColType>> data;
    std::vector<std::string> colnames;
    std::vector<std::string> rownames;

//    template<typename T>
//    T& get_orig_type_(ColType& ct){
//        auto& val = dynamic_cast<DataType<typename std::remove_reference_t<T>>&>(ct.get());
//        return val.get_value();
//    }

//    template<typename T>
//    const T& get_orig_type_(const ColType& ct) const {
//        const auto& val = dynamic_cast<const DataType<typename std::remove_reference_t<T>>&>(ct.get());
//        return val.get_value();
//    }
};

#endif //ASSIGNMENT2_DATAFRAME_HPP
