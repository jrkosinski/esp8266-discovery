package discovery.client.storage;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;

import java.net.InetAddress;
import java.net.UnknownHostException;

import discovery.client.Global;
import discovery.client.model.Device;


/**
 * Created by UserZ150 on 25/4/2560.
 */
public class LocalStorage
{
    private static SharedPreferences sharedPreferences;
    private static SharedPreferences.Editor editor;

    private static final String IpAddressKey = "ipAAddress";

    private static String ipAddress;
    private static int portNumber;

    public static String getIpAddress()
    {
        if (sharedPreferences != null) {
            if (ipAddress == null)
                ipAddress = sharedPreferences.getString(IpAddressKey, "");
        }

        return ipAddress;
    }

    public static void setIpAddress(String value)
    {
        ipAddress = value;
        if (editor != null) {
            editor.putString(IpAddressKey, value);
            editor.commit();
        }
    }

    public static void setIpAddress(InetAddress value)
    {
        if (value != null)
            setIpAddress(value.toString());
        else
            setIpAddress("");
    }

    /*
    Clears the database.
     */
    public static void clear()
    {
        setIpAddress("");
    }

    public static void restoreDevice(Device device)
    {
        String ip = getIpAddress();
        if (ip != null && ip.length() > 0) {
            try {
                device.ipAddress = InetAddress.getByName(ip);
            }
            catch (UnknownHostException e){}
        }

        Log.d("Restoring device", Global.device.toString());
    }

    public static void saveDevice(Device device)
    {
        setIpAddress(device.ipAddress);
        Log.d("Saving device", Global.device.toString());
    }

    public static void initialize(Context context)
    {
        sharedPreferences = context.getSharedPreferences("discoveryStorage", Activity.MODE_PRIVATE);
        editor = sharedPreferences.edit();
    }
}
