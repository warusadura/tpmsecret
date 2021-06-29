#include <stdio.h>
#include <tss2/tss2_esys.h>
#include <tss2/tss2_mu.h>

#include "encrypt_decrypt.h"

uint32_t encrypt_data(ESYS_CONTEXT *ctx, ESYS_TR sk_handle, TPMI_YES_NO
		      encrypt)
{
	uint32_t r = 0;
	FILE *secret_data = NULL;
	FILE *cipher_text = NULL;
	TPM2B_MAX_BUFFER *out_data = NULL;
	TPM2B_IV *iv_out = NULL;
	TPMI_ALG_SYM_MODE mode = TPM2_ALG_NULL;

	/* for passing an initial value for AES to or from the TPM */
	TPM2B_IV iv_in = {
		.size = 16,
		.buffer = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16}
	};

	/* sized buffer that can hold data */
	TPM2B_MAX_BUFFER in_data = {
		.size = 16
	};

	secret_data = fopen("secret_data", "r");
	if (!secret_data) {
		printf("error: reading secret_data!\n");
		//goto error;
	}
	fread(in_data.buffer, sizeof(char), BUFF_SIZE, secret_data);
	printf("%s", in_data.buffer);
	fclose(secret_data);

	r = Esys_EncryptDecrypt2(ctx, sk_handle, ESYS_TR_PASSWORD,
		ESYS_TR_NONE, ESYS_TR_NONE, &in_data, encrypt, mode,
		&iv_in, &out_data, &iv_out);

	if (r != TSS2_RC_SUCCESS) {
		printf("error: Esys_EncryptDecrypt2!\n");
	}

	cipher_text = fopen("cipher_text", "wb");
	if (!cipher_text) {
		printf("error: ");
	}

	printf("%s\n", out_data->buffer);
	fwrite(out_data->buffer, 1, BUFF_SIZE, cipher_text);

	fclose(cipher_text);
	return r;
}

uint32_t decrypt_data(ESYS_CONTEXT *ctx, ESYS_TR sk_handle, TPMI_YES_NO
	              decrypt)
{
	uint32_t r = 0;
	FILE *cipher_text = NULL;
	FILE *plain_text = NULL;
	TPM2B_MAX_BUFFER *out_data = NULL;
	TPM2B_IV *iv_out = NULL;
	TPMI_ALG_SYM_MODE mode = TPM2_ALG_NULL;

	TPM2B_IV iv_in = {
		.size = 16,
		.buffer = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16}
	};

	TPM2B_MAX_BUFFER in_data = {
		.size = 16
	};

	cipher_text = fopen("cipher_text", "rb");
	if (!cipher_text) {
		printf("error: reading cipher_text!\n");
	}
	fread(in_data.buffer, 1, BUFF_SIZE, cipher_text);
	fclose(cipher_text);

	r = Esys_EncryptDecrypt2(ctx, sk_handle, ESYS_TR_PASSWORD,
		ESYS_TR_NONE, ESYS_TR_NONE, &in_data, decrypt, mode,
		&iv_in, &out_data, &iv_out);

	if (r != TSS2_RC_SUCCESS) {
		printf("error: Esys_EncryptDecrypt2!\n");
	}

	plain_text = fopen("plain_text", "w");
	if (!plain_text) {
		printf("error: ");
	}
	fwrite(out_data->buffer, sizeof(char), BUFF_SIZE, plain_text);
	fclose(plain_text);

	printf("%s\n", out_data->buffer);

	return r;
}
