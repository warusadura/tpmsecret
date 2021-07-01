#ifndef EGG_TPM2_H_
#define EGG_TPM2_H_

#include <stdio.h>

#include <glib.h>
#include <tss2/tss2_esys.h>

GBytes *egg_tpm2_generate_master_password (GBytes *, GError *);
GBytes *egg_tpm2_retrieve_master_password (GBytes *, GError *);

/*
 * helper/internal functions to egg_tpm2_generate_master_password
 * gboolean egg_tpm2_generate_primary_key(void);
 * GBytes   *egg_tpm2_generate_master_password(void);
 */
#endif
