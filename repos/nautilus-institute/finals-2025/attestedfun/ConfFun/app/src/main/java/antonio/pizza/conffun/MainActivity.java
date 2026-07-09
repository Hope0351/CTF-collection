package antonio.pizza.conffun;


import static android.security.keystore.KeyProperties.AUTH_BIOMETRIC_STRONG;

import android.app.Activity;
import android.app.KeyguardManager;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;

import androidx.annotation.NonNull;
import androidx.annotation.OpenForTesting;
import android.os.Build;
import android.os.Bundle;
import android.security.ConfirmationCallback;
import android.security.ConfirmationPrompt;
import android.security.keystore.KeyGenParameterSpec;
import android.security.keystore.KeyProperties;
import android.util.Log;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.biometric.BiometricManager;
import androidx.biometric.BiometricPrompt;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.nio.charset.StandardCharsets;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.KeyStore;
import java.security.PrivateKey;
import java.security.Signature;
import java.security.cert.Certificate;
import java.security.cert.X509Certificate;
import java.util.Base64;
import java.util.concurrent.Executor;

public class MainActivity extends AppCompatActivity {

    private String intentData;

    protected KeyPair ConfirmKP;

    private Executor executor;

    private BiometricPrompt biometricPrompt;
    private BiometricPrompt.PromptInfo promptInfo;




    private byte[] challenge;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
        try {
            Intent intent = getIntent();
            String data = intent.getStringExtra("extra_data");
            if (data == null) {
                data = "No data received";
            }
            Log.i("mobisys", data);
            intentData = data;

            challenge = hexToBytes(intentData);

//            challenge = new byte[]{
//                    (byte) 0xB7, (byte) 0xAC, (byte) 0x87, (byte) 0xD6,
//                    (byte) 0x05, (byte) 0xD4, (byte) 0x04, (byte) 0x5D,
//                    (byte) 0x7D, (byte) 0xD6, (byte) 0x5C, (byte) 0x10,
//                    (byte) 0x01, (byte) 0xF2, (byte) 0xC9, (byte) 0xD6,
//                    (byte) 0xFB, (byte) 0x32, (byte) 0x8B, (byte) 0x75,
//                    (byte) 0x37, (byte) 0x27, (byte) 0x06, (byte) 0x80,
//                    (byte) 0x57, (byte) 0x4B, (byte) 0x6D, (byte) 0xB1,
//                    (byte) 0x14, (byte) 0x69, (byte) 0x4F, (byte) 0x53
//            };
            KeyGenParameterSpec.Builder KGPS = new KeyGenParameterSpec.Builder(this.getApplicationContext().getString(getApplicationContext().getApplicationInfo().labelRes)+"confFun", KeyProperties.PURPOSE_SIGN | KeyProperties.PURPOSE_VERIFY);

            KGPS.setAttestationChallenge(challenge);
            KGPS.setDigests(KeyProperties.DIGEST_SHA256, KeyProperties.DIGEST_SHA512);
            if (this.getApplicationContext().getPackageManager().hasSystemFeature(PackageManager.FEATURE_STRONGBOX_KEYSTORE) && Build.VERSION.SDK_INT >= 28) {
                KGPS.setIsStrongBoxBacked(true);
            };
            KeyguardManager KgM = (KeyguardManager) this.getApplicationContext().getSystemService(Context.KEYGUARD_SERVICE);
            if (KgM.isDeviceSecure()) {
                KGPS.setUserAuthenticationRequired(true);
                KGPS.setUserAuthenticationParameters(0,AUTH_BIOMETRIC_STRONG);
            }
            if (Build.VERSION.SDK_INT >= 28) {
                KGPS.setUserConfirmationRequired(true);

            }

            if (Build.VERSION.SDK_INT >= 28) {
                KGPS.setUnlockedDeviceRequired(true);
            }
//            KGPS.setSignaturePaddings(KeyProperties.SIGNATURE_PADDING_RSA_PSS);
            KeyGenParameterSpec kgps = KGPS.build();
            KeyPairGenerator KPG = KeyPairGenerator.getInstance("EC", "AndroidKeyStore");
            KPG.initialize(kgps);
            ConfirmKP = KPG.generateKeyPair();
            writeBytesToFile(this.getApplicationContext(),ConfirmKP.getPublic().getEncoded(),"confPubKey");

            KeyStore ks = KeyStore.getInstance("AndroidKeyStore");
            ks.load(null);

            Certificate[] cc = ks.getCertificateChain(this.getApplicationContext().getString(this.getApplicationContext().getApplicationInfo().labelRes)+"confFun");
            int length = cc.length;
            for (int i=0;i<length;i++)
            {

                X509Certificate xCert;
                xCert = (X509Certificate) cc[length-i-1];
                String cString;
                if(Build.VERSION.SDK_INT >= 26) {
                    cString = Base64.getEncoder().encodeToString(xCert.getEncoded());
                } else {
                    cString = android.util.Base64.encodeToString(xCert.getEncoded(),android.util.Base64.NO_WRAP);
                }
                try {

                    OutputStreamWriter outputStreamWriter = new OutputStreamWriter(this.getApplicationContext().openFileOutput("confCert"+String.valueOf(i+1), Context.MODE_PRIVATE));
                    outputStreamWriter.write(cString);
                    outputStreamWriter.close();
                }
                catch (IOException e) {
                    Log.e("Exception", "File write failed: " + e.toString());
                }


            }





        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        try {
            KeyStore ks = KeyStore.getInstance("AndroidKeyStore");
            ks.load(null);
            KeyStore.Entry entry = ks.getEntry(this.getString(this.getApplicationInfo().labelRes)+"confFun", null);
            final PrivateKey confPrivateKey = ((KeyStore.PrivateKeyEntry) entry).getPrivateKey();

            if (!ConfirmationPrompt.isSupported(getApplicationContext())){
                Log.i("mobisys","Not supported in ConfirmMain");
            }









            executor = ContextCompat.getMainExecutor(this);

            biometricPrompt = new BiometricPrompt(this,
                    executor, new BiometricPrompt.AuthenticationCallback() {
                @Override
                public void onAuthenticationError(int errorCode,
                                                  @NonNull CharSequence errString) {
                    super.onAuthenticationError(errorCode, errString);
                    Toast.makeText(getApplicationContext(),
                                    "Authentication error: " + errString, Toast.LENGTH_SHORT)
                            .show();
                }

                @Override
                public void onAuthenticationSucceeded(@NonNull BiometricPrompt.AuthenticationResult result) {
                    super.onAuthenticationSucceeded(result);
                    Signature sig =result.getCryptoObject().getSignature();
                    Log.i("mobbisys",sig.getAlgorithm());
                    ConfirmationPrompt cp = new ConfirmationPrompt.Builder(getApplicationContext()).setPromptText(intentData).setExtraData(intentData.getBytes()).build();

                    try {
                        cp.presentPrompt(getMainExecutor(), new ConfirmationCallback() {

                            @Override
                            public void onConfirmed(byte[] dataThatWasConfirmed) {
                                super.onConfirmed(dataThatWasConfirmed);
                                try {

                                    writeBytesToFile(getApplicationContext(),dataThatWasConfirmed, "confCBOR");

//                                    Signature sig = Signature.getInstance("SHA256WithRSA/PSS");//change to 512
//                                    sig.initSign(confPrivateKey);
                                    sig.update(dataThatWasConfirmed);
                                    byte[] signedData = sig.sign();
                                    Log.i("confsig",new String(signedData, StandardCharsets.UTF_8));
                                    Log.i("sig_hex", bytesToHex(signedData));
                                    Log.i("cbor_hex", bytesToHex(dataThatWasConfirmed));
                                    Signature verifier = Signature.getInstance("SHA256withECDSA");
                                    verifier.initVerify(ConfirmKP.getPublic());
                                    verifier.update(dataThatWasConfirmed);

                                    // Verify the signature
                                    if(verifier.verify(signedData)) {
                                        Log.i("Verification Results:", "True");
                                    } else {
                                        Log.i("Verification Results:", "False");
                                    }

                                    writeBytesToFile(getApplicationContext(),signedData,"confSignature");


                                } catch (Exception e) {
                                    e.printStackTrace();
                                }
                            }

                            @Override
                            public void onDismissed() {
                                super.onDismissed();
                                Log.i("SARA", "DISMISSED");
                            }

                            @Override
                            public void onCanceled() {
                                super.onCanceled();
                                Log.i("SARA", "CANCELLED");
                            }

                            @Override
                            public void onError(Throwable e) {
                                super.onError(e);
                            }

                        });
                    } catch(Exception e){
                        e.printStackTrace();
                    }

                }

                @Override
                public void onAuthenticationFailed() {
                    super.onAuthenticationFailed();
                }
            });

            promptInfo = new BiometricPrompt.PromptInfo.Builder()
                    .setTitle("Authorization Required")
                    .setDescription(new String(challenge))
                    .setSubtitle("Use your biometric credential")
                    .setNegativeButtonText("Cancel")
                    .setConfirmationRequired(true)
                    .build();

            Signature signature = Signature.getInstance("SHA256withECDSA");
            signature.initSign(confPrivateKey);
            biometricPrompt.authenticate(promptInfo, new BiometricPrompt.CryptoObject(signature));
        } catch (Exception e) {
            e.printStackTrace();
        }





    }

    public static void writeBytesToFile(Context context, byte[] data, String filename) throws IOException {
        File file = new File(context.getFilesDir(), filename);
        try (FileOutputStream out = new FileOutputStream(file)) {
            out.write(data);
        }
    }

    public static byte[] hexToBytes(String hex) {
        int len = hex.length();
        byte[] data = new byte[len / 2];
        for (int i = 0; i < len; i += 2) {
            data[i / 2] = (byte) ((Character.digit(hex.charAt(i), 16) << 4)
                    + Character.digit(hex.charAt(i + 1), 16));
        }
        return data;
    }

    public static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02X", b));
        }
        return sb.toString();
    }
}