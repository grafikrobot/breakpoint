#include <debugging.hpp>
#include <cstdio>

int main()
{
	stdx::breakpoint();
	std::puts("The other side");
}
