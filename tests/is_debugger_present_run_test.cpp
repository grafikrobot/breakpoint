#include <debugging.hpp>
#include <iostream>

int main()
{
	if (stdx::is_debugger_present())
	{
		std::cout << "Here be debuggers!\n";
	}
	else
	{
		std::cout << "These are not debuggers you are looking for.\n";
	}
}
