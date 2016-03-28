#include "stdafx.h"
#include "MyString.h"
#include <assert.h>

using namespace std;

CMyString::CMyString() throw()
{
	m_size = 0;
	m_chars = make_unique<char[]>('\0');
}

CMyString::CMyString(const char * pString)
{
	assert(pString);

	m_size = strlen(pString);
	m_chars.reset(new char[m_size + 1]);
	memcpy(m_chars.get(), pString, m_size + 1);
}

CMyString::CMyString(const char * pString, unsigned length)
{
	assert(pString);

	m_size = length;

	m_chars.reset(new char[m_size + 1]);
	memset(m_chars.get(), '\0', m_size + 1);
	memcpy(m_chars.get(), pString, m_size);
}

CMyString::CMyString(CMyString const& other)
{
	*this = other;
}

CMyString::CMyString(CMyString && other)
{
	*this = move(other);
}

CMyString::CMyString(std::string const& stlString)
: m_size(stlString.length())
{
	m_chars.reset(new char[m_size + 1]);
	memcpy(m_chars.get(), stlString.c_str(), m_size + 1);
}

bool CMyString::Empty()const
{
	return !m_size;
}

size_t CMyString::GetLength() const
{
	return m_size;
}

const char* CMyString::GetStringData() const
{
	return m_chars.get();
}

CMyString const CMyString::SubString(unsigned start, unsigned length /*= UINT_MAX*/) const
{
	if (start + length > m_size)
	{
		return *this;
	}
	
	return CMyString(m_chars.get() + start, length);
}

void CMyString::Clear()
{
	m_chars.reset(nullptr);
}

char& CMyString::operator[](size_t index)
{
	if ((index > m_size)
		|| ((m_size == 0) && (index == 0)))
	{
		throw exception("string subscript out of range");
	}

	return m_chars.get()[index];
}

const char& CMyString::operator[](size_t index) const
{
	if ((index > m_size) 
		|| ((m_size == 0) && (index == 0)))
	{
		throw exception("string subscript out of range");
	}

	return m_chars.get()[index];
}

CMyString& CMyString::operator+=(const CMyString &other)
{
	if (!other.GetLength())
	{
		return *this;
	}

	CMyString tmp = *this + other;
	*this = tmp;

	return *this;
}

CMyString& CMyString::operator=(const CMyString &other)
{
	if (this == &other)
	{
		return *this;
	}

	m_size = other.GetLength();
	m_chars.reset(new char [m_size + 1]);
	memcpy(m_chars.get(), other.GetStringData(), m_size + 1);

	return *this;
}

size_t GetComprasionSize(const CMyString &leftString, const CMyString &rightString)
{
	size_t sizeOfLeftString = leftString.GetLength();
	size_t sizeOfRightString = rightString.GetLength();
	return (sizeOfLeftString > sizeOfRightString) ? sizeOfLeftString : sizeOfRightString;
}

bool operator ==(const CMyString &leftString, const CMyString &rightString)
{
	size_t cmpSize = GetComprasionSize(leftString, rightString);
	return memcmp(leftString.GetStringData(), rightString.GetStringData(), cmpSize) == 0;
}

bool operator !=(const CMyString &leftString, const CMyString &rightString)
{
	size_t cmpSize = GetComprasionSize(leftString, rightString);
	return memcmp(leftString.GetStringData(), rightString.GetStringData(), cmpSize) != 0;
}

CMyString operator +(const CMyString &leftString, const CMyString &rightString)
{
	if (leftString.Empty() && rightString.Empty() )
	{
		return nullptr;
	}

	size_t sizeOfLeftString = leftString.GetLength();
	size_t sizeOfRightString = rightString.GetLength();

	size_t length = leftString.GetLength() + rightString.GetLength() + 1;
	std::unique_ptr<char[]> chars(new char[length]);

	memcpy(chars.get(), leftString.GetStringData(), sizeOfLeftString);
	memcpy(chars.get() + sizeOfLeftString, rightString.GetStringData(), sizeOfRightString);
	
	chars.get()[length - 1] = '\0';

	return CMyString(chars.get(), length-1);
}
