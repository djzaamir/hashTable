/*
 * Generally in c++ programming it is not adviced to spilit declaration and defination of templated classes 
 * because it will produce alot of problems
 */

#pragma once

template<class valueType>
 class HashNode
{
	const char* key;
	valueType value;
	HashNode *next;

public:
	HashNode()
	{
		next = nullptr;
	}
	HashNode(const char* _key , const valueType _value):key(_key),value(_value)
	{
		next = nullptr;
	}
	~HashNode()
	{
		//To empty the linked-list section
		while (next != nullptr)
		{
			HashNode * to_remove = next; //get the target location to remove
			next = next->next;           //look for next location to delete and get a ptr to it
			
			//Perform delete
			delete to_remove;
		}
	}

	//getter and setters
    const char* getKey() const
	{
		return key;
	}
	const valueType& getValue()const
	{
		return value;
	}
	HashNode* getNext()const
	{
		return next;
	}


	void setValue(const valueType value)
	{
		this->value = value;
	}
	void setKey(const char* key)
	{
		this->key = key;
	}
	void setNext(const HashNode* next)
	{
		this->next = next;
	}

};