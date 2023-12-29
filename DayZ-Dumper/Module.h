#pragma once

class Module {
private:
	std::wstring	m_Name;
	UINT64			m_Base = 0;
	UINT64			m_Size = 0;

public:
	Module();
	Module(std::wstring Name, UINT64 Base, UINT64 Size);
	~Module();

public:
	auto GetName() -> std::wstring;
	auto GetBase() -> Address;
	auto GetSize() -> UINT64;

public:
	auto GetSection(const char* Name, UINT64* Size = nullptr) -> Address;

public:
	bool operator ()();
	bool operator ! ();
};