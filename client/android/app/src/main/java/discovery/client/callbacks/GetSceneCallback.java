package discovery.client.callbacks;

import discovery.client.api.ApiStatus;

/**
 * Created by Home on 25/4/2560.
 */
public interface GetSceneCallback extends ApiStatusCallback
{
    public void execute(ApiStatus status, int scene);
}
