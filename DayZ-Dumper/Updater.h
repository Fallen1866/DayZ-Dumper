#pragma once

#define SCAN_OFFSET(klass, name) {Signatures::klass::name##Signature, Signatures::klass::name##Mask, Offsets::klass::name, Signatures::klass::name##Offset, Signatures::klass::name##Type } 
#define SCAN_OFFSETWRAP(klass, name) m_Scans.push_back(SCAN_OFFSET(klass, name))

struct ScanOffset {
	PBYTE		Signature;
	char*		Mask;
	INT64&		RefOffset;	// Negative offsets can occour, lol.
	UINT32		Offset;
	ScanType	Type;
};

class Updater {
private:
	Module*  m_Game = {};
	Address	m_Text = 0;
	UINT64	m_Size = 0;
	PBYTE	m_Code = nullptr;

	std::vector<ScanOffset> m_Scans = {};

public:
	Updater();
	~Updater();

private:
	Address PatternScan(PBYTE Signature, const char* Mask);
	bool DataCompare(PBYTE Data, PBYTE Signature, const char* Mask);

private:
	INT64 ResolveMovQWORD(UINT64 Instruction, UINT32 Offset);
	INT64 ResolveNormal(UINT64 Instruction, UINT32 Offset);
	INT64 ResolveShort(UINT64 Instruction, UINT32 Offset);
	INT64 ResolveBYTE(UINT64 Instruction, UINT32 Offset);
	INT64 ResolveTraceNormal(UINT64 Instruction, UINT32 Offset);	// Unreliable
	INT64 ResolveTraceShort(UINT64 Instruction, UINT32 Offset);		// Unreliable

private:
	bool Code();
	void Setup();

public:
	bool Init(Module* Game);
	bool Scan();
	bool Clean();
};

inline Updater* g_Updater = new Updater;