#include <stdio.h>
#include <tss2/tss2_esys.h>

#include "random.h"

TPM2B_DIGEST generate_random_bytes(ESYS_CONTEXT *ctx)
{
	uint32_t ret = 0;
	TPM2B_DIGEST *random_bytes = NULL;

	ret = Esys_GetRandom(ctx, ESYS_TR_NONE, ESYS_TR_NONE, ESYS_TR_NONE,
		64, &random_bytes);
	if (ret != TSS2_RC_SUCCESS) {
		printf("error: Esys_GetRandom!\n");
		return *random_bytes;
	}
	printf("%o\n", *random_bytes);
	return *random_bytes;
}
