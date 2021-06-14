### tpmsecret

a simple project to work with a TPM.

#### encrypting a file using TPM commands involves the following,

```tpm2_createprimary -c primary.ctx

tpm2_create -C primary.ctx -G aes256 -u key.pub -r key.priv

tpm2_load -C primary.ctx -u key.pub -r key.priv -c key.ctx

tpm2_encryptdecrypt -c key.ctx -o cipher_text secret_data

tpm2_encryptdecrypt -d -c key.ctx -o plain_text cipher_text
```

#### goals:

programmatically (ESAPI) accomplish the same thing.

References: [TPM TSS Quickstarter - Infineon Technologies](https://www.infineon.com/cms/en/product/promopages/tpm-tss-quickstarter/)
