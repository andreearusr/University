import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';
import * as serviceWorker from './serviceWorker';
import { defineCustomElements } from '@ionic/pwa-elements/loader';

defineCustomElements(window);

ReactDOM.render(<App />, document.getElementById('root'));

// export const getLogger: (tag: string) => (...args: any) => void =
//     tag => (...args) => console.log(tag, ...args);
    
// If you want your app to work offline and load faster, you can change
// unregister() to register() below. Note this comes with some pitfalls.
// Learn more about service workers: https://bit.ly/CRA-PWA
serviceWorker.unregister();