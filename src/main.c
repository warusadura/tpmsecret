#include "egg.h"

int
main(int argc, char* argv[])
{
	egg_tpm2_generate_primary_key();
	egg_tpm2_generate_master_password();
	return 0;
}
