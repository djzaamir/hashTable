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
	const valType& operator[](const char* to_look)
	{
		//first calculate hash 
		int hash = hashIt(to_look);

		//Now perform lookup , first at index then in linked-list's
		if (hash_table[hash] == nullptr)
		{
			return -INT32_MAX;

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

	//Operator overload to set key
	void operator[](const char* _key , const valType& _value)
	{
		//just call the underlying add function
		add(_key, _value);
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
				hash_table[hash]->setKey(_value);
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