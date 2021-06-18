#include <stdio.h>
#include <tss2/tss2_esys.h>
#include <tss2/tss2_mu.h>

#include "encrypt_decrypt.h"

int encrypt_data(ESYS_CONTEXT *ctx, ESYS_TR sk_handle, TPM2B_IV *iv_in,
	TPM2B_MAX_BUFFER *in_data, TPMI_YES_NO encrypt)
{
	uint32_t r = 0;
	TPM2B_MAX_BUFFER *out_data = NULL;
	TPM2B_IV *iv_out = NULL;
	TPMI_ALG_SYM_MODE mode = TPM2_ALG_NULL;

	r = Esys_EncryptDecrypt2(ctx, sk_handle, ESYS_TR_PASSWORD,
		ESYS_TR_NONE, ESYS_TR_NONE, in_data, encrypt, mode,
		iv_in, &out_data, &iv_out);

	if (r != TSS2_RC_SUCCESS) {
		printf("error: Esys_EncryptDecrypt2!\n");
	}

	printf("%s\n", out_data->buffer);

	return r;
}

int decrypt_data(ESYS_CONTEXT *ctx, ESYS_TR sk_handle, TPM2B_IV *iv_in,
	TPM2B_MAX_BUFFER *in_data, TPMI_YES_NO decrypt)
{
	uint32_t r = 0;
	TPM2B_MAX_BUFFER *out_data = NULL;
	TPM2B_IV *iv_out = NULL;
	TPMI_ALG_SYM_MODE mode = TPM2_ALG_NULL;

	r = Esys_EncryptDecrypt2(ctx, sk_handle, ESYS_TR_PASSWORD,
		ESYS_TR_NONE, ESYS_TR_NONE, in_data, decrypt, mode,
		iv_in, &out_data, &iv_out);

	if (r != TSS2_RC_SUCCESS) {
		printf("error: Esys_EncryptDecrypt2!\n");
	}

	return r;
}
