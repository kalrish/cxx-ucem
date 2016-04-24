declare -A -r default_installation_dir_variables=(
	[prefix]='/usr/local'
	[exec_prefix]='${installation_dir_variables[prefix]}'
	[includedir]='${installation_dir_variables[prefix]}/include'
	[libdir]='${installation_dir_variables[exec_prefix]}/lib'
)

declare -A installation_dir_variables not_explicitly_set_installation_dir_variables


for argument in "$@" ; do
	if [[ "$argument" =~ ^([^= ]+)=(.+)$ ]] ; then
		variable="${BASH_REMATCH[1]}"
		value="${BASH_REMATCH[2]}"
		
		if [[ -n "${default_installation_dir_variables[$variable]}" ]] ; then
			installation_dir_variables[$variable]="$value"
		elif [[ $variable == 'DESTDIR' ]] ; then
			DESTDIR="$value"
		else
			errors=1
			echo "$0: error: '${variable}' is not a supported installation directory variable"
		fi
	else
		errors=1
		invalid_arguments=1
		echo "$0: error: invalid argument '${argument}'"
	fi
done

if [[ -z $errors ]] ; then
	if [[ -t 1 ]] && type 'tput' &>/dev/null ; then
		# Raw
		declare -r tput_sgr0="$(tput sgr0)"
		declare -r tput_bold="$(tput bold)"
		declare -r tput_setaf_4="$(tput setaf 4)"
		declare -r tput_setaf_6="$(tput setaf 6)"
		declare -r tput_setab_6="$(tput setab 6)"
		
		# Conceptual
		declare -r style_variable="${tput_bold}"
		declare -r style_value="${tput_setaf_6}"
		declare -r style_DESTDIR="${tput_bold}"
		declare -r style_DESTDIR_value="${tput_setab_6}"
		declare -r style_command="${tput_setaf_4}"
	fi
	
	function print_n_run()
	{
		echo "${style_command}${tput_bold}$@${tput_sgr0}"
		$@
	}
	
	for variable in "${!default_installation_dir_variables[@]}" ; do
		if [[ -z "${installation_dir_variables[$variable]}" ]] ; then
			not_explicitly_set_installation_dir_variables[$variable]=1
			installation_dir_variables[$variable]="${default_installation_dir_variables[$variable]}"
		fi
	done
	
	for variable in "${!not_explicitly_set_installation_dir_variables[@]}" ; do
		while [[ "${installation_dir_variables[$variable]}" =~ \$\{installation_dir_variables\[[^\]]+]} ]] ; do
			installation_dir_variables[$variable]="$(eval echo "${installation_dir_variables[$variable]}")"
		done
	done
	
	for variable in "${!installation_dir_variables[@]}" ; do
		echo "${style_variable}${variable}${tput_sgr0}=${style_value}${installation_dir_variables[${variable}]}${tput_sgr0}"
	done
	echo
	echo "${style_DESTDIR}DESTDIR${tput_sgr0}=${style_DESTDIR_value}${DESTDIR}${tput_sgr0}"
	echo
	
	print_n_run install -v -d -- {"${DESTDIR}${installation_dir_variables[includedir]}","${DESTDIR}${installation_dir_variables[libdir]}"}/unicode-character-encoding-model/{coded_character_sets,coded_character_set_translators,character_encoding_forms,character_encoding_schemes}
	print_n_run install -v -t "${DESTDIR}${installation_dir_variables[includedir]}/unicode-character-encoding-model" -- src/*.{hpp,tpp}
	
	exit 0
else
	if [[ -n $invalid_arguments ]] ; then
		echo "$0: valid arguments are of the form \"variable=value\""
	fi
	
	exit 1
fi