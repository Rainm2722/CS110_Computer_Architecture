// #include "vector.hpp"
// #include <iostream>

// template <typename T>
// void ptv(vector<T>& v){
//     for(size_t i = 0;i<v.size();i++)
//         std::cout<<v[i]<<"|";
//     std::cout<<"end";
//     std::cout<<"|size:"<<v.size()<<"\n";

// }
// template <typename T>
// void ptv_iter(vector<T>& v){
//     std::cout<<"iter: \n";
//     for(__detail::__iterator<int> iter = v.begin();iter!=v.end();iter++)
//         std::cout<<*iter<<"|";
//     std::cout<<"end\n";
//     std::cout<<"citer: \n";
//     for(__detail::__const_iterator<int> iter = v.cbegin();iter!=v.cend();iter++)
//         std::cout<<*iter<<"|";
//     std::cout<<"end\n";
// }

// int main(){
//     vector<int> v;
//     for(int i=0;i<20;i++)
//         v.push_back(i);
//     ptv(v);
//     ptv_iter(v);
//     v.insert(++v.begin(),777);
//     ptv(v);
//     v.insert(v.cbegin(),666);
//     ptv(v);
//     v.erase(v.cbegin()+7);
//     ptv(v);
//     v.pop_back();
//     ptv(v);
//     vector<int> v1 {1,2,3,4,5,6,7,5};
//     ptv(v1);
// }


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

int main(){
    vector<int> v;
    __detail::__iterator<int> begin = v.begin();
    for(int i=0;i<20;i++)
        v.insert(v.begin(),666);
    ptv(v);
   
}