#ifndef VERSION_H
#define VERSION_H

#define _WSTR(x) _WSTR_(x)
#define _WSTR_(x) L ## #x
#define _STR(x) _STR_(x)
#define _STR_(x) #x

#pragma region Release build version numbering

// Indicates project maturity and completeness
#define VERSION_MAJOR 0

// Indicates major changes and significant additions, like new logics
#define VERSION_MINOR 3

// Indicates minor changes, like vanilla bugfixes, unhardcodings or hacks
#define VERSION_REVISION 0

// Indicates Phobos-related bugfixes only
#define VERSION_PATCH 1

#pragma endregion

// Build number. Incremented on each released build.
#define BUILD_NUMBER 44

// Nightly defines GIT_COMMIT and GIT_BRANCH in GH Actions

#ifdef IS_RELEASE_VER // Release build metadata
	#define SAVEGAME_ID ((VERSION_MAJOR << 24) | (VERSION_MINOR << 16) | (VERSION_REVISION << 8) | VERSION_PATCH)
	#define FILE_DESCRIPTION "Phobos, Ares-compatible YR engine extension (Merged Starkku PR's)"
	#define FILE_VERSION_STR _STR(VERSION_MAJOR) "." _STR(VERSION_MINOR) "." _STR(VERSION_REVISION) "." _STR(VERSION_PATCH)
	#define FILE_VERSION VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION, VERSION_PATCH
	#define PRODUCT_VERSION "Release Build " FILE_VERSION_STR " (Merged Starkku PR's)"
#elif defined(GIT_COMMIT) // Nightly devbuild metadata
	#define STR_GIT_COMMIT _STR(GIT_COMMIT)
	#define STR_GIT_BRANCH _STR(GIT_BRANCH)

	#define SAVEGAME_ID ((BUILD_NUMBER << 24) | (BUILD_NUMBER << 12) | (BUILD_NUMBER))
	#define FILE_DESCRIPTION "Unstable nightly devbuild of Phobos engine extension (Merged Starkku PR's)"
	#define FILE_VERSION_STR "Commit " STR_GIT_COMMIT " (Merged Starkku PR's)"
	#define FILE_VERSION 0
	#define PRODUCT_VERSION "Nightly Build " STR_GIT_COMMIT " @ " STR_GIT_BRANCH " (Merged Starkku PR's)"
#else // Regular devbuild metadata
	#define SAVEGAME_ID ((BUILD_NUMBER << 24) | (BUILD_NUMBER << 12) | (BUILD_NUMBER))
	#define FILE_DESCRIPTION "Development build of Phobos engine extension (Merged Starkku PR's)"
	#define FILE_VERSION_STR "Build # (Merged Starkku PR's)" _STR(BUILD_NUMBER)
	#define FILE_VERSION 0,0,0,BUILD_NUMBER
	#define PRODUCT_VERSION "Development Build #" _STR(BUILD_NUMBER) " (Merged Starkku PR's)"
#endif

#endif // VERSION_H
