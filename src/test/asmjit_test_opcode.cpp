// [AsmJit]
// Complete x86/x64 JIT and Remote Assembler for C++.
//
// [License]
// Zlib - See LICENSE.md file in the package.

// This file is used to test opcodes generated by AsmJit. Output can be
// disassembled in your IDE or by your favorite disassembler. Instructions
// are grouped by category and then sorted alphabetically.

// [Dependencies]
#include "../asmjit/asmjit.h"
#include "./asmjit_test_opcode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace asmjit;

struct OpcodeDumpInfo {
  uint32_t arch;
  bool useRex1;
  bool useRex2;
};

static const char* archIdToString(uint32_t archId) {
  switch (archId) {
    case Arch::kTypeNone : return "None";
    case Arch::kTypeX86  : return "X86";
    case Arch::kTypeX64  : return "X64";
    case Arch::kTypeArm32: return "ARM32";
    case Arch::kTypeArm64: return "ARM64";

    default:
      return "<unknown>";
  }
}

struct TestErrorHandler : public ErrorHandler {
  virtual bool handleError(Error err, const char* message, CodeEmitter* origin) {
    printf("ERROR 0x%0.8X: %s\n", err, message);
    return true;
  }
};

typedef void (*VoidFunc)(void);

int main(int argc, char* argv[]) {
  TestErrorHandler eh;
  FileLogger logger(stdout);
  logger.addOptions(Logger::kOptionBinaryForm);

  OpcodeDumpInfo infoList[] = {
    { Arch::kTypeX86, false, false },
    { Arch::kTypeX64, false, false },
    { Arch::kTypeX64, false, true  },
    { Arch::kTypeX64, true , false },
    { Arch::kTypeX64, true , true  }
  };

  for (int i = 0; i < ASMJIT_ARRAY_SIZE(infoList); i++) {
    const OpcodeDumpInfo& info = infoList[i];

    printf("Opcodes [ARCH=%s REX1=%s REX2=%s]\n",
      archIdToString(info.arch),
      info.useRex1 ? "true" : "false",
      info.useRex2 ? "true" : "false");

    CodeHolder code(CodeInfo(info.arch));
    code.setLogger(&logger);
    code.setErrorHandler(&eh);

    X86Assembler a(&code);
    asmtest::generateOpcodes(a, info.useRex1, info.useRex2);

    // If this is the host architecture the code generated can be executed
    // for debugging purposes (the first instruction is ret anyway).
    if (code.getArchType() == Arch::kTypeHost) {
      JitRuntime runtime;
      VoidFunc p;
      Error err = runtime.add((void**)&p, &code);
      if (err == kErrorOk) p();
    }
  }

  return 0;
}
