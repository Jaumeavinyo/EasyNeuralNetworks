
#ifndef STRING_H
#define STRING_H

#include <cstring>

class String
{
public:

	String() : p_str(nullptr), p_numChars(0){ }

	String(const char* pstr) : p_numChars(strlen(pstr)), p_str(new char[p_numChars + 1]){
		strcpy_s(p_str, p_numChars + 1, pstr);
	}

	String(const String& pstr) : p_numChars(pstr.p_numChars), p_str(new char[p_numChars + 1]){
		strcpy_s(p_str, p_numChars + 1, pstr.p_str);
	}

	~String()
	{
		delete[] p_str;
	}

	bool Empty() const
	{
		return p_numChars == 0;
	}

	unsigned int Size() const
	{
		return p_numChars;
	}

	void Clear()
	{
		delete[] p_str;
		p_str = nullptr;
		p_numChars = 0;
	}

	const char* GetString() const
	{
		return p_str;
	}

	void operator=(const String& pstr)
	{
		delete[] p_str;
		p_numChars = pstr.p_numChars;
		p_str = new char[p_numChars + 1];
		strcpy_s(p_str, p_numChars + 1, pstr.p_str);
	}

	void operator+=(const String& pstr)
	{
		unsigned int new_num_chars = p_numChars + pstr.p_numChars;
		char* new_str = new char[new_num_chars + 1];
		strcpy_s(new_str, new_num_chars + 1, p_str);
		strcat_s(new_str, new_num_chars + 1, pstr.p_str);
		delete[] p_str;
		p_numChars = new_num_chars;
		p_str = new_str;
	}

	String operator+(const String& s) const
	{
		String concatenation(p_str);
		concatenation += s;
		return concatenation;
	}

	bool operator==(const String& pstr)
	{
		return strcmp(p_str, pstr.p_str) == 0;
	}

	bool operator!=(const String& pstr)
	{
		return strcmp(p_str, pstr.p_str) != 0;
	}

private:

	unsigned int p_numChars = 0;
	char* p_str = nullptr;
};

#endif // STRING_H