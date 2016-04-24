namespace Unicode_CharacterEncodingModel {
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max
	>
	inline bool
	CodedCharacterSet<
	 Derived,
	 Min,
	 Max
	>::maps
	(
	 nonnegative_integer i
	)
	noexcept
	{
		return ((i >= smallest_code_point) && (i <= greatest_code_point)) ? Derived::_maps(i) : false;
	}
}