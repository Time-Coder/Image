#include "util.h"

string num2str(double x)
{
    stringstream ss;
    string str;
    ss << x;
    ss >> str;
    return str;
}

char* cstrcpy(char*& dest_cstr, const char* src_cstr)
{
	if(!dest_cstr)
	{
		dest_cstr = (char*)malloc((strlen(src_cstr) + 1) * sizeof(char));
	}
	else
	{
		dest_cstr = (char*)realloc(dest_cstr, (strlen(src_cstr) + 1) * sizeof(char));
	}
	return strcpy(dest_cstr, src_cstr);
}

char* read_file(const char* filename)
{
    string str;
    ifstream ifs;
    stringstream ss;
    ifs.exceptions(ifstream::failbit | ifstream::badbit);
    try 
    {
        ifs.open(filename);
        ss << ifs.rdbuf();
        ifs.close();
    }
    catch(ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }

	char* cstr = NULL;
	return cstrcpy(cstr, ss.str().c_str());
}

void ok()
{
    cout << "I am here!" << endl;
}

void ok(int n)
{
    cout << "I am here!" << n << endl;
}

char* lower(const char* cstr)
{
    char* dest_cstr = NULL;
    cstrcpy(dest_cstr, cstr);

    if(dest_cstr == NULL)
    {
        return dest_cstr;
    }

    int n = strlen(dest_cstr);
    for(int i = 0; i < n; i++)
    {
        if(dest_cstr[i] >= 'A' && dest_cstr[i] <= 'Z')
        {
            dest_cstr[i] = dest_cstr[i] - ('A' - 'a');
        }
    }
    return dest_cstr;
}

string lower(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

int GTVector::size()const
{
    return things.size();
}

bool GTVector::empty()const
{
    return things.empty();
}

void GTVector::clear()
{
    things.clear();
}

string GTVector::type(int i)const
{
    return things[i].type;
}

Options::Options(Options default_options, GTVector varargin)
{
    int nargin = varargin.size();
    for(int i = 0; i < nargin-1; i += 2)
    {
        if(varargin.type(i) == "PKc" && default_options.has(varargin.at<char*>(i)))
        {
            if(varargin.type(i+1) == "PKc")
                default_options[varargin.at<char*>(i)] = varargin.at<char*>(i+1);
            else if(varargin.type(i+1) == "5Color")
                default_options[varargin.at<char*>(i)] = varargin.at<Color>(i+1);
            else if(varargin.type(i+1) == "f")
                default_options[varargin.at<char*>(i)] = varargin.at<float>(i+1);
        }
    }

    pairs = default_options.pairs;
}

bool Options::has(string name)const
{
    name = lower(name);
    return pairs.find(name) != pairs.end();
}

Thing& Options::operator [](string name)
{
    name = lower(name);
    return pairs[name];
}