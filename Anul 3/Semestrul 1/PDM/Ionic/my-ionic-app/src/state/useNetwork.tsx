import { useEffect, useState } from 'react';
// import { NetworkStatus, Plugins } from '@capacitor/core';

import { Network, NetworkStatus } from '@capacitor/network';

// const { Network } = Plugins;

const initialState = {
  connected: false,
  connectionType: 'unknown',
}

export const useNetwork = () => {
  const [networkStatus, setNetworkStatus] = useState(initialState);

  useEffect(() => {
  const handler = Network.addListener('networkStatusChange', handleNetworkStatusChange);
    Network.getStatus().then(handleNetworkStatusChange);
    let canceled = false;
    return () => {
      canceled = true;
      handler.remove();
    }

    function handleNetworkStatusChange(status: NetworkStatus) {
      console.log('useNetwork - status change', status);
      if (!canceled) {
        setNetworkStatus(status);
      }
    }
    
  }, []);

  return { networkStatus };
};
