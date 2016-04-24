#include <tuple>
#include <iostream>


// VWCEF is a typedef to a variable-width character encoding form
using VWCEF = /* whichever you want */;

// This array holds our code units
constexpr VWCEF::code_unit code_unit_sequence[] = { /* valid code unit sequence here */ };
// How many code units we have
constexpr auto sequence_length = sizeof(code_unit_sequence) / sizeof(*code_unit_sequence);

int main()
{
	const VWCEF::code_unit * p = code_unit_sequence;
	VWCEF::nonnegative_integer cp;
	do
	{
		VWCEF::sequence_length decoded;
		std::tie( cp , decoded ) = VWCEF::decode( p );
		p += decoded;
		std::cout << cp << '\n';
	}
	while ( p != code_unit_sequence+sequence_length );
	
	std::cout << '\n';
}