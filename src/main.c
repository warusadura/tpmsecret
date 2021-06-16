#include <stdio.h>
#include <tss2/tss2_esys.h>
#include <tss2/tss2_mu.h>

#include "primarykey.h"
#include "secondarykey.h"

int main(int argc, char* argv[])
{
	TSS2_RC rc;
	int ret_pk;
	int ret_sk;
	/* ESYS_TR: Esys TPM Resource
	 * reference to ESYS_CONTEXT object */
	ESYS_TR handle = ESYS_TR_NONE;
	/* ESYS_CONTEXT: connection to the TPM */
	ESYS_CONTEXT *ctx;

	/* Initialize ESYS_CONTEXT
	 * paras: esys_context, tcti, abiVersion */
	rc = Esys_Initialize(&ctx, NULL, NULL);

	if (rc != TSS2_RC_SUCCESS)
		goto error;

	ret_pk = create_primary_key(ctx, handle);
	ret_sk = create_secondary_key(ctx, handle);
	return 0;

error:
	printf("no TPM found!\n");
	return 1;
}
