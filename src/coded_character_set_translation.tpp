#include <cassert>


namespace Unicode_CharacterEncodingModel {
	namespace detail {
		template<
		 class CodedCharacterSet1,
		 class CodedCharacterSet2
		>
		inline typename CodedCharacterSet2::nonnegative_integer
		code_point_translator
		(
		 const typename CodedCharacterSet1::nonnegative_integer i
		)
		{
			return i;
		}
	}
	
	template<
	 class CodedCharacterSet1,
	 class CodedCharacterSet2
	>
	inline typename CodedCharacterSet2::nonnegative_integer
	translate_code_point
	(
	 typename CodedCharacterSet1::nonnegative_integer i
	)
	noexcept( noexcept( detail::code_point_translator<CodedCharacterSet1,CodedCharacterSet2>(i) ) )
	{
		assert( CodedCharacterSet1::maps(i) );
		
		const auto translation = detail::code_point_translator<CodedCharacterSet1,CodedCharacterSet2>(i);
		
		assert( CodedCharacterSet2::maps(translation) );
		
		return translation;
	}
}