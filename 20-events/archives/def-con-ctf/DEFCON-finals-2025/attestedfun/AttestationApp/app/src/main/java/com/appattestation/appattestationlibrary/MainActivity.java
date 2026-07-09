package com.appattestation.appattestationlibrary;

import androidx.fragment.app.FragmentActivity;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.security.ConfirmationPrompt;
import android.util.Log;

import com.AppAttestLib.AttestationController;
import com.AppAttestLib.BioConfirmMain;

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.CookieHandler;
import java.net.CookieManager;

public class MainActivity extends FragmentActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        if (!ConfirmationPrompt.isSupported(this.getApplicationContext())){
            Log.i("mobisys","Not supported in Main");
        }
        AttestationController myAC=new AttestationController();
        String certificateChainString = myAC.registerBioConfirm(this,hexStringToByteArray("b7ac87d605d4045d7dd65c1001f2c9d6fb328b7537270680574b6db114694f53"));
        //certificateChainString to be sent to server
        Log.i("CertificateChain",certificateChainString);
        try {
            OutputStreamWriter outputStreamWriter = new OutputStreamWriter(this.openFileOutput("certificateChain.txt", Context.MODE_PRIVATE));
            outputStreamWriter.write(certificateChainString);
            outputStreamWriter.close();
        }
        catch (IOException e) {
            Log.e("Exception", "File write failed: " + e.toString());
        }

        Intent callAttestation = new Intent(this, BioConfirmMain.class);
        callAttestation.putExtra("authParams",new String(hexStringToByteArray("b7ac87d605d4045d7dd65c1001f2c9d6fb328b7537270680574b6db114694f53")));
        this.startActivityForResult(callAttestation,2);
    }



    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == 2) {
            if(resultCode == Activity.RESULT_OK){

                String signatures=data.getStringExtra("Signature");
                Log.i("signatures",signatures);
                //signatures to be sent to server
            }

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

}
