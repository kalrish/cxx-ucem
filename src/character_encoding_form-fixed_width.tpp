#include <cassert>


namespace Unicode_CharacterEncodingModel {
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth,
	 std::size_t SequenceLength
	>
	inline typename CharacterEncodingForm_FixedWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 SequenceLength
	>::nonnegative_integer
	CharacterEncodingForm_FixedWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 SequenceLength
	>::decode
	(
	 const typename CharacterEncodingForm_FixedWidth::code_unit * read_cursor
	)
	noexcept( noexcept( Derived::_decode(read_cursor) ) )
	{
		return Derived::_decode(read_cursor);
	}
	
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth,
	 std::size_t SequenceLength
	>
	inline typename CharacterEncodingForm_FixedWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 SequenceLength
	>::nonnegative_integer
	CharacterEncodingForm_FixedWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 SequenceLength
	>::decode_assuming_validity
	(
	 const typename CharacterEncodingForm_FixedWidth::code_unit * read_cursor
	)
	noexcept
	{
		return Derived::_decode_assuming_validity(read_cursor);
	}
	
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth,
	 std::size_t SequenceLength
	>
	constexpr typename CharacterEncodingForm_FixedWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 SequenceLength
	>::nonnegative_integer
	CharacterEncodingForm_FixedWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 SequenceLength
	>::decode_constexpry
	(
	 const typename CharacterEncodingForm_FixedWidth::code_unit * read_cursor
	)
	noexcept
	{
		return Derived::_decode_constexpry(read_cursor);
	}
	
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth,
	 std::size_t SequenceLength
	>
	inline void
	CharacterEncodingForm_FixedWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 SequenceLength
	>::encode
	(
	 typename CharacterEncodingForm_FixedWidth::nonnegative_integer i,
	 typename CharacterEncodingForm_FixedWidth::code_unit * out
	)
	noexcept
	{
		assert( CharacterEncodingForm_FixedWidth::maps(i) );
		
		Derived::_encode( i , out );
	}
	
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth,
	 std::size_t SequenceLength
	>
	constexpr void
	CharacterEncodingForm_FixedWidth<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth,
	 SequenceLength
	>::encode_constexpry
	(
	 typename CharacterEncodingForm_FixedWidth::nonnegative_integer i,
	 typename CharacterEncodingForm_FixedWidth::code_unit * out
	)
	noexcept
	{
		Derived::_encode_constexpry( i , out );
	}
}