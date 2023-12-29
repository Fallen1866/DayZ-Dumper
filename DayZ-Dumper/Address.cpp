#include "Framework.h"

Address::Address(UINT64 Address) {
	m_Address = Address;
}

Address::Address() {
	m_Address = 0;
}

Address::~Address() {

}

auto Address::StringW(SIZE_T Size) -> std::wstring {
	if (Size == -1) {
		constexpr auto SafeLimit = 0x1000;

		std::wstring Buffer;

		for (int i = 0; i < SafeLimit * sizeof(wchar_t); i += sizeof(wchar_t)) {
			auto Data = g_Coms->Read<wchar_t>((PVOID)(Cast<UINT64>() + i));

			Buffer += Data;

			if (Data == L'\x00')
				break;
		}

		return Buffer;
	}

	wchar_t* ReadBuffer = new wchar_t[Size];

	g_Coms->ReadToBuffer(Cast<PVOID>(), ReadBuffer, Size * sizeof(wchar_t));

	auto StringBuffer = std::wstring(ReadBuffer);

	delete[] ReadBuffer;

	return StringBuffer;
}

auto Address::StringA(SIZE_T Size) -> std::string {
	if (Size == -1) {
		constexpr auto SafeLimit = 0x1000;

		std::string Buffer;

		for (int i = 0; i < SafeLimit; i++) {
			auto Data = g_Coms->Read<char>((PVOID)(Cast<UINT64>() + i));

			Buffer += Data;

			if (Data == '\x00')
				break;
		}

		return Buffer;
	}

	char* ReadBuffer = new char[Size];

	g_Coms->ReadToBuffer(Cast<PVOID>(), ReadBuffer, Size * sizeof(char));

	auto StringBuffer = std::string(ReadBuffer);

	delete[] ReadBuffer;

	return StringBuffer;
}