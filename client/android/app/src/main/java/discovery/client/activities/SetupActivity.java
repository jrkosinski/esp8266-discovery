package discovery.client.activities;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import java.util.Hashtable;

import discovery.client.R;
import discovery.client.presenters.Screen;
import discovery.client.presenters.SetupPresenter;
import discovery.client.presenters.SetupPresenterListener;

public class SetupActivity extends DiscoveryActivity
{
    private final SetupPresenter presenter = new SetupPresenter();

    @Override
    protected int getLayoutResId() { return R.layout.activity_setup;}

    private Button setupButton;
    private EditText wifiSsidText;
    private EditText wifiPasswdText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        this.setupButton = (Button)findViewById(R.id.setupButton);
        this.wifiSsidText = (EditText)findViewById(R.id.wifiSsidText);
        this.wifiPasswdText = (EditText)findViewById(R.id.wifiPasswdText);

        this.presenter.setListener(new PresenterListener());

        this.setupButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View v) {
                presenter.doSetup();
            }
        });
    }

    @Override
    protected void onStart()
    {
        super.onStart();
        this.presenter.start();
    }


    private class PresenterListener extends SetupPresenterListener
    {
        @Override
        public void showErrorMessage(String message)
        {
        }

        @Override
        public void redirect(Screen screen)
        {
            navigateTo(screen);
        }

        @Override
        public void showProgress(boolean show)
        {
            if (show)
                showSpinner();
            else
                dismissSpinner();
        }

        @Override
        public void requestViewState(Hashtable<String, Object> values)
        {
            values.put("context", getApplicationContext());
            values.put("ssid", wifiSsidText.getText().toString());
            values.put("passwd", wifiPasswdText.getText().toString());
        }
    }
}
