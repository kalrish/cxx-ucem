#include <cassert>


namespace Unicode_CharacterEncodingModel {
	template<
	 class Derived,
	 unsigned long long Min,
	 unsigned long long Max,
	 std::size_t CodeUnitWidth
	>
	inline bool
	CharacterEncodingForm<
	 Derived,
	 Min,
	 Max,
	 CodeUnitWidth
	>::maps
	(
	 nonnegative_integer i
	)
	noexcept
	{
		return ((i >= smallest_mapped_nonnegative_integer) && (i <= greatest_mapped_nonnegative_integer)) ? Derived::_maps(i) : false;
	}
}