#ifndef IXM_BREAKPOINT_HPP
#define IXM_BREAKPOINT_HPP

#include <debugging/detail/psnip_debug_trap.h>

namespace stdx {

enum class debugger_query {
	saved,
	immediate
};

bool is_debugger_present(debugger_query q = debugger_query::saved) noexcept;

[[gnu::flatten]] inline void breakpoint() noexcept
{
	psnip_trap();
}


[[gnu::flatten]] inline void breakpoint_if_debugging() noexcept
{
	if (is_debugger_present()) breakpoint();
}

} // namespace stdx

#endif
