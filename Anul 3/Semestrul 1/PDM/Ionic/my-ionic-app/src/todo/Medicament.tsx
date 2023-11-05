import React from 'react';
import { IonItem, IonLabel } from '@ionic/react';
import { MedProps } from './MedProps';

interface MedPropsExt extends MedProps {
  onEdit: (id?: string) => void;
}

const Medicament: React.FC<MedPropsExt> = ({ id, denumire, substantaActiva, gramaj, dataExpirarii, onEdit }) => {
  return (
    <IonItem onClick={() => onEdit(id)} class="contentClassName">
      <IonLabel>{denumire} |  {substantaActiva} | {gramaj} | {dataExpirarii.toString().substring(0,10)}</IonLabel>
    </IonItem>
  );
};

export default Medicament;