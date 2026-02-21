#pragma once

// NOTE: This is meant to ensure that everything runs in 64 bit Windows only, nothing else. 
// It does not include platform specific code at all

// Ensure building on 64 bit Windows only

#ifndef _WIN64
	#error "Surreal Studio only builds on 64 bit Windows!"
#endif // _WIN64

#if defined(__APPLE__)
	#error "Surreal Studio cannot build on MacOS!"
#endif

#if defined(__linux__)
	#error "Surreal Studio cannot build on Linux!"
#endif