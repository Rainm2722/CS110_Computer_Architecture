#include "vector.hpp"
#include <iostream>

template <typename T>
void ptv(vector<T>& v){
    for(size_t i = 0;i<v.size();i++)
        std::cout<<v[i]<<"|";
    std::cout<<"end";
    std::cout<<"|size:"<<v.size()<<"\n";

}
template <typename T>
void ptv_iter(vector<T>& v){
    std::cout<<"iter: \n";
    for(__detail::__iterator<int> iter = v.begin();iter!=v.end();iter++)
        std::cout<<*iter<<"|";
    std::cout<<"end\n";
    std::cout<<"citer: \n";
    for(__detail::__const_iterator<int> iter = v.cbegin();iter!=v.cend();iter++)
        std::cout<<*iter<<"|";
    std::cout<<"end\n";
}