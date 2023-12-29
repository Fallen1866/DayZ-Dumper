#pragma once

// Placed here to stop shitty little linker error. - i'm need better .h management :(
enum class ScanType : int {
	MovRegCS,
	NORMAL,
	SHORT,
	BYTE,
	TRACENORMAL,		// <- Very unreliable, but works.
	TRACESHORT,
};

#define ADD_SIGNATURE(klass, name, off, type, sig, mask) namespace klass { inline BYTE* name##Signature = (BYTE*)(sig); inline char* name##Mask = (char*)(mask); inline UINT32 name##Offset = (UINT32)(off); inline ScanType name##Type = (ScanType)(type); }

namespace Signatures {

/* Module Offsets */
	ADD_SIGNATURE(ModuleBase, World, 0, ScanType::MovRegCS, "\x48\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE9\x00\x00\x00\x00\x49\x8B\xC7\xE9\x00\x00\x00\x00\x48\x8D\x4C\x24\x00\x48\x89\xBC\x24\x00\x00\x00\x00\xE8\x00\x00\x00\x00", "xxx????x????x????xxxx????xxxx?xxxx????x????");

/* World Offsets */
	ADD_SIGNATURE(World, NearEntList,	0,  ScanType::NORMAL,			"\x48\x8B\x83\x00\x00\x00\x00\x49\x8B\x0C\x06\x48\x85\xC9\x74\x14\x40\x38\xB9\x00\x00\x00\x00\x75\x0B", "xxx????xxxxxxxxxxxx????xx");
	ADD_SIGNATURE(World, FarEntList,	0,  ScanType::NORMAL,			"\x48\x8B\x83\x00\x00\x00\x00\x49\x8B\x0C\x06\x48\x3B\xCD\x74\x17\x80\xB9\x00\x00\x00\x00\x00\x75\x0E\x41\xB8\x00\x00\x00\x00\x0F\x28\xCE\xE8\x00\x00\x00\x00\xFF\xC6\x49\x83\xC6\x08\x3B\xB3\x00\x00\x00\x00\x7C\xCB", "xxx????xxxxxxxxxxx?????xxxx????xxxx????xxxxxxxx????xx");
	ADD_SIGNATURE(World, LocalPlayer,	0,  ScanType::TRACENORMAL,		"\xE8\x00\x00\x00\x00\x48\x8B\xD8\x48\x85\xC0\x74\x55\x48\x8B\x10\x48\x8B\xC8\xFF\x92\x00\x00\x00\x00", "x????xxxxxxxxxxxxxxxx????");
	ADD_SIGNATURE(World, LocalOffset,   16, ScanType::TRACENORMAL,		"\xE8\x00\x00\x00\x00\x48\x8B\xD8\x48\x85\xC0\x74\x55\x48\x8B\x10\x48\x8B\xC8\xFF\x92\x00\x00\x00\x00", "x????xxxxxxxxxxxxxxxx????");
	ADD_SIGNATURE(World, Camera,		0,	ScanType::NORMAL,			"\x48\x8B\x97\x00\x00\x00\x00\x48\x8B\x01\xFF\x50\x18\x4C\x8B\x87\x00\x00\x00\x00\x4D\x85\xC0\x74\x0F\x41\xC6\x80\x00\x00\x00\x00\x00\x4C\x8B\x87\x00\x00\x00\x00", "xxx????xxxxxxxxx????xxxxxxxx?????xxx????");

/* DayZInfected Offsets */
	ADD_SIGNATURE(DayZInfected, DayZInfectedType,	0, ScanType::NORMAL, "\x48\x8B\x83\x00\x00\x00\x00\x0F\x28\xC8\x83\xB8\x00\x00\x00\x00\x00\x7C\x0C\xF3\x0F\x10\x83\x00\x00\x00\x00\xF3\x0F\x5F\xC1\x48\x83\xC4\x20\x5B\xC3", "xxx????xxxxx?????xxxxxx????xxxxxxxxxx");
	ADD_SIGNATURE(DayZInfected, EntityVisualState,	0, ScanType::NORMAL, "\x4C\x8B\x82\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x41\x83\x7F\x00\x00\x74\x09\x8B\x46\x48\x24\x21\x3C\x01\x74\x0A\xFF\xC7\x48\xFF\xC3\x49\x3B\xDE\x7C\xBC", "xxx????x????xxx??xxxxxxxxxxxxxxxxxxxxx");
	ADD_SIGNATURE(DayZInfected, InfectedSkeleton,	0, ScanType::NORMAL, "\x48\x83\xB9\x00\x00\x00\x00\x00\x74\x4F\x8B\x89\x00\x00\x00\x00\x85\xC9\x74\x1E\x83\xE9\x01\x74\x0F\x83\xF9\x01\x75\x1F\x48\x8B\xCB\xE8\x00\x00\x00\x00\xEB\x15", "xxx?????xxxx????xxxxxxxxxxxxxxxxxx????xx");

/* DayZInfectedType Offsets */
	ADD_SIGNATURE(DayZInfectedType, ObjectName,		0, ScanType::SHORT,  "\x48\x8B\x58\x70\x48\x85\xDB\x74\x03\xF0\xFF\x03\x48\x8B\x44\x24\x00\xBE\x00\x00\x00\x00\x48\x89\x5C\x24\x00\xEB\x21\x48\x8D\x0D\x00\x00\x00\x00", "xxxxxxxxxxxxxxxx?x????xxxx?xxxxx????");
	ADD_SIGNATURE(DayZInfectedType, CategoryName,	0, ScanType::NORMAL, "\x48\x8B\x81\x00\x00\x00\x00\x48\x8B\xF9\x0F\xB6\xF2\x48\x8D\x48\x10\x48\x85\xC0\x75\x07\x48\x8D\x0D\x00\x00\x00\x00\x48\x8D\x15\x00\x00\x00\x00\x48\x89\x6C\x24\x00\xE8\x00\x00\x00\x00", "xxx????xxxxxxxxxxxxxxxxxx????xxx????xxxx?x????");
	

/* DayZPlayer Offsets */
	ADD_SIGNATURE(DayZPlayer, DayZPlayerType,		0,  ScanType::NORMAL,   "\x48\x8B\x91\x00\x00\x00\x00\x33\xC9\x48\x85\xD2\x48\x8D\x42\xD8\x48\x0F\x44\xC1\xC3", "xxx????xxxxxxxxxxxxxx");
	ADD_SIGNATURE(DayZPlayer, DayZPlayerTypeOffset, 12, ScanType::SHORT, "\x48\x8B\x91\x00\x00\x00\x00\x33\xC9\x48\x85\xD2\x48\x8D\x42\xD8\x48\x0F\x44\xC1\xC3", "xxx????xxxxxxxxxxxxxx");
	ADD_SIGNATURE(DayZPlayer, PlayerSkeleton,		0,	ScanType::NORMAL,	"\x48\x8B\x96\x00\x00\x00\x00\x48\x8D\x4C\x24\x00\x48\x83\xC2\x24\xE8\x00\x00\x00\x00\x48\x8B\xC8\xE8\x00\x00\x00\x00", "xxx????xxxx?xxxxx????xxxx????");

/* Skeleton Offsets */
	ADD_SIGNATURE(Skeleton, AnimClass1, 0,	ScanType::SHORT,		"\x48\x83\xC1\x70\xE9\x00\x00\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x48\x8B\x49\x28\x48\x85\xC9\x75\x03\x32\xC0", "xxxxx????xxxxxxxxxxxxxxxxxx");
	ADD_SIGNATURE(Skeleton, AnimClass2, 16, ScanType::TRACESHORT,	"\xE8\x00\x00\x00\x00\xEB\x12\x4C\x8B\xCB\x89\x7C\x24\x20\x4D\x8B\xC4\x49\x8B\xCE", "x????xxxxxxxxxxxxxxx");

/* AnimClass Offsets */
	ADD_SIGNATURE(AnimClass, MatrixArray, 0, ScanType::NORMAL,		"\x49\x8B\x9E\x00\x00\x00\x00\x4D\x8B\x86\x00\x00\x00\x00\x8B\xCE\x41\x8B\x84\x8E\x00\x00\x00\x00\x48\x8D\x3C\x49\x48\xC1\xE7\x04", "xxx????xxx????xxxxxx????xxxxxxxx");

}