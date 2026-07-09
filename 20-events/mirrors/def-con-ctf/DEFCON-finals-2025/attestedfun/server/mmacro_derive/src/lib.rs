extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, LitStr};

use aes::Aes128;
use cbc::Encryptor;
use cbc::cipher::{KeyIvInit, BlockEncryptMut};
use block_padding::Pkcs7;
use hex;

type Aes128CbcEnc = Encryptor<Aes128>;

#[proc_macro]
pub fn mm(input: TokenStream) -> TokenStream {
    const KEY: &[u8; 16] = b"1fenudafnH23ujj#";
    const IV: &[u8; 16] =  b"889asdNN23ujjXXD";

    let input = parse_macro_input!(input as LitStr);
    let plaintext = input.value();

    // copy plaintext into a mutable buffer
    let mut buffer = plaintext.as_bytes().to_vec();
    let block_size = 16;
    buffer.resize(buffer.len() + block_size, 0); // Make room for padding

    // create a mutable encryptor
    let cipher = Aes128CbcEnc::new(KEY.into(), IV.into());
    let ciphertext = cipher
        .encrypt_padded_mut::<Pkcs7>(&mut buffer, plaintext.len())
        .unwrap();

    let obfuscated = hex::encode(ciphertext);
    let out = LitStr::new(&obfuscated, input.span());
    quote!(#out).into()
}
