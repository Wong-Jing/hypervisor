/// @copyright
/// Copyright (C) 2020 Assured Information Security, Inc.
///
/// @copyright
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// @copyright
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// @copyright
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.

#ifndef FAST_FAIL_HPP
#define FAST_FAIL_HPP

#include <return_to_vmexit_loop.hpp>

#include <bsl/debug.hpp>

namespace mk
{
    /// <!-- description -->
    ///   @brief Provides the main entry point for fast fails that occur
    ///     after a successful launch of the hypervisor. Once this occurs,
    ///     the fast fail path either has to be handled by an extension,
    ///     or a halt() will occur.
    ///
    /// <!-- inputs/outputs -->
    ///   @tparam TLS_CONCEPT defines the type of TLS block to use
    ///   @tparam EXT_CONCEPT defines the type of ext_t to use
    ///   @param tls the current TLS block
    ///   @param ext_fail the ext_t to handle the VMExit
    ///
    template<typename TLS_CONCEPT, typename EXT_CONCEPT>
    constexpr void
    fast_fail(TLS_CONCEPT &tls, EXT_CONCEPT *const ext_fail) noexcept
    {
        bsl::print() << bsl::endl           // --
                     << bsl::bold_red       // --
                     << "fast failing:"     // --
                     << bsl::reset_color    // --
                     << bsl::endl;          // --

        if (nullptr != ext_fail) {
            if (!ext_fail->fail(tls)) {
                bsl::print<bsl::V>() << bsl::here();
                return;
            }

            return_to_vmexit_loop();
        }
    }
}

#endif
