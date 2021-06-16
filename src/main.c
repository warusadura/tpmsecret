#include <stdio.h>
#include <tss2/tss2_esys.h>
#include <tss2/tss2_mu.h>

#include "primarykey.h"
#include "secondarykey.h"

int main(int argc, char* argv[])
{
	/* ESYS_TR: Esys TPM Resource
	 * reference to ESYS_CONTEXT object */
	ESYS_TR pr_handle = ESYS_TR_NONE;
	ESYS_TR sk_handle = ESYS_TR_NONE;

	uint32_t r = 0;
	int ret;
	/* ESYS_CONTEXT: connection to the TPM */
	ESYS_CONTEXT *ctx;

	/* Initialize ESYS_CONTEXT
	 * paras: esys_context, tcti, abiVersion */
	r = Esys_Initialize(&ctx, NULL, NULL);

	if (r != TSS2_RC_SUCCESS)
		goto error;

	ret = create_primary_key(ctx, pr_handle);
	ret = create_secondary_key(ctx, pr_handle, sk_handle);

	return ret;

error:
	printf("no TPM found!\n");
	Esys_Finalize(&ctx);
	return 1;
}
