import React, { useContext } from 'react';
import { RouteComponentProps } from 'react-router';
import {
  IonContent,
  IonFab,
  IonFabButton,
  IonHeader,
  IonIcon,
  IonList, IonLoading,
  IonPage,
  IonTitle,
  IonToolbar
} from '@ionic/react';
import { add, cameraOutline, locationOutline } from 'ionicons/icons';
import Medicament from './Medicament';
///import { getLogger } from '../index';
import { MedContext } from './MedProvider';

//const log = getLogger('MedsList');
import { useAppState } from '../state/useAppState';
import { useNetwork } from '../state/useNetwork';
import { useBackgroundTask } from '../state/useBackgroundTask';

const MedsList: React.FC<RouteComponentProps> = ({ history }) => {
  const { appState } = useAppState();
  const { networkStatus } = useNetwork();
  // useBackgroundTask(() => new Promise(resolve => {
  //   console.log('My Background Task');
  //   resolve();
  // }));

  const { meds, fetching, fetchingError } = useContext(MedContext);
  // log('render');
  return (
    <IonPage>
      <IonHeader>
        <IonToolbar class="toolbarClassName">
          <IonTitle>Medicamente</IonTitle>
        </IonToolbar>
      </IonHeader>
      <IonFab vertical="top" horizontal="end" slot="fixed">
        <IonFabButton onClick={() => history.push('/medicament')} size='small' class="addClassName">
          <IonIcon icon={add} />
        </IonFabButton>
      </IonFab>
      <IonContent class="contentClassName">
        <div>App state is {JSON.stringify(appState)}</div>
        <div>Network status is {JSON.stringify(networkStatus)}</div>

        <IonLoading isOpen={fetching} message="Fetching meds" />
        {meds && (
          <IonList>
            {meds.map(({ id, denumire, substantaActiva, gramaj, dataExpirarii }) =>
              <Medicament key={id} id={id} denumire={denumire} substantaActiva={substantaActiva}
                gramaj={gramaj} dataExpirarii={dataExpirarii}
                onEdit={id => history.push(`/medicament/${id}`)} />)}
          </IonList>
        )}
        {fetchingError && (
          <div>{fetchingError.message || 'Failed to fetch meds'}</div>
        )}
        <IonFabButton onClick={() => history.push('/photos')}>
          <IonIcon icon={cameraOutline} />
        </IonFabButton>
        <IonFabButton onClick={() => history.push('/location')}>
          <IonIcon icon={locationOutline} />
        </IonFabButton>
      </IonContent>
    </IonPage>
  );
};

export default MedsList;
