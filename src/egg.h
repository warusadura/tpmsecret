#ifndef EGG_TPM2_H_
#define EGG_TPM2_H_

#include <stdio.h>

#include <glib.h>
#include <tss2/tss2_esys.h>

gboolean egg_tpm2_generate_primary_key      (void);
gboolean egg_tpm2_generate_master_password  (void);
GBytes   *egg_tpm2_retrieve_master_password (const GBytes *data,
		                             GBytes **data_out);

#endif
