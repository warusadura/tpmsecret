#include <stdio.h>
#include <tss2/tss2_mu.h>
#include <tss2/tss2_esys.h>

#include "primarykey.h"

int create_primary_key(void)
{
	ESYS_TR handle = ESYS_TR_NONE;
	printf("%d\n", handle);
	uint32_t r = 0;
	ESYS_CONTEXT *ctx;

	r = Esys_Initialize(&ctx, NULL, NULL);
	printf("%d\n", r);

	TPM2B_AUTH auth_pk = {
		.size = 5,
		.buffer = {1, 2, 3, 4, 5}
	};

	TPM2B_SENSITIVE_CREATE in_sensitive_para = {
		.size = 4,
		.sensitive = {
			.userAuth = {
				.size = 0,
				.buffer = {0},
			},
			.data = {
				.size = 0,
				.buffer = {0},
			},
		},
	};

	in_sensitive_para.sensitive.userAuth = auth_pk;

	TPM2B_PUBLIC public_key_para = {
		.size = 0,
		.publicArea = {
			.type = TPM2_ALG_RSA,
			.nameAlg = TPM2_ALG_SHA256,
			.objectAttributes = (
				TPMA_OBJECT_USERWITHAUTH |
				TPMA_OBJECT_RESTRICTED |
				TPMA_OBJECT_DECRYPT |
				TPMA_OBJECT_FIXEDTPM |
				TPMA_OBJECT_FIXEDPARENT |
				TPMA_OBJECT_SENSITIVEDATAORIGIN
				),
			.authPolicy = {
				.size = 0,
			},
			.parameters.rsaDetail = {
				.symmetric = {
					.algorithm = TPM2_ALG_AES,
					.keyBits.aes = 128,
					.mode.aes = TPM2_ALG_CFB,
				},
				.scheme = {
					.scheme = TPM2_ALG_NULL
				},
				.keyBits = 2048,
				.exponent = 65537,
			},
			.unique.rsa = {
				.size = 0,
				.buffer = {},
			},
		},
	};

	TPM2B_DATA additional_info = {
		.size = 0,
		.buffer = {},
	};

	TPML_PCR_SELECTION pcr = {
		.count = 0,
	};

	TPM2B_PUBLIC *public;
	TPM2B_CREATION_DATA *creation_data;
	TPM2B_DIGEST *hash;
	TPMT_TK_CREATION *ticket;

	r = Esys_CreatePrimary (ctx, ESYS_TR_RH_OWNER, ESYS_TR_PASSWORD,
				ESYS_TR_NONE, ESYS_TR_NONE,
				&in_sensitive_para, &public_key_para,
				&additional_info, &pcr, &handle, &public,
				&creation_data, &hash, &ticket);

	if (r != TSS2_RC_SUCCESS) {
		printf("error: Esys_CreatePrimary!\n");
		goto error;
	} else
		printf("a primary key created!\n");

	r = Esys_FlushContext(ctx, handle);
	if (r != TSS2_RC_SUCCESS) {
		printf("error: Esys_FlushContext handle\n");
		goto error;
	}

	Esys_Finalize(&ctx);

	return 0;

error:
	if (handle != ESYS_TR_NONE)
		if (Esys_FlushContext(ctx, handle) != TSS2_RC_SUCCESS)
			printf("cleanup failed");

	if (ctx)
		Esys_Finalize(&ctx);
	return 1;
}