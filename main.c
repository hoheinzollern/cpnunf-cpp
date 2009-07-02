#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "netconv.h"
#include "unfold.h"
#include "output.h"

/*****************************************************************************/

void usage(char *myname)
{
	fprintf(stderr,
		"Unfolder -- unfolder for nets with read arcs\n\n"
		"Usage: unfolder -[lLd] <LLnetfile>\n"
		"\t-l outputs the net in ll_net format\n"
		"\t-L outputs the net in ll_net format with the extension of"
		"histories\n"
		"\t-d outputs the net in dot file format [default] \n\n"

	"Unfolder is a spin-off from Mole that works for nets with read arcs.\n"
	"The output is a dot-compatible graph of the result.\n\n"

	"Version 0.0.1 (14.06.2009)\n");

	exit(1);
}

/*****************************************************************************/

/**
 * Main function, calls all necessary function for unfolding the net
 * \param argc
 * \param argv 
 * \return the exitcode
 */
int main (int argc, char **argv)
{
	if (argc == 2 || argc == 3) {
		char    *llnet = argv[argc-1];
		char    *stoptr_name = NULL;
		net = read_pep_net(llnet);
		nc_static_checks(net,stoptr_name);

		unfold();

		if (argc == 3) {
			if (strcmp(argv[1], "-l")==0)
				write_ll_net(unf, cutoff_list, UNF_FALSE);
			else if (strcmp(argv[1], "-L")==0)
				write_ll_net(unf, cutoff_list, UNF_TRUE);
			else if (strcmp(argv[1], "-d")==0)
				write_dot_output(unf, cutoff_list);
		} else
			write_dot_output(unf, cutoff_list);
	} else
		usage(argv[0]);

	return exitcode;
}
