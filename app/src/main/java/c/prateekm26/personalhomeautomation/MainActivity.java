package c.prateekm26.personalhomeautomation;

import android.annotation.SuppressLint;
import android.support.v7.app.AppCompatActivity;
import android.content.Intent;
import android.os.Bundle;
import android.speech.RecognizerIntent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Locale;

import static android.view.View.*;

public class MainActivity extends AppCompatActivity {
    private TextView txvResult;
   // private Text txt;
    Button btnOn,btnOff,btnSpeak;
    @SuppressLint("WrongViewCast")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //txt=findViewById(R.id.IP_Address);
        txvResult = (TextView) findViewById(R.id.txvResult);
        btnOn=findViewById(R.id.Relay_on);
        btnOff=findViewById(R.id.Relay_off);
        btnOn.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View view) {
                String command="light on";
                 String ip_address="192.168.137.1";
                client(ip_address,command);
//ClientSocket socket =new ClientSocket(ip_address,command);
            }
        });
        btnOff.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View view) {
                String command="light off";
                String ip_address="192.168.137.1";
                client(ip_address,command);
                //ClientSocket socket =new ClientSocket(ip_address,command);
            }
        });
    }
    private void client(String ip_address,String command){
        Socket s;

        {
            try {
                while(true) {
                    s = new Socket("192.168.43.236", 80);
                    PrintStream ps = new PrintStream(s.getOutputStream());
                    ps.println(command);
                    ps.flush();
                    s.close();
                }

            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    public void getSpeechInput(View view) {

        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());

        if (intent.resolveActivity(getPackageManager()) != null) {
            startActivityForResult(intent, 10);
        } else {
            Toast.makeText(this, "Your Device Don't Support Speech Input", Toast.LENGTH_SHORT).show();
        }
    }
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        switch (requestCode) {
            case 10:
                if (resultCode == RESULT_OK && data != null) {
                    ArrayList<String> result = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
                    txvResult.setText(result.get(0));

                }
                break;
        }
    }
}
