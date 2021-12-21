#ifndef IXM_BREAKPOINT_HPP
#define IXM_BREAKPOINT_HPP

#include <debugging/detail/psnip_debug_trap.h>

namespace stdx {

bool is_debugger_present() noexcept;

[[gnu::flatten]] void breakpoint()
{
	if (is_debugger_present()) psnip_trap();
}

} // namespace stdx

#endif
