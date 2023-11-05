import React from 'react';
import { Redirect, Route } from 'react-router-dom';
import { IonApp, IonRouterOutlet } from '@ionic/react';
import { IonReactRouter } from '@ionic/react-router';

/* Core CSS required for Ionic components to work properly */
import '@ionic/react/css/core.css';

/* Basic CSS for apps built with Ionic */
import '@ionic/react/css/normalize.css';
import '@ionic/react/css/structure.css';
import '@ionic/react/css/typography.css';

/* Optional CSS utils that can be commented out */
import '@ionic/react/css/padding.css';
import '@ionic/react/css/float-elements.css';
import '@ionic/react/css/text-alignment.css';
import '@ionic/react/css/text-transformation.css';
import '@ionic/react/css/flex-utils.css';
import '@ionic/react/css/display.css';

/* Theme variables */
import './theme/variables.css';
import { MedProvider } from './todo/MedProvider';
import MedsList from './todo/MedsList';
import MedEdit from './todo/MedEdit';
import PhotoGalery from './pages/PhotoGalery';
import MyLocation from './pages/MyLocation';
import { AuthProvider, Login, PrivateRoute } from './auth';

export const getLogger: (tag: string) => (...args: any) => void =
  tag => (...args) => console.log(tag, ...args);

const App: React.FC = () => (
  <IonApp>
    <MedProvider>
      <IonReactRouter>
        <IonRouterOutlet>
          <AuthProvider>
            <Route path="/login" component={Login} exact={true} />
            <MedProvider>
              <PrivateRoute path="/medicamente" component={MedsList} exact={true} />
              <PrivateRoute path="/medicament" component={MedEdit} exact={true} />
              <PrivateRoute path="/medicament/:id" component={MedEdit} exact={true} />
              <PrivateRoute path="/photos" component={PhotoGalery} exact={true} />
              <PrivateRoute path="/location" component={MyLocation} exact={true} />
            </MedProvider>
            <Route exact path="/" render={() => <Redirect to="/medicamente" />} />
          </AuthProvider>
        </IonRouterOutlet>
      </IonReactRouter>
    </MedProvider>
  </IonApp>
);

export default App;
