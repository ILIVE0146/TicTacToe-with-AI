#include<iostream>
#include<string>
#include<fstream>
using namespace std;
void is_file_exist(string fileName)
{
    std::ifstream infile(fileName);
    if(!infile.good())
    {
        cout<<"Some files are missing"<<endl<<fileName<<endl;
        exit(0); // exit 
    }
}
void fileParser()
{
    fstream fptr;
    fptr.open("files_to_check.txt",ios::in); //open a file to perform read operation using file object
   if (fptr.is_open()){   //checking whether the file is open
      string file_name;
      while(getline(fptr, file_name)){ //read data from file object and put it into string.
         is_file_exist(file_name);
      }
      cout<<"File check completed."<<endl;
      fptr.close(); //close the file object.
   }
}

// int main()
// {
//     fileParser();
// }