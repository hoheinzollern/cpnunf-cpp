#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "netconv.h"
#include "unfold.h"

/*****************************************************************************/

void usage(char *myname)
{
	fprintf(stderr,
		"Unfolder -- unfolder for nets with read arcs\n\n"
		"Usage: unfolder <LLnetfile>\n\n"

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
	int	 i;
	char    *llnet = NULL;
	char    **dptr = &llnet;
	char    *stoptr_name = NULL;
	char    COMPRESS = 1;

	for (i = 1; i < argc; i++)
		if (!strcmp(argv[i],"-f"))
			COMPRESS = 0;
		else
		{
			if (!dptr) usage(argv[0]);
			*dptr = argv[i];
			dptr = NULL;
		}

	if (!llnet) usage(argv[0]);

	net = read_pep_net(llnet);
	nc_static_checks(net,stoptr_name);

	unfold();

	write_dot_output(unf,cutoff_list);

	return exitcode;
}
