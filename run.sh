# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: othello <othello@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/10 18:24:25 by ohengelm          #+#    #+#              #
#    Updated: 2026/07/10 18:41:34 by othello          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# solvable="-s "
# unsolvable="-u "
# iterations="-i 10000 "
size=5

printSyntax()
{
	echo "usage: run.sh [-h] [-s] [-u] [-i ITERATIONS] [size]"
}

printHelp()
{
	cat << EOF

positional arguments:
  size                  Size of the puzzle's side. Must be >3.

options:
  -h, --help            show this help message and exit
  -s, --solvable        Forces generation of a solvable puzzle. Overrides -u.
  -u, --unsolvable      Forces generation of an unsolvable puzzle
  -i ITERATIONS, --iterations ITERATIONS
                        Number of passes
EOF
}

while [[ $# -gt 0 ]]; do
	case "$1" in
		-h|--help)
			printSyntax
			printHelp
			exit 0;
			;;
		-s|--solvable)
			solvable="$1 "
			;;
		-u|--unsolvable)
			unsolvable="$1 "
			;;
		-i*|--iterations*)
			if [[ "$1" == "-i" || "$1" == "--iterations" ]]; then
				[[ -n "$2" ]] || { echo "Error: missing argument." >&2; exit 1; }
				value="$2"
				shift
			else
				value="${1#-i}"
				value="${value#--iterations=}"
			fi

			[[ "$value" =~ ^[0-9]+$ ]] || {
				echo "Error: iterations must be a number." >&2
				exit 1
			}
			iterations="-i $value "
			;;
		*)
			if [[ "$1" =~ ^[0-9]+$ ]]; then
				size="$1"
			else
				printSyntax
				echo "error: unrecognized arguments: $1" >&2;
				exit 1
			fi
			;;
	esac
	shift
done

if [ -n "${solvable}" ]; then
	unset unsolvable;
fi
if [ -z "${size}" ]; then
	echo "run.sh: error: the following arguments are required: size" >&2
	exit 1
fi

clear
make BUILD=debug || exit 1
python3 assets/npuzzle-gen.py ${solvable}${unsolvable}${iterations}${size}
