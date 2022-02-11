#if defined(linux) || defined(__linux) || defined(__linux__) \
	|| defined(__gnu_linux__)

#	include <debugging.hpp>

#	include <atomic>
#	include <fstream>
#	include <string>

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
			std::ifstream proc_self_status_f("/proc/self/status");
			if (!proc_self_status_f) return is_present_state::absent;
			std::string buffer(256, '\0');
			proc_self_status_f.read(&buffer[0], 256);
			auto index = buffer.find("TracerPid:\t");
			if (index == buffer.npos) return is_present_state::absent;
			return buffer[index + 11] != '0'
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
