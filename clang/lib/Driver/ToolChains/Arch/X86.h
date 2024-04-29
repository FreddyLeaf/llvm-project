//===--- X86.h - X86-specific Tool Helpers ----------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_ARCH_X86_H
#define LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_ARCH_X86_H

#include "clang/Driver/Driver.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Option.h"
#include "llvm/TargetParser/Triple.h"
#include <string>
#include <vector>

namespace clang {
namespace driver {
namespace tools {
namespace x86 {

std::string getX86TargetCPU(const Driver &D, const llvm::opt::ArgList &Args,
                            const llvm::Triple &Triple);

void getX86TargetFeatures(const Driver &D, const llvm::Triple &Triple,
                          const llvm::opt::ArgList &Args,
                          std::vector<llvm::StringRef> &Features);

} // end namespace x86
} // end namespace target
// namespace toolchains {
// // Common Toolchain base class for X86.
// class LLVM_LIBRARY_VISIBILITY X86ToolChain : public Generic_ELF {
// public:
//     X86ToolChain(const Driver &D, const llvm::Triple &Triple,
//                          const llvm::opt::ArgList &Args, StringRef Platform,
//                          const char *EnvVar);
//
//     llvm::DenormalMode getDefaultDenormalModeForType(
//             const llvm::opt::ArgList &DriverArgs, const JobAction &JA,
//             const llvm::fltSemantics *FPType) const override {
//         // DAZ and FTZ are on by default for bf16.
//         if (FPType == &llvm::APFloat::BFloat())
//             return llvm::DenormalMode::getPreserveSign();
//         return llvm::DenormalMode::getIEEE();
//     }
// };
// } // end namespace toolchains
} // end namespace driver
} // end namespace clang

#endif // LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_ARCH_X86_H
