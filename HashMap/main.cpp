#include <iostream>
#include "HashTable.h"
#define LOG(x) std::cout << x << std::endl;

int main(int argc, char* argv[])
{

	HashTable<int> fav_nums("Aamir", 100);
     
	fav_nums["Ali"] = 1900;
	fav_nums["Atif"] = 2200;


	LOG(fav_nums["Aamir"]);
	LOG(fav_nums["Ali"]);
	LOG(fav_nums["Atif"]);

	
	std::cin.get();
}
