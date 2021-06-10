#include <stdio.h>
#include <tss2/tss2_mu.h>
#include <tss2/tss2_esys.h>

#include "primarykey.h"

void create_primary_key(void)
{
	ESYS_TR handle = ESYS_TR_NONE;
	uint32_t r = 0;
	ESYS_CONTEXT *ctx;

	r = Esys_Initialize(&ctx, NULL, NULL);
}
