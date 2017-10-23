#include <iostream>
#include "HashTable.h"

int main(int argc, char* argv[])
{

	HashTable<int> fav_nums("Aamir", 100);
//	 fav_nums.add("Aamir", 200);
  
	fav_nums["Aamir"] = 999;

	std::cout << fav_nums["Aamir"] << std::endl;

	std::cin.get();
}
