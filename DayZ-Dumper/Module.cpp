#include "Framework.h"

Module::Module() {

}

Module::Module(std::wstring Name, UINT64 Base, UINT64 Size) {
	m_Name = Name;
	m_Base = Base;
	m_Size = Size;
}

Module::~Module() {

}

auto Module::GetName() -> std::wstring {
	return m_Name;
}

auto Module::GetBase() -> Address {
	return Address(m_Base);
}

auto Module::GetSize() -> UINT64 {
	return m_Size;
}

auto Module::GetSection(const char* Name, UINT64* Size) -> Address {

	auto Dos = GetBase().Read<IMAGE_DOS_HEADER>();

	if (!Dos.e_lfanew)
		return NULL;

	auto Nt = GetBase().Read<IMAGE_NT_HEADERS>(
		Dos.e_lfanew
	);


	for (auto i = 0; i < Nt.FileHeader.NumberOfSections; i++) {
		const auto SectionHeader = g_Coms->Read<IMAGE_SECTION_HEADER>(
			(PVOID)(GetBase().Cast<UINT64>() + Dos.e_lfanew + sizeof(IMAGE_NT_HEADERS) + (i * sizeof(IMAGE_SECTION_HEADER)))
		);

		if (!strcmp((const char*)SectionHeader.Name, Name)) {
			
			if (Size)
				*Size = SectionHeader.SizeOfRawData;

			return GetBase().Cast(SectionHeader.VirtualAddress);
		}
	}

	return NULL;
}

bool Module::operator ()() {
	return m_Base;
}

bool Module::operator ! () {
	return !m_Base;
}
