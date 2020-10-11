#include<iostream>
#include<fstream>
using namespace std;
bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}
int main()
{
    cout<<is_file_exist("pvp.cpp");
}