// cert_chain_checker.rs
//
// Refactored: read four Base64-encoded DER certificates from a file, verify the chain
// treating the first certificate as root, selecting only SHA-256 as the signature algorithm,
// inspect only the 4th certificate's Android Key Attestation (hardwareEnforced), and print out its userAuthType.
// Additionally, capture and print any signatureAlgorithm parameters.

mod revoked;
use revoked::REVOKED;

// ─── Std ───────────────────────────────────────────────────────────────
use std::{
    env,
    fs::{self, OpenOptions},
    io::{self, Write},
    path::Path,
    process,
    thread,
    time::{Duration, SystemTime, UNIX_EPOCH},
};

// ─── Crates ────────────────────────────────────────────────────────────
use aes::Aes128;
use base64::{engine::general_purpose::STANDARD, Engine};
use block_modes::{BlockMode, Cbc};
use block_modes::block_padding::Pkcs7;
use hex;
use hmac::{Hmac, Mac};
use jsonwebtoken::{encode, Algorithm, EncodingKey, Header};
use num_bigint::BigUint;
use num_traits::cast::ToPrimitive;
use once_cell::sync::OnceCell;
use openssl::{
    hash::MessageDigest,
    rsa::Padding,
    sign::{RsaPssSaltlen, Verifier},
    x509::{X509, X509Ref},
};
use rand::Rng;
use reqwest::blocking::Client;
use serde::{Deserialize, Serialize};
use serde_cbor::Value as ValueC;
use serde_json::{json, Value};
use sha2::{Digest, Sha256, Sha512};
use simple_asn1::{ASN1Block, ASN1Class, OID, from_der, to_der};

// ─── Type Aliases ──────────────────────────────────────────────────────
type Aes128Cbc = Cbc<Aes128, Pkcs7>;

// ─── Macros ────────────────────────────────────────────────────────────
use mmacro_derive::mm;


macro_rules! pmm {
    ($msg:expr) => {
        format!("[[[{} {}]]]", mm!($msg), line!())
    };
}


// openssl pkey -pubin -in rootkey.pem -outform DER | hexdump -v -e '1/1 "0x%02X,"'
const EXPECTED_ROOT_PUBKEY_DER: &[u8] = &[
0x30,0x82,0x02,0x22,0x30,0x0D,0x06,0x09,0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x01,0x05,0x00,0x03,0x82,0x02,0x0F,0x00,0x30,0x82,0x02,0x0A,0x02,0x82,0x02,0x01,0x00,0xAF,0xB6,0xC7,0x82,0x2B,0xB1,0xA7,0x01,0xEC,0x2B,0xB4,0x2E,0x8B,0xCC,0x54,0x16,0x63,0xAB,0xEF,0x98,0x2F,0x32,0xC7,0x7F,0x75,0x31,0x03,0x0C,0x97,0x52,0x4B,0x1B,0x5F,0xE8,0x09,0xFB,0xC7,0x2A,0xA9,0x45,0x1F,0x74,0x3C,0xBD,0x9A,0x6F,0x13,0x35,0x74,0x4A,0xA5,0x5E,0x77,0xF6,0xB6,0xAC,0x35,0x35,0xEE,0x17,0xC2,0x5E,0x63,0x95,0x17,0xDD,0x9C,0x92,0xE6,0x37,0x4A,0x53,0xCB,0xFE,0x25,0x8F,0x8F,0xFB,0xB6,0xFD,0x12,0x93,0x78,0xA2,0x2A,0x4C,0xA9,0x9C,0x45,0x2D,0x47,0xA5,0x9F,0x32,0x01,0xF4,0x41,0x97,0xCA,0x1C,0xCD,0x7E,0x76,0x2F,0xB2,0xF5,0x31,0x51,0xB6,0xFE,0xB2,0xFF,0xFD,0x2B,0x6F,0xE4,0xFE,0x5B,0xC6,0xBD,0x9E,0xC3,0x4B,0xFE,0x08,0x23,0x9D,0xAA,0xFC,0xEB,0x8E,0xB5,0xA8,0xED,0x2B,0x3A,0xCD,0x9C,0x5E,0x3A,0x77,0x90,0xE1,0xB5,0x14,0x42,0x79,0x31,0x59,0x85,0x98,0x11,0xAD,0x9E,0xB2,0xA9,0x6B,0xBD,0xD7,0xA5,0x7C,0x93,0xA9,0x1C,0x41,0xFC,0xCD,0x27,0xD6,0x7F,0xD6,0xF6,0x71,0xAA,0x0B,0x81,0x52,0x61,0xAD,0x38,0x4F,0xA3,0x79,0x44,0x86,0x46,0x04,0xDD,0xB3,0xD8,0xC4,0xF9,0x20,0xA1,0x9B,0x16,0x56,0xC2,0xF1,0x4A,0xD6,0xD0,0x3C,0x56,0xEC,0x06,0x08,0x99,0x04,0x1C,0x1E,0xD1,0xA5,0xFE,0x6D,0x34,0x40,0xB5,0x56,0xBA,0xD1,0xD0,0xA1,0x52,0x58,0x9C,0x53,0xE5,0x5D,0x37,0x07,0x62,0xF0,0x12,0x2E,0xEF,0x91,0x86,0x1B,0x1B,0x0E,0x6C,0x4C,0x80,0x92,0x74,0x99,0xC0,0xE9,0xBE,0xC0,0xB8,0x3E,0x3B,0xC1,0xF9,0x3C,0x72,0xC0,0x49,0x60,0x4B,0xBD,0x2F,0x13,0x45,0xE6,0x2C,0x3F,0x8E,0x26,0xDB,0xEC,0x06,0xC9,0x47,0x66,0xF3,0xC1,0x28,0x23,0x9D,0x4F,0x43,0x12,0xFA,0xD8,0x12,0x38,0x87,0xE0,0x6B,0xEC,0xF5,0x67,0x58,0x3B,0xF8,0x35,0x5A,0x81,0xFE,0xEA,0xBA,0xF9,0x9A,0x83,0xC8,0xDF,0x3E,0x2A,0x32,0x2A,0xFC,0x67,0x2B,0xF1,0x20,0xB1,0x35,0x15,0x8B,0x68,0x21,0xCE,0xAF,0x30,0x9B,0x6E,0xEE,0x77,0xF9,0x88,0x33,0xB0,0x18,0xDA,0xA1,0x0E,0x45,0x1F,0x06,0xA3,0x74,0xD5,0x07,0x81,0xF3,0x59,0x08,0x29,0x66,0xBB,0x77,0x8B,0x93,0x08,0x94,0x26,0x98,0xE7,0x4E,0x0B,0xCD,0x24,0x62,0x8A,0x01,0xC2,0xCC,0x03,0xE5,0x1F,0x0B,0x3E,0x5B,0x4A,0xC1,0xE4,0xDF,0x9E,0xAF,0x9F,0xF6,0xA4,0x92,0xA7,0x7C,0x14,0x83,0x88,0x28,0x85,0x01,0x5B,0x42,0x2C,0xE6,0x7B,0x80,0xB8,0x8C,0x9B,0x48,0xE1,0x3B,0x60,0x7A,0xB5,0x45,0xC7,0x23,0xFF,0x8C,0x44,0xF8,0xF2,0xD3,0x68,0xB9,0xF6,0x52,0x0D,0x31,0x14,0x5E,0xBF,0x9E,0x86,0x2A,0xD7,0x1D,0xF6,0xA3,0xBF,0xD2,0x45,0x09,0x59,0xD6,0x53,0x74,0x0D,0x97,0xA1,0x2F,0x36,0x8B,0x13,0xEF,0x66,0xD5,0xD0,0xA5,0x4A,0x6E,0x2F,0x5D,0x9A,0x6F,0xEF,0x44,0x68,0x32,0xBC,0x67,0x84,0x47,0x25,0x86,0x1F,0x09,0x3D,0xD0,0xE6,0xF3,0x40,0x5D,0xA8,0x96,0x43,0xEF,0x0F,0x4D,0x69,0xB6,0x42,0x00,0x51,0xFD,0xB9,0x30,0x49,0x67,0x3E,0x36,0x95,0x05,0x80,0xD3,0xCD,0xF4,0xFB,0xD0,0x8B,0xC5,0x84,0x83,0x95,0x26,0x00,0x63,0x02,0x03,0x01,0x00,0x01,
];


// 1) Your “whitelist” of a single valid rootOfTrust.verifiedBootKey:
static VALID_BOOT_KEYS: &[&[u8]] = &[
    &[
        0x0f, 0x6e, 0x75, 0xc8, 0x01, 0x83, 0xb5, 0xde,
        0xc0, 0x74, 0xb0, 0x05, 0x4d, 0x42, 0x71, 0xe9,
        0x93, 0x89, 0xeb, 0xe4, 0xb1, 0x36, 0xb0, 0x81,
        0x9d, 0xe1, 0xf1, 0x50, 0xba, 0x0f, 0xf9, 0xd7,
    ],
];

// 2) Your “whitelist” of a single valid rootOfTrust.verifiedBootHash:
static VALID_BOOT_HASHES: &[&[u8]] = &[
    &[
        0x7f, 0x20, 0xe3, 0x10, 0x2e, 0x51, 0xb2, 0x65,
        0xae, 0xda, 0xc1, 0x6f, 0x49, 0x7f, 0x42, 0xcb,
        0x2e, 0xd2, 0x30, 0x94, 0xac, 0x2e, 0x77, 0x36,
        0x63, 0xa7, 0x4d, 0x70, 0x06, 0x07, 0x5e, 0x4d,
    ],
];

const CERT_ROOT: [u8; 1380] = [ 48, 130, 5, 96, 48, 130, 3, 72, 160, 3, 2, 1, 2, 2, 9, 0, 232, 250, 25, 99, 20, 210, 250, 24, 48, 13, 6, 9, 42, 134, 72, 134, 247, 13, 1, 1, 11, 5, 0, 48, 27, 49, 25, 48, 23, 6, 3, 85, 4, 5, 19, 16, 102, 57, 50, 48, 48, 57, 101, 56, 53, 51, 98, 54, 98, 48, 52, 53, 48, 30, 23, 13, 49, 54, 48, 53, 50, 54, 49, 54, 50, 56, 53, 50, 90, 23, 13, 50, 54, 48, 53, 50, 52, 49, 54, 50, 56, 53, 50, 90, 48, 27, 49, 25, 48, 23, 6, 3, 85, 4, 5, 19, 16, 102, 57, 50, 48, 48, 57, 101, 56, 53, 51, 98, 54, 98, 48, 52, 53, 48, 130, 2, 34, 48, 13, 6, 9, 42, 134, 72, 134, 247, 13, 1, 1, 1, 5, 0, 3, 130, 2, 15, 0, 48, 130, 2, 10, 2, 130, 2, 1, 0, 175, 182, 199, 130, 43, 177, 167, 1, 236, 43, 180, 46, 139, 204, 84, 22, 99, 171, 239, 152, 47, 50, 199, 127, 117, 49, 3, 12, 151, 82, 75, 27, 95, 232, 9, 251, 199, 42, 169, 69, 31, 116, 60, 189, 154, 111, 19, 53, 116, 74, 165, 94, 119, 246, 182, 172, 53, 53, 238, 23, 194, 94, 99, 149, 23, 221, 156, 146, 230, 55, 74, 83, 203, 254, 37, 143, 143, 251, 182, 253, 18, 147, 120, 162, 42, 76, 169, 156, 69, 45, 71, 165, 159, 50, 1, 244, 65, 151, 202, 28, 205, 126, 118, 47, 178, 245, 49, 81, 182, 254, 178, 255, 253, 43, 111, 228, 254, 91, 198, 189, 158, 195, 75, 254, 8, 35, 157, 170, 252, 235, 142, 181, 168, 237, 43, 58, 205, 156, 94, 58, 119, 144, 225, 181, 20, 66, 121, 49, 89, 133, 152, 17, 173, 158, 178, 169, 107, 189, 215, 165, 124, 147, 169, 28, 65, 252, 205, 39, 214, 127, 214, 246, 113, 170, 11, 129, 82, 97, 173, 56, 79, 163, 121, 68, 134, 70, 4, 221, 179, 216, 196, 249, 32, 161, 155, 22, 86, 194, 241, 74, 214, 208, 60, 86, 236, 6, 8, 153, 4, 28, 30, 209, 165, 254, 109, 52, 64, 181, 86, 186, 209, 208, 161, 82, 88, 156, 83, 229, 93, 55, 7, 98, 240, 18, 46, 239, 145, 134, 27, 27, 14, 108, 76, 128, 146, 116, 153, 192, 233, 190, 192, 184, 62, 59, 193, 249, 60, 114, 192, 73, 96, 75, 189, 47, 19, 69, 230, 44, 63, 142, 38, 219, 236, 6, 201, 71, 102, 243, 193, 40, 35, 157, 79, 67, 18, 250, 216, 18, 56, 135, 224, 107, 236, 245, 103, 88, 59, 248, 53, 90, 129, 254, 234, 186, 249, 154, 131, 200, 223, 62, 42, 50, 42, 252, 103, 43, 241, 32, 177, 53, 21, 139, 104, 33, 206, 175, 48, 155, 110, 238, 119, 249, 136, 51, 176, 24, 218, 161, 14, 69, 31, 6, 163, 116, 213, 7, 129, 243, 89, 8, 41, 102, 187, 119, 139, 147, 8, 148, 38, 152, 231, 78, 11, 205, 36, 98, 138, 1, 194, 204, 3, 229, 31, 11, 62, 91, 74, 193, 228, 223, 158, 175, 159, 246, 164, 146, 167, 124, 20, 131, 136, 40, 133, 1, 91, 66, 44, 230, 123, 128, 184, 140, 155, 72, 225, 59, 96, 122, 181, 69, 199, 35, 255, 140, 68, 248, 242, 211, 104, 185, 246, 82, 13, 49, 20, 94, 191, 158, 134, 42, 215, 29, 246, 163, 191, 210, 69, 9, 89, 214, 83, 116, 13, 151, 161, 47, 54, 139, 19, 239, 102, 213, 208, 165, 74, 110, 47, 93, 154, 111, 239, 68, 104, 50, 188, 103, 132, 71, 37, 134, 31, 9, 61, 208, 230, 243, 64, 93, 168, 150, 67, 239, 15, 77, 105, 182, 66, 0, 81, 253, 185, 48, 73, 103, 62, 54, 149, 5, 128, 211, 205, 244, 251, 208, 139, 197, 132, 131, 149, 38, 0, 99, 2, 3, 1, 0, 1, 163, 129, 166, 48, 129, 163, 48, 29, 6, 3, 85, 29, 14, 4, 22, 4, 20, 54, 97, 225, 0, 124, 136, 5, 9, 81, 139, 68, 108, 71, 255, 26, 76, 201, 234, 79, 18, 48, 31, 6, 3, 85, 29, 35, 4, 24, 48, 22, 128, 20, 54, 97, 225, 0, 124, 136, 5, 9, 81, 139, 68, 108, 71, 255, 26, 76, 201, 234, 79, 18, 48, 15, 6, 3, 85, 29, 19, 1, 1, 255, 4, 5, 48, 3, 1, 1, 255, 48, 14, 6, 3, 85, 29, 15, 1, 1, 255, 4, 4, 3, 2, 1, 134, 48, 64, 6, 3, 85, 29, 31, 4, 57, 48, 55, 48, 53, 160, 51, 160, 49, 134, 47, 104, 116, 116, 112, 115, 58, 47, 47, 97, 110, 100, 114, 111, 105, 100, 46, 103, 111, 111, 103, 108, 101, 97, 112, 105, 115, 46, 99, 111, 109, 47, 97, 116, 116, 101, 115, 116, 97, 116, 105, 111, 110, 47, 99, 114, 108, 47, 48, 13, 6, 9, 42, 134, 72, 134, 247, 13, 1, 1, 11, 5, 0, 3, 130, 2, 1, 0, 32, 200, 195, 141, 75, 220, 169, 87, 27, 70, 140, 137, 47, 255, 114, 170, 198, 248, 68, 161, 29, 65, 168, 240, 115, 108, 195, 125, 22, 214, 66, 109, 142, 126, 148, 7, 4, 76, 234, 57, 230, 139, 7, 193, 61, 191, 21, 3, 221, 92, 133, 189, 175, 178, 192, 45, 95, 108, 219, 78, 250, 129, 39, 223, 139, 4, 241, 130, 119, 15, 196, 231, 116, 91, 127, 206, 170, 135, 18, 154, 136, 1, 206, 142, 155, 192, 203, 150, 55, 155, 77, 38, 168, 45, 48, 253, 156, 47, 142, 237, 109, 193, 190, 47, 132, 182, 137, 228, 217, 20, 37, 139, 20, 75, 186, 230, 36, 161, 199, 6, 113, 19, 46, 47, 6, 22, 168, 132, 178, 164, 214, 164, 111, 250, 137, 182, 2, 191, 186, 216, 12, 18, 67, 113, 31, 86, 235, 96, 86, 246, 55, 200, 160, 20, 28, 197, 64, 148, 38, 139, 140, 60, 125, 185, 148, 179, 92, 13, 205, 108, 178, 171, 194, 218, 254, 226, 82, 2, 61, 45, 234, 12, 214, 195, 104, 190, 163, 230, 65, 72, 134, 246, 177, 229, 139, 91, 215, 199, 48, 178, 104, 196, 227, 193, 251, 100, 36, 185, 31, 235, 189, 184, 12, 88, 110, 42, 232, 54, 140, 132, 213, 209, 9, 23, 189, 162, 86, 23, 137, 212, 104, 115, 147, 52, 14, 46, 37, 79, 86, 14, 246, 75, 35, 88, 252, 220, 15, 191, 198, 112, 9, 82, 231, 8, 191, 252, 198, 39, 80, 12, 31, 102, 232, 30, 161, 124, 9, 141, 122, 46, 155, 24, 128, 27, 122, 180, 172, 113, 88, 125, 52, 93, 204, 131, 9, 213, 182, 42, 80, 66, 122, 166, 208, 61, 203, 5, 153, 108, 150, 186, 12, 93, 113, 233, 33, 98, 192, 22, 202, 132, 159, 243, 95, 13, 82, 198, 93, 5, 96, 90, 71, 243, 174, 145, 122, 205, 45, 249, 16, 239, 210, 50, 102, 136, 89, 110, 246, 155, 59, 245, 254, 49, 84, 247, 174, 184, 128, 160, 167, 60, 160, 77, 148, 194, 206, 131, 23, 238, 180, 61, 94, 255, 88, 131, 227, 54, 245, 242, 73, 218, 172, 164, 137, 146, 55, 191, 38, 126, 92, 67, 171, 2, 234, 68, 22, 36, 3, 114, 59, 230, 170, 105, 44, 97, 189, 174, 158, 212, 9, 212, 99, 196, 201, 124, 100, 48, 101, 119, 238, 242, 188, 117, 96, 183, 87, 21, 204, 156, 125, 198, 124, 134, 8, 45, 183, 81, 168, 156, 48, 52, 151, 98, 176, 120, 35, 133, 135, 92, 241, 163, 198, 22, 110, 10, 227, 193, 45, 55, 78, 45, 79, 24, 70, 243, 24, 116, 75, 216, 121, 181, 135, 50, 155, 240, 24, 33, 122, 108, 12, 119, 36, 26, 72, 120, 228, 53, 192, 48, 121, 203, 69, 18, 137, 197, 119, 98, 6, 6, 154, 47, 141, 101, 248, 64, 225, 68, 82, 135, 190, 216, 119, 171, 174, 36, 226, 68, 53, 22, 141, 85, 60, 228, ];


const CERT_L2_PC: [u8; 516] = [
    48, 130, 2, 0, 48, 130, 1, 133, 160, 3, 2, 1, 2, 2, 16, 86,
    154, 36, 1, 186, 146, 56, 48, 155, 218, 192, 6, 194, 172, 37, 29, 48,
    10, 6, 8, 42, 134, 72, 206, 61, 4, 3, 2, 48, 63, 49, 18, 48,
    16, 6, 3, 85, 4, 12, 12, 9, 83, 116, 114, 111, 110, 103, 66, 111,
    120, 49, 41, 48, 39, 6, 3, 85, 4, 5, 19, 32, 102, 51, 100, 102,
    49, 57, 55, 98, 49, 52, 49, 99, 57, 51, 52, 55, 99, 55, 100, 97,
    102, 48, 51, 55, 53, 101, 99, 48, 102, 57, 52, 57, 48, 30, 23, 13,
    50, 48, 48, 57, 49, 49, 49, 56, 48, 50, 52, 52, 90, 23, 13, 51,
    48, 48, 57, 48, 57, 49, 56, 48, 50, 52, 52, 90, 48, 63, 49, 18,
    48, 16, 6, 3, 85, 4, 12, 12, 9, 83, 116, 114, 111, 110, 103, 66,
    111, 120, 49, 41, 48, 39, 6, 3, 85, 4, 5, 19, 32, 48, 54, 56,
    52, 50, 102, 56, 52, 98, 99, 98, 97, 100, 98, 100, 49, 57, 54, 52,
    48, 53, 98, 102, 100, 54, 97, 54, 51, 52, 57, 101, 98, 48, 89, 48,
    19, 6, 7, 42, 134, 72, 206, 61, 2, 1, 6, 8, 42, 134, 72, 206,
    61, 3, 1, 7, 3, 66, 0, 4, 57, 152, 154, 242, 121, 228, 244, 64,
    100, 0, 113, 23, 69, 139, 198, 163, 43, 77, 86, 5, 100, 240, 91, 168,
    58, 38, 68, 0, 4, 134, 19, 147, 101, 51, 113, 242, 188, 90, 48, 245,
    213, 62, 150, 139, 98, 249, 205, 80, 78, 105, 95, 243, 82, 228, 208, 108,
    74, 82, 60, 136, 228, 112, 254, 155, 163, 99, 48, 97, 48, 29, 6, 3,
    85, 29, 14, 4, 22, 4, 20, 81, 36, 110, 176, 49, 199, 18, 182, 110,
    198, 44, 204, 88, 144, 180, 222, 27, 190, 35, 73, 48, 31, 6, 3, 85,
    29, 35, 4, 24, 48, 22, 128, 20, 110, 230, 17, 223, 112, 70, 213, 187,
    52, 109, 141, 45, 142, 6, 55, 31, 82, 113, 171, 77, 48, 15, 6, 3,
    85, 29, 19, 1, 1, 255, 4, 5, 48, 3, 1, 1, 255, 48, 14, 6,
    3, 85, 29, 15, 1, 1, 255, 4, 4, 3, 2, 2, 4, 48, 10, 6,
    8, 42, 134, 72, 206, 61, 4, 3, 2, 3, 105, 0, 48, 102, 2, 49,
    0, 238, 223, 90, 165, 41, 206, 19, 165, 160, 13, 53, 145, 154, 70, 235,
    206, 204, 25, 174, 99, 141, 137, 7, 213, 232, 162, 166, 57, 67, 100, 7,
    180, 179, 245, 153, 29, 232, 220, 37, 79, 144, 9, 186, 173, 133, 158, 141,
    135, 2, 49, 0, 186, 93, 206, 49, 82, 246, 94, 53, 202, 168, 10, 17,
    29, 122, 66, 221, 122, 160, 214, 192, 70, 1, 247, 129, 171, 237, 98, 79,
    69, 186, 132, 19, 99, 26, 145, 227, 246, 185, 125, 153, 10, 176, 59, 171,
    57, 42, 111, 99,
];


const CERT_L2_BIO: [u8; 1135] = [
    48, 130, 4, 107, 48, 130, 2, 83, 160, 3, 2, 1, 2, 2, 16, 21,
    137, 125, 129, 154, 109, 246, 44, 5, 115, 190, 26, 227, 47, 92, 54, 48,
    13, 6, 9, 42, 134, 72, 134, 247, 13, 1, 1, 11, 5, 0, 48, 63,
    49, 18, 48, 16, 6, 3, 85, 4, 12, 12, 9, 83, 116, 114, 111, 110,
    103, 66, 111, 120, 49, 41, 48, 39, 6, 3, 85, 4, 5, 19, 32, 102,
    51, 100, 102, 49, 57, 55, 98, 49, 52, 49, 99, 57, 51, 52, 55, 99,
    55, 100, 97, 102, 48, 51, 55, 53, 101, 99, 48, 102, 57, 52, 57, 48,
    30, 23, 13, 50, 48, 48, 57, 49, 49, 49, 56, 48, 50, 52, 52, 90,
    23, 13, 51, 48, 48, 57, 48, 57, 49, 56, 48, 50, 52, 52, 90, 48,
    63, 49, 18, 48, 16, 6, 3, 85, 4, 12, 12, 9, 83, 116, 114, 111,
    110, 103, 66, 111, 120, 49, 41, 48, 39, 6, 3, 85, 4, 5, 19, 32,
    48, 54, 56, 52, 50, 102, 56, 52, 98, 99, 98, 97, 100, 98, 100, 49,
    57, 54, 52, 48, 53, 98, 102, 100, 54, 97, 54, 51, 52, 57, 101, 98,
    48, 130, 1, 34, 48, 13, 6, 9, 42, 134, 72, 134, 247, 13, 1, 1,
    1, 5, 0, 3, 130, 1, 15, 0, 48, 130, 1, 10, 2, 130, 1, 1,
    0, 244, 160, 40, 135, 226, 181, 143, 175, 55, 219, 170, 87, 134, 169, 40,
    60, 84, 203, 87, 53, 31, 179, 99, 36, 209, 155, 226, 147, 108, 136, 184,
    199, 91, 10, 205, 93, 233, 146, 54, 102, 8, 29, 48, 187, 24, 101, 84,
    32, 239, 190, 101, 122, 147, 76, 216, 46, 56, 209, 139, 108, 173, 244, 203,
    23, 166, 236, 210, 60, 183, 228, 65, 239, 34, 246, 129, 139, 16, 214, 83,
    145, 226, 197, 69, 86, 87, 166, 117, 32, 23, 224, 103, 171, 154, 235, 223,
    12, 203, 10, 106, 205, 217, 137, 40, 201, 90, 230, 121, 12, 89, 201, 177,
    250, 100, 220, 49, 60, 113, 113, 30, 151, 61, 131, 175, 25, 210, 223, 76,
    189, 239, 112, 66, 233, 233, 158, 197, 223, 1, 174, 180, 134, 41, 22, 57,
    107, 37, 168, 125, 31, 87, 113, 98, 3, 103, 159, 52, 121, 9, 57, 34,
    3, 125, 84, 244, 91, 130, 180, 176, 234, 84, 211, 116, 49, 206, 34, 110,
    215, 143, 187, 217, 95, 112, 125, 232, 11, 100, 216, 230, 78, 34, 233, 150,
    11, 191, 16, 124, 221, 246, 138, 85, 92, 229, 252, 94, 103, 147, 51, 162,
    212, 31, 28, 83, 148, 187, 134, 101, 95, 109, 36, 254, 134, 250, 150, 145,
    63, 9, 23, 124, 212, 50, 131, 98, 123, 81, 213, 225, 236, 170, 48, 138,
    172, 45, 54, 62, 120, 191, 73, 103, 179, 103, 142, 233, 191, 84, 240, 55,
    241, 2, 3, 1, 0, 1, 163, 99, 48, 97, 48, 29, 6, 3, 85, 29,
    14, 4, 22, 4, 20, 66, 228, 203, 247, 99, 128, 36, 176, 219, 80, 89,
    196, 215, 177, 77, 252, 210, 138, 238, 5, 48, 31, 6, 3, 85, 29, 35,
    4, 24, 48, 22, 128, 20, 69, 44, 198, 55, 73, 63, 136, 173, 201, 138,
    221, 251, 73, 201, 75, 117, 174, 136, 24, 19, 48, 15, 6, 3, 85, 29,
    19, 1, 1, 255, 4, 5, 48, 3, 1, 1, 255, 48, 14, 6, 3, 85,
    29, 15, 1, 1, 255, 4, 4, 3, 2, 2, 4, 48, 13, 6, 9, 42,
    134, 72, 134, 247, 13, 1, 1, 11, 5, 0, 3, 130, 2, 1, 0, 48,
    24, 103, 249, 247, 118, 231, 74, 88, 88, 154, 109, 218, 32, 82, 37, 182,
    250, 33, 148, 252, 163, 27, 225, 34, 65, 27, 83, 75, 105, 196, 15, 135,
    134, 226, 181, 117, 100, 138, 19, 199, 146, 89, 17, 27, 0, 67, 20, 210,
    65, 34, 93, 207, 161, 115, 128, 92, 32, 252, 194, 208, 90, 233, 50, 248,
    43, 58, 98, 14, 39, 131, 136, 36, 185, 20, 231, 61, 162, 19, 248, 97,
    239, 59, 117, 122, 108, 222, 76, 122, 225, 149, 55, 194, 245, 251, 203, 76,
    37, 170, 70, 93, 112, 39, 66, 99, 153, 231, 220, 231, 164, 237, 215, 4,
    193, 177, 248, 212, 106, 227, 47, 1, 11, 5, 84, 237, 176, 205, 39, 224,
    195, 187, 199, 181, 11, 187, 126, 51, 14, 86, 26, 142, 155, 250, 108, 160,
    56, 161, 234, 95, 231, 52, 139, 40, 57, 115, 76, 109, 15, 240, 229, 24,
    62, 67, 206, 71, 144, 195, 87, 27, 23, 98, 130, 70, 46, 74, 204, 179,
    42, 124, 248, 46, 54, 75, 33, 126, 213, 214, 201, 100, 184, 158, 26, 107,
    125, 211, 157, 235, 254, 31, 2, 130, 129, 212, 163, 253, 114, 208, 204, 215,
    191, 171, 66, 165, 36, 136, 167, 38, 244, 113, 72, 225, 26, 20, 92, 37,
    39, 6, 90, 131, 239, 87, 50, 235, 93, 94, 241, 69, 155, 195, 95, 12,
    61, 111, 227, 96, 40, 3, 242, 141, 156, 108, 120, 220, 213, 33, 77, 250,
    226, 70, 80, 230, 139, 239, 54, 135, 24, 161, 154, 149, 212, 229, 225, 127,
    79, 138, 40, 113, 5, 27, 197, 170, 113, 160, 90, 176, 94, 160, 203, 206,
    93, 24, 53, 160, 143, 225, 177, 17, 97, 206, 185, 85, 149, 255, 64, 160,
    13, 106, 57, 171, 94, 232, 11, 86, 63, 195, 253, 124, 3, 215, 182, 18,
    68, 195, 213, 62, 189, 11, 179, 166, 37, 27, 47, 15, 163, 57, 247, 226,
    143, 57, 204, 70, 103, 254, 183, 146, 48, 199, 176, 241, 180, 210, 254, 116,
    52, 38, 129, 152, 75, 52, 75, 40, 189, 48, 250, 52, 199, 199, 1, 162,
    7, 156, 121, 173, 92, 27, 125, 229, 168, 72, 24, 45, 35, 118, 188, 194,
    7, 59, 65, 212, 186, 216, 113, 95, 40, 31, 182, 6, 158, 120, 166, 113,
    128, 230, 84, 237, 7, 187, 30, 148, 0, 0, 176, 167, 93, 157, 167, 114,
    84, 208, 132, 19, 213, 181, 204, 66, 249, 214, 216, 255, 63, 9, 21, 171,
    201, 183, 46, 76, 61, 233, 64, 94, 33, 159, 91, 52, 104, 148, 86, 200,
    65, 91, 10, 69, 237, 139, 215, 17, 128, 130, 208, 233, 33, 113, 164, 71,
    2, 144, 199, 96, 0, 69, 202, 46, 62, 179, 83, 79, 107, 17, 117, 63,
    148, 202, 228, 137, 100, 89, 37, 141, 126, 1, 42, 111, 144, 50, 144, 109,
    201, 14, 125, 233, 196, 163, 107, 209, 28, 64, 34, 23, 181, 107, 95,
];

static TEAM_ID: OnceCell<i32> = OnceCell::new();

const HINT: &str = "23a583c02d4895d460f9d3b40406607ce98312719d0bdeda0c2ea987f0638909f0e8e27403960be740a4ee6461d4780bbeb2843cef7799dba753ba298294e9bd909c3ea19253e95c92f4d6de81356ef352cfc4adde16f0a2de8fb128ccc170431ae83c6ddf6022965aabe2f75cae89edda2ef6169fe5f9839dd30d3b23e71ea254643d1bfab924194acbdb9c81c2ecfa0e0921514bfaf1b61d2ef774ea142e85";
const ZERO_IV: &[u8; 16] = &[0; 16];


// Accept anything that implements Display (e.g., &str, String)
fn bail<T: std::fmt::Display>(msg: T) -> ! {
    eprintln!("{}", msg);
    process::exit(1);
}


/// Read a file "submissions/<team_id>", decode non-empty lines from Base64 => Vec<DER bytes>
fn read_and_decode_file(team_id: i32) -> Vec<Vec<u8>> {
    let filepath = format!("submissions/{}.in", team_id);
    let path = Path::new(&filepath);
    let metadata = fs::metadata(path).unwrap_or_else(|_| bail(pmm!("Failed to get file metadata")));
    if metadata.len() > 10 * 1024 * 1024 {
        bail(pmm!("File exceeds 10 MB limit"));
    }
    let content = fs::read_to_string(path).unwrap_or_else(|_| bail(pmm!("Failed to read file")));
    content
        .lines()
        .enumerate()
        .filter_map(|(_, line)| {
            let trimmed = line.trim();
            if trimmed.is_empty() { None } else {
                Some(STANDARD.decode(trimmed).unwrap_or_else(|_| bail(pmm!("Invalid base64 on line"))))
            }
        })
        .collect()
}


#[derive(Debug, Clone)]
pub struct Certificate {
    pub cert_bytes: Vec<u8>,
    pub tbs: Vec<u8>,
    pub signature: Vec<u8>,
    pub issuer: Vec<u8>,
    pub subject: Vec<u8>,
    pub spki: Vec<u8>,
    pub sig_alg_oid: OID,
    pub sig_alg_params: Option<ASN1Block>,
    pub attestation_version: Option<u64>,
    pub security_level: u64,
    pub km_security_level: u64,
    pub user_auth_type: u64,
    pub auth_time: u64,
    pub osversion: u64,
    pub attestation_challenge: Vec<u8>,

    pub boot_key: Vec<u8>,
    pub device_locked: bool,
    pub verified_boot_state: u64,
    pub boot_hash: Vec<u8>,
}

/// Parse a single DER certificate and extract fields including signatureAlgorithm OID and parameters
fn parse_certificate(cert_bytes: &[u8]) -> Option<Certificate> {
    // Parse full certificate via ASN.1
    let cert_blocks = match from_der(cert_bytes) {
        Ok(blocks) => blocks,
        Err(_) => {
            eprintln!("{}", pmm!("Failed to parse certificate DER"));
            return None;
        }
    };
    let outer = match &cert_blocks[0] {
        ASN1Block::Sequence(_, items) => items,
        _ => {
            eprintln!("{}", pmm!("Certificate not SEQUENCE"));
            return None;
        }
    };
    // tbsCertificate is first element
    let tbs_block = if let ASN1Block::Sequence(_, _) = &outer[0] {
        outer[0].clone()
    } else {
        eprintln!("{}", pmm!("tbsCertificate not SEQUENCE"));
        return None;
    };

    let tbs = match to_der(&tbs_block) {
        Ok(bytes) => bytes,
        Err(_) => {
            eprintln!("{}", pmm!("Failed to DER-encode tbsCertificate"));
            return None;
        }
    };

    // signatureAlgorithm is second element
    let sig_alg_block = if let ASN1Block::Sequence(_, _) = &outer[1] {
        outer[1].clone()
    } else {
        eprintln!("{}", pmm!("signatureAlgorithm not SEQUENCE"));
        return None;
    };
    let alg_bytes = match to_der(&sig_alg_block) {
        Ok(b) => b,
        Err(_) => {
            eprintln!("{}", pmm!("Failed to DER-encode signatureAlgorithm"));
            return None;
        }
    };
    let alg_blocks = match from_der(&alg_bytes) {
        Ok(b) => b,
        Err(_) => {
            eprintln!("{}", pmm!("Failed parse signatureAlgorithm ASN.1"));
            return None;
        }
    };
    let ASN1Block::Sequence(_, alg_items) = &alg_blocks[0] else {
        eprintln!("{}", pmm!("Invalid signatureAlgorithm format"));
        return None;
    };
    let sig_alg_oid = match &alg_items[0] {
        ASN1Block::ObjectIdentifier(_, oid) => oid.clone(),
        _ => {
            eprintln!("{}", pmm!("algorithm OID not found"));
            return None;
        }
    };

    let sig_alg_params = alg_items.get(1).cloned();
    // signature BIT STRING is third element
    let signature = match &outer[2] {
        ASN1Block::BitString(_, _, data) => data.clone(),
        _ => {
            eprintln!("{}", pmm!("signature BIT STRING not found"));
            return None;
        }
    };

    // extract issuer, subject, spki from tbsCertificate
    let ASN1Block::Sequence(_, tbs_items) = &tbs_block else {
        eprintln!("{}", pmm!("Malformed tbsCertificate sequence"));
        return None;
    };
    let mut idx = 0;
    // Optional version [0]
    if let ASN1Block::Explicit(ASN1Class::ContextSpecific, _, tag, _) = &tbs_items[idx] {
        if tag == &BigUint::from(0u32) {
            idx += 1;
        }
    }
    // Skip serialNumber and inner signature
    idx += 2;
    // Issuer
    let issuer = match to_der(&tbs_items[idx]) {
        Ok(b) => b,
        Err(_) => {
            eprintln!("{}", pmm!("Failed DER-encode issuer"));
            return None;
        }
    };
    idx += 1;
    // Skip validity
    idx += 1;
    // Subject
    let subject = match to_der(&tbs_items[idx]) {
        Ok(b) => b,
        Err(_) => {
            eprintln!("{}", pmm!("Failed DER-encode subject"));
            return None;
        }
    };
    idx += 1;
    // SubjectPublicKeyInfo
    let spki = match to_der(&tbs_items[idx]) {
        Ok(b) => b,
        Err(_) => {
            eprintln!("{}", pmm!("Failed DER-encode spki"));
            return None;
        }
    };
    let cert_bytes = cert_bytes.to_vec();

    Some(Certificate {
        cert_bytes,
        tbs,
        signature,
        issuer,
        subject,
        spki,
        sig_alg_oid,
        sig_alg_params,
        attestation_version: None,
        security_level: 0,
        km_security_level: 0,
        user_auth_type: 0,
        auth_time: 0,
        osversion: 0,
        attestation_challenge: Vec::new(),

        boot_key: Vec::new(),
        device_locked: false,
        verified_boot_state: 7,
        boot_hash: Vec::new(),
    })
}


fn sigalg_is_sha256(cert: &X509Ref) -> bool {
    use openssl::nid::Nid;
    let actual_oid = match cert.signature_algorithm().object().nid() {
        nid if nid != Nid::UNDEF => nid,
        _ => return false,
    };
    matches!(
        actual_oid,
        Nid::SHA256WITHRSAENCRYPTION | Nid::ECDSA_WITH_SHA256
    )
}


use x509_parser::parse_x509_certificate;
use x509_parser::extensions::ParsedExtension;



fn check_key_usage(cert_bytes: &[u8], is_ca: bool) -> bool {
    // 1) Parse the certificate
    let (_, cert) = match parse_x509_certificate(cert_bytes) {
        Ok((rem, cert)) if rem.is_empty() => (rem, cert),
        Ok((_rem, _)) => {
            //println!("=== ERROR: Trailing data after X.509 cert: {} bytes", rem.len());
            return false;
        }
        Err(_err) => {
            //println!("=== ERROR: Failed to parse certificate: {:?}", err);
            return false;
        }
    };

    // 2) Extract basicConstraints
    let bc = cert
        .extensions()
        .iter()
        .find_map(|ext| match ext.parsed_extension() {
            ParsedExtension::BasicConstraints(bc) => Some(bc),
            _ => None,
        });

    // CA cert must have a BasicConstraints CA:TRUE, leaf must not
    if is_ca {
        match bc {
            Some(bc) if bc.ca => {}
            _ => {
                //println!("=== ERROR: CA cert missing BasicConstraints CA:TRUE");
                return false;
            }
        }
    } else if let Some(bc) = bc {
        if bc.ca {
            //println!("=== ERROR: Leaf cert has BasicConstraints CA:TRUE");
            return false;
        }
    }

    // 3) Extract keyUsage
    let ku = cert
        .extensions()
        .iter()
        .find_map(|ext| match ext.parsed_extension() {
            ParsedExtension::KeyUsage(ku) => Some(ku),
            _ => None,
        });

    // Leaf needs digitalSignature; CA needs keyCertSign
    if let Some(ku) = ku {
        if is_ca {
            if !ku.key_cert_sign() {
                //println!("=== ERROR: CA cert missing keyCertSign");
                return false;
            }
        } else {
            if !ku.digital_signature() {
                //println!("=== ERROR: Leaf cert missing digitalSignature");
                return false;
            }
        }
    } else {
        //println!("=== ERROR: Missing KeyUsage extension");
        return false;
    }

    true
}



fn verify_signature(cert_bytes: &[u8], tbs: &[u8], sig: &[u8], _is_parent: bool) -> (bool, bool){
    let cert = X509::from_der(cert_bytes);
    if cert.is_err() {
        return (false, false);
    }
    let cert = cert.unwrap();

    // Check the signature algorithm and key usage early

    if !sigalg_is_sha256(&cert){
        return (false, false);
    }


    // Get serial in hex and decimal
    let serial_bn = match cert.serial_number().to_bn() {
        Ok(bn) => bn,
        Err(_) => return (false, false),
    };
    let serial_bytes = serial_bn.to_vec();
    
    let serial_hex = hex::encode(&serial_bytes);
    //let serial_hex = "c360da616de6583ae816cdefdda66221";
    let serial_decimal = serial_bn.to_dec_str().unwrap();
    //let serial_decimal = "11918519357273683794";

    //println!("Certificate serial number: hex = 0x{}, decimal = {}", serial_hex, serial_decimal);

    // Check against REVOKED
    let mut is_revoked = false;
    if let Ok(val) = u128::from_str_radix(&serial_hex, 16) {
        if REVOKED.contains(&val) {
            is_revoked = true;
        }
    }
    if let Ok(val) = serial_decimal.parse::<u128>() {
        if REVOKED.contains(&val) {
            is_revoked = true;
        }
    }

    // Do the actual verification
    let pubkey = cert.public_key();
    if pubkey.is_err() {
        return (false, false);
    }
    let pubkey = pubkey.unwrap();

    let verifier_result = Verifier::new(MessageDigest::sha256(), &pubkey);
    if verifier_result.is_err() {
        return (false, is_revoked);
    }
    let mut verifier = verifier_result.unwrap();

    if verifier.update(tbs).is_err() {
        return (false, is_revoked);
    }

    let verify_result = verifier.verify(sig);
    if verify_result.is_err() || !verify_result.unwrap() {
        return (false, is_revoked);
    }

    (true, is_revoked)
}


fn subject_matches_tbs(cert_bytes: &[u8], tbs_bytes: &[u8]) -> bool {
    // --- 1) Parse the full certificate DER ---
    let cert_blocks = match from_der(cert_bytes) {
        Ok(b) => b,
        Err(_e) => {
            //println!("=== ERROR: parse full cert DER failed: {}", e);
            return false;
        }
    };

    // Extract the full TBSCertificate sequence (outer_seq[0])
    let full_tbs_seq = if let Some(ASN1Block::Sequence(_, outer_seq)) = cert_blocks.get(0) {
        if let Some(ASN1Block::Sequence(_, seq)) = outer_seq.get(0) {
            seq
        } else {
            //println!("=== ERROR: full cert missing TBSCertificate sequence");
            return false;
        }
    } else {
        //println!("=== ERROR: unexpected full cert structure");
        return false;
    };

    // --- 2) Parse the standalone TBSCertificate DER ---
    let tbs_blocks = match from_der(tbs_bytes) {
        Ok(b) => b,
        Err(_e) => {
            //println!("=== ERROR: parse TBSCertificate DER failed: {}", e);
            return false;
        }
    };

    // The first block is the TBSCertificate sequence
    let tbs_tbs_seq = if let Some(ASN1Block::Sequence(_, seq)) = tbs_blocks.get(0) {
        seq
    } else {
        //println!("=== ERROR: TBSCertificate missing sequence");
        return false;
    };

    // --- 3) Locate the subjectName field (6th element) ---
    let full_subj = if let Some(block) = full_tbs_seq.get(5) {
        block
    } else {
        //println!("=== ERROR: full TBSCertificate missing subjectName at position 5");
        return false;
    };
    let tbs_subj = if let Some(block) = tbs_tbs_seq.get(5) {
        block
    } else {
        //println!("=== ERROR: standalone TBSCertificate missing subjectName at position 5");
        return false;
    };

    // --- 4) Compare them ---
    if full_subj != tbs_subj {
        //println!("=== SUBJECT MISMATCH ===");
        //println!("Expected subjectName (from full cert): {:?}", full_subj);
        //println!("Actual   subjectName (tbs only)   : {:?}", tbs_subj);
        return false;
    }

    // All good
    true
}



pub fn validate_chain(certs: &[Certificate]) -> (bool, bool, bool) {
    for (i, cert) in certs.iter().enumerate() {
        let is_last = i == certs.len() - 1;
        let is_ca = !is_last;

        if !check_key_usage(&cert.cert_bytes, is_ca) {
            return (false, false, false);
        }
    }

    let root = &certs[0];
    let root_cert = X509::from_der(&root.cert_bytes);
    if root_cert.is_err() {
        return (false, false, false);
    }
    let root_cert = root_cert.unwrap();

    let root_pubkey = root_cert.public_key();
    if root_pubkey.is_err() {
        return (false, false, false);
    }
    let root_pubkey = root_pubkey.unwrap();

    let root_der = root_pubkey.public_key_to_der();
    if root_der.is_err() {
        return (false, false, false);
    }
    let root_der = root_der.unwrap();

    if !subject_matches_tbs(&root.cert_bytes, &root.tbs) {
        return (false, false, false);
    }


    let mut is_revoked;
    is_revoked = false;

    /*if !subject_matches_tbs(&root.cert_bytes, &root.tbs) {
        return (false, false, false);
    }*/
    let (ok, t) = verify_signature(&root.cert_bytes, &root.tbs, &root.signature, true);
    is_revoked = t || is_revoked;
    if !ok {
        return (false, is_revoked, false)
    }
    //println!("ROOT Verified");

    for window in certs.windows(2) {
        let parent = &window[0];
        let child = &window[1];

        if !subject_matches_tbs(&parent.cert_bytes, &parent.tbs) {
            return (false, false, false);
        }
        if !subject_matches_tbs(&child.cert_bytes, &child.tbs) {
            return (false, false, false);
        }
        if child.issuer != parent.subject {
            return (false, false, false)
        }

        /*if !subject_matches_tbs(&child.cert_bytes, &child.tbs) {
            return (false, false, false);
        }*/
        let (ok, t) = verify_signature(&parent.cert_bytes, &child.tbs, &child.signature, false);
        is_revoked = t || is_revoked;
        if !ok {
            return (false, is_revoked, false)
        }
        //println!("CHILD Verified");
    }

    //outputres(pstr);

    let mut is_correct_root = false;
    if root_der == EXPECTED_ROOT_PUBKEY_DER {
        is_correct_root = true
        //bail(pmm!("Root certificate does not match expected public key"));
    }

    (true, is_revoked, is_correct_root)
}





fn inspect_android_key_attestation_bio(mut cert: Certificate) -> Option<Certificate> {
    //println!("===== inspect_android_key_attestation_bio");
    let attest_oid = OID::new(vec![1u32.into(),3u32.into(),6u32.into(),1u32.into(),4u32.into(),1u32.into(),11129u32.into(),2u32.into(),1u32.into(),17u32.into()]);
    let blocks = match from_der(&cert.tbs) {
        Ok(b) => b,
        Err(_) => {
            eprintln!("{}", pmm!("Failed parse TBS"));
            return None;
        }
    };
    let seq = match &blocks[0] { ASN1Block::Sequence(_, v) => v, _ => return Some(cert) };

    if let Some(ASN1Block::Explicit(ASN1Class::ContextSpecific, _, _, inner)) = seq.iter().find(|b| matches!(b, ASN1Block::Explicit(ASN1Class::ContextSpecific, _, tag, _) if tag.to_u64().unwrap_or(0)==3)) {
        if let ASN1Block::Sequence(_, exts) = &**inner { for ext in exts {

            if let ASN1Block::Sequence(_, items) = ext {
                if let ASN1Block::ObjectIdentifier(_, oid) = &items[0] {
                    if oid == &attest_oid {
                        if let Some((_, ASN1Block::OctetString(_, data))) = items.iter().enumerate().find(|(_, itm)| matches!(itm, ASN1Block::OctetString(_, _))) {
                            let att = match from_der(data) {
                                Ok(v) => v,
                                Err(_) => {
                                    eprintln!("{}", pmm!("Failed parse attestation DER"));
                                    return None;
                                }
                            };
                            if let ASN1Block::Sequence(_, att_items) = &att[0] {
                                cert.attestation_challenge = match att_items.get(4) {
                                    Some(ASN1Block::OctetString(_, bytes)) => bytes.clone(),
                                    _ => Vec::new(),
                                };

                                cert.security_level = if let Some(ASN1Block::Unknown(_, _, _, _, bytes)) = att_items.get(1) {
                                    bytes.get(0).copied().unwrap_or(0) as u64
                                } else {
                                    0
                                };
                                cert.km_security_level = if let Some(ASN1Block::Unknown(_, _, _, _, bytes)) = att_items.get(3) {
                                    bytes.get(0).copied().unwrap_or(0) as u64
                                } else {
                                    0
                                };


                                if let Some(ASN1Block::Sequence(_, auth_list)) = att_items.get(7) {
                                    for (_, auth) in auth_list.iter().enumerate() {
                                        if let ASN1Block::Explicit(ASN1Class::ContextSpecific, _, tag_u, inner_u) = auth {
                                            //println!("Found ContextSpecific tag: {}", tag_u);
                                            if tag_u.to_u64().unwrap_or(0) == 504 {
                                                if let ASN1Block::Integer(_, u) = &**inner_u {
                                                    cert.user_auth_type = u.to_u64().unwrap_or(0);
                                                }
                                            }

                                            if tag_u.to_u64().unwrap_or(0) == 505 {
                                                if let ASN1Block::Integer(_, u) = &**inner_u {
                                                    cert.auth_time = u.to_u64().unwrap_or(0);
                                                    //println!(">> {:?}",cert.auth_time);
                                                }
                                            }

                                            if tag_u.to_u64().unwrap_or(0) == 509 {
                                                //println!(">>> {:?}", inner_u);
                                            }
                                            if tag_u.to_u64().unwrap_or(0) == 705 {
                                                if let ASN1Block::Integer(_, u) = &**inner_u {
                                                    let t1 = u.to_u64().unwrap_or(0);
                                                    cert.osversion = t1*1000000;
                                                    //println!(">> {:?}",t1);
                                                }
                                            }
                                            if tag_u.to_u64().unwrap_or(0) == 706 {
                                                if let ASN1Block::Integer(_, u) = &**inner_u {
                                                    let t1 = u.to_u64().unwrap_or(0);
                                                    cert.osversion += t1;
                                                }
                                            }

                                            if tag_u.to_u64().unwrap_or(0) == (689+cert.auth_time) { //704
                                                // inner_u is a Box<ASN1Block>, so &**inner_u gives &ASN1Block
                                                match &**inner_u {
                                                    ASN1Block::Sequence(_, items) if items.len() == 4 => {
                                                        // 0: verifiedBootKey OCTET_STRING
                                                        if let ASN1Block::OctetString(_, key) = &items[0] {
                                                            cert.boot_key = key.clone();
                                                            //println!("rootOfTrust.verifiedBootKey: {}", hex::encode(key));
                                                        } else {
                                                            //println!("rootOfTrust.verifiedBootKey: unexpected {:?}", items[0]);
                                                        }
                                                        // 1: deviceLocked BOOLEAN
                                                        if let ASN1Block::Boolean(_, locked) = &items[1] {
                                                            cert.device_locked = *locked;
                                                            //println!("rootOfTrust.deviceLocked: {}", locked);
                                                        } else {
                                                            //println!("rootOfTrust.deviceLocked: unexpected {:?}", items[1]);
                                                        }
                                                        let verified_boot_state: u64 = match &items[2] {
                                                            ASN1Block::Unknown(_, _, _, _, data) => { //0 is verified
                                                                num_bigint::BigUint::from_bytes_be(data)
                                                                    .to_u64()
                                                                    .unwrap_or(77)
                                                            },
                                                            _ => 78
                                                        };
                                                        cert.verified_boot_state = verified_boot_state;
                                                        //println!("rootOfTrust.verifiedBootState: {}", verified_boot_state);
                                                        // 3: verifiedBootHash OCTET_STRING
                                                        if let ASN1Block::OctetString(_, hash) = &items[3] {
                                                            cert.boot_hash = hash.clone();
                                                            //println!("rootOfTrust.verifiedBootHash: {}", hex::encode(hash));
                                                        } else {
                                                            //println!("rootOfTrust.verifiedBootHash: unexpected {:?}", items[3]);
                                                        }
                                                    }
                                                    ASN1Block::Sequence(_, _items) => {
                                                        /*println!(
                                                            "rootOfTrust sequence has {} items (expected 4): {:?}",
                                                            items.len(),
                                                            items
                                                        );*/
                                                    }
                                                    _other => {
                                                        //println!("rootOfTrust is not a SEQUENCE: {:?}", other);
                                                    }
                                                }
                                            }
                                        }

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }}
    }
    Some(cert)
}


fn inspect_android_key_attestation_pc(mut cert: Certificate) -> Option<Certificate> {
    //println!("===== inspect_android_key_attestation_pc");
    let attest_oid = OID::new(vec![1u32.into(),3u32.into(),6u32.into(),1u32.into(),4u32.into(),1u32.into(),11129u32.into(),2u32.into(),1u32.into(),17u32.into()]);
    let blocks = match from_der(&cert.tbs) {
        Ok(b) => b,
        Err(_) => {
            eprintln!("{}", pmm!("Failed parse TBS"));
            return None;
        }
    };
    let seq = match &blocks[0] { ASN1Block::Sequence(_, v) => v, _ => return Some(cert) };

    if let Some(ASN1Block::Explicit(ASN1Class::ContextSpecific, _, _, inner)) = seq.iter().find(|b| matches!(b, ASN1Block::Explicit(ASN1Class::ContextSpecific, _, tag, _) if tag.to_u64().unwrap_or(0)==3)) {
        if let ASN1Block::Sequence(_, exts) = &**inner { for ext in exts {

            if let ASN1Block::Sequence(_, items) = ext {
                if let ASN1Block::ObjectIdentifier(_, oid) = &items[0] {
                    if oid == &attest_oid {
                        if let Some((_, ASN1Block::OctetString(_, data))) = items.iter().enumerate().find(|(_, itm)| matches!(itm, ASN1Block::OctetString(_, _))) {
                            let att = match from_der(data) {
                                Ok(v) => v,
                                Err(_) => {
                                    eprintln!("{}", pmm!("Failed parse attestation DER"));
                                    return None;
                                }
                            };
                            if let ASN1Block::Sequence(_, att_items) = &att[0] {
                                cert.attestation_challenge = match att_items.get(4) {
                                    Some(ASN1Block::OctetString(_, bytes)) => bytes.clone(),
                                    _ => Vec::new(),
                                };

                                cert.security_level = if let Some(ASN1Block::Unknown(_, _, _, _, bytes)) = att_items.get(1) {
                                    bytes.get(0).copied().unwrap_or(0) as u64
                                } else {
                                    0
                                };
                                cert.km_security_level = if let Some(ASN1Block::Unknown(_, _, _, _, bytes)) = att_items.get(3) {
                                    bytes.get(0).copied().unwrap_or(0) as u64
                                } else {
                                    0
                                };

                                /*
                                let bytes = &cert.attestation_challenge;
                                // Option 1: build a single String and print it
                                let hex_list = bytes
                                    .iter()
                                    .map(|b| format!("0x{:02X}", b))
                                    .collect::<Vec<_>>()
                                    .join(", ");
                                println!("attestation_challenge = [{}]", hex_list);
                                */


                                if let Some(ASN1Block::Sequence(_, auth_list)) = att_items.get(7) {
                                    for (_, auth) in auth_list.iter().enumerate() {
                                        if let ASN1Block::Explicit(ASN1Class::ContextSpecific, _, tag_u, inner_u) = auth {
                                            //println!("Found ContextSpecific tag: {}", tag_u);
                                            if tag_u.to_u64().unwrap_or(0) == 504 {
                                                if let ASN1Block::Integer(_, u) = &**inner_u {
                                                    cert.user_auth_type = u.to_u64().unwrap_or(0);
                                                }
                                            }

/*
                                            if tag_u.to_u64().unwrap_or(0) == 505 {
                                                if let ASN1Block::Integer(_, u) = &**inner_u {
                                                    cert.auth_time = u.to_u64().unwrap_or(0);
                                                    //println!(">> {:?}",cert.auth_time);
                                                }
                                            }
*/

//this is a hack, it should not be auth_time
//508 is trustedConfirmationRequired
                                            if tag_u.to_u64().unwrap_or(0) == 508 {
                                                cert.auth_time += 1;
                                            }

//this is a hack, it should not be auth_time
//509 is unlockedDeviceRequired
                                            if tag_u.to_u64().unwrap_or(0) == 509 {
                                                cert.auth_time += 1;
                                            }

                                            if tag_u.to_u64().unwrap_or(0) == 705 {
                                                if let ASN1Block::Integer(_, u) = &**inner_u {
                                                    let t1 = u.to_u64().unwrap_or(0);
                                                    cert.osversion = t1*1000000;
                                                    //println!(">> {:?}",t1);
                                                }
                                            }
                                            if tag_u.to_u64().unwrap_or(0) == 706 {
                                                if let ASN1Block::Integer(_, u) = &**inner_u {
                                                    let t1 = u.to_u64().unwrap_or(0);
                                                    cert.osversion += t1;
                                                }
                                            }

                                            if tag_u.to_u64().unwrap_or(0) == (704) {
                                                // inner_u is a Box<ASN1Block>, so &**inner_u gives &ASN1Block
                                                match &**inner_u {
                                                    ASN1Block::Sequence(_, items) if items.len() == 4 => {
                                                        // 0: verifiedBootKey OCTET_STRING
                                                        if let ASN1Block::OctetString(_, key) = &items[0] {
                                                            cert.boot_key = key.clone();
                                                            //println!("rootOfTrust.verifiedBootKey: {}", hex::encode(key));
                                                        } else {
                                                            //println!("rootOfTrust.verifiedBootKey: unexpected {:?}", items[0]);
                                                        }
                                                        // 1: deviceLocked BOOLEAN
                                                        if let ASN1Block::Boolean(_, locked) = &items[1] {
                                                            cert.device_locked = *locked;
                                                            //println!("rootOfTrust.deviceLocked: {}", locked);
                                                        } else {
                                                            //println!("rootOfTrust.deviceLocked: unexpected {:?}", items[1]);
                                                        }
                                                        let verified_boot_state: u64 = match &items[2] {
                                                            ASN1Block::Unknown(_, _, _, _, data) => { //0 is verified
                                                                num_bigint::BigUint::from_bytes_be(data)
                                                                    .to_u64()
                                                                    .unwrap_or(77)
                                                            },
                                                            _ => 78
                                                        };
                                                        cert.verified_boot_state = verified_boot_state;
                                                        //println!("rootOfTrust.verifiedBootState: {}", verified_boot_state);
                                                        // 3: verifiedBootHash OCTET_STRING
                                                        if let ASN1Block::OctetString(_, hash) = &items[3] {
                                                            cert.boot_hash = hash.clone();
                                                            //println!("rootOfTrust.verifiedBootHash: {}", hex::encode(hash));
                                                        } else {
                                                            //println!("rootOfTrust.verifiedBootHash: unexpected {:?}", items[3]);
                                                        }
                                                    }
                                                    ASN1Block::Sequence(_, _items) => {
                                                        /*println!(
                                                            "rootOfTrust sequence has {} items (expected 4): {:?}",
                                                            items.len(),
                                                            items
                                                        );*/
                                                    }
                                                    _other => {
                                                        //println!("rootOfTrust is not a SEQUENCE: {:?}", other);
                                                    }
                                                }
                                            }
                                        }

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }}
    }
    Some(cert)
}


fn outputres(s: &str) {
    let team_id = TEAM_ID.get().unwrap_or_else(|| bail(pmm!("TEAM_ID not set")));
    let filename = format!("results/{}.out", team_id);

    let mut file = OpenOptions::new()
        .create(true)
        .append(true)
        .open(&filename)
        .unwrap_or_else(|_| bail(pmm!("Failed to open output file")));

    if let Err(_) = writeln!(file, "{}", s) {
        bail(pmm!("Failed to write to output file {}: {}"));
    }
}


fn hmac_rnumber(rnumber: i32) -> String {
    // rnumber should be between 1 and 2000
    let secret = fs::read("hmacsecret.key")
        .unwrap_or_else(|_| bail(pmm!("Failed to read key")));
    let msg = rnumber.to_string();

    type HmacSha256 = Hmac<Sha256>;
    let mut mac = HmacSha256::new_from_slice(&secret)
        .unwrap_or_else(|_| bail(pmm!("Invalid key: {e}")));
    mac.update(msg.as_bytes());
    let result = mac.finalize();
    let code_bytes = result.into_bytes();

    hex::encode(code_bytes)
}


/// Verifies an RSA-PSS signature (allowing SHA-256) over `tbs`
/// using the public key from a DER-encoded certificate.
///
/// Returns `true` if verification succeeds with either digest, `false` otherwise.
pub fn verify_signature_bio(cert_bytes: &[u8], tbs: &[u8], sig: &[u8]) -> bool {
    // 1) Parse the certificate
    let cert = match X509::from_der(cert_bytes) {
        Ok(c) => c,
        Err(_) => return false,
    };
    // 2) Extract the public key
    let pubkey = match cert.public_key() {
        Ok(pk) => pk,
        Err(_) => return false,
    };
    // 3) Try verifying with SHA-256 and then SHA-512
    for &md in &[MessageDigest::sha256()] {
        // a) New verifier for this digest
        let mut verifier = match Verifier::new(md, &pubkey) {
            Ok(v) => v,
            Err(_) => continue,
        };
        // b) Set RSA-PSS padding
        if verifier.set_rsa_padding(Padding::PKCS1_PSS).is_err() { continue; }
        // c) Use salt length = digest length
        if verifier.set_rsa_pss_saltlen(RsaPssSaltlen::DIGEST_LENGTH).is_err() { continue; }
        // d) Feed in the data
        if verifier.update(tbs).is_err() { continue; }
        // e) Check the signature
        if verifier.verify(sig).unwrap_or(false) {
            return true;
        }
    }
    // None of the digests worked
    false
}


pub fn verify_signature_pc(cert_bytes: &[u8], msg: &[u8], sig: &[u8]) -> bool {
    // 1) Parse the certificate
    let cert = match X509::from_der(cert_bytes) {
        Ok(c)  => c,
        Err(_) => return false,
    };

    if let Ok(_alg) = cert.signature_algorithm().object().nid().long_name() {
        //println!("Signature algorithm: {}", alg);
    } else {
        //println!("Could not determine signature algorithm");
    }

    // 2) Extract its public key
    let pubkey = match cert.public_key() {
        Ok(k)  => k,
        Err(_) => return false,
    };

    // 3) Create a verifier for SHA-256 / ECDSA
    let mut verifier = match Verifier::new(MessageDigest::sha256(), &pubkey) {
        Ok(v)  => v,
        Err(_) => return false,
    };

    // 4) Feed in the message
    if verifier.update(msg).is_err() {
        return false;
    }

    // 5) Verify the signature (DER-encoded ECDSA)
    let res = verifier.verify(sig).unwrap_or(false);


    res
}


fn check_cbor(v: &ValueC, expected: &[u8]) -> bool {
    match v {
        ValueC::Map(map) => {
            if map.len() != 2 {
                //println!("CBOR map does not have exactly 2 entries");
                return false;
            }

            // Convert expected bytes to UPPERCASE hex string and hex-encoded bytes
            let expected_hex_str1 = expected.iter()
                .map(|b| format!("{:02X}", b))
                .collect::<String>();
            let expected_hex_bytes1 = expected_hex_str1.as_bytes();
            let expected_hex_str2 = expected.iter()
                .map(|b| format!("{:02x}", b))
                .collect::<String>();
            let expected_hex_bytes2 = expected_hex_str2.as_bytes();

            let mut found_extra = false;
            let mut found_prompt = false;

            for (k, val) in map {
                match k {
                    ValueC::Text(s) if s == "extra" => {
                        match val {
                            ValueC::Bytes(b) => {
                                //println!("🔍 extra:");
                                //println!("  expected (hex bytes): {:02X?}", expected_hex_bytes1);
                                //println!("  expected (hex bytes): {:02X?}", expected_hex_bytes2);
                                //println!("  actual   (hex bytes): {:02X?}", b);
                                if b == expected_hex_bytes1 || b == expected_hex_bytes2 {
                                    found_extra = true;
                                } else {
                                    //println!("'extra' does not match expected hex bytes");
                                    return false;
                                }
                            }
                            _ => {
                                //println!("'extra' is not a CBOR byte string");
                                return false;
                            }
                        }
                    }
                    ValueC::Text(s) if s == "prompt" => {
                        match val {
                            ValueC::Text(t) => {
                                //println!("🔍 prompt:");
                                //println!("  expected (string): {}", expected_hex_str1);
                                //println!("  expected (string): {}", expected_hex_str2);
                                //println!("  actual   (string): {}", t);
                                if *t == expected_hex_str1 || *t == expected_hex_str2 {
                                    found_prompt = true;
                                } else {
                                    //println!("'prompt' does not match expected hex string");
                                    return false;
                                }
                            }
                            _ => {
                                //println!("'prompt' is not a CBOR text string");
                                return false;
                            }
                        }
                    }
                    _ => {
                        //println!("Unexpected key in CBOR map: {:?}", k);
                        return false;
                    }
                }
            }

            if found_extra && found_prompt {
                //println!("CBOR structure is valid");
                true
            } else {
                //println!("CBOR structure missing required keys");
                false
            }
        }
        _ => {
            //println!("Top-level CBOR is not a map");
            false
        }
    }
}


pub fn is_valid_boot_integrity(cert: &Certificate) -> bool {

    //println!("{} {}", cert.verified_boot_state, cert.device_locked);
    if cert.verified_boot_state == 0 && cert.device_locked {
        if VALID_BOOT_KEYS.iter().any(|&key| cert.boot_key.as_slice() == key){
            if VALID_BOOT_HASHES.iter().any(|&hash| cert.boot_hash.as_slice() == hash){
                return true
            }
        }
    }
    false
}


fn sleep_random() {
    let mut rng = rand::thread_rng();
    let ms = rng.gen_range(500..=3_000);
    thread::sleep(Duration::from_millis(ms));
}


/// Service account structure matching the JSON file
#[derive(Deserialize)]
struct ServiceAccount { client_email: String, private_key: String, token_uri: String, }

/// JWT claims for OAuth2 JWT-bearer flow
#[derive(Serialize)]
struct Claims<'a> { iss: &'a str, scope: &'a str, aud: &'a str, exp: usize, iat: usize, }

/// Synchronously verifies an Android Play Integrity token and returns the raw JSON response as a String, or bails on error
pub fn verify_integrity_token_sync(integrity_token: &str) -> String {
    if integrity_token.trim().is_empty() { bail(pmm!("Missing integrityToken")); }

    if integrity_token.len() > 1024{
        bail(pmm!("Integrity token for di too long"));
    }
    sleep_random();

    let sa_data = fs::read_to_string("pi.json").unwrap_or_else(|_| bail(pmm!("Failed to read SA file")));
    let sa: ServiceAccount = serde_json::from_str(&sa_data).unwrap_or_else(|_| bail(pmm!("Invalid SA JSON")));

    let now = SystemTime::now().duration_since(UNIX_EPOCH).unwrap_or_else(|_| bail(pmm!("System time error")));
    let iat = now.as_secs() as usize;
    let exp = iat + 3600;
    let claims = Claims { iss: &sa.client_email, scope: "https://www.googleapis.com/auth/playintegrity", aud: &sa.token_uri, iat, exp };

    let jwt = encode(&Header::new(Algorithm::RS256), &claims, &EncodingKey::from_rsa_pem(sa.private_key.as_bytes()).unwrap_or_else(|_| bail(pmm!("JWT encoding error")))).unwrap_or_else(|_| bail(pmm!("JWT encode error")));

    let client = Client::new();
    let token_json: serde_json::Value = client.post(&sa.token_uri)
        .form(&[("grant_type", "urn:ietf:params:oauth:grant-type:jwt-bearer"), ("assertion", &jwt)])
        .send().unwrap_or_else(|_| bail(pmm!("Token request failed")))
        .json().unwrap_or_else(|_| bail(pmm!("Token parse failed")));
    let access_token = token_json.get("access_token").and_then(|v| v.as_str()).unwrap_or_else(|| bail(pmm!("No access_token in response")));

    let url = "https://playintegrity.googleapis.com/v1/com.pizza.integritycheckjava:decodeIntegrityToken";
    let api_resp = client.post(url)
        .bearer_auth(access_token)
        .json(&json!({ "integrityToken": integrity_token }))
        .send()
        .unwrap_or_else(|_| bail(pmm!("API request failed")));

    // Capture status before consuming response body
    let _status = api_resp.status();
    let raw_json = api_resp.text().unwrap_or_else(|_| bail(pmm!("Reading response failed")));

    //if !status.is_success() { bail(pmm!("Verification failed")); }
    raw_json
}


pub fn inspect_token_payload(json_str: &str, expected_challenge: &[u8]) {
    // 1) Parse whole JSON
    let root: Value = match serde_json::from_str(json_str) {
        Ok(v) => v,
        Err(_) => bail(pmm!("Failed to parse JSON")),
    };
    outputres("di0");

    // Navigate into tokenPayloadExternal
    let ext = root.get("tokenPayloadExternal");

    // Condition set 1: requestDetails + appIntegrity
    let mut ok1 = false;
    if let Some(ext) = ext {
        if let Some(req) = ext.get("requestDetails") {
            ok1 = req.get("requestPackageName").and_then(Value::as_str)
                == Some("com.pizza.integritycheckjava");
        }
        if ok1 {
            if let Some(app) = ext.get("appIntegrity") {
                ok1 &= app.get("packageName").and_then(Value::as_str)
                    == Some("com.pizza.integritycheckjava");
                ok1 &= app.get("certificateSha256Digest")
                    .and_then(Value::as_array)
                    .and_then(|arr| arr.get(0).and_then(Value::as_str))
                    == Some("4qklVGyquQ26FnzLLIaNW8-ziSiZbuyL2hXk0spKNyg");
                //println!("---> version code {:?}", app.get("versionCode").and_then(Value::as_str));
                ok1 &= app.get("versionCode").and_then(Value::as_str) == Some("5");
            } else {
                ok1 = false;
            }
        }
    }
    if ok1 {
        outputres("di2");
    }

    // Condition set 2: deviceIntegrity
    let mut ok2 = false;
    if let Some(ext) = ext {
        if let Some(dev) = ext.get("deviceIntegrity") {
            if let Some(arr) = dev.get("deviceRecognitionVerdict").and_then(Value::as_array) {
                ok2 = arr.len() == 2
                    && arr.get(0).and_then(Value::as_str) == Some("MEETS_DEVICE_INTEGRITY")
                    && arr.get(1).and_then(Value::as_str) == Some("MEETS_STRONG_INTEGRITY");
            }
        }
    }
    if ok2 {
        outputres("di1");
    }

    let mut ok3 = false;
    if let Some(ext) = ext {
        if let Some(req) = ext.get("requestDetails") {
            if let Some(hash_str) = req.get("requestHash").and_then(Value::as_str) {
                if let Ok(hash_bytes) = hex::decode(hash_str) {
                    ok3 = hash_bytes == expected_challenge;
                }
            }
        }
    }
    if ok3 {
        outputres("di3");
    }

    // Combined condition
    if ok1 && ok2 && ok3{
        outputres("di4");
    }
}


pub fn check_hint_password() {
    // 1) Prompt
    println!("Enter the password: ");
    io::stdout().flush().unwrap_or_default();
    let mut input = String::new();
    if io::stdin().read_line(&mut input).is_err() {
        process::exit(2);
    }
    let input = input.trim_end_matches(&['\r', '\n'][..]);

    if input.len() > 100                // length limit
        || !input.starts_with("dHNhZDUyMw")  // required prefix
        || input.len() != 16           // exact length
        || !input.chars().all(|c| c.is_ascii_alphabetic()) // letters only
    {
        process::exit(2);
    }
    let mut hasher = Sha512::new();
    hasher.update(input.as_bytes());
    let digest = hasher.finalize();
    if &digest[..6] != b"\x04\xb8\x8ekx\x10" {
        process::exit(2);
    }

    // decode hex ciphertext
    let ct = hex::decode(HINT).unwrap_or_else(|_| process::exit(2));
    // build cipher and decrypt
    let cipher = Aes128Cbc::new_from_slices(input.as_bytes(), ZERO_IV).unwrap_or_else(|_| process::exit(2));
    let pt = cipher.decrypt_vec(&ct).unwrap_or_else(|_| process::exit(2));
    // print plaintext
    let secret = String::from_utf8(pt).unwrap_or_else(|_| process::exit(2));
    println!("{}", secret);
    process::exit(5);
}


fn strong_cert_match_pc(a: Vec<u8>, b: Vec<u8>) -> bool {
    a.as_slice() == &CERT_ROOT && b.as_slice() == &CERT_L2_PC
}


fn strong_cert_match_bio(a: Vec<u8>, b: Vec<u8>) -> bool {
    a.as_slice() == &CERT_ROOT && b.as_slice() == &CERT_L2_BIO
}



fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 3 && args.len() != 4 { bail("Usage: ./attestedfun <round_id:int> <team_id:int>"); }

    let team_id: i32 = args[2].parse().unwrap_or_else(|_| bail(pmm!("team_id not int")));
    TEAM_ID.set(team_id).unwrap_or_else(|_| bail(pmm!("TEAM_ID already set")));
    let round_id: i32 = args[1].parse().unwrap_or_else(|_| bail(pmm!("round_id not int")));

    let args: Vec<String> = env::args().collect();
    let hint_requested = args.get(3).map(|s| s == "--hint").unwrap_or(false);
    if hint_requested {
        check_hint_password();
    }

    let hex_code = hmac_rnumber(round_id);
    let expected_challenge: Vec<u8> = match hex::decode(&hex_code) {
        Ok(b) => b,
        Err(_) => Vec::new(),  // or handle the decode error however you like
    };

    let b64inputs = read_and_decode_file(team_id);
    //println!("Found {} certificates", b64inputs.len());
    if b64inputs.len() != 12 { bail(pmm!("Need 12 b64inputs")); }
    outputres("b1");


    let maybe_certs = (
        parse_certificate(&b64inputs[0]),
        parse_certificate(&b64inputs[1]),
        parse_certificate(&b64inputs[2]),
        parse_certificate(&b64inputs[3]),
    );

    if let (Some(c0), Some(c1), Some(c2), Some(c3)) = maybe_certs {
        let biocerts: Vec<Certificate> = vec![c0, c1, c2, c3];

        if strong_cert_match_bio(b64inputs[0].clone(), b64inputs[2].clone()) {
            outputres("biochain0");
        }

        let bio_cert_bytes: &[u8] = &biocerts[3].cert_bytes;
        let tbs: &[u8] = &expected_challenge;
        let bio_sig_bytes: Vec<u8> = b64inputs[4].clone();
        let vs = verify_signature_bio(bio_cert_bytes, tbs, bio_sig_bytes.as_slice());
        if vs {
            outputres("biosig1");
        }
        let (correct, revoked_used, is_correct_root) = validate_chain(&biocerts);
        if correct{
            outputres("biochain1");
            if !revoked_used{
                outputres("biochain2");
            }
            if is_correct_root{
                outputres("biochain3");
            }
        }

        let bio_parsed_cert = inspect_android_key_attestation_bio(biocerts[3].clone());
        if bio_parsed_cert.is_none() {
            eprintln!("{}", pmm!("Failed to inspect biometric certificate"));
        }else{
            let bio_parsed_cert = bio_parsed_cert.unwrap();
            //print_cert_info(&bio_parsed_cert);
            if bio_parsed_cert.user_auth_type == 2 && bio_parsed_cert.security_level == 2 && bio_parsed_cert.km_security_level == 2 {
                outputres("biocert1");
            }
            if bio_parsed_cert.auth_time  >= 5 && bio_parsed_cert.auth_time  <= 20{
                outputres("biocert2");
            }
            if bio_parsed_cert.osversion  == 150000202411 {
                outputres("biocert3");
            }
            //println!("found att challenge: {}", hex::encode(&bio_parsed_cert.attestation_challenge));
            if bio_parsed_cert.attestation_challenge == expected_challenge {
                outputres("biochall1");
            }
            if is_valid_boot_integrity(&bio_parsed_cert){
                outputres("biobstate1");
            }
        }
    }


    let maybe_certs = (
        parse_certificate(&b64inputs[5]),
        parse_certificate(&b64inputs[6]),
        parse_certificate(&b64inputs[7]),
        parse_certificate(&b64inputs[8]),
    );

    if let (Some(c0), Some(c1), Some(c2), Some(c3)) = maybe_certs {
        let pccerts: Vec<Certificate> = vec![c0, c1, c2, c3];

        if strong_cert_match_pc(b64inputs[5].clone(), b64inputs[7].clone()) {
            outputres("pcchain0");
        }


        let pc_cert_bytes: &[u8] = &pccerts[3].cert_bytes;
        let tbs: &[u8] = &b64inputs[10];
        let pc_sig_bytes: Vec<u8> = b64inputs[9].clone();
        let vs = verify_signature_pc(pc_cert_bytes, tbs, pc_sig_bytes.as_slice());
        //println!("======= pc signature: {}", vs);
        if vs {
            outputres("pcsig1");
        }


        if let Ok(val) = serde_cbor::from_slice::<ValueC>(&tbs) {
            //println!("------> CBOR");
            let res = check_cbor(&val, &expected_challenge);
            if res {
                outputres("pcsig2");
            }
        }else{
            //println!("------> wrong CBOR");
        }

        let (correct, revoked_used, is_correct_root) = validate_chain(&pccerts);
        if correct{
            outputres("pcchain1");
            if !revoked_used{
                outputres("pcchain2");
            }
            if is_correct_root{
                outputres("pcchain3");
            }
        }

        let pc_parsed_cert = inspect_android_key_attestation_pc(pccerts[3].clone());
        if pc_parsed_cert.is_none() {
            eprintln!("{}", pmm!("Failed to inspect biometric certificate"));
        }else{
            let pc_parsed_cert = pc_parsed_cert.unwrap();
            //print_cert_info(&pc_parsed_cert);
            if pc_parsed_cert.user_auth_type == 2 && pc_parsed_cert.security_level == 2 && pc_parsed_cert.km_security_level == 2 {
                outputres("pccert1");
            }
            //this is a hack, it should not be auth_time, this is 1 if trustedConfirmationRequired plus 1 if unlockedDeviceRequired
            //println!("trustedConfirmationRequired: {:?}", pc_parsed_cert.auth_time);
            if pc_parsed_cert.auth_time  == 2{
                outputres("pccert2");
            }
            if pc_parsed_cert.osversion  == 150000202411 {
                outputres("pccert3");
            }
            //println!("found att challenge: {}", hex::encode(&pc_parsed_cert.attestation_challenge));
            if pc_parsed_cert.attestation_challenge == expected_challenge {
                outputres("pcchall1");
            }
            if is_valid_boot_integrity(&pc_parsed_cert){
                outputres("pcbstate1");
            }
        }
    }

    if let Some(data) = b64inputs.get(11) {
        let datax: Vec<u8> = data.iter().map(|b| b ^ 0xE1).collect();
        let token_str = String::from_utf8_lossy(&datax);
        let response_json = verify_integrity_token_sync(&token_str);
        //println!("{}", response_json);
        inspect_token_payload(&response_json, &expected_challenge);
    }


}
