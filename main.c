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
		"Mora -- unfolder for nets with read arcs\n\n"
		"Usage: mora [-f] <LLnetfile>\n\n"

	"Mora is a spin-off from Mole that works for nets with read arcs.\n"
	"The output is a dot-compatible graph of the result.\n\n"

	"Option -f outputs the unfolding of the net where read arcs are\n"
	"replaced by produce/consume loops.\n\n"

	"Version 0.0.3 (21.03.2007)\n");

	exit(1);
}

/*****************************************************************************/

/**
 * Prova di documentazione, funzione main.
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

	write_dot_output(unf,cutoff_list,0);

	return exitcode;
}
