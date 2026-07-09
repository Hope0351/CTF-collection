package com.AppAttestLib;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;
import androidx.biometric.BiometricManager;
import androidx.biometric.BiometricPrompt;

import android.app.Activity;
import android.app.KeyguardManager;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.provider.Settings;
import android.security.ConfirmationCallback;
import android.security.ConfirmationPrompt;
import android.security.keystore.KeyGenParameterSpec;
import android.security.keystore.KeyProperties;
import android.util.Log;
import android.widget.Toast;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.security.KeyStore;
import java.security.PrivateKey;
import java.util.Arrays;
import java.util.Objects;
import java.util.concurrent.Executor;

import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.Signature;
import java.util.UUID;

import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;


public class BioConfirmMain extends AppCompatActivity{

    private Executor executor;
    private BiometricPrompt biometricPrompt;
    private BiometricPrompt.PromptInfo promptInfo;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Intent incomingIntent = getIntent();
        final String[] confirmationmessage = new String[1];
        String paymentDetails= incomingIntent.getStringExtra("authParams");
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
        try {
            String retMsg=paymentDetails;
            final String prompttext = retMsg.substring(5,retMsg.length());
            final String nonce = retMsg.substring(0,5);
            try {
                KeyStore ks = KeyStore.getInstance("AndroidKeyStore");
                ks.load(null);

                KeyStore.Entry entry = ks.getEntry(this.getString(this.getApplicationInfo().labelRes)+"bioFun", null);
                final PrivateKey bioPrivateKey = ((KeyStore.PrivateKeyEntry) entry).getPrivateKey();
                entry = ks.getEntry(this.getString(this.getApplicationInfo().labelRes)+"confFun", null);
                final PrivateKey confPrivateKey = ((KeyStore.PrivateKeyEntry) entry).getPrivateKey();
                executor = ContextCompat.getMainExecutor(this);

                biometricPrompt = new BiometricPrompt(BioConfirmMain.this,
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
                            Signature biosig= result.getCryptoObject().getSignature();
                            //biosig.update((prompttext+nonce).getBytes());
                            String tbS="b7ac87d605d4045d7dd65c1001f2c9d6fb328b7537270680574b6db114694f53";

                            biosig.update(new byte[] {
                                    (byte) 0xB7, (byte) 0xAC, (byte) 0x87, (byte) 0xD6,
                                    (byte) 0x05, (byte) 0xD4, (byte) 0x04, (byte) 0x5D,
                                    (byte) 0x7D, (byte) 0xD6, (byte) 0x5C, (byte) 0x10,
                                    (byte) 0x01, (byte) 0xF2, (byte) 0xC9, (byte) 0xD6,
                                    (byte) 0xFB, (byte) 0x32, (byte) 0x8B, (byte) 0x75,
                                    (byte) 0x37, (byte) 0x27, (byte) 0x06, (byte) 0x80,
                                    (byte) 0x57, (byte) 0x4B, (byte) 0x6D, (byte) 0xB1,
                                    (byte) 0x14, (byte) 0x69, (byte) 0x4F, (byte) 0x53
                            });
                            byte[] signedPromptNonce=biosig.sign();
                            Log.i("biosig",new String(signedPromptNonce, StandardCharsets.UTF_8));
                            try {
                                OutputStreamWriter outputStreamWriter = new OutputStreamWriter(BioConfirmMain.super.getApplicationContext().openFileOutput("bioSignature", Context.MODE_PRIVATE));
                                outputStreamWriter.write(new String(signedPromptNonce, StandardCharsets.ISO_8859_1));
                                outputStreamWriter.close();
                            }
                            catch (IOException e) {
                                Log.e("Exception", "File write failed: " + e.toString());
                            }
                            writeBytesToFile(BioConfirmMain.this.getApplicationContext(),signedPromptNonce,"bioSignature");
                            byte[] extraData= new byte[(prompttext+nonce).getBytes().length + signedPromptNonce.length];
                            System.arraycopy((prompttext+nonce).getBytes(),0,extraData,0,(prompttext+nonce).getBytes().length);
                            System.arraycopy(signedPromptNonce,0,extraData,(prompttext+nonce).getBytes().length,signedPromptNonce.length);
//                            ConfirmationPrompt cp = new ConfirmationPrompt.Builder(BioConfirmMain.super.getApplicationContext()).setPromptText(prompttext).setExtraData(extraData).build();
                            if (!ConfirmationPrompt.isSupported(BioConfirmMain.super.getApplicationContext())){
                                Log.i("mobisys","Not supported in BioConfirmMain");
                            }
                            ConfirmationPrompt cp = new ConfirmationPrompt.Builder(BioConfirmMain.super.getApplicationContext()).setPromptText("b7ac87d605d4045d7dd65c1001f2c9d6fb328b7537270680574b6db114694f53").setExtraData("b7ac87d605d4045d7dd65c1001f2c9d6fb328b7537270680574b6db114694f53".getBytes()).build();

                            try {
                                cp.presentPrompt(getMainExecutor(), new ConfirmationCallback() {

                                    @Override
                                    public void onConfirmed(byte[] dataThatWasConfirmed) {
                                        super.onConfirmed(dataThatWasConfirmed);
                                        try {
                                            Signature sig = Signature.getInstance("SHA256WithRSA/PSS");//change to 512
                                            sig.initSign(confPrivateKey);
                                            sig.update(dataThatWasConfirmed);
                                            byte[] signedData = sig.sign();
                                            Log.i("confsig",new String(signedData, StandardCharsets.UTF_8));
                                            try {
                                                OutputStreamWriter outputStreamWriter = new OutputStreamWriter(BioConfirmMain.super.getApplicationContext().openFileOutput("confSignature", Context.MODE_PRIVATE));
                                                outputStreamWriter.write(new String(signedData, StandardCharsets.ISO_8859_1));
                                                outputStreamWriter.close();
                                            }
                                            catch (IOException e) {
                                                Log.e("Exception", "File write failed: " + e.toString());
                                            }
                                            confirmationmessage[0] = new String(dataThatWasConfirmed) + "<==>"+new String(signedData);
                                            Intent returnIntent = new Intent();
                                            returnIntent.putExtra("Signature",confirmationmessage[0]);
                                            setResult(Activity.RESULT_OK,returnIntent);
                                            finish();
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
                        } catch (Exception e) {
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
                        .setDescription(prompttext)
                        .setSubtitle("Use your biometric credential")
                        .setNegativeButtonText("Cancel")
                        .setConfirmationRequired(true)
                        .build();


                Signature signature = Signature.getInstance("SHA256withRSA/PSS");
                signature.initSign(bioPrivateKey);
                biometricPrompt.authenticate(promptInfo, new BiometricPrompt.CryptoObject(signature));
            } catch (Exception e){
                e.printStackTrace();
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static byte[] hexStringToByteArray(String s) {
        int len = s.length();
        byte[] data = new byte[len/2];

        for(int i = 0; i < len; i+=2){
            data[i/2] = (byte) ((Character.digit(s.charAt(i), 16) << 4) + Character.digit(s.charAt(i+1), 16));
        }

        return data;
    }

    public static void writeBytesToFile(Context context, byte[] data, String filename) throws IOException {
        File file = new File(context.getFilesDir(), filename);
        try (FileOutputStream out = new FileOutputStream(file)) {
            out.write(data);
        }
    }
}
