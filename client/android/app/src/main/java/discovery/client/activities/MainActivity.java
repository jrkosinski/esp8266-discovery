package discovery.client.activities;

import android.os.Bundle;

import java.util.Hashtable;

import discovery.client.R;
import discovery.client.presenters.MainPresenter;
import discovery.client.presenters.MainPresenterListener;
import discovery.client.presenters.Screen;

public class MainActivity extends DiscoveryActivity
{
    private final MainPresenter presenter = new MainPresenter();

    @Override
    protected int getLayoutResId() { return R.layout.activity_main;}

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        this.presenter.setListener(new PresenterListener());
    }

    @Override
    protected void onStart()
    {
        super.onStart();
        this.presenter.start();
    }


    private final class PresenterListener extends MainPresenterListener
    {
        @Override
        public void requestViewState(Hashtable<String, Object> values) {
            values.put("context", getApplicationContext());
        }

        @Override
        public void showErrorMessage(String message) {
        }

        @Override
        public void redirect(Screen screen) {
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
