#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) \
	|| defined(__TOS_WIN__) || defined(__WINDOWS__)

#	include <debugging.hpp>

#	define WIN32_LEAN_AND_MEAN
#	define NOMINMAX
#	include <Windows.h>

namespace stdx {

namespace
{
	struct debugger_info
	{
		enum class is_present_state { unknown = 0, present, absent };

		std::atomic<is_present_state> is_present;

		debugger_info()
		{
			is_present.store(query_debugger_present());
		}

		static is_present_state query_debugger_present() noexcept
		{
			return ::IsDebuggerPresent()
				? is_present_state::present
				: is_present_state::absent;
		}
	};

	static debugger_info cached_debugger_info;
}

bool is_debugger_present(debugger_query q) noexcept
{
	if (q == debugger_query::immediate)
		cached_debugger_info.is_present.store(
			debugger_info::query_debugger_present());
	return cached_debugger_info.is_present.load()
		== debugger_info::is_present_state::present;
}

} // namespace stdx

#endif
