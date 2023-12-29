#include "Framework.h"

Updater::Updater() {

}

Updater::~Updater() {
	if (m_Code)
		delete[] m_Code;
}


Address Updater::PatternScan(PBYTE Signature, const char* Mask) {
	for (SIZE_T i = 0; i < m_Size; i++)
		if (DataCompare(&m_Code[i], Signature, Mask))
			return m_Text.Cast<UINT64>(i);

	return 0;
}

/* Thanks to that one guy on uc */
bool Updater::DataCompare(PBYTE Data, PBYTE Signature, const char* Mask) {

	for (; *Mask; ++Mask, ++Data, ++Signature)
		if (*Mask == 'x' && *Data != *Signature)
			return FALSE;

	return (*Mask == NULL);
}

/* Returns the offset to the qword, not the actual address. */
INT64 Updater::ResolveMovQWORD(UINT64 Instruction, UINT32 Offset) {

	Instruction += Offset;

	const auto InstructionOffset = g_Coms->Read<int>((PVOID)(Instruction + 3));

	Instruction += 7;

	return (Instruction + InstructionOffset) - m_Game->GetBase().Cast<UINT64>();
}

INT64 Updater::ResolveNormal(UINT64 Instruction, UINT32 Offset) {

	Instruction += Offset;

	const auto InstructionOffset = g_Coms->Read<int>((PVOID)(Instruction + 3));

	return InstructionOffset;
}

INT64 Updater::ResolveShort(UINT64 Instruction, UINT32 Offset) {

	Instruction += Offset;

	const auto InstructionOffset = g_Coms->Read<BYTE>((PVOID)(Instruction + 3));

	return InstructionOffset;
}

INT64 Updater::ResolveBYTE(UINT64 Instruction, UINT32 Offset) {

	Instruction += Offset;

	const auto InstructionOffset = g_Coms->Read<int>((PVOID)(Instruction + 2));

	return InstructionOffset;
}

INT64 Updater::ResolveTraceNormal(UINT64 Instruction, UINT32 Offset) {

	const auto CallOffset = g_Coms->Read<int>((PVOID)(Instruction + 1));

	// Go into Call.

	const auto CallEntry = Instruction + CallOffset + 5;

	// Go to offset from there

	const auto InstructionOffset = g_Coms->Read<int>((PVOID)(CallEntry + Offset + 3));

	return InstructionOffset;
}

INT64 Updater::ResolveTraceShort(UINT64 Instruction, UINT32 Offset) {

	const auto CallOffset = g_Coms->Read<int>((PVOID)(Instruction + 1));

	// Go into Call.

	const auto CallEntry = Instruction + CallOffset + 5;

	// Go to offset from there

	const auto InstructionOffset = g_Coms->Read<BYTE>((PVOID)(CallEntry + Offset + 3));

	return (UINT64)InstructionOffset;
}


bool Updater::Code() {
	m_Text = m_Game->GetSection(".text", &m_Size);

	if (!m_Text)
		return false;

	m_Code = new BYTE[m_Size];

	memset(m_Code, 0, m_Size);

	return g_Coms->ReadToBuffer(m_Text.Cast<PVOID>(), m_Code, m_Size);
}

void Updater::Setup() {
	

/* Module Offsets */
	SCAN_OFFSETWRAP(ModuleBase, World);

/* World Offsets */
	SCAN_OFFSETWRAP(World, NearEntList);
	SCAN_OFFSETWRAP(World, FarEntList);
	SCAN_OFFSETWRAP(World, LocalPlayer);
	SCAN_OFFSETWRAP(World, LocalOffset);
	SCAN_OFFSETWRAP(World, Camera);

/* DayZInfected Offsets */
	SCAN_OFFSETWRAP(DayZInfected, DayZInfectedType);
	SCAN_OFFSETWRAP(DayZInfected, EntityVisualState);
	SCAN_OFFSETWRAP(DayZInfected, InfectedSkeleton);

/* DayZInfectedType Offsets */
	SCAN_OFFSETWRAP(DayZInfectedType, ObjectName);
	SCAN_OFFSETWRAP(DayZInfectedType, CategoryName);

/* DayZPlayer Signatures */
	SCAN_OFFSETWRAP(DayZPlayer, DayZPlayerType);
	SCAN_OFFSETWRAP(DayZPlayer, DayZPlayerTypeOffset);
	SCAN_OFFSETWRAP(DayZPlayer, PlayerSkeleton);

/* Skeleton Signature */
	SCAN_OFFSETWRAP(Skeleton, AnimClass1);
	SCAN_OFFSETWRAP(Skeleton, AnimClass2);

/* AnimClass Signature */
	SCAN_OFFSETWRAP(AnimClass, MatrixArray);

}

bool Updater::Init(Module* Game) {
	
	if (!Game)
		return false;
	
	m_Game = Game;

	Setup();

	return Code();
}

bool Updater::Scan() {
	
	for (auto& Scan : m_Scans) {

		auto Instruction = PatternScan(Scan.Signature, Scan.Mask);

		if (!Instruction) {
			printf("[Updater] Pattern Failed: 0x%llX\n[Updater] Reverted to default -> 0x%llX\n", Instruction.Cast<UINT64>(), Scan.RefOffset);
			continue;
		}

		switch (Scan.Type) {

		case ScanType::MovRegCS:		Scan.RefOffset = ResolveMovQWORD(Instruction.Cast<UINT64>(), Scan.Offset);		break;
		case ScanType::NORMAL:			Scan.RefOffset = ResolveNormal(Instruction.Cast<UINT64>(), Scan.Offset);		break;
		case ScanType::SHORT:			Scan.RefOffset = ResolveShort(Instruction.Cast<UINT64>(), Scan.Offset);			break;
		case ScanType::BYTE:			Scan.RefOffset = ResolveBYTE(Instruction.Cast<UINT64>(), Scan.Offset);			break;
		case ScanType::TRACENORMAL:		Scan.RefOffset = ResolveTraceNormal(Instruction.Cast<UINT64>(), Scan.Offset);	break;
		case ScanType::TRACESHORT:		Scan.RefOffset = ResolveTraceShort(Instruction.Cast<UINT64>(), Scan.Offset);	break;
		
		default:
			printf("[Updater] Invalid Type...\n");
			break;
		}

		printf("Offset: 0x%llX\n", Scan.RefOffset);
	}

	return true;

}

bool Updater::Clean() {

	if (m_Code)
		delete[] m_Code;

	return true;

}
