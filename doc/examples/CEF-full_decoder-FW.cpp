#include <iostream>


// FWCEF is a typedef to a fixed-width character encoding form
using FWCEF = /* the one you choose */;

// This array holds our code units
constexpr FWCEF::code_unit code_unit_sequence[] = { /* your code units here */ };
// How many code units we have
constexpr auto sequence_length = sizeof(code_unit_sequence) / sizeof(*code_unit_sequence);

static_assert( sequence_length % FWCEF::sequence_length == 0,
	"the length of the code unit sequence must be a multiple of the length of code unit sequences mapped by the fixed-width character encoding form" );

int main()
{
	for ( decltype(sizeof(code_unit_sequence)) i = 0 ; i < sequence_length ; ++i )
	{
		std::cout << FWCEF::decode( &code_unit_sequence[i] ) << ' ';
	}
	
	std::cout << '\n';
}