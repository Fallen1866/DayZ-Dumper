#pragma once

/* Windows & Standard Libraries */
#include <Windows.h>
#include <dwmapi.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>
#include <string>
#include <format>
#include <array>
#include <map>
#include <unordered_map>
#include <TlHelp32.h>
#include <intrin.h>

/* Resource Headers */
#include "Target.h"
#include "Offsets.h"
#include "Signatures.h"

/* Utility Headers */
#include "Mem.h"
#include "Address.h"
#include "Module.h"


/* Module Headers */
#include "Updater.h"

#include "Boot.h"

inline Module g_Game = Module();