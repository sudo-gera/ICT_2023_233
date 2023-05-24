#include <iostream>
#include <string>
#include <vector>

/// \brief prefix function of a string
/// \param str - input string
template<typename T>
auto PrefixFun(T&&str){
    std::vector<size_t> result(str.size());
    for (size_t i=1;i<str.size();++i){
        size_t k=result[i-1];
        while (k>0 and str[i]!=str[k]){
            k=result[k-1];
        }
        if (str[i]==str[k]){
            k++;
        }
        result[i]=k;
    }
    return result;
}

int main(){
    std::string text;
    std::string pattern;
    std::cin>>text>>pattern;
    auto pref_fun=PrefixFun(pattern+" "+text);
    for (size_t i=0;i<pref_fun.size();++i){
        if (pref_fun[i]>=pattern.size()){
            std::cout<<i-pattern.size()*2<<"\n";
        }
    }
}
