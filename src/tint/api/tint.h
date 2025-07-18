// Copyright 2023 The Dawn & Tint Authors
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef SRC_TINT_API_TINT_H_
#define SRC_TINT_API_TINT_H_

#include <cstdint>
#include <string>
#include <vector>

#if TINT_BUILD_SPV_READER && TINT_BUILD_WGSL_WRITER
#include "src/tint/lang/wgsl/writer/ir_to_program/program_options.h"
#include "src/tint/utils/result.h"
#endif  // TINT_BUILD_SPV_READER && TINT_BUILD_WGSL_WRITER

namespace tint {

/// Initialize initializes the Tint library. Call before using the Tint API.
void Initialize();

/// Shutdown uninitializes the Tint library. Call after using the Tint API.
void Shutdown();

#if TINT_BUILD_SPV_READER && TINT_BUILD_WGSL_WRITER
/// Convert a SPIR-V binary to a WGSL shader module string.
/// @param spirv the SPIR-V binary
/// @param wgsl_options the options to use for generating WGSL
/// @returns the WGSL module, or a failure
tint::Result<std::string> SpirvToWgsl(const std::vector<uint32_t>& spirv,
                                      const wgsl::writer::ProgramOptions& wgsl_options = {});
#endif  // TINT_BUILD_SPV_READER && TINT_BUILD_WGSL_WRITER

}  // namespace tint

#endif  // SRC_TINT_API_TINT_H_
