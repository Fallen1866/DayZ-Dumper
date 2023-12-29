#pragma once

class Interface {
private:
	DWORD	m_ProcessId = 0;
	HANDLE	m_Handle	= 0;

public:
	Interface();
	~Interface();

private:
	bool OpenHandle();
	bool FindProcess(const char* ProcessName, DWORD& Pid);

public:
	template<typename T>
	inline T Read(PVOID MemoryLocation) {
		T Buffer = {};

		::ReadProcessMemory(m_Handle, (LPCVOID)MemoryLocation, &Buffer, sizeof(T), NULL);

		return Buffer;
	}

	template<typename T>
	inline void Write(PVOID MemoryLocation, T Buffer) {
		::WriteProcessMemory(m_Handle, (LPVOID)MemoryLocation, &Buffer, sizeof(T), NULL);
	}

	PVOID GetModule(const wchar_t* ModuleName);

	bool ReadToBuffer(PVOID MemoryLocation, PVOID Buffer, SIZE_T Size);
	bool WriteToBuffer(PVOID MemoryLocation, PVOID Buffer, SIZE_T Size);

public:
	bool Init(const char* ProcessName);
};

inline Interface* g_Coms = new Interface;