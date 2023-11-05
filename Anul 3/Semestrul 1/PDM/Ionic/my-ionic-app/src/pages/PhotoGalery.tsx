import {
    IonActionSheet,
    IonCol,
    IonContent,
    IonFab,
    IonFabButton,
    IonGrid,
    IonHeader,
    IonIcon,
    IonImg,
    IonPage,
    IonRow,
    IonTitle,
    IonToolbar
} from '@ionic/react';
import React, { useState } from 'react';
import { camera, close, exitOutline, trash } from 'ionicons/icons';
import { MyPhoto, usePhotos } from './usePhotos';
import { phonePortraitOutline } from "ionicons/icons";
import { RouteComponentProps } from 'react-router';

const PhotoGalery: React.FC<RouteComponentProps> = ({ history }) => {
    const { photos, takePhoto, deletePhoto } = usePhotos();
    const [photoToDelete, setPhotoToDelete] = useState<MyPhoto>();
    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Photo Galery</IonTitle>
                </IonToolbar>
                <IonFabButton onClick={() => history.goBack()}>
                    <IonIcon icon={exitOutline} />
                </IonFabButton>
            </IonHeader>
            <IonContent fullscreen>
                <IonHeader collapse="condense">
                    <IonToolbar>
                        <IonTitle size="large">Blank</IonTitle>
                    </IonToolbar>
                </IonHeader>
                <IonGrid>
                    <IonRow>
                        {photos.map((photo, index) => (
                            <IonCol size="6" key={index}>
                                <IonImg onClick={() => setPhotoToDelete(photo)}
                                    src={photo.webviewPath} />
                            </IonCol>
                        ))}
                    </IonRow>
                </IonGrid>
                <IonFab vertical="bottom" horizontal="center" slot="fixed">
                    <IonFabButton onClick={() => takePhoto()}>
                        <IonIcon icon={camera} />
                    </IonFabButton>
                </IonFab>
                <IonActionSheet
                    isOpen={!!photoToDelete}
                    buttons={[{
                        text: 'Delete',
                        role: 'destructive',
                        icon: trash,
                        handler: () => {
                            if (photoToDelete) {
                                deletePhoto(photoToDelete);
                                setPhotoToDelete(undefined);
                            }
                        }
                    }, {
                        text: 'Cancel',
                        icon: close,
                        role: 'cancel'
                    }]}
                    onDidDismiss={() => setPhotoToDelete(undefined)}
                />
            </IonContent>
        </IonPage>
    );
}

export default PhotoGalery;