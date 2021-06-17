#include <stdio.h>
#include <tss2/tss2_esys.h>
#include <tss2/tss2_mu.h>

#include "secondarykey.h"

int create_secondary_key(ESYS_CONTEXT *ctx, ESYS_TR *pr_handle,
	ESYS_TR *sk_handle)
{
	uint32_t r = 0;

	TPM2B_AUTH auth_sk = {
		.size = 6,
		.buffer = {6, 7, 8, 9, 10, 11}
	};

	TPM2B_SENSITIVE_CREATE in_sensitive_para = {
		.size = 0,
		.sensitive = {
			.userAuth = {
				.size = 0,
				.buffer = {0}
			},
			.data = {
				.size = 16,
				.buffer = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
					11, 12, 16}
			}
		}
	};

	in_sensitive_para.sensitive.userAuth = auth_sk;

	TPM2B_PUBLIC public_key_para = {
		.size = 0,
		.publicArea = {
			.type = TPM2_ALG_SYMCIPHER,
			.nameAlg = TPM2_ALG_SHA256,
			.objectAttributes = (
				TPMA_OBJECT_USERWITHAUTH |
				TPMA_OBJECT_SIGN_ENCRYPT |
				TPMA_OBJECT_FIXEDTPM |
				TPMA_OBJECT_FIXEDPARENT |
				TPMA_OBJECT_DECRYPT),
			.authPolicy = {
				.size = 0,
			},
			.parameters.symDetail = {
				.sym = {
					.algorithm = TPM2_ALG_AES,
					.keyBits = {.aes = 128},
					.mode = {.aes = TPM2_ALG_CFB}
				}
			},
			.unique.sym = {
				.size = 0,
				.buffer = {}
			}
		}
	};

	TPM2B_DATA additional_info = {
		.size = 0,
		.buffer = {}
	};

	TPML_PCR_SELECTION pcr = {
		.count = 0,
	};

	TPM2B_PUBLIC *public;
	TPM2B_PRIVATE *private;
	TPM2B_CREATION_DATA *creation_data;
	TPM2B_DIGEST *hash;
	TPMT_TK_CREATION *ticket;

	r = Esys_Create(ctx, *pr_handle, ESYS_TR_PASSWORD, ESYS_TR_NONE,
		ESYS_TR_NONE, &in_sensitive_para,
		&public_key_para, &additional_info, &pcr, &private,
		&public, &creation_data, &hash, &ticket);

	if (r != TSS2_RC_SUCCESS) {
		printf("error: Esys_Create!\n");
		goto error;
	} else
		printf("a secondary AES key created!\n");

	/* load the secondary key */
	r = Esys_Load(ctx, *pr_handle, ESYS_TR_PASSWORD, ESYS_TR_NONE,
		ESYS_TR_NONE, private, public, sk_handle);

	if (r != TSS2_RC_SUCCESS) {
		printf("error: Esys_Load!\n");
		goto error;
	} else
		printf("AES key loaded!\n");

	/* authorize loaded key */
	r = Esys_TR_SetAuth(ctx, *sk_handle, &auth_sk);

	if (r != TSS2_RC_SUCCESS) {
		printf("error: Esys_SetAuth!\n");
		goto error;
	}

	return r;

error:
	return 1;
}
