package discovery.client.callbacks;

import discovery.client.api.ApiStatus;

/**
 * Created by Home on 24/4/2560.
 */
public interface ApiStatusCallback
{
    public void execute(ApiStatus status);
}