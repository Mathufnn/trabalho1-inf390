#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

int main() 
{
  cout<<"haha"<<endl;
  this_thread::sleep_for(std::chrono::milliseconds(5000));
  cout<<"haha2" << endl;
}