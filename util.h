#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <vector>
#include <typeinfo>
#include <map>
#include <algorithm>
#include "color.h"

using namespace std;

string num2str(double x);
char* read_file(const char* filename);
char* cstrcpy(char*& dest_cstr, const char* src_cstr);
void ok();
void ok(int n);

char* lower(const char* cstr);
string lower(string str);

struct Thing
{
	void* ptr_data = NULL;
	string type;
	int size = 0;

public:
	Thing(){}

	template<class DataType>
	Thing(const DataType& data);

	template<class DataType>
	DataType& data();
};

template<class DataType>
DataType& Thing::data()
{
	return *((DataType*)ptr_data);
}

class GTVector
{
private:
	vector<Thing> things;

public:
	GTVector(){}

	template<class DataType>
	GTVector(int n, const DataType& data) : things(vector<Thing>(n, Thing(data))) {}

	template<class DataType>
	GTVector(DataType argv) : things(vector<Thing>(1, Thing(argv))) {}

	template<class DataType, class... DataTypes>
	GTVector(DataType first, DataTypes... rest);

	int size()const;
	bool empty()const;

	template<class DataType>
	void push_back(const DataType& data);

	template<class DataType>
	DataType pop_back();

	template<class DataType>
	void push_front(const DataType& data);

	template<class DataType>
	DataType pop_front();

	template<class DataType>
	DataType& front();

	template<class DataType>
	DataType& back();

	template<class DataType>
	DataType& at(int i);

	template<class DataType>
	DataType at(int i)const;

	template<class DataType>
	DataType get(int i)const;

	string type(int i)const;

	void clear();
};

class Options
{
private:
	map<string, Thing> pairs;

public:
	Options(){}
	Options(const Options& options) : pairs(options.pairs) {}

	template<class ... DataTypes>
	Options(Options default_options, DataTypes... argv);

	Options(Options default_options, GTVector varargin);
	Thing& operator [](string name);
	bool has(string name)const;
};

template<class ... DataTypes>
Options::Options(Options default_options, DataTypes... argv)
{
	GTVector varargin(argv...);
	int nargin = varargin.size();
	for(int i = 0; i < nargin-1; i += 2)
	{
		if(varargin.type(i) == "PKc" && default_options.has(varargin.at<char*>(i)))
		{
			if(varargin.type(i+1) == "PKc")
			{
				default_options[varargin.at<char*>(i)] = string(varargin.at<char*>(i+1));
			}
			else if(varargin.type(i+1) == "5Color")
				default_options[varargin.at<char*>(i)] = varargin.at<Color>(i+1);
			else if(varargin.type(i+1) == "f")
				default_options[varargin.at<char*>(i)] = varargin.at<float>(i+1);
		}
	}

	pairs = default_options.pairs;
}

template<class DataType>
Thing::Thing(const DataType& data)
{
	type = typeid(data).name();
	size = sizeof(data);
	ptr_data = (void*)(new DataType(data));
}

template<class DataType, class... DataTypes>
GTVector::GTVector(DataType first, DataTypes... rest) :
things(vector<Thing>(1, Thing(first)))
{
	GTVector vector_rest(rest...);
	things.insert(things.end(), vector_rest.things.begin(), vector_rest.things.end());
}

template<class DataType>
void GTVector::push_back(const DataType& data)
{
	things.push_back(Thing(data));
}

template<class DataType>
DataType GTVector::pop_back()
{
	DataType back_data = *(DataType*)(things.back().ptr_data);
	things.pop_back();
	return back_data;
}

template<class DataType>
void GTVector::push_front(const DataType& data)
{
    things.insert(things.begin(), Thing(data));
}

template<class DataType>
DataType GTVector::pop_front()
{
    DataType back_data = *(DataType*)(things.front().ptr_data);
	things.erase(things.begin());
	return back_data;
}

template<class DataType>
DataType& GTVector::front()
{
	return *(DataType*)(things.front().ptr_data);
}

template<class DataType>
DataType& GTVector::back()
{
	return *(DataType*)(things.back().ptr_data);
}

template<class DataType>
DataType& GTVector::at(int i)
{
	return *(DataType*)(things.at(i).ptr_data);
}

template<class DataType>
DataType GTVector::at(int i)const
{
	return *(DataType*)(things.at(i).ptr_data);
}

template<class DataType>
DataType GTVector::get(int i)const
{
	return *(DataType*)(things.at(i).ptr_data);
}

#endif