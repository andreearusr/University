import React, { useContext, useEffect, useState } from 'react';
import {
  IonButton,
  IonButtons,
  IonContent,
  IonDatetime,
  IonHeader,
  IonInput,
  IonLabel,
  IonLoading,
  IonPage,
  IonTitle,
  IonToolbar
} from '@ionic/react';
import { MedContext } from './MedProvider';
import { RouteComponentProps } from 'react-router';
import { MedProps } from './MedProps';
import { labelStyle } from './styles';
//import { getLogger } from '..';

//const log = getLogger('ItemEdit');

interface MedEditProps extends RouteComponentProps<{
  id?: string;
}> { }

const ItemEdit: React.FC<MedEditProps> = ({ history, match }) => {
  const { meds, saving, savingError, saveMed } = useContext(MedContext);
  const [denumire, setDenumire] = useState('');
  const [substantaActiva, setSubstantaActiva] = useState('');
  const [gramaj, setGramaj] = useState(0);
  const [dataExpirarii, setDataExpirarii] = useState(new Date());
  const [medicament, setMedicament] = useState<MedProps>();
  useEffect(() => {
    //log('useEffect');
    const routeId = match.params.id || '';
    const medicament = meds?.find(it => it.id === routeId);
    setMedicament(medicament);
    if (medicament) {
      setDenumire(medicament.denumire);
      setSubstantaActiva(medicament.substantaActiva);
      setGramaj(medicament.gramaj);
      setDataExpirarii(medicament.dataExpirarii);
    }
  }, [match.params.id, meds]);
  const handleSave = () => {
    const editedMed = medicament ? { ...medicament, denumire, substantaActiva, gramaj, dataExpirarii }
      : { denumire, substantaActiva, gramaj, dataExpirarii };
    saveMed && saveMed(editedMed).then(() => history.goBack());
  };
 // log('render');
  return (
    <IonPage>
      <IonHeader>
        <IonToolbar class="toolbarClassName">
          <IonTitle>Edit</IonTitle>
          <IonButtons slot="end">
            <IonButton onClick={handleSave} class="buttonClassName">
              Save
            </IonButton>
          </IonButtons>
        </IonToolbar>
      </IonHeader>
      <IonContent class='contentClassName'>
        <IonLabel style={labelStyle}>--Denumire--</IonLabel>
        <IonInput value={denumire} onIonChange={e => setDenumire(e.detail.value || '')} />
        <IonLabel style={labelStyle}>--Substanta activa--</IonLabel>
        <IonInput value={substantaActiva} onIonChange={e => setSubstantaActiva(e.detail.value || '')} />
        <IonLabel style={labelStyle}>--Gramaj--</IonLabel>
        <IonInput value={gramaj} onIonChange={e => setGramaj(Number(e.detail.value) || 0)} />
        <IonLabel style={labelStyle}>--Data expirarii--</IonLabel>
        <IonDatetime value={String(dataExpirarii)} onIonChange={e => setDataExpirarii(new Date(e.detail.value + "") || new Date())} min={"2022"} max={"2042"} />
        <IonLoading isOpen={saving} />
        {savingError && (
          <div>{savingError.message || 'Failed to save medicament'}</div>
        )}
      </IonContent>
    </IonPage>
  );
};

export default ItemEdit;
