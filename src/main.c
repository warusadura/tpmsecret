#include <stdio.h>
#include <tss2/tss2_esys.h>
#include <tss2/tss2_mu.h>

#include "primarykey.h"
#include "encrypt.h"

int main(int argc, char* argv[])
{
	TSS2_RC rc;
	int ret;
	/* ESYS_CONTEXT: connection to the TPM */
	ESYS_CONTEXT *ctx;

	/* Initialize ESYS_CONTEXT
	 * paras: esys_context, tcti, abiVersion */
	rc = Esys_Initialize(&ctx, NULL, NULL);

	if (rc != TSS2_RC_SUCCESS)
		goto error;

	//unseal_password_auth(ctx);
	ret = create_primary_key(ctx);
	return ret;

error:
	printf("no TPM found!\n");
	return 1;
}
