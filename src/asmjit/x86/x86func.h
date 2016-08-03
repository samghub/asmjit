// [AsmJit]
// Complete x86/x64 JIT and Remote Assembler for C++.
//
// [License]
// Zlib - See LICENSE.md file in the package.

// [Guard]
#ifndef _ASMJIT_X86_X86FUNC_H
#define _ASMJIT_X86_X86FUNC_H

#include "../build.h"
#if !defined(ASMJIT_DISABLE_COMPILER)

// [Dependencies]
#include "../base/func.h"
#include "../x86/x86operand.h"

// [Api-Begin]
#include "../apibegin.h"

namespace asmjit {

//! \addtogroup asmjit_x86
//! \{

// ============================================================================
// [asmjit::TypeId]
// ============================================================================

#if !defined(ASMJIT_DOCGEN)
ASMJIT_TYPE_ID(X86Mm, VirtType::kIdX86Mm);
ASMJIT_TYPE_ID(X86Xmm, VirtType::kIdX86Xmm);
ASMJIT_TYPE_ID(X86Ymm, VirtType::kIdX86Ymm);
ASMJIT_TYPE_ID(X86Zmm, VirtType::kIdX86Zmm);
#endif // !ASMJIT_DOCGEN

// ============================================================================
// [asmjit::X86FuncDecl]
// ============================================================================

//! X86 function, including calling convention, arguments and their
//! register indexes or stack positions.
struct X86FuncDecl : public FuncDecl {
  // --------------------------------------------------------------------------
  // [Construction / Destruction]
  // --------------------------------------------------------------------------

  //! Create a new `X86FuncDecl` instance.
  ASMJIT_INLINE X86FuncDecl() { reset(); }

  // --------------------------------------------------------------------------
  // [Accessors - X86]
  // --------------------------------------------------------------------------

  //! Get used registers mask for the given register class `rc`.
  //!
  //! NOTE: The result depends on the function calling convention AND the
  //! function prototype. Returned mask contains only registers actually used
  //! to pass function arguments.
  ASMJIT_INLINE uint32_t getUsed(uint32_t rc) const { return _used.get(rc); }

  //! Get passed registers mask for the given register class `rc`.
  //!
  //! NOTE: The result depends on the function calling convention used; the
  //! prototype of the function doesn't affect the mask returned.
  ASMJIT_INLINE uint32_t getPassed(uint32_t rc) const { return _passed.get(rc); }

  //! Get preserved registers mask for the given register class `rc`.
  //!
  //! NOTE: The result depends on the function calling convention used; the
  //! prototype of the function doesn't affect the mask returned.
  ASMJIT_INLINE uint32_t getPreserved(uint32_t rc) const { return _preserved.get(rc); }

  //! Get ther order of passed registers (GP).
  //!
  //! NOTE: The result depends on the function calling convention used; the
  //! prototype of the function doesn't affect the mask returned.
  ASMJIT_INLINE const uint8_t* getPassedOrderGp() const { return _passedOrderGp; }

  //! Get ther order of passed registers (XMM/YMM/ZMM).
  //!
  //! NOTE: The result depends on the function calling convention used; the
  //! prototype of the function doesn't affect the mask returned.
  ASMJIT_INLINE const uint8_t* getPassedOrderXyz() const { return _passedOrderXyz; }

  // --------------------------------------------------------------------------
  // [SetPrototype]
  // --------------------------------------------------------------------------

  //! Set function prototype.
  //!
  //! This will set function calling convention and setup arguments variables.
  //!
  //! NOTE: This function will allocate variables, it can be called only once.
  ASMJIT_API Error setPrototype(const FuncPrototype& p);

  // --------------------------------------------------------------------------
  // [Reset]
  // --------------------------------------------------------------------------

  ASMJIT_API void reset();

  // --------------------------------------------------------------------------
  // [Members]
  // --------------------------------------------------------------------------

  //! Used registers.
  X86RegMask _used;
  //! Passed registers (defined by the calling convention).
  X86RegMask _passed;
  //! Preserved registers (defined by the calling convention).
  X86RegMask _preserved;

  //! Order of registers used to pass GP function arguments.
  uint8_t _passedOrderGp[8];
  //! Order of registers used to pass XMM/YMM/ZMM function arguments.
  uint8_t _passedOrderXyz[8];
};

//! \}

} // asmjit namespace

// [Api-End]
#include "../apiend.h"

// [Guard]
#endif // !ASMJIT_DISABLE_COMPILER
#endif // _ASMJIT_X86_X86FUNC_H
