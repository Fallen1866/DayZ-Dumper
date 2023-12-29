#pragma once

class Address {
private:
	UINT64 m_Address = 0;

public:
	Address(UINT64 Address);
	Address();
	~Address();

public:
	template<typename T = Address>
	T Read(UINT64 Offset = 0x0) {
		// SIMULATE SLOW READS >:)
		//for (int i = 0; i < 50000; i++) {}

		return g_Coms->Read<T>((PVOID)(m_Address + Offset));
	}

	template<typename T>
	void Write(T Buffer, UINT64 Offset = 0x0) {
		g_Coms->Write((PVOID)(m_Address + Offset), Buffer);
	}

	template<typename T = Address>
	T Cast(INT64 Offset = 0x0) {
		return (T)(m_Address + Offset);
	}


	template<typename T = Address>
	T Chain(std::vector<UINT64> Offsets) {
		T Result = Cast<T>();

		for (auto& Offset : Offsets)
			Result = Read<T>(Offset);

		return Result;
	}

public:
	std::wstring StringW(SIZE_T Size = 20);
	std::string StringA(SIZE_T Size = 20);

public:
	bool operator ! () {
		return !m_Address;
	}

	bool operator ()() {
		return m_Address;
	}

	bool operator == (Address _Address) {
		return _Address.Cast<UINT64>() == Cast<UINT64>();
	}

	Address operator + (Address _Address) {
		return Address(_Address.Cast<UINT64>() + Cast<UINT64>());
	}

	Address operator + (UINT64 Relative) {
		return Address(Cast<UINT64>() + Relative);
	}
};