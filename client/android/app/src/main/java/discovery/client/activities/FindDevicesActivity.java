package discovery.client.activities;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import java.util.Hashtable;

import discovery.client.R;
import discovery.client.presenters.FindDevicesPresenter;
import discovery.client.presenters.FindDevicesPresenterListener;
import discovery.client.presenters.Screen;

public class FindDevicesActivity extends DiscoveryActivity
{
    private final FindDevicesPresenter presenter = new FindDevicesPresenter();
    private Button findButton;

    @Override
    protected int getLayoutResId() { return R.layout.activity_find_devices;}

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        this.findButton = (Button)findViewById(R.id.findButton);

        this.presenter.setListener(new PresenterListener());

        this.findButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View v) {
                presenter.findDevices();
            }
        });
    }


    private final class PresenterListener extends FindDevicesPresenterListener
    {
        @Override
        public void requestViewState(Hashtable<String, Object> values)
        {
        }

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
            if (show == true)
                showSpinner();
            else
                dismissSpinner();
        }
    }
}
