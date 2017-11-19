package discovery.client.presenters;

import android.content.Context;

import discovery.client.Global;
import discovery.client.api.ApiStatus;
import discovery.client.callbacks.ApiStatusCallback;
import discovery.client.storage.LocalStorage;
import discovery.client.tasks.UdpBroadcastTask;

/**
 * Created by Home on 25/4/2560.
 */
public class MainPresenter extends PresenterBase
{
    @Override
    public void start()
    {
        super.start();

        this.listener.showProgress(true);

        //if we have a saved IP, attempt to get status of that...
        if (Global.device.ipAddress != null)
        {
            this.getApiStatus();
        }
        else
        {
            requestViewState();
            new FindDevicesTask().execute(getContext());
        }
    }

    private final void getApiStatus()
    {
        Global.apiInterface.getStatusAsync(new ApiStatusCallback() {
            @Override
            public void execute(ApiStatus status) {
                listener.showProgress(false);

                switch (status) {
                    case NotFound:
                        listener.redirect(Screen.Discover);
                        break;
                    case NotSetUp:
                        listener.redirect(Screen.Setup);
                        break;
                    case Running:
                        listener.redirect(Screen.Scenes);
                        break;
                }
            }
        });
    }

    private Context getContext()
    {
        Context out = null;

        Object o = this.getFormValue("context");
        if (o != null)
            out = (Context) o;

        return out;
    }

    private final class FindDevicesTask extends UdpBroadcastTask
    {
        @Override
        protected void onPostExecute(ApiStatus result)
        {
            switch(result)
            {
                case NotFound:
                    listener.redirect(Screen.Discover);
                    break;
                default:
                    LocalStorage.saveDevice(Global.device);
                    getApiStatus();
                    break;
            }
        }
    }
}
