#include "Framework.h"

Interface::Interface() {

}

Interface::~Interface() {
	if (m_ProcessId && m_Handle)
		CloseHandle(m_Handle);
}

bool Interface::OpenHandle() {

	m_Handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_ProcessId);

	return m_Handle != INVALID_HANDLE_VALUE;
}

bool Interface::FindProcess(const char* ProcessName, DWORD& Pid) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 ProcessEntry;
	ProcessEntry.dwSize = sizeof(ProcessEntry);

	if (Process32First(hSnap, &ProcessEntry)) {
		do {

			if (!strcmp(ProcessName, ProcessEntry.szExeFile)) {
				Pid = ProcessEntry.th32ProcessID;

				CloseHandle(hSnap);

				return true;
			}

		} while (Process32Next(hSnap, &ProcessEntry));
	}

	CloseHandle(hSnap);
	return false;
}

Module Interface::GetModule(const wchar_t* ModuleName) {

	auto Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, m_ProcessId);

	if (!Snapshot) {
		CloseHandle(Snapshot);
		return {};
	}

	auto Buffer = Module{};

	MODULEENTRY32W ModuleEntry;
	ModuleEntry.dwSize = sizeof(ModuleEntry);

	if (Module32FirstW(Snapshot, &ModuleEntry)) {
		do {

			if (!wcscmp(ModuleName, ModuleEntry.szModule)) {

				Buffer = Module(
					ModuleName,
					(UINT64)ModuleEntry.modBaseAddr,
					(UINT64)ModuleEntry.modBaseSize
				);

				break;
			}

		} while (Module32NextW(Snapshot, &ModuleEntry));
	}

	CloseHandle(Snapshot);
	return Buffer;
}

bool Interface::ReadToBuffer(PVOID MemoryLocation, PVOID Buffer, SIZE_T Size) {
	return ReadProcessMemory(m_Handle, (LPCVOID)MemoryLocation, Buffer, Size, NULL);
}

bool Interface::WriteToBuffer(PVOID MemoryLocation, PVOID Buffer, SIZE_T Size) {
	return WriteProcessMemory(m_Handle, (LPVOID)MemoryLocation, Buffer, Size, NULL);
}

bool Interface::Init(const char* ProcessName) {

	if (!FindProcess(ProcessName, m_ProcessId))
		return false;

	return OpenHandle();
}