import axios from 'axios';
import { baseUrl, config, withLogs } from '../core';
//import { getLogger } from '../index';
import { MedProps } from './MedProps';

//const log = getLogger('medApi');

const medUrl = `http://${baseUrl}/medicament`;

export const getMeds: () => Promise<MedProps[]> = () => {
  return withLogs(axios.get(medUrl, config), 'getMeds');
}

export const createMed: (item: MedProps) => Promise<MedProps[]> = medicament => {
  return withLogs(axios.post(medUrl, medicament, config), 'createMed');
}

export const updateMed: (item: MedProps) => Promise<MedProps[]> = medicament => {
  return withLogs(axios.put(`${medUrl}/${medicament.id}`, medicament, config), 'updateMed');
}

interface MessageData {
  event: string;
  payload: {
    medicament: MedProps;
  };
}

export const newWebSocket = (onMessage: (data: MessageData) => void) => {
  const ws = new WebSocket(`ws://${baseUrl}`)
  ws.onopen = () => {
   // log('web socket onopen');
  };
  ws.onclose = () => {
  //  log('web socket onclose');
  };
  ws.onerror = error => {
   // log('web socket onerror', error);
  };
  ws.onmessage = messageEvent => {
   // log('web socket onmessage');
    onMessage(JSON.parse(messageEvent.data));
  };
  return () => {
    ws.close();
  }
}
