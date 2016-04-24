# Guards a C++ header
# 
# The inclusion guard macro name is computed from the output name.
# A #line directive is added so that compiler diagnostics are issued as for
#    the original file.
# 
# Arguments:
#  #1  input path
#  #2  output path


declare -r INPUT="$1" OUTPUT="$2"

INCLUSION_GUARD="UNICODE_CHARACTER_ENCODING_MODEL_INCLUSION_GUARD_${OUTPUT}"
# Replace all dots ('.') with underscores ('_')
INCLUSION_GUARD="${INCLUSION_GUARD//./_}"
# Replace all hyphens ('-') with underscores ('_')
INCLUSION_GUARD="${INCLUSION_GUARD//-/_}"
# Replace all forward slashes ('/') with underscores ('_')
INCLUSION_GUARD="${INCLUSION_GUARD////_}"

{
	echo "#ifndef ${INCLUSION_GUARD}
#define ${INCLUSION_GUARD}


#if __cplusplus == 201402L
#line 1 \"${INPUT}\""
	cat -- "$INPUT"
	echo -n '


#else
#error cxx-ucem requires C++14
#endif
#endif'
} >"$OUTPUT"