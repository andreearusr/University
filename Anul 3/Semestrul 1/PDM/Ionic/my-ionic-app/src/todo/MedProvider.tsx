import React, { useCallback, useEffect, useReducer } from 'react';
import PropTypes from 'prop-types';
//import { getLogger } from '../index';
import { MedProps } from './MedProps';
import { createMed, getMeds, newWebSocket, updateMed } from './medApi';

//const log = getLogger('ItemProvider');

type SaveMedFn = (medicament: MedProps) => Promise<any>;

export interface MedsState {
  meds?: MedProps[],
  fetching: boolean,
  fetchingError?: Error | null,
  saving: boolean,
  savingError?: Error | null,
  saveMed?: SaveMedFn,
}

interface ActionProps {
  type: string,
  payload?: any,
}

const initialState: MedsState = {
  fetching: false,
  saving: false,
};

const FETCH_ITEMS_STARTED = 'FETCH_ITEMS_STARTED';
const FETCH_ITEMS_SUCCEEDED = 'FETCH_ITEMS_SUCCEEDED';
const FETCH_ITEMS_FAILED = 'FETCH_ITEMS_FAILED';
const SAVE_ITEM_STARTED = 'SAVE_ITEM_STARTED';
const SAVE_ITEM_SUCCEEDED = 'SAVE_ITEM_SUCCEEDED';
const SAVE_ITEM_FAILED = 'SAVE_ITEM_FAILED';

const reducer: (state: MedsState, action: ActionProps) => MedsState =
  (state, { type, payload }) => {
    switch (type) {
      case FETCH_ITEMS_STARTED:
        return { ...state, fetching: true, fetchingError: null };
      case FETCH_ITEMS_SUCCEEDED:
        return { ...state, meds: payload.meds, fetching: false };
      case FETCH_ITEMS_FAILED:
        return { ...state, fetchingError: payload.error, fetching: false };
      case SAVE_ITEM_STARTED:
        return { ...state, savingError: null, saving: true };
      case SAVE_ITEM_SUCCEEDED:
        const meds = [...(state.meds || [])];
        const medicament = payload.medicament;
        const index = meds.findIndex(it => it.id === medicament.id);
        if (index === -1) {
          meds.splice(0, 0, medicament);
        } else {
          meds[index] = medicament;
        }
        return { ...state, meds, saving: false };
      case SAVE_ITEM_FAILED:
        return { ...state, savingError: payload.error, saving: false };
      default:
        return state;
    }
  };

export const MedContext = React.createContext<MedsState>(initialState);

interface MedProviderProps {
  children: PropTypes.ReactNodeLike,
}

export const MedProvider: React.FC<MedProviderProps> = ({ children }) => {
  const [state, dispatch] = useReducer(reducer, initialState);
  const { meds, fetching, fetchingError, saving, savingError } = state;
  useEffect(getMedsEffect, []);
  useEffect(wsEffect, []);
  const saveMed = useCallback<SaveMedFn>(saveItemCallback, []);
  const value = { meds, fetching, fetchingError, saving, savingError, saveMed };
  //log('returns');
  return (
    <MedContext.Provider value={value}>
      {children}
    </MedContext.Provider>
  );

  function getMedsEffect() {
    let canceled = false;
    fetchItems();
    return () => {
      canceled = true;
    }

    async function fetchItems() {
      try {
      //  log('fetchMeds started');
        dispatch({ type: FETCH_ITEMS_STARTED });
        const meds = await getMeds();
     //   log('fetchMeds succeeded');
        if (!canceled) {
          dispatch({ type: FETCH_ITEMS_SUCCEEDED, payload: { meds } });
        }
      } catch (error) {
      //  log('fetchMeds failed');
        dispatch({ type: FETCH_ITEMS_FAILED, payload: { error } });
      }
    }
  }

  async function saveItemCallback(medicament: MedProps) {
    try {
      //log('saveItem started');
      dispatch({ type: SAVE_ITEM_STARTED });
      const savedMed = await (medicament.id ? updateMed(medicament) : createMed(medicament));
    //  log('saveItem succeeded');
      dispatch({ type: SAVE_ITEM_SUCCEEDED, payload: { medicament: savedMed } });
    } catch (error) {
      //log('saveItem failed');
      dispatch({ type: SAVE_ITEM_FAILED, payload: { error } });
    }
  }

  function wsEffect() {
    let canceled = false;
  //  log('wsEffect - connecting');
    const closeWebSocket = newWebSocket(message => {
      if (canceled) {
        return;
      }
      const { event, payload: { medicament } } = message;
   //   log(`ws message, med ${event}`);
      if (event === 'created' || event === 'updated') {
        dispatch({ type: SAVE_ITEM_SUCCEEDED, payload: { medicament } });
      }
    });
    return () => {
    //  log('wsEffect - disconnecting');
      canceled = true;
      closeWebSocket();
    }
  }
};
