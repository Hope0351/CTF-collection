package antonio.pizza.biometricfun;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;

import androidx.annotation.NonNull;
import androidx.annotation.OpenForTesting;
import androidx.biometric.BiometricManager;
import androidx.biometric.BiometricPrompt;
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

    protected KeyPair BioKP;

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

            KeyGenParameterSpec.Builder BioKGPS = new KeyGenParameterSpec.Builder(this.getApplicationContext().getString(this.getApplicationContext().getApplicationInfo().labelRes) + "bioFun", KeyProperties.PURPOSE_SIGN | KeyProperties.PURPOSE_VERIFY);
            BioKGPS.setAttestationChallenge(challenge);
            BioKGPS.setDigests(KeyProperties.DIGEST_SHA256, KeyProperties.DIGEST_SHA512);
            if (this.getApplicationContext().getPackageManager().hasSystemFeature(PackageManager.FEATURE_STRONGBOX_KEYSTORE) && Build.VERSION.SDK_INT >= 28) {
                BioKGPS.setIsStrongBoxBacked(true);
            }
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
                BioKGPS.setUserAuthenticationRequired(true);
                BioKGPS.setUserAuthenticationParameters(15, KeyProperties.AUTH_BIOMETRIC_STRONG);
                Log.i("mobisys", "using new api");
            } else {
                BioKGPS.setUserAuthenticationRequired(true);
                BioKGPS.setUserAuthenticationValidityDurationSeconds(-1);
            }
            if (Build.VERSION.SDK_INT >= 28) {
                BioKGPS.setUnlockedDeviceRequired(true);
            }
            BioKGPS.setSignaturePaddings(KeyProperties.SIGNATURE_PADDING_RSA_PSS);
            KeyGenParameterSpec biokgps = BioKGPS.build();
            KeyPairGenerator BioKPG = KeyPairGenerator.getInstance("RSA", "AndroidKeyStore");
            BioKPG.initialize(biokgps);
            BioKP = BioKPG.generateKeyPair();
            writeBytesToFile(this.getApplicationContext(), BioKP.getPublic().getEncoded(), "bioPubKey");


            KeyStore ks = KeyStore.getInstance("AndroidKeyStore");
            ks.load(null);

            Certificate[] cc = ks.getCertificateChain(this.getApplicationContext().getString(this.getApplicationContext().getApplicationInfo().labelRes)+"bioFun");
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

                    OutputStreamWriter outputStreamWriter = new OutputStreamWriter(this.getApplicationContext().openFileOutput("bioCert"+String.valueOf(i+1), Context.MODE_PRIVATE));
                    outputStreamWriter.write(cString);
                    outputStreamWriter.close();
                }
                catch (IOException e) {
                    Log.e("Exception", "File write failed: " + e.toString());
                }


            }

            BiometricManager biometricManager = BiometricManager.from(this);
            switch (biometricManager.canAuthenticate()) {
                case BiometricManager.BIOMETRIC_SUCCESS:
                    Log.d("SARA", "App can authenticate using biometrics.");
                    break;
                case BiometricManager.BIOMETRIC_ERROR_NO_HARDWARE:
                    Log.e("SARA", "No biometric features available on this device.");
                    break;
                case BiometricManager.BIOMETRIC_ERROR_HW_UNAVAILABLE:
                    Log.e("SARA", "Biometric features are currently unavailable.");
                    break;
                case BiometricManager.BIOMETRIC_ERROR_NONE_ENROLLED:
                    Log.e("SARA", "Biometric not enrolled");
                    break;
            }





            promptInfo = new BiometricPrompt.PromptInfo.Builder()
                    .setTitle("Authorization Required")
                    .setDescription(new String(challenge))
                    .setSubtitle("Use your biometric credential")
                    .setNegativeButtonText("Cancel")
                    .setConfirmationRequired(true)
                    .build();




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
            KeyStore.Entry entry = ks.getEntry(this.getString(this.getApplicationInfo().labelRes)+"bioFun", null);
            final PrivateKey bioPrivateKey = ((KeyStore.PrivateKeyEntry) entry).getPrivateKey();

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
                public void onAuthenticationSucceeded(
                        @NonNull BiometricPrompt.AuthenticationResult result) {
                    super.onAuthenticationSucceeded(result);
                    try {

                        Signature signature = Signature.getInstance("SHA256withRSA/PSS");
                        signature.initSign(bioPrivateKey);
                        Signature biosig= signature;


                        biosig.update(challenge);
                        byte[] signedPromptNonce=biosig.sign();
                        Log.i("biosig",new String(signedPromptNonce, StandardCharsets.UTF_8));
                        try {
                            OutputStreamWriter outputStreamWriter = new OutputStreamWriter(getApplicationContext().openFileOutput("bioSignature", Context.MODE_PRIVATE));
                            outputStreamWriter.write(new String(signedPromptNonce, StandardCharsets.ISO_8859_1));
                            outputStreamWriter.close();
                        }
                        catch (IOException e) {
                            Log.e("Exception", "File write failed: " + e.toString());
                        }
                        writeBytesToFile(getApplicationContext(),signedPromptNonce,"bioSignature");










                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }

                @Override
                public void onAuthenticationFailed() {
                    super.onAuthenticationFailed();
                }
            });


            biometricPrompt.authenticate(promptInfo);




//            biometricPrompt.authenticate(promptInfo, new BiometricPrompt.CryptoObject(signature));
        } catch (Exception e) {
            throw new RuntimeException(e);
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
}