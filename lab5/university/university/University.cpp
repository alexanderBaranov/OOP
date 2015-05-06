#include "stdafx.h"
#include "University.h"


CUniversity::CUniversity(std::string name)
:m_name(name)
{
}


CUniversity::~CUniversity()
{
}


const std::string CUniversity::GetName() const
{
	return m_name;
}


void CUniversity::SetName(const std::string name)
{
	m_name = name;
}
