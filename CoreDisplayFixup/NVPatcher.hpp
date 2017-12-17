//
//  NVPatcher.hpp
//  NVPatcher (CoreDisplayFixup)
//
//  Copyright © 2017 Vanilla. All rights reserved.
//
//  This module is based on lvs1974's NvidiaGraphicsFixup.
//

#ifndef NVPatcher_hpp
#define NVPatcher_hpp

#include <Headers/kern_patcher.hpp>

struct KextPatch {
	KernelPatcher::LookupPatch patch;
	uint32_t minKernel;
	uint32_t maxKernel;
};

class NVPatcher {
	public:
		bool init();

	private:
		/**
		 *  Patch kext if needed and prepare other patches
		 *
		 *  @param patcher KernelPatcher instance
		 *  @param index   kinfo handle
		 *  @param address kinfo load address
		 *  @param size    kinfo memory size
		 */
		void processKext(KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size);
		
		/**
		 *  Apply kext patches for loaded kext index
		 *
		 *  @param patcher    KernelPatcher instance
		 *  @param index      kinfo index
		 *  @param patches    patch list
		 *  @param patchesNum patch number
		 */
		void applyPatches(KernelPatcher &patcher, size_t index, const KextPatch *patches, size_t patchesNum);
		
		/**
		 * Current progress mask
		 */
		struct ProcessingState {
			enum : uint32_t {
				NothingReady          = 0,
				NVGK100ReslPatched    = 1,
				NVGK100WebReslPatched = 2,
				NVGM100ReslPatched    = 4,
				NVGP100ReslPatched    = 8,
				EverythingDone = NVGK100ReslPatched | NVGK100WebReslPatched | NVGM100ReslPatched | NVGP100ReslPatched
			};
		};
		uint32_t progressState = ProcessingState::NothingReady;
};

#endif /* NVPatcher_hpp */
