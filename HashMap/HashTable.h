#pragma once
#include "hashNode.h"

template<class valType>
class HashTable
{
	//vars
	const static int table_size = 1000;
	HashNode<valType>* hash_table[HashTable::table_size];

public:
#pragma region Constructors
	HashTable()
	{
		//Default constructor
	}
	HashTable(const char* _key, const valType _value)
	{
		//Nullify all nodes
		for (int i = 0; i < table_size; i++)
		{
			hash_table[i] = nullptr;
		}
		add(_key, _value);
	}
	~HashTable()
	{
		//remove all dynamically allocated memory
		for (int i = 0; i < table_size; i++)
		{
			delete hash_table[i];
		}
	}
#pragma endregion 

#pragma region Operators and Public functions
	//Operator overload to get key easily
	 valType& operator[](const char* to_look)
	{
		//first calculate hash 
		int hash = hashIt(to_look);

		//Now perform lookup , first at index then in linked-list's
		if (hash_table[hash] == nullptr)
		{   


			//                 PROBEM

			//Error , cant set new values like      fav_num["Ali"] = 1900;
			//Because of following code
			//When finding hash index NUll like above 
			//Code just returns garbage value
			//We want to create a new index hash location in hash table
			//And return the value location inside that hashnode from here


			//                 SOLUTION

			/*
			 *   Ok so here's how i am going to fix it
			 *   call the regular add function pass the key's calculated hash
			 *   and for value which we dont have right now some garbarge value
			 *   and then return the memory referecne of that garbage value
			 *   this way it can be reset in the calling function
			 */
  
			add(to_look, -INT32_MAX);

			//get value
			return this->operator[](to_look);

		}
		else if (hash_table[hash]->getKey() == to_look)
		{
			return hash_table[hash]->getValue();
		}
		else
		{
			//look thru linked-list
			HashNode<valType> *temp = hash_table[hash]->getNext();
			while (temp != nullptr)
			{
				if (temp->getKey() == to_look)
				{
					return temp->getValue();
				}
			}
		}
	}

	//add function
	void add(const char* _key, const valType _value)
	{
		//Process key with hashing funtion and store in hash table
		int hash = hashIt(_key);

		//if calculated hash index not empty then use linked-list insertion
		if (hash_table[hash] != nullptr)
		{
			//first look this index(hash)
			if (hash_table[hash]->getKey() == _key)
			{
				hash_table[hash]->setValue(_value);
				return;
			}
			else
			{
				insertIntoList(hash_table[hash], _key, _value);
			}
		}

		 //Fresh add
		else
		{
			//otherwise perform normal insertion in the hashtable
			hash_table[hash] = new HashNode<valType>(_key, _value);
		}
	}

	//remove function
	void remove(const char* _key)
	{
		int hash = hashIt(_key);
		if (hash_table[hash] != nullptr)
		{
			//then , first look for key on the current index
			if (hash_table[hash]->getKey() == _key)
			{

				/*
				 *   This is not good , we still could have a linked-list in the object
				 *   By doing this that will be lost too
				 *
				 *
				 *
				 */

				hash_table = nullptr;
			}
			//othewise look in linked-list
			else
			{
				HashNode<valType> *temp = hash_table[hash]->next;
				while (temp != nullptr)
				{
					if (temp->getKey() == _key)
					{
						//at this point we have to readjust linked-list pointer's

					}
				}
			}
		}
	}
#pragma endregion

#pragma region Private Functional Area
private:

	//for hasing
	int hashIt(const char* key)
	{
		int char_sum = 0;
		while (char c = *key++)
		{
			char_sum += static_cast<int>(c);
		}

		return char_sum % HashTable::table_size;
	}


	//To insert in a singly linked list if index is already bound to a value
	void insertIntoList(HashNode<valType> *node, const char* _key, const valType &_value)
	{
		if (node == nullptr)
		{
			node = new HashNode<valType>(_key, _value);
		}
		else
		{
			//Before proceding check if key matches with this , node so we can update any value
			if (node->getKey() == _key)
			{
				node->setValue(_value);
				return;
			}

			insertIntoList(node->getNext(), _key, _value);
		}
	}
	#pragma endregion
};