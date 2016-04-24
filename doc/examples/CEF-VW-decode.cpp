#include <tuple>

template<
 class VWCEF /* a variable-width character encoding form */
>
void decode_a_single_nonnegative_integer
(
 const typename VWCEF::code_unit * code_units /* pointing to a series of code units */
)
{
	typename VWCEF::nonnegative_integer nni;
	typename VWCEF::sequence_length how_many_code_units_were_decoded;

	std::tie( nni , how_many_code_units_were_decoded ) = VWCEF::decode( code_units );
}