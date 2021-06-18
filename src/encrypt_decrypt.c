#include <stdio.h>
#include <tss2/tss2_esys.h>
#include <tss2/tss2_mu.h>

#include "encrypt_decrypt.h"

int encrypt_data(ESYS_CONTEXT *ctx, ESYS_TR sk_handle)
{
	uint32_t r = 0;
	TPMI_YES_NO decrypt = TPM2_YES;
	TPMI_YES_NO encrypt = TPM2_NO;
	TPMI_ALG_SYM_MODE mode = TPM2_ALG_NULL;
	TPM2B_MAX_BUFFER *out_data = NULL;
	TPM2B_IV *iv_out = NULL;
	
	TPM2B_IV iv_in = {
		.size = 16,
		.buffer = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16}
	};

	TPM2B_MAX_BUFFER in_data = {
		.size = 16,
		.buffer = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16}
	};

	r = Esys_EncryptDecrypt2(ctx, sk_handle, ESYS_TR_PASSWORD,
		ESYS_TR_NONE, ESYS_TR_NONE, &in_data, encrypt, mode,
		&iv_in, &out_data, &iv_out);

	if (r != TSS2_RC_SUCCESS) {
		printf("error: Esys_EncryptDecrypt2!\n");
	}
	return r;
}

int decrypt_data(ESYS_CONTEXT *ctx, ESYS_TR sk_handle)
{
	uint32_t r = 0;
	return r;
}
