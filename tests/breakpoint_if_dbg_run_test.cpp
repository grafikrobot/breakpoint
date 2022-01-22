#include <debugging.hpp>
#include <cstdio>

int main()
{
	stdx::breakpoint_if_debugging();
	std::puts("The other side");
}
