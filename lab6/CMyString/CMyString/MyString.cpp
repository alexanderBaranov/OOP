#include "stdafx.h"
#include "MyString.h"
#include <assert.h>

using namespace std;

CMyString::CMyString()
{
	SetEmptyString();
}

CMyString::CMyString(const char * pString)
{
	assert(pString);

	size_t size = strlen(pString);
	m_chars = make_unique<char[]>(size + 1);
	memcpy(m_chars.get(), pString, size + 1);

	m_size = size;
}

CMyString::CMyString(const char * pString, size_t length)
{
	assert(pString);

	m_chars = make_unique<char[]>(length + 1);
	memcpy(m_chars.get(), pString, length);
	m_chars.get()[length] = '\0';

	m_size = length;
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
{
	size_t size = stlString.length();

	m_chars = make_unique<char[]>(size + 1);
	memcpy(m_chars.get(), stlString.c_str(), size + 1);

	m_size = size;
}

CMyString::CMyString(std::unique_ptr<char[]> &&pString, size_t length)
{
	m_chars = move(pString);
	m_size = length;
}

void CMyString::SetEmptyString()
{
	m_chars = make_unique<char[]>(1);
	m_chars.get()[0] = '\0';
	m_size = 0;
}

bool CMyString::Empty() const
{
	return !m_size;
}

size_t CMyString::GetLength() const
{
	return m_size;
}

char* CMyString::GetStringDataImpl() const
{
	return (m_chars != nullptr) ? m_chars.get() : "";
}

const char* CMyString::GetStringData() const
{
	return GetStringDataImpl();
}

CMyString CMyString::SubString(size_t start, size_t length /*= SIZE_MAX*/) const
{
	if (start >= m_size)
	{
		return CMyString();
	}

	if (start + length > m_size)
	{
		return CMyString(m_chars.get() + start, m_size - start);
	}
	
	return CMyString(m_chars.get() + start, length);
}

void CMyString::Clear()
{
	if (m_size)
	{
		SetEmptyString();
	}
}

char& CMyString::operator[](size_t index)
{
	if (index > m_size)
	{
		throw out_of_range("string subscript out of range");
	}

	return GetStringDataImpl()[index];
}

const char& CMyString::operator[](size_t index) const
{
	if (index > m_size)
	{
		throw out_of_range("string subscript out of range");
	}

	return GetStringDataImpl()[index];
}

CMyString& CMyString::operator+=(const CMyString &other)
{
	if (other.Empty())
	{
		return *this;
	}

	size_t length = m_size + other.GetLength();
	auto chars = make_unique<char[]>(length + 1);

	memcpy(chars.get(), m_chars.get(), m_size);
	memcpy(chars.get() + m_size, other.GetStringData(), other.GetLength() + 1);

	m_chars = move(chars);
	m_size = length;

	return *this;
}

CMyString& CMyString::operator=(const CMyString &other)
{
	if (this == &other)
	{
		return *this;
	}

	size_t length = other.GetLength();

	m_chars = make_unique<char[]>(length + 1);
	memcpy(m_chars.get(), other.GetStringData(), length + 1);
	m_size = length;

	return *this;
}

CMyString& CMyString::operator=(CMyString &&other)
{
	if (this == &other)
	{
		return *this;
	}

	m_chars = move(other.m_chars);
	m_size = other.m_size;

	other.m_size = 0;
	//other.m_chars = make_unique<char[]>(1);
	//other.m_chars.get()[0] = '\0';

	return *this;
}

bool StringsAreEqual(const CMyString &leftString, const CMyString &rightString)
{
	size_t sizeOfLeftString = leftString.GetLength();
	size_t sizeOfRightString = rightString.GetLength();

	return (sizeOfLeftString == sizeOfRightString) ?
		memcmp(leftString.GetStringData(), rightString.GetStringData(), sizeOfRightString) == 0 :
		false;
}

bool operator ==(const CMyString &leftString, const CMyString &rightString)
{
	return StringsAreEqual(leftString, rightString);
}

bool operator !=(const CMyString &leftString, const CMyString &rightString)
{
	return !StringsAreEqual(leftString, rightString);
}

CMyString operator +(const CMyString &leftString, const CMyString &rightString)
{
	if (leftString.Empty() && rightString.Empty())
	{
		return "";
	}

	auto temp = std::make_unique<char[]>(leftString.m_size + rightString.m_size + 1);
	memcpy(temp.get(), leftString.m_chars.get(), leftString.m_size);
	memcpy(temp.get() + leftString.m_size, rightString.m_chars.get(), rightString.m_size + 1);

	return CMyString(std::move(temp), leftString.m_size + rightString.m_size);
}
