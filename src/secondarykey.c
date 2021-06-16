#include <stdio.h>
#include <tss2/tss2_esys.h>
#include <tss2/tss2_mu.h>

#include "secondarykey.h"

int create_secondary_key(ESYS_CONTEXT *ctx, ESYS_TR handle)
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
				.size = 8,
				.buffer = {3, 2, 3, 2, 3, 2, 3, 2}
			}
		}
	};

	in_sensitive_para.sensitive.userAuth = auth_sk;

	TPM2B_PUBLIC public_key_para = {
		.size = 0,
		.publicArea = {
			.type = TPM2_ALG_KEYEDHASH,
			.nameAlg = TPM2_ALG_SHA256,
			.objectAttributes = (
				TPMA_OBJECT_USERWITHAUTH |
				TPMA_OBJECT_FIXEDTPM |
				TPMA_OBJECT_FIXEDPARENT),
			.authPolicy = {
				.size = 0,
			},
			.parameters.keyedHashDetail = {
				.scheme = {
					.scheme = TPM2_ALG_NULL,
					.details = {
						.hmac = {
							.hashAlg = TPM2_ALG_SHA256
						}
					}
				}
			},
			.unique.keyedHash = {
				.size = 0,
				.buffer = {}
			},
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
	TPM2B_SENSITIVE_DATA *out_data;

	r = Esys_Create(ctx, handle, ESYS_TR_PASSWORD, ESYS_TR_NONE,
		ESYS_TR_NONE, &in_sensitive_para,
		&public_key_para, &additional_info, &pcr, &private,
		&public, &creation_data, &hash, &ticket);

	if (r != TSS2_RC_SUCCESS) {
		printf("error: Esys_Create!\n");
		goto error;
	} else
		printf("a secondary key created!\n");

error:
	return 1;
}
