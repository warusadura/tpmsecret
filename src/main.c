#include <stdio.h>
#include <tss2/tss2_esys.h>
#include <tss2/tss2_mu.h>

#include "encrypt_decrypt.h"
#include "primarykey.h"
#include "random.h"
#include "secondarykey.h"

int main(int argc, char* argv[])
{
	/* ESYS_TR: Esys TPM Resource
	 * reference to ESYS_CONTEXT object */
	ESYS_TR pr_handle = ESYS_TR_NONE;
	ESYS_TR sk_handle = ESYS_TR_NONE;
	/* boolean type */
	TPMI_YES_NO encrypt = TPM2_NO;
	TPMI_YES_NO decrypt = TPM2_YES;
	TPM2B_DIGEST random_bytes;

	uint32_t ret;
	/* ESYS_CONTEXT: connection to the TPM */
	ESYS_CONTEXT *ctx;

	/* Initialize ESYS_CONTEXT
	 * paras: esys_context, tcti, abiVersion */
	ret = Esys_Initialize(&ctx, NULL, NULL);

	if (ret != TSS2_RC_SUCCESS)
		goto error;

	ret = create_primary_key(ctx, &pr_handle);
	ret = create_secondary_key(ctx, &pr_handle, &sk_handle);

	/* encrypt_decrypt */

	ret = encrypt_data(ctx, sk_handle, encrypt);
	ret = decrypt_data(ctx, sk_handle, decrypt);

	random_bytes = generate_random_bytes(ctx);

	return (int)ret;

error:
	printf("no TPM found!\n");
	Esys_Finalize(&ctx);
	return 1;
}
