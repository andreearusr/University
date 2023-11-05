import { IonContent, IonFabButton, IonHeader, IonIcon, IonPage, IonTitle, IonToolbar } from '@ionic/react';
import { exitOutline } from 'ionicons/icons';
import React from 'react';
import { RouteComponentProps } from 'react-router';
import MyMap from '../components/MyMap';
import { useMyLocation } from './useMyLocation';

const MyLocation:  React.FC<RouteComponentProps> = ({ history }) => {
    const myLocation = useMyLocation();
    const { latitude: lat, longitude: lng } = myLocation.position?.coords || {}

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Blank</IonTitle>
                    <IonFabButton onClick={() => history.goBack()}>
                        <IonIcon icon={exitOutline} />
                    </IonFabButton>
                </IonToolbar>
            </IonHeader>
            <IonContent fullscreen>
                <IonHeader collapse="condense">
                    <IonToolbar>
                        <IonTitle size="large">Blank</IonTitle>
                    </IonToolbar>
                </IonHeader>
                <div>My Location is</div>
                <div>latitude: {lat}</div>
                <div>longitude: {lng}</div>
                {lat && lng &&
                    <MyMap
                        lat={lat}
                        lng={lng}
                        onMapClick={log('onMap')}
                        onMarkerClick={log('onMarker')}
                    />}
            </IonContent>
        </IonPage>
    );

    function log(source: string) {
        return (e: any) => console.log(source, e);
    };
};

export default MyLocation;