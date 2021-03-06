package discovery.client.tasks;

import android.content.Context;
import android.os.AsyncTask;

import discovery.client.Global;
import discovery.client.api.ApiStatus;
import discovery.client.api.UdpBroadcast;

/**
 * Created by Home on 25/4/2560.
 */
public class UdpBroadcastTask extends AsyncTask<Context, Object, ApiStatus>
{
    protected ApiStatus doInBackground(Context... args)
    {
        UdpBroadcast udp = new UdpBroadcast(args[0]);
        udp.sendBroadcast("hello" );

        return Global.device.status;
    }

    protected void onProgressUpdate(Object... progress)
    {
    }

    protected void onPostExecute(ApiStatus result)
    {
    }
}
