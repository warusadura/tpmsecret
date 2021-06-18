#include <stdio.h>
#include <tss2/tss2_esys.h>
#include <tss2/tss2_mu.h>

#include "encrypt_decrypt.h"
#include "primarykey.h"
#include "secondarykey.h"

int main(int argc, char* argv[])
{
	/* ESYS_TR: Esys TPM Resource
	 * reference to ESYS_CONTEXT object */
	ESYS_TR pr_handle = ESYS_TR_NONE;
	ESYS_TR sk_handle = ESYS_TR_NONE;
	/* boolean type */
	TPMI_YES_NO encrypt_decrypt;

	uint32_t r = 0;
	int ret;
	/* ESYS_CONTEXT: connection to the TPM */
	ESYS_CONTEXT *ctx;

	/* Initialize ESYS_CONTEXT
	 * paras: esys_context, tcti, abiVersion */
	r = Esys_Initialize(&ctx, NULL, NULL);

	if (r != TSS2_RC_SUCCESS)
		goto error;

	ret = create_primary_key(ctx, &pr_handle);
	ret = create_secondary_key(ctx, &pr_handle, &sk_handle);

	/* encrypt_decrypt */

	/* for passing an initial value for AES to or from the TPM */
	TPM2B_IV iv_in = {
		.size = 16,
		.buffer = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16}
	};

	/* sized buffer that can hold data */
	TPM2B_MAX_BUFFER in_data = {
		.size = 16,
		.buffer = "hello world!"
	};

	encrypt_decrypt = TPM2_NO;

	ret = encrypt_data(ctx, sk_handle, &iv_in, &in_data, encrypt_decrypt);

	return ret;

error:
	printf("no TPM found!\n");
	Esys_Finalize(&ctx);
	return 1;
}
