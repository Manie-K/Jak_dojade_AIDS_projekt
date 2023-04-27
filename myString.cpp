#include "myString.h"

myString::myString() { size = 0; data = nullptr; }
myString::~myString() { 
	if (this != nullptr) {
		delete[] data;
		data = nullptr;
	}
}

myString::myString(const char* newData)
{
	if (newData == nullptr)
	{
		data = nullptr;
		size = 0;
		return;
	}
	size = strlen(newData) + 1;
	data = new char[size];
	for (int i = 0; i < size; i++)
		data[i] = newData[i];
}

myString::myString(const myString& temp)
{
	if (temp.size == 0)
	{
		size = 0;
		data = nullptr;
		return;
	}
	size = temp.size;
	data = new char[size];
	int actualSize = 0;
	for (int i = 0; i < size; i++) {
		if (temp.data[i] != '\xFD') {
			data[i] = temp.data[i];
			actualSize++;
		}
		else i--;
	}
	size = actualSize;
	data[size - 1] = STR_END_KEY;
}

void myString::pushCharAtEnd(const char ch)
{
	if (data == nullptr || size == 0)
	{
		size = 2;
		data = new char[size];
		data[0] = ch;
		data[1] = STR_END_KEY;
		return;
	}
	if (ch != STR_END_KEY)
	{
		char* temp = new char[size];
		for (int i = 0; i < size; i++)
			temp[i] = data[i];
		delete[] data;
		size++;
		data = new char[size];

		for (int i = 0; i < size - 2; i++)
		{
			data[i] = temp[i];
		}
		data[size - 2] = ch;
		data[size - 1] = STR_END_KEY;

		delete[] temp;
		temp = nullptr;
	}
}

void myString::trim()
{
	if (size == 1)
		return;
	int beginCount = 0;
	int endCount = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (data[i] == STR_END_KEY || data[i] == SPACE_KEY || data[i] == ENTER_KEY || data[i] == TAB_KEY || data[i] == CARRIAGE_KEY
			|| data[i] == VERT_TAB_KEY || data[i] == FORM_KEY)
			beginCount++;
		else
			break;
	}

	for (int i = size - 1; i >= 0; i--)
	{
		if (data[i] == STR_END_KEY || data[i] == SPACE_KEY || data[i] == ENTER_KEY || data[i] == TAB_KEY || data[i] == CARRIAGE_KEY
			|| data[i] == VERT_TAB_KEY || data[i] == FORM_KEY)
			endCount++;
		else
			break;
	}

	if (beginCount + endCount >= size)
	{
		delete[] data;
		data = new char[1];
		data[0] = STR_END_KEY;
		size = 1;
		return;
	}
	int newSize = size + 1 - endCount - beginCount;

	char* tab = new char[newSize];
	for (int i = beginCount; i <= size-endCount; i++)
	{
		tab[i - beginCount] = data[i];
	}
	tab[newSize - 1] = STR_END_KEY;
	delete[] data;
	size = newSize;
	data = new char[size];
	for (int i = 0; i < size; i++)
		data[i] = tab[i];
	data[size - 1] = STR_END_KEY;
	delete[] tab;  
}

int myString::toInt() const
{	if(size == 0) 
		return 0;
	const int asciiOffset = 48;
	int result = 0;
	int tenPower = 1;

	for (int i = size - 2; i >= 0; i--)
	{
		if (data[i] == '-')
		{
			result *= -1;
			continue;
		}
		result += (int)(data[i] - asciiOffset) * tenPower;
		tenPower *= 10;
	}
	return result;
}

const char* myString::getCharPointer() const{
	return data;
}

size_t myString::getSize() const {return size; }

ostream& operator<<(ostream& os, const myString& s) 
{
	if (s.data == "")
		return os;
	os << s.data;
	return os;
}

istream& operator>>(istream& is, myString& s)
{
	const int BUFFER_SIZE = 2048;
	char* buffer = new char[BUFFER_SIZE];
	is >> buffer;
	
	if (s.data != nullptr)
		delete[] s.data;
	s.size = strlen(buffer) + 1;
	s.data = new char[s.size];
	for (int i = 0; i < s.size; i++)
		s.data[i] = buffer[i];

	delete[] buffer;
	return is;
}

bool myString::operator==(const myString& s) const
{
	if (this == nullptr)
		return false;
	if (data == nullptr || &s == nullptr || s.data == nullptr)
		return false;
	if (s.size != this->size)
		return false;
	for (int i = 0; i < size; i++)
	{
		if (data[i] != s.data[i])
			return false;
	}
	return true;
}
bool myString::operator==(myString& s) const
{
	if (this == nullptr)
		return false;
	if (data == nullptr || &s == nullptr || s.data == nullptr)
		return false;
	if (s.size != this->size)
		return false;
	for (int i = 0; i < size; i++)
	{
		if (data[i] != s.data[i])
			return false;
	}
	return true;
}

bool myString::operator==(const char* s)
{
	int tempSize = strlen(s)+1;
	if (tempSize != size)
		return false;
	for (int i = 0; i < size; i++)
		if (data[i] != s[i])
			return false;
	return true;
}

myString& myString::operator=(const myString& s)
{
	if (this == nullptr || &s == nullptr || s.data == nullptr)
		return *this;
	delete[] data;
	size = s.size;
	data = new char[size];
	for (int i = 0; i < size; i++)
		data[i] = s.data[i];
	return *this;
}

myString& myString::operator=(const char* s)
{
	if (s == nullptr || this == nullptr)
		return *this;
	delete[] data;
	size = strlen(s) + 1;
	data = new char[size];
	for (int i = 0; i < size; i++)
		data[i] = s[i];
	return *this;
}

myString& myString::operator+=(const myString& s)
{
	char* oldData = new char[size];
	for (int i = 0; i < size; i++)
		oldData[i] = data[i];
	delete[] data;
	int oldSize = size;
	size = size + s.size - 1;
	data = new char[size];
	int i;
	for (i = 0; i < oldSize - 1; i++)
		data[i] = oldData[i];
	for (i = oldSize - 1; i < size; i++)
		data[i] = s.data[i - oldSize + 1];
	data[size - 1] = STR_END_KEY;
	delete[] oldData;
	return *this;
}

char myString::operator[](size_t index) const
{
	if (this == nullptr || data == nullptr)
		return SPACE_KEY;
	if (index >= 0 && index < size)
		return (char)data[index];
	return SPACE_KEY;
}