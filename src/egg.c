#include "egg.h"

static ESYS_CONTEXT *ctx;
ESYS_TR pr_handle = ESYS_TR_NONE;

static gboolean
egg_tpm2_generate_primary_key(void)
{
	uint32_t ret = 0;

	ret = Esys_Initialize(&ctx, NULL, NULL);

	if (ret != TSS2_RC_SUCCESS) {
		printf("error: Esys_Initialize: NO TPM!\n");
		Esys_Finalize(&ctx);
		return FALSE;
	}

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
				TPMA_OBJECT_SENSITIVEDATAORIGIN),
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

	ret = Esys_CreatePrimary (ctx, ESYS_TR_RH_OWNER, ESYS_TR_PASSWORD,
		ESYS_TR_NONE, ESYS_TR_NONE, &in_sensitive_para,
		&public_key_para, &additional_info, &pcr, &pr_handle,
		&public, &creation_data, &hash, &ticket);

	if (ret != TSS2_RC_SUCCESS) {
		printf("error: Esys_CreatePrimary!\n");
		return FALSE;
	} else
		printf("a primary key created!\n");

	return TRUE;
}

GBytes *
egg_tpm2_generate_master_password(GBytes *input, GError *error)
{
	/* master password generation */
	uint32_t ret = 0;
	TPM2B_DIGEST *random_bytes = NULL;
	FILE *processed_key_file = NULL;
	TPM2B_MAX_BUFFER *out_data = NULL;
	TPM2B_IV *iv_out = NULL;
	TPMI_ALG_SYM_MODE mode = TPM2_ALG_NULL;

	ret = Esys_GetRandom(ctx, ESYS_TR_NONE, ESYS_TR_NONE, ESYS_TR_NONE,
		64, &random_bytes);
	if (ret != TSS2_RC_SUCCESS) {
		printf("error: Esys_GetRandom!\n");
		/* g_debug ("error: Esys_GetRandom!\n");
		 * undefined reference to 'g_log'
		 */
		return FALSE;
	}

	/* master password encrypting */

	TPM2B_IV iv_in = {
		.size = 64,
	};

	/* sized buffer that can hold data */
	TPM2B_MAX_BUFFER in_data = {
		.size = 64,
	};

	return NULL;
}
