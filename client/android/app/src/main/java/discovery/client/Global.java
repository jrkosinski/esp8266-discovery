package discovery.client;

import java.net.InetAddress;
import java.net.UnknownHostException;

import discovery.client.api.*;
import discovery.client.model.Device;

/**
 * Created by Home on 24/4/2560.
 */
public final class Global
{
    public final static IApiInterface apiInterface = new  ApiInterface();
    public final static Device device = new Device();

    public static void initializeDevice(String ip, int port)
    {
        try {
            if (ip != null) {
                device.ipAddress = InetAddress.getByName(ip);
            }
        }
        catch (UnknownHostException e){}

        device.tcpPort = port;
        device.status = ApiStatus.Unknown;
    }
}


