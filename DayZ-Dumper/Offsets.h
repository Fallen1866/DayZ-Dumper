#pragma once

#define ADD_OFFSET(klass, name, def) namespace klass { inline INT64 name = def; }

namespace Offsets {

/* ModuleBase Offsets */
	ADD_OFFSET(ModuleBase, World, 0x413B418);	

/* World Offsets */
	ADD_OFFSET(World, NearEntList, 0x0EB0);
	ADD_OFFSET(World, FarEntList, 0x1000);
	ADD_OFFSET(World, LocalPlayer, 0x28D8);
	ADD_OFFSET(World, LocalOffset, 0x00A8);
	ADD_OFFSET(World, Camera, 0x01B8);

/* DayZInfected Offsets */
	ADD_OFFSET(DayZInfected, DayZInfectedType, 0x0168);
	ADD_OFFSET(DayZInfected, EntityVisualState, 0x01C0);
	ADD_OFFSET(DayZInfected, InfectedSkeleton, 0x0698);

	
/* DayZPlayer Offsets */
	ADD_OFFSET(DayZPlayer, DayZPlayerType,			0x0000);
	ADD_OFFSET(DayZPlayer, DayZPlayerTypeOffset,	0x0000);
	ADD_OFFSET(DayZPlayer, PlayerSkeleton,			0x0830);
	
/* DayZInfectedType Offsets */
	ADD_OFFSET(DayZInfectedType, ObjectName,	0x0070);	 
	ADD_OFFSET(DayZInfectedType, CategoryName,	0x0000);	 
	ADD_OFFSET(DayZInfectedType, FullName,		0x0088);
	
/* Skeleton Offsets */
	ADD_OFFSET(Skeleton, AnimClass1, 0x70);
	ADD_OFFSET(Skeleton, AnimClass2, 0x28);

	
/* AnimClass Offsets */
	ADD_OFFSET(AnimClass, MatrixArray, 0x0BF0);
	ADD_OFFSET(AnimClass, MatrixEntry, 0x0054);

}