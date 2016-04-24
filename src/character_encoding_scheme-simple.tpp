namespace Unicode_CharacterEncodingModel {
	template<
	 class Derived,
	 std::size_t CodeUnitWidth
	>
	inline typename CharacterEncodingScheme_Simple<
	 Derived,
	 CodeUnitWidth
	>::code_unit
	CharacterEncodingScheme_Simple<
	 Derived,
	 CodeUnitWidth
	>::deserialize
	(
	 const unsigned char * read_cursor
	)
	noexcept
	{
		return Derived::_deserialize( read_cursor );
	}
	
	template<
	 class Derived,
	 std::size_t CodeUnitWidth
	>
	constexpr typename CharacterEncodingScheme_Simple<
	 Derived,
	 CodeUnitWidth
	>::code_unit
	CharacterEncodingScheme_Simple<
	 Derived,
	 CodeUnitWidth
	>::deserialize_constexpry
	(
	 const unsigned char * read_cursor
	)
	noexcept
	{
		return Derived::_deserialize_constexpry( read_cursor );
	}
	
	template<
	 class Derived,
	 std::size_t CodeUnitWidth
	>
	inline void
	CharacterEncodingScheme_Simple<
	 Derived,
	 CodeUnitWidth
	>::serialize
	(
	 typename CharacterEncodingScheme_Simple::code_unit cu,
	 unsigned char * out
	)
	noexcept
	{
		Derived::_serialize( cu , out );
	}
	
	template<
	 class Derived,
	 std::size_t CodeUnitWidth
	>
	constexpr void
	CharacterEncodingScheme_Simple<
	 Derived,
	 CodeUnitWidth
	>::serialize_constexpry
	(
	 typename CharacterEncodingScheme_Simple::code_unit cu,
	 unsigned char * out
	)
	noexcept
	{
		Derived::_serialize_constexpry( cu , out );
	}
}