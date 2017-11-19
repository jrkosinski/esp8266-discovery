package discovery.client.api;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Home on 19/11/2560.
 */
public class ConnectAP
{
    private Context context;
    WifiManager mainWifi;
    WifiReceiver receiverWifi;

    public void tryConnect(){
        mainWifi = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);

        receiverWifi = new WifiReceiver();
        context.registerReceiver(receiverWifi, new IntentFilter(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION));

        if(mainWifi.isWifiEnabled()==false)
        {
            mainWifi.setWifiEnabled(true);
        }
    }

    class WifiReceiver extends BroadcastReceiver
    {
        ArrayList<String> connections=new ArrayList<String>();

        public void onReceive(Context c, Intent intent)
        {
            connections.clear();

            StringBuilder sb = new StringBuilder();
            List<ScanResult> wifiList;
            wifiList = mainWifi.getScanResults();
            for(int i = 0; i < wifiList.size(); i++)
            {
                connections.add(wifiList.get(i).SSID);
            }
        }
    }
}
