#include <cassert>


namespace Unicode_CharacterEncodingModel {
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth,
	 std::size_t MinSequenceLength,
	 std::size_t MaxSequenceLength
	>
	inline std::tuple<
	 typename CharacterEncodingForm_VariableWidth<
	  Derived,
	  Min,
	  Max,
	  CodeUnitWidth,
	  MinSequenceLength,
	  MaxSequenceLength
	 >::nonnegative_integer,
	 typename CharacterEncodingForm_VariableWidth<
	  Derived,
	  Min,
	  Max,
	  CodeUnitWidth,
	  MinSequenceLength,
	  MaxSequenceLength
	 >::sequence_length
	>
	CharacterEncodingForm_VariableWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 MinSequenceLength,
	 MaxSequenceLength
	>::decode
	(
	 const typename CharacterEncodingForm_VariableWidth::code_unit * read_cursor
	)
	noexcept( noexcept( Derived::_decode(read_cursor) ) )
	{
		return Derived::_decode( read_cursor );
	}
	
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth,
	 std::size_t MinSequenceLength,
	 std::size_t MaxSequenceLength
	>
	inline std::tuple<
	 typename CharacterEncodingForm_VariableWidth<
	  Derived,
	  Min,
	  Max,
	  CodeUnitWidth,
	  MinSequenceLength,
	  MaxSequenceLength
	 >::nonnegative_integer,
	 typename CharacterEncodingForm_VariableWidth<
	  Derived,
	  Min,
	  Max,
	  CodeUnitWidth,
	  MinSequenceLength,
	  MaxSequenceLength
	 >::sequence_length
	>
	CharacterEncodingForm_VariableWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 MinSequenceLength,
	 MaxSequenceLength
	>::decode_assuming_validity
	(
	 const typename CharacterEncodingForm_VariableWidth::code_unit * read_cursor
	)
	noexcept
	{
		return Derived::_decode_assuming_validity( read_cursor );
	}
	
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth,
	 std::size_t MinSequenceLength,
	 std::size_t MaxSequenceLength
	>
	constexpr std::tuple<
	 typename CharacterEncodingForm_VariableWidth<
	  Derived,
	  Min,
	  Max,
	  CodeUnitWidth,
	  MinSequenceLength,
	  MaxSequenceLength
	 >::nonnegative_integer,
	 typename CharacterEncodingForm_VariableWidth<
	  Derived,
	  Min,
	  Max,
	  CodeUnitWidth,
	  MinSequenceLength,
	  MaxSequenceLength
	 >::sequence_length
	>
	CharacterEncodingForm_VariableWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 MinSequenceLength,
	 MaxSequenceLength
	>::decode_constexpry
	(
	 const typename CharacterEncodingForm_VariableWidth::code_unit * read_cursor
	)
	noexcept
	{
		return Derived::_decode_constexpry( read_cursor );
	}
	
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth,
	 std::size_t MinSequenceLength,
	 std::size_t MaxSequenceLength
	>
	inline std::tuple<
	 typename CharacterEncodingForm_VariableWidth<
	  Derived,
	  Min,
	  Max,
	  CodeUnitWidth,
	  MinSequenceLength,
	  MaxSequenceLength
	 >::nonnegative_integer,
	 typename CharacterEncodingForm_VariableWidth<
	  Derived,
	  Min,
	  Max,
	  CodeUnitWidth,
	  MinSequenceLength,
	  MaxSequenceLength
	 >::sequence_length
	>
	CharacterEncodingForm_VariableWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 MinSequenceLength,
	 MaxSequenceLength
	>::decode
	(
	 const typename CharacterEncodingForm_VariableWidth::code_unit * read_cursor,
	 sequence_length code_units_left
	)
	{
		assert( code_units_left > 0 );
		
		return Derived::_decode( read_cursor , code_units_left );
	}
	
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth,
	 std::size_t MinSequenceLength,
	 std::size_t MaxSequenceLength
	>
	inline typename CharacterEncodingForm_VariableWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 MinSequenceLength,
	 MaxSequenceLength
	>::sequence_length
	CharacterEncodingForm_VariableWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 MinSequenceLength,
	 MaxSequenceLength
	>::encoded_length
	(
	 typename CharacterEncodingForm_VariableWidth::nonnegative_integer i
	)
	noexcept
	{
		assert( CharacterEncodingForm_VariableWidth::maps(i) );
		
		return Derived::_encoded_length(i);
	}
	
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth,
	 std::size_t MinSequenceLength,
	 std::size_t MaxSequenceLength
	>
	constexpr typename CharacterEncodingForm_VariableWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 MinSequenceLength,
	 MaxSequenceLength
	>::sequence_length
	CharacterEncodingForm_VariableWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 MinSequenceLength,
	 MaxSequenceLength
	>::encoded_length_constexpry
	(
	 typename CharacterEncodingForm_VariableWidth::nonnegative_integer i
	)
	noexcept
	{
		return Derived::_encoded_length_constexpry(i);
	}
	
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth,
	 std::size_t MinSequenceLength,
	 std::size_t MaxSequenceLength
	>
	inline typename CharacterEncodingForm_VariableWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 MinSequenceLength,
	 MaxSequenceLength
	>::sequence_length
	CharacterEncodingForm_VariableWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 MinSequenceLength,
	 MaxSequenceLength
	>::encode
	(
	 typename CharacterEncodingForm_VariableWidth::nonnegative_integer i,
	 typename CharacterEncodingForm_VariableWidth::code_unit * out
	)
	noexcept
	{
		assert( CharacterEncodingForm_VariableWidth::maps(i) );
		
		return Derived::_encode( i , out );
	}
	
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth,
	 std::size_t MinSequenceLength,
	 std::size_t MaxSequenceLength
	>
	constexpr typename CharacterEncodingForm_VariableWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 MinSequenceLength,
	 MaxSequenceLength
	>::sequence_length
	CharacterEncodingForm_VariableWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 MinSequenceLength,
	 MaxSequenceLength
	>::encode_constexpry
	(
	 typename CharacterEncodingForm_VariableWidth::nonnegative_integer i,
	 typename CharacterEncodingForm_VariableWidth::code_unit * out
	)
	noexcept
	{
		return Derived::_encode_constexpry( i , out );
	}
}